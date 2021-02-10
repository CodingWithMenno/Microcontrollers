/*
 * Week2.c
 *
 * Created: 10-2-2021 10:03:18
 * Author : Dell
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setDisplayDigit(int);
void wait(int);

//Alle mogelijke nummers die op de 7 segment kunnen worden getoond
const unsigned char hexNumbers[17] =
{
	0x3F, //0
	0x06, //1
	0x5B, //2
	0x4F, //3
	0x66, //4
	0x6D, //5
	0x7C, //6
	0x07, //7
	0x7F, //8
	0x6F, //9
	0x77, //A
	0x7C, //B
	0x39, //C
	0x5E, //D
	0x79, //E
	0x71, //F
	0xF9  //Error
};

//De digit die aanstaat
int currentDigit;

int main( void ) {
	currentDigit = 0;
	
	PORTA = 0xFF; //Zet alles van poort A op output
	PORTB = 0x00; //Zet alles van poort B op input

	while(1)
	{
		if (PINB & 0x01 && PINB & 0x02) //Check of B0 en B1 zijn ingedrukt
		{
			currentDigit = 0;
		} else if (PINB & 0x01 && currentDigit <= 16) //Check of B0 is ingedrukt en de huidige digit niet hoger is dan 16
		{
			currentDigit++;
		} else if (PINB & 0x02 && currentDigit >= -1) //Check of B1 is ingedrukt en de huidige digit niet kleiner is dan -1
		{
			currentDigit--;
		}
		
		setDisplayDigit(currentDigit);
		
		wait(200);
	}

	return 1;
}

void setDisplayDigit(int digit)
{
	if (digit < 0 || digit > 15) //Kijk of de meegekregen waarde niet valid is
	{
		DDRA = hexNumbers[16];
	} else
	{
		DDRA = hexNumbers[digit];
	}
}

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}