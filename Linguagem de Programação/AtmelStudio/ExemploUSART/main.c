#define F_CPU 16000000UL //definição da frequência de clock para uso da biblioteca delay
#include <avr/io.h>	     //biblioteca para acesso aos registradores do uC
#include "util/delay.h"	    //biblioteca para funções de delay

int main(void)			 //função principal
{
	DDRB = 0b00100000;	 //configura pino PB5 como saída e demais como entradas
	
	while(1)			 //loop principal
	{
		PORTB^=(1<<PB5); //inverte estado do pino PB5
		_delay_ms(100); //aguarda 1 seg
	}
}
