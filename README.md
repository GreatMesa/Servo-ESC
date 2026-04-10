# Servo-ESC
Custom 4-Layer Board for better servo control.
Mainly uses I2C for IC communication & the analog pheripherials on the STM32F301
## Overview
This project stems from the want to replace the boards that normally control position on commercial servos.

The reason why I wanted to replace them is because 1, you can only control the position of the servo motors and not the velocity, let alone the torque. Also, you cannot get any useful feedback back from the servos, which means that you cannot get the current or temperature of the board, which could be useful for looking at possible faults / seeing the current overall power consumption.

With these Servo ESC's, you can communicate to the board using I2C, which allows to send the wanted position, velocity, and torque, while also communicating back the current position, velocity, torque, power consumption, and board temperature. This allows for a much higher view into what is happening in the board while also giving the servo greater precision.

## Board Schematic
<img width="1541" height="1160" alt="Screenshot 2026-04-10 005249" src="https://github.com/user-attachments/assets/03f1024e-469b-4bfd-a997-f056aa560edb" />

## PCB Layout
<img width="2083" height="1016" alt="Screenshot 2026-01-02 130759" src="https://github.com/user-attachments/assets/65330889-7cdb-4b2b-97b0-8231ca28c1e2" />

## 3D Model
<img width="1077" height="554" alt="Screenshot 2026-01-01 115603" src="https://github.com/user-attachments/assets/247c3d3a-18f9-4961-b0b1-2e3bfa306048" />

