


#ifndef KEYPAD_H_
#define KEYPAD_H_
#define DDR_keypad DDRA
#define PORT_keypad PORTA
#define PIN_keypad PINA
#define setbit(reg,pos) reg|=1<<pos
#define clrbit(reg,pos) reg&=~(1<<pos)
#define togglebit(reg,pos) reg^=1<<pos

char keypad_scan(void);
void keypad_Init(void);




#endif /* KEYPAD_H_ */