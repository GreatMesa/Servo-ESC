#include "TMP102.h"
#include "stm32f3xx_hal_i2c.h"
#include <stdint.h>


#define TMP102_ADDR         (0x48 << 1)
#define TMP102_TIMEOUT      100
#define TMP102_RESOLUTION   0.0625f     /* 12-bit: 0.0625°C per LSB */

uint8_t getTMPConfig()
{
    uint8_t config = 0;

    config |= (SHUTDOWN   & 0x1) << 0;   /* SD  bit 0 */
    config |= (THERMOSTAT & 0x1) << 1;   /* TM  bit 1 */
    config |= (POLARITY   & 0x1) << 2;   /* POL bit 2 */
    config |= (FAULT      & 0x3) << 3;   /* F1:F0 bits 4:3 */
    config |= 0x60;   /* R1:R0 bits 6:5 - normally read only */

    return config;
}

bool TMP102_Initialize(TMP102 *tmp102, I2C_HandleTypeDef *I2Chandle, GPIO_TypeDef *interrupt)
{
    tmp102->I2Chandle = I2Chandle;
    tmp102->raw_temp  = 0;
    tmp102->tempature = 0.0f;
    tmp102->high      = false;
    tmp102->low       = false;

    uint8_t txBuf[3];

    /* Set register pointer to config register and write config */
    txBuf[0] = TMP_CONFIG_REGISTER;
    txBuf[1] = getTMPConfig() | 0x60;    /* OR in the read-only R1:R0 = 11 bits */
    txBuf[2] = 0x80;                     /* CR1:CR0 = 10 -> 4Hz conversion rate  */

    tmp102->hal = HAL_I2C_Master_Transmit(
        tmp102->I2Chandle,
        TMP102_ADDR,
        txBuf,
        3,
        TMP102_TIMEOUT
    );

    if (tmp102->hal != HAL_OK)
    {
        return false;
    }

    /* Point register pointer back to temperature register for subsequent reads */
    txBuf[0] = TEMPATURE_REGISTER;

    tmp102->hal = HAL_I2C_Master_Transmit(
        tmp102->I2Chandle,
        TMP102_ADDR,
        txBuf,
        1,
        TMP102_TIMEOUT
    );

    return (tmp102->hal == HAL_OK);
}

void readTempature(TMP102 *tmp102)
{
    uint8_t rxBuf[2];

    tmp102->hal = HAL_I2C_Master_Receive(
        tmp102->I2Chandle,
        TMP102_ADDR,
        rxBuf,
        2,
        TMP102_TIMEOUT
    );

    if (tmp102->hal != HAL_OK)
    {
        return;
    }

    /* 
     * Temperature register format (12-bit normal mode):
     * Byte 1: MSB [D11:D4]
     * Byte 2: LSB [D3:D0, 0, 0, AL, EM]  <- lower 4 bits are flags, not temp
     *
     * Combine and shift down 4 to get the 12-bit signed value
     */
    tmp102->raw_temp = (int16_t)((rxBuf[0] << 8) | rxBuf[1]) >> 4;

    /* Update alert flags from the LSB byte */
    tmp102->high = (rxBuf[1] & 0x02) ? true : false;   /* AL bit */
    tmp102->low  = (rxBuf[1] & 0x01) ? true : false;   /* EM bit - repurposed as low flag if wired */

    tmp102->tempature = (float)tmp102->raw_temp * 0.0625f;
}