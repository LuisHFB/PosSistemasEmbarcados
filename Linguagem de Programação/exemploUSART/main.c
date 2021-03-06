/*
 * exemploUSART.c
 *
 * Created: 22/09/2018 09:25:37
 * Author : M3LLOD
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "adc.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
//#define F_CPU 16000000UL


ISR(USART_RX_vect) //#Interrupt.h
{
	char res;
	res = USART_Receive();
	USART_Transmit(res);
}

int main(void)
{
	int valor;
	char buffer[6]; //65535 + '\+0'
	
	
	USART_Init();
	USART_StrTx("HELLO");
	USART_rxIE();
	
	adc_init();
	
    while (1) 
    {
		//USART_rxIE();
		 valor = adc_read(0);
		 sprintf(buffer, "%d", valor); //stdio.h
		_delay_ms(100);
		
		//##IMPEDIR COCORRENCIA NO USO DO BUFFER   ESCRITA/LEITURA;  <<<<  REINTRANCIA
		cli(); //Desabilita Interrupçoes
		USART_StrTx(buffer);
		sei(); //Habilita Interrupcoes
		
		
		USART_StrTx("\r\n");
    }
}

