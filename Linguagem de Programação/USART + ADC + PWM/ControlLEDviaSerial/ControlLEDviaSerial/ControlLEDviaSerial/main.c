/*
 * ControlLEDviaSerial.c
 *
 * Created: 25/09/2018 13:31:25
 * Author : 404
 */ 
//[PD03_000]

#include <avr/io.h>
#include <avr/interrupt.h> //Interrcões
#include <avr/eeprom.h>
#include "usart.h"
#include "adc.h"
#include "pwm.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

//#define F_CPU 16000000UL

//char conta;
//int conta2 = 48;

char buffer[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
int contabuffer = 0;
char recebido='?';
int valorPWM=0;


void iniciaLEDS()
{
		
		
	valorPWM = eeprom_read_byte((const uint8_t *)3);
	PwmD03Init();
	PwmD03SetDuty(valorPWM);
	
	valorPWM = eeprom_read_byte((const uint8_t *)5);
	PwmD05Init();
	PwmD05SetDuty(valorPWM);
	
	valorPWM = eeprom_read_byte((const uint8_t *)6);
	PwmD06Init();
	PwmD06SetDuty(valorPWM);
	
	valorPWM = eeprom_read_byte((const uint8_t *)9);
	PwmD09Init();
	PwmD09SetDuty(valorPWM);
	
	valorPWM = eeprom_read_byte((const uint8_t *)10);
	PwmD10Init();
	PwmD10SetDuty(valorPWM);
	
	valorPWM = eeprom_read_byte((const uint8_t *)11);
	PwmD11Init();
	PwmD11SetDuty(valorPWM);
	
}



ISR(USART_RX_vect) //#Interrupt.h
{
	
	recebido = USART_Receive();
	
	if(recebido == '[' && contabuffer == 0)
	{
		buffer[0] = '[';
		contabuffer++; //[4576735683568537683
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
	USART_StrTx("Aguadando Comando");
	USART_StrTx("\r\n\n");
	DDRD = 0xFF;
	PORTD = 0x00;
	_delay_ms(5000);
	
	iniciaLEDS();
	
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
			USART_StrTx("\r\n");
			if(buffer[1] == 'P' && buffer[5] == '_')
			{
				valorPWM = (buffer[6] - 48) * 100;
				valorPWM += (buffer[7] - 48) * 10;
				valorPWM += buffer[8] - 48;
				USART_StrTx("Pino: ");
				USART_Transmit(buffer[2]);
				USART_Transmit(buffer[3]);
				USART_Transmit(buffer[4]);
				USART_StrTx(" Com PWM de: ");
				
				
				char strvalorPWM[3];
				sprintf(strvalorPWM, "%d", valorPWM);
				USART_StrTx(strvalorPWM );
				
				USART_StrTx(" Em %: ");
				valorPWM = (valorPWM*100)/255;
				sprintf(strvalorPWM, "%d", valorPWM);
				USART_StrTx(strvalorPWM );
				USART_StrTx("%\r\n\n");
				
				USART_StrTx("Aguadando Comando");
				USART_StrTx("\r\n\n");
				
				
				
				if(buffer[2] == 'D' && buffer[3] == '0' && buffer[4] == '6')
				{
					PwmD06SetDuty(valorPWM);
					eeprom_write_byte((uint8_t *)6, valorPWM);
				}
				else if(buffer[2] == 'D' && buffer[3] == '0' && buffer[4] == '5')
				{
					PwmD05SetDuty(valorPWM);
					eeprom_write_byte((uint8_t *)5, valorPWM);
				}
				else if(buffer[2] == 'D' && buffer[3] == '0' && buffer[4] == '9')
				{
					PwmD09SetDuty(valorPWM);
					eeprom_write_byte((uint8_t *)9, valorPWM);
				}
				else if(buffer[2] == 'D' && buffer[3] == '1' && buffer[4] == '0')
				{
					PwmD10SetDuty(valorPWM);
					eeprom_write_byte((uint8_t *)10, valorPWM);
				}
				else if(buffer[2] == 'D' && buffer[3] == '0' && buffer[4] == '3')
				{
					PwmD03SetDuty(valorPWM);
					eeprom_write_byte((uint8_t *)3, valorPWM);
				}
				else if(buffer[2] == 'D' && buffer[3] == '1' && buffer[4] == '1')
				{
					PwmD11SetDuty(valorPWM);
					eeprom_write_byte((uint8_t *)11, valorPWM);
				}
				else
				{
					USART_StrTx("Comando Invalido");
					USART_StrTx("\r\n");
					USART_StrTx("Aguadando Comando");
					USART_StrTx("\r\n\n");
				}
				
			}
			else
			{
				USART_StrTx("Comando Invalido");
				USART_StrTx("\r\n");
			}
			contabuffer = 0;
			for(int i=0;i<=9;i++) { buffer[i] = '0'; }
			
			
		}
		
		else if(buffer[0] == '[' && contabuffer > 0 && buffer[9] != ']')
		{
			USART_StrTx("Comando Invalido");
			USART_StrTx("\r\n");
			USART_StrTx("Aguadando Comando");
			USART_StrTx("\r\n\n");
			contabuffer = 0;
			for(int i=0;i<=9;i++) { buffer[i] = '0'; }	
		}
		
    }
}




