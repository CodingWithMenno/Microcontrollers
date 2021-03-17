#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void wait(int ms);
void timer1Init();
void setPwmTargetValue(int);

// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;
	timer1Init();
	wait(1000);
	
	for (int i = 250; i < 2500; i++)
	{
		setPwmTargetValue(i);
		wait(1);
	}

}

void timer1Init()
{
	OCR1A = 250;				// Sets the compare value of timer 1
	ICR1 = 10000;				// Sets the upper limit to timer 1
	TCCR1A = 0b10000010;		// Set OC1A as output
	TCCR1B = 0b00010010;		// fast PWM 8 bit, prescaler=8, RUN
}

void setPwmTargetValue(int value)
{
	OCR1A = value;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}