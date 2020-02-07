

#ifndef I2C_H_
#define I2C_H_

void I2C_Init();
void I2C_StartBit();
void I2C_StopBit();
unsigned char I2C_GetStatus();
void I2C_Write(unsigned char);

unsigned char I2C_ReadACK();
unsigned char I2C_ReadNack();

#endif /* I2C_H_ */