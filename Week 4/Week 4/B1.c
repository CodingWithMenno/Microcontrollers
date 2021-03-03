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
	//Port F word input en A en B output
	DDRF = 0x00;
	DDRA = 0xff;
	DDRB = 0xff;
	
	
	//6e bit staat aan (ADLAR (telt vanaf 6 t/m 15))
	//De laatste 4 bits zijn voor het selecteren van welke input channel
	ADMUX = 0b01100001;
	
	//De ADC instellen met bepaalde instellingen
	ADCSRA = 0b11100110;
	
	
	while (1) 
	{ 
		//Zet de laatste bits (8 t/m 15) in port b
		PORTB = ADCH;
		//Zet de eerste 2 bits in port a
		PORTA = ADCL;
		wait(1); 
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

