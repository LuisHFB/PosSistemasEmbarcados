#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
//#define F_CPU 16000000UL

void PwmD06Init(void)
{
	//DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	TCCR0A |= (1<<COM0A1) | (1 << WGM01) | (1 << WGM00);				// Fast PWM 8 bits, modo 5, non-inverting mode.
	TCCR0B |= (1<<CS01);					// Prescaler = 1. Fpwm = 8M/(256xPrescaler)=31,25Khz
}

void PwmD06SetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR0A = ((int)Duty*255)/100;
	OCR0B = ((int)Duty*255)/100;
}

void PwmD05Init(void)
{
	DDRD |= (1 << DDD5);
	TCCR0A |= (1<<COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1<<CS01);
}

void PwmD05SetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR0B = ((int)Duty*255)/100;
}

void PwmD09Init(void)
{
	DDRB |= (1 << DDB1);
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) |  (1 << WGM10);
	TCCR1B |= (1<<CS11) | (1 << WGM12);
}

void PwmD09SetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR1A = ((int)Duty*255)/100;
}

void PwmD10Init(void)
{
	DDRB |= (1 << DDB2);
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) |  (1 << WGM10);
	TCCR1B |= (1<<CS11) | (1 << WGM12);
}

void PwmD10SetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR1B = ((int)Duty*255)/100;
}

void PwmD03Init(void)
{
	DDRD |= (1 << DDD3);
	TCCR2A |= (1<<COM2B1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1<<CS21);
}

void PwmD03SetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR2B = ((int)Duty*255)/100;
}

void PwmD11Init(void)
{
	DDRB |= (1 << DDB3);
	TCCR2A |= (1<<COM2A1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1<<CS21);
}

void PwmD11SetDuty(unsigned int Duty)			// Usa esta função quando quer ajuste de 0 100%
{
	OCR2A = ((int)Duty*255)/100;
}