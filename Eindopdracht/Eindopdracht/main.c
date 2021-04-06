#define F_CPU 8e6
#include <stdio.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "lrf.h"

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
	servo1_targetValue = 90;
	servo2_targetValue = 90;
	
	USART_Init(BAUD);
	char *data = (char*) malloc(sizeof(char) * 20);
	int distance = 0;
	
	while (1)
	{	
		USART_Transmit(SINGLE_RANGE_COMMAND_A);	// Send measure command to lrf
		USART_Receive_String(data);	// Receive string form lrf
		distance = USART_onlyNumbers(data);	// Get the distance from the string
		
		wait(3000);			
	}
	
	free(data);
	return 1;
}

void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}