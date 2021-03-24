#define F_CPU 8e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x) 1<<(x)

void wait(int ms);
void timer1Init();
void setPwmTargetValue(int);

static int servoValue;

// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;
	timer1Init();
	wait(1000);
	
	while (1)
	{
		for (int i = 250; i < 2500; i++)
		{
			servoValue = i;
			wait(1);
		}
		
		for (int i = 2500; i > 250; i--)
		{
			servoValue = i;
			wait(1);
		}
	}
	
	return 1;
}

ISR(TIMER1_COMPA_vect)
{
	setPwmTargetValue(servoValue);
}

void timer1Init()
{
	int startValue = 250;
	
	OCR1A = startValue;			// Sets the compare value of timer 1, (this is linked to port B5)
	servoValue = startValue;
	
	//Zet de compare modus aan
	TIMSK |= BIT(4);
		
	//Zet het interrupt systeem aan
	sei();
	
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