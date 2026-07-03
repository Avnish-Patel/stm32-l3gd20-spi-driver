/*
 * l3gd20.h
 *
 *  Created on: Jun 29, 2026
 *      Author: dev
 */

#ifndef _L3GD20_H
#define _L3GD20_H

#include "main.h"

/* Register addresses */

#define L3GD20_WHO_AM_I 0x0F
#define L3GD20_CTRL_REG1 0x20
#define L3GD20_CTRL_REG2 0x21
#define L3GD20_CTRL_REG3 0x22
#define L3GD20_CTRL_REG4 0x23
#define L3GD20_CTRL_REG5 0x24

#define L3GD20_OUT_X_L 0x28
#define L3GD20_OUT_X_H 0x29
#define L3GD20_OUT_Y_L 0x2A
#define L3GD20_OUT_Y_H 0x2B
#define L3GD20_OUT_Z_L 0x2C
#define L3GD20_OUT_Z_H 0x2D


/* SPI command bits */

#define L3GD20_READ 0x80
#define L3GD20_AUTO_INCREMENT 0x40
#define L3GD20_STATUS_REG  0x27
#define L3GD20_TEMP_REG 0x26


#define L3GD20_CS_LOW()\
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET)
#define L3GD20_CS_HIGH()\
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET)

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
}L3GD20_Data_t;


//    uint8_t L3GD20_SPI_Transfer(uint8_t txData);  // the function in made static in .c file

uint8_t L3GD20_ReadReg(uint8_t reg);
void L3GD20_WriteReg(uint8_t reg,uint8_t value);
void L3GD20_Init(void);
void L3GD20_Multi_Read(uint8_t reg, uint8_t *data, uint8_t length);
void L3GD20_ReadXYZ(L3GD20_Data_t *gyro);
void L3GD20_EnableHPF(void);
void L3GD20_DisableHPF(void);
int8_t L3GD20_GetTemperature(void);
void L3GD20_SetHPF(uint8_t value);

#endif /* INC_L3GD20_H_ */
