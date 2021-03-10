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

void wait(int);

#define BIT(x) 1<<(x)

int main(void)
{
	init();
	
	//Port F word input en A output
	DDRF = 0x00;
	DDRA = 0xff;
	DDRB = 0xff;
	
	
	//6e bit staat uit (ADLAR (telt vanaf 0 t/m 10))
	//De eerste 4 bits zijn voor het selecteren van welke input channel
	ADMUX = 0b11000011;
	
	//Laatste bit is om de adc te enablen
	//1 na laatste is om een conversie te starten op de adc
	//6e bit is freerunning mode
	//Eerste 3 bits is voor de prescaler
	ADCSRA = 0b11100110;
	
	char lcdText[50] = " ";
	
	while (1) 
	{ 
		//Reken de ADCL input om naar graden celcius
		int degrees = (int) (ADCL / 2.56);
		sprintf(lcdText, "Graden: %d", degrees);
		PORTA = ADCL;
		PORTB = ADCH;
		display_text(lcdText);
		wait(1000);
		clearDisplay();
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

