#define F_CPU 8e6
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "lrf.h"
#include "lcd.h"

#define BIT(x) 1<<(x)

static void wait(int);

struct CAMERA_SETTING
{
	int distance; // Lrf distance
	int focus; // Servo 1
	int zoom; // Servo 2
};

static int totalCameraSegments = 5;
static struct CAMERA_SETTING cameraSettings[] = 
{
	{ 150, 105, 180 },
	{ 450, 95, 140 },
	{ 675, 44, 80 },
	{ 900, 42, 75 },
	{ 1200, 40, 30 }
};

// Extern variable to the servo1 angle (angle between 0 and 110 (safe angles))
int servo1_targetValue;
// Extern variable to the servo2 angle (angle between 180 and 30 (safe angle))
int servo2_targetValue;


int main(void)
{
	DDRB = 0xFF; // Set whole port B as output
	
	init(); // Lcd init
	
	servo_init();
	wait(1000); // Wait for the init of the servo's
	
	USART_Init(MYUBRR);	// Init the lrf
	char *data = (char*) malloc(sizeof(char) * 20);
	int distance = 0;
	
	while (1)
	{	
		USART_Transmit(SINGLE_RANGE_COMMAND_A);	// Send measure command to lrf
		USART_Receive_String(data);	// Receive string form lrf
		distance = USART_onlyNumbers(data);	// Get the distance from the string
		if (distance == 0)
		{
			wait(2000);
			continue;
		}
		
		sprintf(data, "Distance: %d", distance);
		clearDisplay();
		display_text(data);	// Show the distance on the lcd
		
		// Get the closest zoom and focus setting from the measured distance
		int minDifference = 1000;
		struct CAMERA_SETTING settingToUse = cameraSettings[0];
		for (int i = 0; i < totalCameraSegments; i++)
		{
			int difference = abs(distance - cameraSettings[i].distance);
			
			if (difference < minDifference)
			{
				minDifference = difference;
				settingToUse = cameraSettings[i];
			}
		}
		
		servo1_targetValue = settingToUse.focus; // Focus on target
		servo2_targetValue = settingToUse.zoom;	// Zoom to target
		
		wait(3000);	
	}
	
	free(data);
	return 1;
}

static void wait(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms(1);
}