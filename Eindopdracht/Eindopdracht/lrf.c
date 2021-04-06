/*
 * lrf.c
 *
 * Created: 24-3-2021 14:09:32
 *  Author: timoj
 */ 
#include <avr/io.h>
#include "lrf.h"

#define FOSC 8000000 // Clock Speed
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_Receive_String(char* data)
{
	int i = 0;
	
	char tempData = 'a';
	
	//char *pChar = &tempData;
	
	while(tempData != ':')
	{
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC)) );
		
		tempData = UDR0;
		//display_text(pChar);
		
		data[i] = tempData;
		i++;
	}
	data[i] = '\0';
}

int USART_onlyNumbers(char* data)
{
	char subArray[5];
		for (int i = 0; i < 4; i++)
		{
			subArray[i] = data[i+5];
		}
		
		int distance;
		sscanf(subArray, "%d", &distance);

	return distance;
}
