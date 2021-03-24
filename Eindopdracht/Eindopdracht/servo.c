#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

static void setPwmTargetValue(int);

// Start value of the servo (0-180 degrees)
static const int startValue = 0;
// Extern variable for the servo target value
int servo_targetValue;


ISR(TIMER1_COMPA_vect)
{
	// Go slow to target value
	const int speed = 1;
	static int currentValue = startValue;
	
	// Maps the value from 0-180 to 250-2500 (frequency of the servo)
	int targetValue = (servo_targetValue - 0) / (180 - 0) * (2500 - 250) + 250;
	
	if (currentValue < targetValue)
	currentValue += speed;
	else if (currentValue > targetValue)
	currentValue -= speed;
	
	setPwmTargetValue(currentValue);
}

void servo1_init()
{
	DDRB = 0xFF;				// Set whole port B as output
	
	OCR1A = (startValue - 0) / (180 - 0) * (2500 - 250) + 250;	// Sets the compare value of timer 1, (this is linked to port B5)
	servo_targetValue = startValue;
	
	TIMSK |= 1<<(4);			// Turn on compare mode
	sei();						// Turn on interrupt system
	
	ICR1 = 10000;				// Sets the upper limit to timer 1
	TCCR1A = 0b10000010;		// Set OC1A as output
	TCCR1B = 0b00010010;		// fast PWM 8 bit, prescaler=8, RUN
}

static void setPwmTargetValue(int value)
{
	OCR1A = value;
}