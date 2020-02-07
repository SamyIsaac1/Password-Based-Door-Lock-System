#include <avr/io.h>
#include "SPI.h"
void SPI_SlaveInit(void)
{
	DDR_SPI = (1<<DD_MISO);   //   MISO pin is output
	SPCR = (1<<SPE);		 // SPI Enable 
}
char SPI_SlaveReceive(void)
{	
	while(!(SPSR & (1<<SPIF)))
	;								// wait until Interrupt flag is set indicating that the received is complete
	return SPDR;					// return the received data
}
void SPI_SlaveTransmit(char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)))
	;
}
char SPI_MasterReceive(void)
{
	while(!(SPSR & (1<<SPIF)))
	;
	return SPDR;
}
void SPI_MasterTransmit(char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)))
	;
}
void SPI_MasterInit(void)
{
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);      // MOSI and SCK pins are output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	// Enable SPI ,Master mode, Fosc/16
}