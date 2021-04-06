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
	// Set the in and outputs at PORTB
	DDRB = 0xFF;
	servo_init();

	
	while (1)
	{
		servo1_targetValue = 180;
		servo2_targetValue = 180;
		wait(10000);
		
		servo1_targetValue = 0;
		servo2_targetValue = 0;
		wait(10000);
	}
	
	return 1;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}