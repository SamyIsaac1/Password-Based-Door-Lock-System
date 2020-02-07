#include <avr/io.h>
#include "Keypad.h"

void keypad_Init(void)
{
	DDR_keypad=0x0F;
	PORT_keypad=0xFF;
}

char keypad_scan(void)
{
	char row,key1;
	for(row=0;row<4;row++)
	{
		PORT_keypad=0xFF;
		clrbit(PORT_keypad,row);
		key1=PIN_keypad&0xF0;
		if(key1!=0xF0)
		{
			while((PIN_keypad&0xF0)!=0xF0);
			break;
		}
	}
	if(row==4)
	return 0;
	switch(row)
	{
		case 0: switch(key1)
		{
			case 0x70: return '/';
			case 0xB0: return '9';
			case 0xD0: return '8';
			case 0xE0: return '7';
		}
		case 1: switch(key1)
		{
			case 0x70: return '*';
			case 0xB0: return '6';
			case 0xD0: return '5';
			case 0xE0: return '4';
		}
		case 2: switch(key1)
		{
			case 0x70: return '-';
			case 0xB0: return '3';
			case 0xD0: return '2';
			case 0xE0: return '1';
		}
		case 3: switch(key1)
		{
			case 0x70: return '+';
			case 0xB0: return '=';
			case 0xD0: return '0';
			case 0xE0: return 'C';
		}
	}
	return 0;
}
