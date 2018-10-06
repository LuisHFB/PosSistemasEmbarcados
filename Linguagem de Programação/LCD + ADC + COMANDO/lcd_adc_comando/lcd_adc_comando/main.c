#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "adc.h"
#include "lcd.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
//#define F_CPU 16000000UL



char buffer[6] = {'0','0','0','0','0','0'};
char buffer_valor[6];
int contabuffer = 0;
char recebido='?';
int valor;

ISR(USART_RX_vect) //#Interrupt.h
{

	recebido = USART_Receive();
	USART_Transmit(recebido);
	
	if(recebido == '[' && contabuffer == 0)
	{
		buffer[0] = '[';
		contabuffer++; //[4576735683568537683
	}
	
	else if(buffer[0] == '[' && contabuffer > 0 && recebido != '[' && buffer[5] != ']')
	{
		buffer[contabuffer] = recebido;
		contabuffer++;
	}
	else
	{
		contabuffer++;
	}
	
	
}

int main(void)
{
	
	
	
	USART_Init();
	//USART_StrTx("HELLO");
	USART_rxIE();
	
	adc_init();
	
	DisplayLCD_Init();
	//DisplayLCD_Out(1,2, "BOM DIA");
	DisplayLCD_Cmd(LCD_Clear);
	
	sei();
	
	while (1)
	{
		
		DisplayLCD_Out(1,1,"- Entre c/ Cmd");
		
		if(buffer[0] == '[' && buffer[1] == 'A' &&buffer[2] == 'D' && buffer[3] == 'C' &&  buffer[5] == ']')
		{
			if(buffer[4] == '0' || buffer[4] == '1' || buffer[4] == '2' || buffer[4] == '3' || buffer[4] == '4' || buffer[4] == '5')
			{
			
			DisplayLCD_Cmd(LCD_Clear);
			cli();
			for(int i=0; i<=5 ;i++)
			{
				USART_Transmit(buffer[i]);
				DisplayLCD_Chr(1,1+i,buffer[i]);
			}
			sei();
			USART_StrTx("\r\n");
			DisplayLCD_Chr(2,16,'s');
			
			for(int i=57; i>48; i--)
			{
				DisplayLCD_Chr(2,15,i);
				for(int j=0; j<4; j++)
				{
					if(buffer[4] == '0') { valor = adc_read(0); sprintf(buffer_valor, "%d", valor); DisplayLCD_Out(2,1,"    ");} //stdio.h}
					if(buffer[4] == '1') { valor = adc_read(1); sprintf(buffer_valor, "%d", valor); DisplayLCD_Out(2,1,"    ");} //stdio.h}
					if(buffer[4] == '2') { valor = adc_read(2); sprintf(buffer_valor, "%d", valor); DisplayLCD_Out(2,1,"    ");} //stdio.h}
					if(buffer[4] == '3') { valor = adc_read(3); sprintf(buffer_valor, "%d", valor); DisplayLCD_Out(2,1,"    ");} //stdio.h}
					if(buffer[4] == '4') { valor = adc_read(4); sprintf(buffer_valor, "%d", valor); DisplayLCD_Out(2,1,"    ");} //stdio.h}
					if(buffer[4] == '5') { valor = adc_read(5); sprintf(buffer_valor, "%d", valor); DisplayLCD_Out(2,1,"    ");} //stdio.h}
					DisplayLCD_Out(2,1,buffer_valor);
					_delay_ms(250);
				}
				
			}
			DisplayLCD_Cmd(LCD_Clear);	
			contabuffer=0;
			for(int i=0;i<=5;i++) { buffer[i] = '0'; }
			}
			
			else
			{
				DisplayLCD_Cmd(LCD_Clear);
				for(int i=0;i<=2;i++) {  DisplayLCD_Out(2,1,"- Cmd Invalido");	_delay_ms(250); DisplayLCD_Cmd(LCD_Clear); _delay_ms(250);}
				contabuffer=0;
				for(int i=0;i<=5;i++) { buffer[i] = '0'; }
			}
			
				
		}
		else if(contabuffer > 0 && buffer[0] != '[')
		{
		DisplayLCD_Cmd(LCD_Clear);
		for(int i=0;i<=2;i++) {  DisplayLCD_Out(2,1,"- Cmd Invalido");	_delay_ms(250); DisplayLCD_Cmd(LCD_Clear); _delay_ms(250);}
		contabuffer=0;
		for(int i=0;i<=5;i++) { buffer[i] = '0'; }
		}
	}
}

