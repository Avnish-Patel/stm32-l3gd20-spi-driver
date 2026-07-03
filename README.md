# STM32 L3GD20 SPI Driver

A reusable SPI driver for the onboard **L3GD20 three-axis gyroscope** available on the **STM32F429I-DISC1 Discovery Board**. 
The driver is developed using STM32 HAL and demonstrates SPI register communication, burst data acquisition, and sensor configuration.

---

## Features

- SPI register read and write
- Multi-byte (burst) register read using auto-increment
- Read 3-axis angular velocity (X, Y, Z)
- Read onboard temperature register
- High-Pass Filter (HPF) enable/disable
- HPF configuration
- Modular driver (`l3gd20.c` / `l3gd20.h`)
- Easy integration into other STM32 projects

---

## Hardware Used

- STM32F429I-DISC1 Discovery Board
- Onboard L3GD20 3-axis gyroscope
- STM32CubeIDE
- STM32 HAL Library
- USART1 for serial debugging

---

## SPI Configuration

| Parameter | Value |
|-----------|-------|
| Mode | Master |
| Direction | Full Duplex |
| Data Size | 8-bit |
| Clock Polarity | High |
| Clock Phase | 2nd Edge |
| NSS | Software |
| Baud Rate Prescaler | 16 |
| Bit Order | MSB First |

---

## Driver Architecture

```
Application
      │
      ▼
l3gd20.h
      │
      ▼
l3gd20.c
      │
      ▼
STM32 HAL SPI
      │
      ▼
L3GD20 Gyroscope

---

## Sample Output

```
X=   18    Y=   82    Z=  603
X=   23    Y=   79    Z=  598
X=   15    Y=   88    Z=  610
```

---

## Project Structure

```
Core/
Drivers/
│
├── Inc/
│      l3gd20.h
│
├── Src/
│      l3gd20.c
│
└── main.c
```

---

## Concepts Demonstrated

- SPI Full-Duplex Communication
- Register-Level Sensor Interface
- Burst Data Acquisition
- Auto-Increment Addressing
- Embedded Driver Development
- Modular Firmware Design
- STM32 HAL Peripheral Programming

---

