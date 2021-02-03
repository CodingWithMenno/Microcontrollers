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

typedef struct {
	unsigned char led;
	unsigned int delay;	
} ledPattern;

ledPattern arrayPattern[] = {
	{0b00000000, 20}, {0b00000001, 100}, {0b00000010, 500}, {0b00001000, 1000}
};

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
	int size = 4;
	int index = 0;
	
    while (1) 
    {
		PORTD = arrayPattern[index].led;
		wait(arrayPattern[index].delay);
		
		index++;
		index %= size;
    }
	
	return 1;
}

