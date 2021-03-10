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

#define BIT(x) 1<<(x)

int main(void)
{
	//Port F word input en A en B output
	DDRF = 0x00;
	DDRA = 0xff;
	DDRB = 0xff;
	
	DDRC = 0x00;
	DDRD = 0xff;
	
	
	//6e bit staat aan (ADLAR (telt vanaf 6 t/m 15))
	//De eerste 4 bits zijn voor het selecteren van welke input channel
	ADMUX = 0b01100011;
	
	//Laatste bit is om de adc te enablen
	//1 na laatste is om een conversie te starten op de adc
	//6e bit is freerunning mode
	//Eerste 3 bits is voor de prescaler
	ADCSRA = 0b10000110;
	
	
	while (1) 
	{ 
		//Controleer voor een button input
		if (PINC & 0x01)
		{
			//Forceer een conversie start
			ADCSRA |= BIT(6);
			while (ADCSRA & BIT(6))
			{	
				PORTD = 0xff;
				
				//Zet de laatste bits (8 t/m 15) in port b
				PORTB = ADCH;
			}
			
			PORTD = 0x00;
		}
		
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

