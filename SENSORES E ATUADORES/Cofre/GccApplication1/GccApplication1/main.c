/*e
 * GccApplication1.c
 *
 * Created: 03/10/2018 17:36:24
 * Author : MarcoASMA
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include <util/delay.h>
#include <stdio.h>
#include "defs.h"

signed char encoderPoscount = 0;
int pinALast = 0;
int aVal = 0;
int aVal2 = 0;

int bCW= 0;


char contador_envia[4];

char senha[6] = {8,-2,8,7,17,0};
signed char posLida;
char validaSenha;
//8>>
//10<<
//11>>
//1<<
//11>>
//17<<
char lePosEncoder()
{
	if(PIND & (1<<DDD3)) { aVal = 1; } else { aVal  = 0; }
	
	//USART_Transmit(aVal+48);
	if(aVal != pinALast)
	{
		if(PIND & (1<<DDD4)) { aVal2 = 1; } else { aVal2  = 0; }
		if(aVal2 == aVal) { encoderPoscount++; bCW =1; }
		else { bCW = 0; encoderPoscount--; }
		
		USART_StrTx("- Rotacao: ");
		if(bCW){ USART_StrTx("Horario\r\n"); }
		else { USART_StrTx("anti-Horario\r\n"); }
		USART_StrTx("- Posicao do Encoder: ");
		sprintf(contador_envia, "%d", encoderPoscount);
		USART_StrTx(contador_envia);
		USART_StrTx("\r\n\r\n");
	}
	pinALast = aVal;
	return encoderPoscount;
}

int main(void)
{
	DDRD = 0x00;
	DDRB = 0xFF;
	PORTB = 0x00;
	
	
	USART_Init();
	
	if(PIND & (1<<DDD3)) { pinALast = 1; } else { pinALast = 0; }
	
	while(1)
	{
		posLida = lePosEncoder();
		if(validaSenha == 0 && posLida == 8) { _delay_ms(50); USART_StrTx("\r\n -Primeira SENHA OK"); validaSenha = 1;}
			if(validaSenha == 1 && posLida == -2) { _delay_ms(50); USART_StrTx("\r\n -Segunda SENHA OK"); validaSenha = 2;}
				 if(validaSenha == 2 && posLida == 8) { _delay_ms(50); USART_StrTx("\r\n -Terceira SENHA OK"); validaSenha = 3;}
					if(validaSenha == 3 && posLida == 7) { _delay_ms(50); USART_StrTx("\r\n -Quarta SENHA OK"); validaSenha = 4;}
						if(validaSenha == 4 && posLida == 17) { _delay_ms(50); USART_StrTx("\r\n -Quinta SENHA OK"); validaSenha = 5;}
							if(validaSenha ==5 && posLida == 0) { _delay_ms(50); USART_StrTx("\r\n -Sexta SENHA OK"); validaSenha = 6;}
	if(validaSenha == 6)
	{
		validaSenha = 0;
		for(int i=0;i<10;i++)
		{
		PORTB = 0xFF;  _delay_ms(100); PORTB = 0x00;  _delay_ms(100);	
		}
		
	} 
		
	}
}


