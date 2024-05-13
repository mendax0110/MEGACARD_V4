/*
 * Tryout3.c
 *
 * Created: 12.05.2024 11:34:59
 * Author : Adrian
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

#include "bluetooth.h"

void initPorts()
{
	DDRD |= (1 << PD1);		// TxD - Transmit -> Output
	DDRD &= ~(1 << PD0);	// RxD - Receive -> Input
}

void initUart()
{
	UBRRH = 0x00;	// Define Baudrate -> https://wormfood.net/avrbaudcalc.php
	UBRRL = 0x4D;
	UCSRB |= (1 << TXEN)|(1 << RXEN);	// Activate Transmission and Receivce
	UCSRC |= (1 << UCSZ1)|(1 << UCSZ0);	// Parity Bit Disabled, Async Mode 8 Databits per packet
}

int main(void)
{
	initPorts();
	initUart();
	bt_init(9600);	// define Baudate with Library Method
	
	while(1)
	{
		while(!(UCSRA & (1 << UDRE)))	// UDRE = 1 if the transmission is finished
		{
			UDR = 'A';	// or UDR = 65;
		}
	}
}