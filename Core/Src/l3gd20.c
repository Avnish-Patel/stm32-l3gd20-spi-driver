/*
 * l3gd20.c
 *
 *  Created on: Jun 29, 2026
 *      Author: dev
 */
#include "l3gd20.h"
#include "stdint.h"


extern SPI_HandleTypeDef hspi5;

static uint8_t L3GD20_SPI_Transfer(uint8_t txData){

	uint8_t rxData;

	HAL_SPI_TransmitReceive(&hspi5, &txData, &rxData, 1, HAL_MAX_DELAY);

	return rxData;
}

uint8_t L3GD20_ReadReg(uint8_t reg){

	uint8_t value;
	//uint8_t dummy;

	L3GD20_CS_LOW();
	// sending register address with read byte
	L3GD20_SPI_Transfer(reg|L3GD20_READ);
	// send dummy byte to receive the required data (dummy sent to share clock to shift data)
	value=L3GD20_SPI_Transfer(0x00);

	L3GD20_CS_HIGH();
	//printf("Dummy = %02X  Value = %02X\r\n", dummy, value);

	return value;
}

void L3GD20_WriteReg(uint8_t reg,uint8_t value){

	L3GD20_CS_LOW();
	L3GD20_SPI_Transfer(reg);    // 7th bit is 0 for write
	L3GD20_SPI_Transfer(value);
	L3GD20_CS_HIGH();
}

void L3GD20_Init(void){
	/* enable x,y,z axis
	 * power on
	 * output data rate 95 Hz
	 * cutoff=12.5 Hz
	 */
	L3GD20_WriteReg(L3GD20_CTRL_REG1,0x0F);

	/* Full scale = 250dps*/

	L3GD20_WriteReg(L3GD20_CTRL_REG4, 0x00|0x80);
}

void L3GD20_Multi_Read(uint8_t reg, uint8_t *data, uint8_t length){
	uint8_t len_read=length+1;
	uint8_t tx[len_read];
	uint8_t rx[len_read];

	tx[0]=reg|L3GD20_READ|L3GD20_AUTO_INCREMENT;
	for (uint8_t i = 1; i < len_read; i++) {
          tx[i]=0x00;
	}
	L3GD20_CS_LOW();
	HAL_SPI_TransmitReceive(&hspi5, tx, rx, len_read, HAL_MAX_DELAY);
	L3GD20_CS_HIGH();
	for (uint8_t i=1; i < len_read; i++) {
	          data[i-1]=rx[i];
		}
}

void L3GD20_ReadXYZ(L3GD20_Data_t *gyro){
   uint8_t buffer[6];

   L3GD20_Multi_Read(L3GD20_OUT_X_L, buffer, 6);

   gyro->x=(int16_t)((buffer[1]<<8)|buffer[0]);
   gyro->y=(int16_t)((buffer[3]<<8)|buffer[2]);
   gyro->z=(int16_t)((buffer[5]<<8)|buffer[4]);
}

int8_t L3GD20_GetTemperature(void){
	int8_t temp;
	temp=(int8_t)(L3GD20_ReadReg(L3GD20_TEMP_REG));

	return temp;
}
void L3GD20_EnableHPF(void){
	uint8_t reg;

	reg = L3GD20_ReadReg(L3GD20_CTRL_REG5);

	reg |= (1<<4);

	L3GD20_WriteReg(L3GD20_CTRL_REG5, reg);
}

void L3GD20_DisableHPF(void){
	uint8_t reg;

	reg = L3GD20_ReadReg(L3GD20_CTRL_REG5);

	reg &= ~(1<<4);

	L3GD20_WriteReg(L3GD20_CTRL_REG5, reg);
}

void L3GD20_SetHPF(uint8_t value)
{
    L3GD20_WriteReg(L3GD20_CTRL_REG2, value);
}
