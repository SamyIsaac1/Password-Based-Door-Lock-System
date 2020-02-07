

#ifndef EXTEPROM_H_
#define EXTEPROM_H_

char ExtEPROM_Write(unsigned int addr,unsigned char data);
char ExtEPROM_Read(unsigned int addr,unsigned char *data);

#endif /* EXTEPROM_H_ */