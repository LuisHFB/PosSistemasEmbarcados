//#include <stdio.h>
#include <avr/io.h>

void Pwm1AInit(void)
{
	TCCR1A |= (1<<COM1A1)|(1<<WGM10);				// Fast PWM 8 bits, modo 5, non-inverting mode.
	TCCR1B |= (1<<WGM12)|(1<<CS10);					// Prescaler = 1. Fpwm = 8M/(256xPrescaler)=31,25Khz
}

void Pwm1ASetDuty(unsigned short int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR1A = ((float)Duty/100)*255;
}