#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

#define BIT(x) 1<<(x)

void wait(int ms);

// Extern variable to the servo1 angle (defined in servo.h)
int servo1_targetValue;
// Extern variable to the servo2 angle (defined in servo.h)
int servo2_targetValue;


int main( void )
{
	DDRB = 0xFF;				// Set whole port B as output
	servo_init();
	
	while (1)
	{				
		servo1_targetValue = 90;
		servo2_targetValue = 90;
	}
	
	return 1;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}