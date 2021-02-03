/*
 * Week1.c
 *
 * Created: 3-2-2021 13:50:41
 * Author : Dell
 */ 

#define F_CPU 8e6
#define BIT(x) (1 << (x))

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) 
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
    DDRD = 0b11111111;
	unsigned char led = 0b10000000;
	
    while (1) 
    {
		for (int i = 0; i < 7; i++)
		{
			PORTD = led;
			led = (led >> 1); 
			wait(50);
		}
		
		for (int i = 0; i < 7; i++)
		{
			PORTD = led;
			led = (led << 1); 
			wait(50);
		}
		
		wait(50);
    }
	
	return 1;
}

