#define F_CPU 16000000UL	// Define a frequência do microcontrolador
#include <avr/io.h>		// Biblioteca para o uso dos IOs do MCU
#include <util/delay.h>		// Biblioteca para o uso das rotinas de delay

void ConfigMCU()
{
	DDRB = 0XFF;           //Configura todos os pinos do PORTB como saída 
	PORTB = 0;             //Todo o PORTB terá nível lógico zero.
}

int main(void)
{
    ConfigMCU(); 
    while (1) 
    {
		 PORTB ^= 0xFF;   //Toggle, ou seja, inverte dos os pinos do PORTB;
		 _delay_ms(300);  //Delay de 300ms  	  
    }
}



