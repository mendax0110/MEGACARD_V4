/*
 * HealthCheckAVR.c
 *
 * Created: 03.01.2023 14:59:07
 * Author : Adrian
 */ 
#define F_CPU 120000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr)
{
	/*Set baud rate*/
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/*Enable receiver and transmitter*/
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/*Set frame format: 8 data, 2 stop bit*/
	UCSRC = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit(unsigned char data)
{
	/*Wait for empty transmit buffer*/
	while(!(UCSRA & (1<<UDRE)));
	/*Put data into buffer, sends the data*/
	UDR = data;
}

unsigned char USART_Receive(void)
{
	/*Wait for data to be received*/
	while(!(UCSRA & (1<<RXC)));
	/*Get and return received data from buffer*/
	return UDR;
}

int perform_routine_check()
{
	/*Initialize result to 0 (indicating success)*/
	int result = 0;
	
	/*Check the value of the ADC Data Register to make sure the ADC is working properly*/
	if(ADC == 0)
	{
		result = 1;
	}
	
	/*Check the vlaue of the Timer Counter Register to make sure the time is working properly*/
	if(TCNT0 == 0)
	{
		result = 1;
	}
	
	/*Return the result of the check*/
	return result;
}

int main(void)
{
	/*Initialize the USART*/
	USART_Init(MYUBRR);
	
	/*Perform routine check*/
	int check_result = perform_routine_check();
	
	/*Output the result of the check via serial command line*/
	if(check_result == 0)
	{
		USART_Transmit('H');
		USART_Transmit('e');
		USART_Transmit('a');
		USART_Transmit('l');
		USART_Transmit('t');
		USART_Transmit('h');
		USART_Transmit('y');
	}
	else
	{
		 USART_Transmit('E');
		 USART_Transmit('r');
		 USART_Transmit('r');
		 USART_Transmit('o');
		 USART_Transmit('r');
	}
	
	return 0;
}

