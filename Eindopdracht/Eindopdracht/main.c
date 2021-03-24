#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

#define BIT(x) 1<<(x)

void wait(int ms);

// Extern variable to the servo angle, value between 0-180 (defined in servo.h)
int servo_targetValue;


int main( void )
{
	servo1_init();
	wait(1000);
	
	while (1)
	{
		if(servo_targetValue == 180)
		{
			servo_targetValue = 0;
		} else
		{
			servo_targetValue = 180;
		}

		wait(5000);
	}
	
	return 1;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}