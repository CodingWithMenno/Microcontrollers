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

void wait(int);

//Een struct voor 1 segment in een totaal patroon
typedef struct Pattern{
	unsigned char data;
	unsigned char delay;
} segmentPattern;

//Een lijst met meerdere segmenten die samen één/meerdere patronen vormen
segmentPattern arrayPattern[] = {
	{0x01, 40}, {0x02, 40}, {0x04, 40}, {0x08, 40}, {0x10, 40}, {0x20, 40}, {0x01, 40}, //cirkel patroon
	{0x22, 80}, {0x14, 80}, {0x08, 80}, //druppel splitsing patroon
};


int main( void ) {

	int index = 0;
	
	PORTA = 0xFF; //Zet alles van poort A op output

	while(1)
	{
		DDRA = arrayPattern[index].data; //Het aanzetten van het display met de index
		wait(arrayPattern[index].delay); //Wachten met de lengte van de delay die bij de index hoort
		
		index++;
		index %= (sizeof(arrayPattern) / sizeof(segmentPattern)); //Zorgen dat wanneer het einde van de array is bereikt de index weer naar 0 gaat.
		
	}

	return 1;
}

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}