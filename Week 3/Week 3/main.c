/*
 * Week 3.c
 *
 * Created: 24-2-2021 09:56:39
 * Author : Dell
 */ 

#define F_CPU 8e6
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define BIT(x) 1<<x

void wait(int);
void timer2Init();

int main(void)
{
	//Init the lcd module
    init();
	
	//Forceer D7 naar een output
	DDRD |= BIT(7);
	
	//Init de timer 2
	timer2Init();
	
	while (1) { wait(100); }
	
	return 1;
}

//Interrupt method voor timer 2
ISR(TIMER2_COMP_vect)
{
	//Houd bij wat de milliseconden zijn
	static int msCount = 0;
	msCount++;
	
	static bool isHigh = true;
	
	if (isHigh && msCount == 15)
	{
		isHigh = false;
		msCount = 0;
		
		//Forceer D7 naar laag
		PORTD &= ~BIT(7);
	} else if (!isHigh && msCount == 25)
	{
		isHigh = true;
		msCount = 0;
		
		//Forceer D7 naar hoog
		PORTD |= BIT(7);
	}
}

void timer2Init()
{
	//Elke ms een interrupt
	OCR2 = 250;
	
	//Zet de compare modus aan
	TIMSK |= BIT(7);
	
	//Zet het interrupt systeem aan
	sei();
	
	//Initialiseer de timer met prescaler van 32
	//TCCR2 = 0b00001101;
	TCCR2 = 0x0C;
}

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

