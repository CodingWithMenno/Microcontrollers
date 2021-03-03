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

void wait(int);

#define BIT(x) 1<<x

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xff;
	DDRB = 0xff;
	
	//Referentie spanning van de ADC instellen
	ADMUX = 0x61;
	//De ADC instellen met bepaalde instellingen
	ADCSRA = 0xE6;
	//Het manier van opslaan kiezen
	//ADLAR = 0x1;
	
	while (1) 
	{ 
		PORTB = ADCL;
		PORTA = ADCH;
		wait(10); 
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

