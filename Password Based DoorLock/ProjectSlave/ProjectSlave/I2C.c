#include <avr/io.h>


void I2C_Init()
{
	TWCR=(1<<TWEN);  //Enable TWI
	TWSR=0x00;
	TWBR=0x01;
}
void I2C_StartBit()
{
	//Enable TWI ,Start Condition 
	TWCR=(1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while((TWCR&(1<<TWINT))==0);   //the interrupt flag is set  when a job is finished
}
void I2C_StopBit()
{
	TWCR=(1<<TWEN)|(1<<TWSTO)|(1<<TWINT);   //Enable TWI ,STOP Condition
}
unsigned char I2C_GetStatus()
{
	return (TWSR&0xF8);   // the first three bits are reserved ,So we wanna read the other bits
}
void I2C_Write(unsigned char data)
{
	TWDR=data;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while((TWCR&(1<<TWINT))==0);
}
unsigned char I2C_ReadACK()
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while((TWCR&(1<<TWINT))==0);
	return TWDR;
}
unsigned char I2C_ReadNack()
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	while((TWCR&(1<<TWINT))==0);
	return TWDR;
}
