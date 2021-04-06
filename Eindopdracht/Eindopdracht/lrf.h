/*
 * lrf.h
 *
 * Created: 24-3-2021 14:09:45
 *  Author: timoj
 */ 
#ifndef LRF_H
#define LRF_H

#define BAUD 9600
#define FOSC 8000000 // Clock Speed
#define MYUBRR FOSC/16/BAUD-1

#define SINGLE_RANGE_COMMAND_A 'R'
#define SINGLE_RANGE_COMMAND_B 'A'

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Receive_String(char* data);
int USART_onlyNumbers(char* data);

#endif
