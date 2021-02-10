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
#include <stdbool.h>

void shiftLed();
void reset();

//Het ledje wat aanstaat in het looplicht patroon
unsigned char currentLed;
//Bijhouden op het looppatroon naar links of naar rechts gaat
bool isGoingLeft;

int main( void ) {
	currentLed = 0x01;
	isGoingLeft = true;
	
	DDRB = 0xFF;			// PORTB alles op output
	DDRD = 0x00;			//PORTD alles op input

	// Init Interrupt hardware
	EIMSK |= 0x06;			// Enable INT1 & INT2 (0b110)
	EICRA |= 0x3C;			// INT1 en INT2 op rising edge (0b111100)
		
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
	while(1) //Nutteloze while true loop
	{}

	return 1; //Nog nuttelozere return
}

//Interrupt voor D1
ISR( INT1_vect ) {
	reset();
}

//Interrupt voor D2
ISR( INT2_vect ) {
	shiftLed();
}

void shiftLed()
{
	if (isGoingLeft)
	{	
		//Zet het ledje 1 naar links
		currentLed = currentLed << 1;
		PORTB = (currentLed);
		
		//Als de meest linker led aanstaat moet je naar rechts gaan
		if (currentLed == 0x80)
		{
			isGoingLeft = false;
		}
	} else
	{
		//Zet het ledje 1 naar rechts
		currentLed = currentLed >> 1;
		PORTB = (currentLed);
		
		//Als de meest rechter led aanstaat moet je weer naar links gaan
		if (currentLed == 0x01)
		{
			isGoingLeft = true;
		}
	}
}

//Reset het looplicht naar de B0 (de meest rechter)
void reset()
{
	currentLed = 0x01;
	PORTB = (currentLed);
	isGoingLeft = true;
}