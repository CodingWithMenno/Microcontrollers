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
	
    while (1) 
    {
		if (PINC & 0x01)
		{
			PORTD = 0x80;
			wait(100);
			PORTD = 0x00;
			wait(100);
		} else {
			PORTD = 0x00;
		}
    }
	
	return 1;
}