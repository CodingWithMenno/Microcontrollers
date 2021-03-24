#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

// Maps the value between two numbers: https://stackoverflow.com/questions/345187/math-mapping-numbers
//#define MAP(x) (x - 0) / (180 - 0) * (1500 - 250) + 250

// Start value of the servo (250-1500)
static const int startValue = 0;
// Extern variable for the servo target value
int servo_targetValue;


ISR(TIMER1_COMPA_vect)
{
	// Go slow to target value
	const float speed = 1;
	static float currentValue = startValue;
	
	// Maps the value from 0-180 to 250-1500 (frequency of the servo)
	//float targetValue = MAP(servo_targetValue);
	
	if (currentValue < servo_targetValue)
	currentValue += speed;
	else if (currentValue > servo_targetValue)
	currentValue -= speed;
	
	OCR1A = currentValue;
}

void servo1_init()
{
	DDRB = 0xFF;				// Set whole port B as output
	
	OCR1A = 250; //MAP(startValue);	// Sets the compare value of timer 1, (this is linked to port B5)
	servo_targetValue = startValue;
	
	TIMSK |= 1<<(4);			// Turn on compare mode
	sei();						// Turn on interrupt system
	
	ICR1 = 10000;				// Sets the upper limit to timer 1
	TCCR1A = 0b10000010;		// Set OC1A as output
	TCCR1B = 0b00010010;		// fast PWM 8 bit, prescaler=8, RUN
}