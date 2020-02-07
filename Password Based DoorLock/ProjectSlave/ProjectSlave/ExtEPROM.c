#include <avr/io.h>
#include "I2C.h"

char ExtEPROM_Write(unsigned int addr,unsigned char data)
{
	// Sequence start, Write mode ,slave address ,send data, stop condition
	I2C_StartBit();
	if(I2C_GetStatus() != 0x08)  // ERROR
	return 1;
	I2C_Write(0b10100000);       //0xA0 for writing
	if(I2C_GetStatus() != 0x18)  // ERROR
	return 2;
	I2C_Write((unsigned char)(addr));
	if(I2C_GetStatus() != 0x28)  // ERROR
	return 3;
	I2C_Write(data);
	if(I2C_GetStatus() != 0x28)  // ERROR
	return 4;
	I2C_StopBit();
	return 5;				     // SUCCESS
	
}

char ExtEPROM_Read(unsigned int addr,unsigned char *data)
{
	// Sequence start, Write mode A0,Send address ,start again,reading mode A1
	//NACK for Ending the read process ,Stop bit to end the comm.
	I2C_StartBit();
	if(I2C_GetStatus() != 0x08)
		return 1;
	I2C_Write(0b10100000);
	if(I2C_GetStatus() != 0x18)
		return 2;
	I2C_Write((unsigned char)(addr));
	if(I2C_GetStatus() != 0x28)
	return 3;
	I2C_StartBit();
	if(I2C_GetStatus() != 0x10)
	return 4;
	I2C_Write(0b10100001);		//0xA1 for reading 
	if(I2C_GetStatus() != 0x40)
	return 5;
	*data=I2C_ReadNack();
	if(I2C_GetStatus() != 0x58)
	return 6;
	I2C_StopBit();
	return 7;
}