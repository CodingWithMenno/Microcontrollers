#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

#define BIT(x) 1<<(x)

void wait(int ms);

// Extern variable to the servo1 angle, value between 250-1500 (defined in servo.h)
int servo1_targetValue;
// Extern variable to the servo2 angle, value between 250-2500 (defined in servo.h)
int servo2_targetValue;


int main( void )
{
	DDRB = 0xFF;				// Set whole port B as output
	servo_init();
	
	while (1)
	{		
		servo1_targetValue = 1500;
		servo2_targetValue = 250;
		wait(10000);
		servo1_targetValue = 250;
		servo2_targetValue = 2500;
		wait(10000);
	}
	
	return 1;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}