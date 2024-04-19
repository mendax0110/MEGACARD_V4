/*
 * 1_Simple_Transmit.c
 *
 * Created: 19.04.2024 16:01:51
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/portpins.h>

void initPorts()
{
	DDRD |= (1 << PD1);		// TxD - Transmit -> Ausgang
	DDRD &= ~(1 << PD0);	// RxD - Recevice -> Eingang
}

int main(void)
{
	UBRRH = 0;	// define Baudrate	-> https://wormfood.net/avrbaudcalc.php
	UBRRL = 0;
	// Recevier bzw. Tranmitter aktivieren
	// Protokoll definieren
	initPorts();
    while (1) 
    {
    }
}

