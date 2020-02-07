#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include "PWM.h"
#include "I2C.h"
#include "ExtEPROM.h"
#include "Timer.h"

typedef unsigned char uint8;
#define SevenSeg_DDR DDRA
#define SevenSeg_PORT PORTA
#define _equal

void INT2_Start();
void INT1_Start();
void SetTimeCW_ACW(uint8 timeCW,uint8 timeACW);
uint8 SPI_IntReceive[20];
uint8 UART_IntReceive[20];
uint8 volatile UART_count=0,SPI_count=0,countCW=0,countACW=0;
uint8 arr[20];
long unsigned int static StaticNotInitNotUsed;
long unsigned int NotUsed = 4;
long unsigned int const ConstNotUsed = 9;


int main()
{
	Motor_Speed=MAX;
	uint8 counter=0;
	uint8 eeData,wrong=0;
	unsigned int addr=0x001;
	uint8 *Admin="Hello, Welcome to Admin Control Room\n\r\0";
	uint8 *EnterPass="Please Enter Password:\0";
	uint8 *WrongPass="\n\rWrong Password Try Again:\0";
	uint8 *PassAccept="\n\rPassword Accepted\n\r\0";
	uint8 count=0;
	uint8 pass=0;
	
	I2C_Init();
	SPI_SlaveInit();
	SevenSeg_DDR=0xFF;
	PWM_Init();
	UART_Init();
	Timer2_Init();
	setbit(DDRD,6);
	clrbit(PORTD,6);
	setbit(DDRD,5);
	clrbit(PORTD,5);
	sei();
	
	ExtEPROM_Write(0x001,50);
	_delay_ms(20);
	ExtEPROM_Write(0x002,49);
	_delay_ms(20);
	ExtEPROM_Write(0x003,49);
	_delay_ms(20);
	ExtEPROM_Write(0x004,50);
	_delay_ms(20);
	ExtEPROM_Write(0x005,49);
	_delay_ms(20);
	ExtEPROM_Write(0x006,49);
	_delay_ms(20);
	ExtEPROM_Write(0x007,49);
	_delay_ms(20);
	ExtEPROM_Write(0x008,49);
	_delay_ms(20);
	
	for(count=0;count<9;count++)
	{
		ExtEPROM_Read(addr,&eeData);
		arr[count]=eeData;
		addr++;
	}
	for(count=0;Admin[count]!='\0';count++)
	UART_Transmit(Admin[count]);
	for(count=0;EnterPass[count]!='\0';count++)
	UART_Transmit(EnterPass[count]);
	
	while(1)
	{
		if(UART_count==4)
		{
			UART_count=0;
			for(counter=0;counter<4;counter++)
			{
				if(UART_IntReceive[counter]==arr[counter])
				{
					pass++;
				}
				else
				{
					for(count=0;WrongPass[count]!='\0';count++)
					UART_Transmit(WrongPass[count]);
					break;
				}
			}
		}
		if(SPI_count==4)
		{
			SPI_count=0;
			for(counter=0;counter<4;counter++)
			{
				if((uint8)SPI_IntReceive[counter]==(uint8)(arr[counter+4]-48))
				pass++;
				else
				{
					for(count=0;WrongPass[count]!='\0';count++)
					UART_Transmit(WrongPass[count]);
					INT1_Start();
					break;
				}
			}
		}
		if(pass == 4)
		{
			for(count=0;PassAccept[count]!='\0';count++)
			UART_Transmit(PassAccept[count]);
			Motor_CW();
			SetTimeCW_ACW(60,60);
			INT2_Start();
		}
		pass=0;
	}
}
ISR(SPI_STC_vect)
{
	SPI_IntReceive[SPI_count]=SPI_SlaveReceive();
	SPI_IntReceive[SPI_count]=SPI_IntReceive[SPI_count]&(0x0F); //Fi Hasshassa fil MSB fi awel reading lel Value bass
	SevenSeg_PORT=SPI_IntReceive[SPI_count];
	SPI_count++;
}
ISR(USART_RXC_vect)
{
	UART_IntReceive[UART_count]=UART_Receive();
	UART_count++;
}
ISR(TIMER2_OVF_vect)
{
	if((TIFR&(1<<TOV2))!=0)
	{
		TIFR=(1<<TOV2);
		if(countCW > 0)
		countCW--;
		else if(countACW > 0)
		{
			if(countCW == 0)
			{
				Motor_AntiCW();
				countACW--;
			}
			if(countACW == 1)
			{
				Motor_Stop();
				countACW--;
			}
		}
	}
}
void SetTimeCW_ACW(uint8 timeCW,uint8 timeACW)
{
	countCW=timeCW;
	countACW=timeACW;
}
void INT2_Start()
{
	setbit(PORTD,6);
	_delay_ms(50);
	clrbit(PORTD,6);
}
void INT1_Start()
{
	setbit(PORTD,5);
	_delay_ms(50);
	clrbit(PORTD,5);
}