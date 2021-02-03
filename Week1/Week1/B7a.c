/*
 * Week1.c
 *
 * Created: 3-2-2021 13:50:41
 * Author : Dell
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

//Alle states in het systeem
typedef enum 
{
	START_STATE,
	S1_STATE,
	S2_STATE,
	S3_STATE,
	END_STATE
} systemState;

//Alle mogelijke events in het systeem die de huidige state kan veranderen naar een andere state 
typedef enum
{
	D7_EVENT,
	D6_EVENT,
	D5_EVENT,
	NULL
} systemEvent;

void wait(int);
systemEvent getCurrentEvent(void);
void init(systemState);
void exitState(systemState);

int main(void)
{	
	//Alle leds op rij D als output zetten
    DDRD = 0b11111111;
	
	//De eerste state waar het systeem in komt is de start state
	systemState currentState = START_STATE;
	systemEvent newEvent = NULL;
	
	//De eerste state initialiseren
	init(currentState);
	
    while (1) 
    {
		//Het event ophalen (als er geen nieuw event is word NULL terug gegeven)
		newEvent = getCurrentEvent();
		
		if (newEvent == NULL)
		{
			continue;
		}
		
		//Handelen a.d.h.v. de huidige state
		switch(currentState)
		{
			case START_STATE:
				if (newEvent == D6_EVENT) //Wanneer de event gelijk is aan het nieuwe event word er van state veranderd
				{
					exitState(currentState); //Eerst word de huidige state afgesloten door de exitState() methode aan te roepen
					currentState = S1_STATE; //Vervolgens word de huidige state aangepast
					init(currentState); //En als laatste word de nieuwe state geinitialiseerd
				} else if (newEvent == D5_EVENT)
				{
					exitState(currentState);
					currentState = S2_STATE;
					init(currentState);
				}
				break;	
			case S1_STATE:
				if(newEvent == D5_EVENT)
				{
					exitState(currentState);
					currentState = S2_STATE;
					init(currentState);
					
				}else if(newEvent == D7_EVENT)
				{
					exitState(currentState);
					currentState = START_STATE;
					init(currentState);
				}
				break;
			case S2_STATE:
				if(newEvent == D5_EVENT)
				{
					exitState(currentState);
					currentState = S3_STATE;
					init(currentState);
				}else if(newEvent == D7_EVENT)
				{
					exitState(currentState);
					currentState = START_STATE;
					init(currentState);
					
				}else if(newEvent == D6_EVENT)
				{
					exitState(currentState);
					currentState = S1_STATE;
					init(currentState);
				}
				break;
			case S3_STATE:
				if(newEvent == D5_EVENT || newEvent == D6_EVENT)
				{
					exitState(currentState);
					currentState = END_STATE;
					init(currentState);
				}else if(newEvent == D7_EVENT)
				{
					exitState(currentState);
					currentState = START_STATE;
					init(currentState);
				}
				break;
			case END_STATE:
				if(newEvent == D7_EVENT)
				{
					exitState(currentState);
					currentState = START_STATE;
					init(currentState);
				}
		}
    }
	
	return 1;
}

//Geeft het huidige event terug als deze er is
systemEvent getCurrentEvent()
{
	if(PIND & 0x40){
		return D7_EVENT;
	}else if(PIND & 0x20){
		return D6_EVENT;
	}else if(PIND & 0x10){
		return D5_EVENT;
	}else{
		return NULL;
	}
	
}

//Initialiseerd de state die is meegegeven door de actie uit te voeren die bij het initialeseren van deze state hoort
void init(systemState state)
{
	switch(state)
	{
		case START_STATE:
			PORTC = 0x80;
			break;
		case S1_STATE:
			PORTC  = 0x40;
			break;
		case S2_STATE:
			PORTC  = 0x20;
			break;
		case S3_STATE:
			PORTC  = 0x10;
			break;
		case END_STATE:
			PORTC  = 0x08;
			break;
	}
	
}

//Sluit de meegegeven state af door de actie uit te voeren die bij het afsluiten van deze state hoort
void exitState(systemState state)
{
	switch(state)
	{
		case START_STATE:
			PORTC  = 0x00;
			break;
		case S1_STATE:
			PORTC  = 0x00;
			break;
		case S2_STATE:
			PORTC  = 0x00;
			break;
		case S3_STATE:
			PORTC  = 0x00;
			break;
		case END_STATE:
			PORTC  = 0x00;
			break;
	}
	
}

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

