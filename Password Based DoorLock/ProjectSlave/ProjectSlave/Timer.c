#include <avr/io.h>

typedef unsigned char uint8;
void Timer2_Init()
{
	//Normal mode ,set OC2 on compare match , clk/1024
	TCCR2=(1<<COM21)|(1<<COM20)|(1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK=(1<<TOIE2); //Overflow  interrupt Enable
} 

