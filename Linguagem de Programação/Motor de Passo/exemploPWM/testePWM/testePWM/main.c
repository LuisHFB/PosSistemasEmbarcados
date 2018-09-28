/*
 * testePWM.c
 *
 * Created: 26/09/2018 15:18:24
 * Author : MarcoASMA
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "pwm.h"

int i =0;
int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x01;
    /* Replace with your application code */
	PwmD6AInit();
    while (1) 
    {
		
		PwmD6ASetDuty(i);
		_delay_ms(2);
		i++;
		if(i>255) i=0;
		(PORTB == 0x08) ? (PORTB = 0x01) : (PORTB = PORTB<<1);
    }
}

