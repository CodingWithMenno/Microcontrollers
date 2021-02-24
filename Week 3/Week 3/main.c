/*
 * Week 3.c
 *
 * Created: 24-2-2021 09:56:39
 * Author : Dell
 */ 

#define F_CPU 8e6
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define BIT(x) 1<<x

void wait(int);

int main(void)
{
	//Init the lcd module
    init();
	set_cursor(0);
	
	//Init the button and counter
	DDRD &= ~BIT(7);
	TCCR2 = 0x07;
	
	//Geheugen reserveren voor de char
	char *totalPressed = "                 ";
	
    while (1) 
    {
		//De int van de counter omzetten naar een char en plaatsten in totalPressed
		sprintf(totalPressed, "%d", TCNT2);
		
		clearDisplay();
		display_text(totalPressed);
		
		wait(100);
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

