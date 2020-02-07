

#ifndef UART_H_
#define UART_H_

void UART_Init();
void UART_Transmit(unsigned char UART_data);
unsigned char UART_Receive();

#endif /* UART_H_ */