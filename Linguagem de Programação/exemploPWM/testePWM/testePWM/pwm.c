#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#define F_CPU 16000000UL

void PwmD6AInit(void)
{
	DDRD |= (1 << DDD6);
	TCCR0A |= (1<<COM0A1) | (1 << WGM01) | (1 << WGM00);				// Fast PWM 8 bits, modo 5, non-inverting mode.
	TCCR0B |= (1<<CS01);					// Prescaler = 1. Fpwm = 8M/(256xPrescaler)=31,25Khz
}

void PwmD6ASetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR0A = ((int)Duty*255)/100;
}