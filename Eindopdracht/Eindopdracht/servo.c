#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

// Maps the value
double map(double, int, int);

// Start value of the servo
static const int startValue1 = 250;
static const int startValue2 = 250;

// Extern variables for the servo target values
int servo1_targetValue;
int servo2_targetValue;


ISR(TIMER1_COMPA_vect)
{
	// Go slow to target value
	const float speed = 1;
	static float currentValue = startValue1;
	
	// Maps the value from 0-180 to 250-1500 (frequency of the servo)
	float targetValue = map(servo1_targetValue, 250, 1300);
	
	if (currentValue < targetValue)
	currentValue += speed;
	else if (currentValue > targetValue)
	currentValue -= speed;
	
	OCR1A = currentValue;
}

ISR(TIMER1_COMPB_vect)
{
	// Go slow to target value
	const float speed = 1;
	static float currentValue = startValue2;
	
	// Maps the value from 0-180 to 250-1300 (frequency of the servo)
	float targetValue = map(servo2_targetValue, 250, 1300);
	
	if (currentValue < targetValue)
	currentValue += speed;
	else if (currentValue > targetValue)
	currentValue -= speed;
	
	OCR1B = currentValue;
}

void servo_init()
{
	OCR1A = startValue1;		// Sets the compare value of timer 1, (this is linked to port B5)
	OCR1B = startValue2;		// Sets the compare value of timer 1, (this is linked to port B6)
	
	servo1_targetValue = startValue1;
	servo2_targetValue = startValue2;
	
	TIMSK |= 1<<(3);			// Turn on compare mode for channel A
	TIMSK |= 1<<(4);			// Turn on compare mode for channel B
	sei();						// Turn on interrupt system
	
	ICR1 = 10000;				// Sets the upper limit to timer 1
	TCCR1A = 0b10100010;		// Set OC1B as output
	TCCR1B = 0b00010010;		// fast PWM 8 bit, prescaler=8, RUN
}

double map(double value, int newMin, int newMax)
{
	// Maps the value between two numbers: https://stackoverflow.com/questions/345187/math-mapping-numbers
	return (value - 0) / (180 - 0) * (newMax - newMin) + newMin;
}