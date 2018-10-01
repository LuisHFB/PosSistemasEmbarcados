/*
 * SonarMOTORpasso.c
 *
 * Created: 29/09/2018 13:34:49
 * Author : M3LLOD
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x0F;
	
	PORTB = 0x01;
    while (1) 
    {
		//(PORTB == 0x08) ? (PORTB = 0x01) : (PORTB = PORTB<<1);
		//(PORTB == )
		if(PORTB == 0x08) PORTB = 0x01;
		else if(PORTB%2) PORTB = PORTB << 1;
		_delay_ms(200);
    }
}

