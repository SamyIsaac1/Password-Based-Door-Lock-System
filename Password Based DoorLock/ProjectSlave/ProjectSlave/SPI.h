

#ifndef SPI_H_
#define SPI_H_
#define DD_MOSI 5
#define DD_SCK 7
#define DD_MISO 6
#define DDR_SPI DDRB

void SPI_MasterInit(void);
char SPI_MasterReceive(void);
void SPI_MasterTransmit(char);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
void SPI_SlaveTransmit(char cData);

#endif /* SPI_H_ */