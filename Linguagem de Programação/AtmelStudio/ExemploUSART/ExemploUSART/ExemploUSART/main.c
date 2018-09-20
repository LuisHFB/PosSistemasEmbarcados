#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#include "usart.h"

int main(void)
{
	//DDRB = 0x10;
	DDRB = 0b00100000;
	//DDRC = 0xFF;
	USART_Init();
	while(1) //loop forever
	{
		PORTB ^= 0b00100000;  //toggle port B
		//PORTB ^= 0x10;  //toggle port B
		_delay_ms(100); //wait 1 second
		USART_StrTx("Hello World\n");
		
	}
}
