
#define F_CPU 8e6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"

#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define BIT(x) ( 1<<x )

// wait(): busy waiting for 'ms' millisecond - used library: util/delay.h
void wait(int ms)
{
	for (int i=0; i<ms; i++)
		_delay_ms(1);
}

void USART_Init(unsigned int ubrr)
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS)|(3<<UCSZ0);
	
}

void USART_Transmit(unsigned char data)
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


int main()
{
	init();
	clearDisplay();
	set_cursor(0);

	unsigned char data = ' ';
	
	USART_Init( MYUBRR );
	
	data = 'R';
	while(1)
	{
		USART_Transmit(data);
		
		char receivedString[20];
		USART_Receive_String(receivedString);
		
		char subArray[5];
		for (int i = 0; i < 4; i++)
		{
			subArray[i] = receivedString[i+5];
		}
		
	
		
		int distance;
		sscanf(subArray, "%d", &distance);
		
		
		char *test = "     ";
		sprintf(test, "%d", distance);
		
		 
		
		
		clearDisplay();
		display_text(test);
	
		//char received = USART_Receive();
		//while (received == 'm')
		//{
			//received = USART_Receive();
			//display_text("i");
		//}	
		//received = USART_Receive();
		//received = USART_Receive();	
		//received = USART_Receive();	
		//received = USART_Receive();	
		//received = USART_Receive();
		//received = USART_Receive();	
		//received = USART_Receive();	
		//received = USART_Receive();	
		//received = USART_Receive();			
		
		//if(received == 'm')
		//display_text("test");
		//clearDisplay();
		//display_text("test");
		wait(10000);
	}
	return (1);
}
