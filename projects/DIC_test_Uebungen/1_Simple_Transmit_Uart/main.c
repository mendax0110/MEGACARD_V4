/*
 * 1_Simple_Transmit_Uart.c
 *
 * Created: 11.05.2024 10:02:03
 * Author : Adrian
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/portpins.h>

#include "bluetooth.h"

void initPorts()
{
	DDRD |= (1 << PD1);		// TxD - Transmit -> Output
	DDRD &= ~(1 << PD0);	// RxD - Recevice -> Input
}

void initUart()
{
	UBRRH = 0x00;	// define Baudrate -> https://wormfood.net/avrbaudcalc.php
	UBRRL = 0x4D;
	UCSRB |= (1 << TXEN)|(1 << RXEN);	// Activate Transmission and Recevice
	UCSRC |= (1 << UCSZ1)|(1 << UCSZ0);	// Parity Disabled, Async Mode 8 Databits per packet
}


int main(void)
{
	initPorts();
	initUart();
	bt_init(9600);	// define Baudrate
	
    while (1) 
    {
		while(!(UCSRA & (1 << UDRE)))	// UDRE = 1 if the transmission is finished
		{
			UDR = 'A';	// or UDR = 65
		}
    }
}

