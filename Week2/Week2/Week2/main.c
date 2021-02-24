#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "B5/lcd.h"

#define LCD_E 3
#define LCD_RS 2

void confirmCommand();
void write_command(unsigned char);
void write_data(unsigned char);
void init();
void display_text(char *str);
void set_cursor(int position);
void clearDisplay();
void wait(int);

int main(void)
{
	init();
	set_cursor(0);
	display_text("hey");
	
	while (1)
	{
		wait(10);
	}
	
	return 1;
}

void init()
{
	DDRC = 0xFF;
	PORTC = 0x00;

	PORTC = 0x28;	// function set
	confirmCommand();

	PORTC = 0x28;   // function set
	confirmCommand();
	PORTC = 0x80;
	confirmCommand();

	clearDisplay();

	write_command(0x0F); //Display on/off control
	
	write_command(0x06); //Entry mode set
}

void clearDisplay()
{
	write_command(0x01); //Clear display
}

void confirmCommand()
{
	PORTC |= (1<<LCD_E);
	wait(1);
	PORTC &= ~(1<<LCD_E);
	wait(1);
}

void display_text(char *str)
{
	for(;*str; str++)
	{
		write_data(*str);
	}
}

void set_cursor(int position)
{
	write_command(0x80 + position);
}

void write_command(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	confirmCommand();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	confirmCommand();
}

void write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	confirmCommand();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	confirmCommand();
}

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}