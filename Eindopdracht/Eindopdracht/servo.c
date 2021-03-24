#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"

// Maps the value between two numbers: https://stackoverflow.com/questions/345187/math-mapping-numbers
//#define MAP(x) (x - 0) / (180 - 0) * (1500 - 250) + 250


// Start value of the servo
static const int startValue = 0;

// Extern variables for the servo target values
int servo1_targetValue;
int servo2_targetValue;


ISR(TIMER1_COMPA_vect)
{
	// Go slow to target value
	const float speed = 1;
	static float currentValue = startValue;
	
	// Maps the value from 0-180 to 250-1500 (frequency of the servo)
	//float targetValue = MAP(servo_targetValue);
	
	if (currentValue < servo1_targetValue)
	currentValue += speed;
	else if (currentValue > servo1_targetValue)
	currentValue -= speed;
	
	OCR1A = currentValue;
}

ISR(TIMER1_COMPB_vect)
{
	// Go slow to target value
	const float speed = 1;
	static float currentValue = startValue;
	
	// Maps the value from 0-180 to 250-1500 (frequency of the servo)
	//float targetValue = MAP(servo_targetValue);
	
	if (currentValue < servo2_targetValue)
	currentValue += speed;
	else if (currentValue > servo2_targetValue)
	currentValue -= speed;
	
	OCR1B = currentValue;
}

void servo_init()
{
	OCR1A = 250;				// Sets the compare value of timer 1, (this is linked to port B5)
	OCR1B = 250;				// Sets the compare value of timer 1, (this is linked to port B6)
	servo2_targetValue = startValue;
	
	TIMSK |= 1<<(3);			// Turn on compare mode for channel A
	TIMSK |= 1<<(4);			// Turn on compare mode for channel B
	sei();						// Turn on interrupt system
	
	ICR1 = 10000;				// Sets the upper limit to timer 1
	TCCR1A = 0b10100010;		// Set OC1B as output
	TCCR1B = 0b00010010;		// fast PWM 8 bit, prescaler=8, RUN
}