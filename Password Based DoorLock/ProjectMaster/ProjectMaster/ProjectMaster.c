#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "SPI.h"
#include "Keypad.h"

#define _equal
#define True 3
typedef unsigned char uint8;
uint8 Reject_Int1=0;
uint8 Accept_Int2=0;
uint8 Notinitialized;
volatile uint8 Reject_count=0;
uint8 NotUsed= 4;
void ExtInt_Init();

main()
{
	sei();
	keypad_Init();
	LCD_init();
	SPI_MasterInit();
	ExtInt_Init();
	
	uint8 count1=6;
	uint8 key_pressed='0',i,state=1,Error_try=0;
	uint8 key[4];
	uint8 counter=0,count=0;
	
	uint8 *EnterPass="Please Enter Password:\0";
	uint8 *WrongPass="\n\rWrong Password Try Again:\0";
	uint8 *PassAccept="\n\rPassword Accepted\n\r\0";
	LCD_gotoxy(1,5);
	LCD_sendStrAnimated("Hello Samy \0");
	_delay_ms(500);
	LCD_clr();
	for(count=0;EnterPass[count]!='\0';count++)
	LCD_sendData(EnterPass[count]);
	Reject_Int1=0;
	Reject_count=0;
	while(1)
	{
		if(Reject_Int1 == True)
		{
			LCD_clr();
			LCD_gotoxy(1,12);
			LCD_sendStrAnimated("REJECTED\0");
			Reject_Int1=0;
			Reject_count++;
			if(Reject_count==3)
			{
				LCD_clr();
				LCD_gotoxy(0,5);
				LCD_sendStrAnimated("Too many Wrong Password\0");
				LCD_gotoxy(1,6);
				LCD_sendStrAnimated("Please Contact Admin\0");
			}
			while(Reject_count==3);
		}
		
		if(Accept_Int2 == True)
		{
			LCD_clr();
			LCD_gotoxy(1,12);
			LCD_sendStrAnimated("ACCEPTED\0");
			Accept_Int2=0;
		}
		key_pressed=keypad_scan();
		if(key_pressed!=0)
		{
			key[count]=key_pressed;
			if(key_pressed == 'C')
			{
				LCD_clr();
				LCD_gotoxy(1,12);
				LCD_sendStr("Start Over\0");
			}
			else
			{
				if(counter == 4)
				counter = 0;
				if(counter == 0)
				LCD_clr();
				counter++;
				LCD_sendData(key_pressed);
				key_pressed-=48;
				SPI_MasterTransmit(2*key_pressed);
			}
		}
	}
}
void ExtInt_Init()
{
	GICR=(1<<INT2)|(1<<INT0);
	MCUCR=(1<<ISC01);
}
ISR(INT2_vect)
{
	Accept_Int2 = True;
	Reject_count = 0;
}
ISR(INT0_vect)
{
	Reject_Int1 = True;
}
