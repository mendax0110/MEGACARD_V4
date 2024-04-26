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

void initUart()
{
	
}

int main(void)
{
	UBRRH = 0x00;	// define Baudrate	-> https://wormfood.net/avrbaudcalc.php
	UBRRL = 0x4D;
	UCSRB |= (1 << TXEN)|(1 << RXEN);	// transmission and recevive activate
	UCSRC |= (1 << UCSZ1)|(1 << UCSZ0);	// parity displayed, Asynchroner Mode 8 Datenbits pro Packet
										// Anzahl der Stopbits = 1 -> 8N1 - 8 Datenbits, NoParity, 1 Stopbit
	
	// Recevier bzw. Tranmitter aktivieren
	// Protokoll definieren
	initPorts();
    while (1) 
    {
		while (!(UCSRA & (1 << UDRE)))	// UDRE = 1 sobald die Übertragung fertig ist
		{
			UDR = 'A';
		}
    }
}