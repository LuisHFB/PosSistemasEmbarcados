/*
 * ControlLEDviaSerial.c
 *
 * Created: 25/09/2018 13:31:25
 * Author : 404
 */ 


#include <avr/io.h>
#include <avr/interrupt.h> //Interrcões
#include "usart.h"
#include "adc.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
//#define F_CPU 16000000UL

//char conta;
//int conta2 = 48;

char buffer[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
int contabuffer = 0;
char recebido='?';

ISR(USART_RX_vect) //#Interrupt.h
{
	
	recebido = USART_Receive();
	
	if(recebido == '[' && contabuffer == 0)
	{
		buffer[0] = '[';
		contabuffer++;
	}
	
	else if(buffer[0] == '[' && contabuffer > 0 && recebido != '[')
	{
		buffer[contabuffer] = recebido;
		contabuffer++;
	}
	
	else if(buffer[0] == '[' && contabuffer > 0)
	{
		for(int i=0;i<=9;i++) { buffer[i] = '0'; }
		contabuffer=0;
	}
	
	
	
	
	
		
}

int main(void)
{
	USART_Init();
	USART_StrTx("HELLO");
	USART_Transmit('\r');
	USART_Transmit('\n');
	USART_rxIE();
	
    while (1) 
    {
		sei();
		_delay_ms(1000);
		cli();
		
		if(buffer[0] == '[' && buffer[9] == ']')
		{
			for(int i=0; i<=9 ;i++)
			{
				USART_Transmit(buffer[i]);
				
			}
			contabuffer = 0;
			for(int i=0;i<=9;i++) { buffer[i] = '0'; }
			USART_StrTx("\r\n");
		}
		
		else if(buffer[0] == '[' && contabuffer > 0 && buffer[9] != ']')
		{
			USART_StrTx("Comando Invalido");
			USART_StrTx("\r\n");
			contabuffer = 0;
			for(int i=0;i<=9;i++) { buffer[i] = '0'; }	
		}
		
		else
		{
			USART_StrTx("Aguadando Comando");
			USART_StrTx("\r\n");
		}
		//##IMPEDIR COCORRENCIA NO USO DO BUFFER   ESCRITA/LEITURA;  <<<<  REINTRANCIA
		//cli(); //Desabilita Interrupçoes
		/*for(int i=0; i<=9 ;i++)
		{
			USART_Transmit(buffer[i]);
		}*/
		//sei(); //Habilita Interrupcoes
		/*if(buffer[0] == '[' && contabuffer <=9 && recebido != '?')
		{
			//USART_Transmit(contabuffer+48);
			buffer[contabuffer] = recebido;
			contabuffer++;
			recebido='?';
		}
		

		
		else if(recebido == '[' && contabuffer == 0 && recebido != '?')
		{
			//USART_Transmit(contabuffer+48);
			buffer[0] = '[';
			contabuffer++;
			recebido='?';
		}
		
		else
		{
			contabuffer = 0;
			for(int i=0;i<=9;i++)
			{
				buffer[i] = '0';
			}
			recebido='?';
		}
		
		for(int i=0; i<=9 ;i++)
		{
			USART_Transmit(buffer[i]);
			buffer[i] = '0';
		}
		
		USART_Transmit('\r');
		USART_Transmit('\n');
		recebido='?';
		
		
		
		if(contabuffer == 10 && buffer[9] == ']')
		{
			contabuffer = 0;
			
			for(int i=0; i<=9 ;i++)
			{
				USART_Transmit(buffer[i]);
				buffer[i] = '0';
			}
			
			USART_Transmit('\r');
			USART_Transmit('\n');
			recebido='?';
		}
		
		else if(contabuffer > 0 && buffer[0] != '[')
		{
			contabuffer = 0;
			for(int i=0;i<=9;i++)
			{
				buffer[i] = '0';
			}
			recebido='?';
		}*/
		//sei();
		
		//USART_StrTx("\r\n");
    }
}




