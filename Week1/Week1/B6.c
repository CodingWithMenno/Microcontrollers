/*
 * Week1.c
 *
 * Created: 3-2-2021 13:50:41
 * Author : Dell
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

typedef enum { one, four} frequenties;

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{	
	frequenties currentFreq = one;
	bool isOne = false;
    DDRD = 0b11111111;
	
    while (1) 
    {
		if(PINC & 0x01)
		{
			isOne = !isOne;
		} 
		
		if(isOne){
			currentFreq = one;
		}else{
			currentFreq = four;
		}
		
		
		switch(currentFreq)
		{
			case one: 
			PORTD = 0x80;
			wait(1000);
			PORTD = 0x00;
			wait(1000);
			break;
			
			case four: 
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
			wait(250);
			break;
		}

    }
	
	return 1;
}

