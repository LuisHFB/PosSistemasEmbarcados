char matriz[20];
char *pot;
char aux=0;

//pot = &matriz[0];  //pega o endereço da primeira posição e armazea na variavel pot (nao no poteiro)
//pot = matriz //mesmo que anterior

ISR(USART_RX_vect)
{
	char res;
	res = USART_Receive();
	if(res == '[')
	{
		pot = matriz;
		aux 1;
	}
	else
	{
		if(aux==1)
		{
			if((pot-matriz) < 20)
			{
			*pot = res; //Armazena o coteúdo recebido na matriz por Meio do ponteiro
			pot++;
			}
		}
	
		
	}
	
	if(res == ']')
	{
	 decMatriz();
	 aux = 0;
	}
	
}




void decMatriz();
{
	if(matriz[0] == 'L' && matriz[1] == 'D')
	{
		switch(matriz[2])
		{
			case '0';
			if(matriz[3] == '0')
			{
				Set_bit(PORTB, 5);
				USAR_StrTx(matriz);
			}
			else
			{
				Clr_bit(PORTB, 5);
			}
			break;
		}
	}
