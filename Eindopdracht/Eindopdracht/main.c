#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

#define BIT(x) 1<<(x)

void wait(int ms);

// Extern variable to the servo angle, value between 250-1500 (defined in servo.h)
int servo_targetValue;


int main( void )
{
	servo1_init();
	//wait(1000);
	
	while (1)
	{		
		servo_targetValue = 250;
		wait(10000);
		servo_targetValue = 1500;
		wait(10000);
	}
	
	return 1;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}