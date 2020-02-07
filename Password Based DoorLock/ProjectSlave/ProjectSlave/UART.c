#include <avr/io.h>

void UART_Init()
{
	UBRRL=0b00110011;                       //UBRRL = 51 For 1 MHz Crystal and 1200 baud rate
	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);   // Enable RX and TX and RX complete interrupt
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); // Character size 8 bits
	
}
void UART_Transmit(unsigned char UART_data)
{
	while((UCSRA&(1<<UDRE))==0);   // Check if the UDR is empty
	UDR=UART_data;
}
unsigned char UART_Receive()
{
	while((UCSRA&(1<<RXC))==0);  // check data is received
	return UDR;
}