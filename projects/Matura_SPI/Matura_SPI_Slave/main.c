/*
 * Matura_SPI_Slave.c
 *
 * Created: 07.08.2025 21:18:54
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void init_ports()
{
	DDRC = 0xFF;	// PORTC als ausgang für LED muster
	PORTC = 0x00;
	
	DDRB &= ~((1 << PB5) | (1 << PB7)); //MOSI und SCK als Eingang
	DDRB |= (1 << PB6);	// MISO als ausgang
	DDRB &= ~(1 << PB4); // SS als eingang
	
	PORTB |= (1 << PB4); // Pull up an PB4
}

void init_SPI_slave()
{
	SPCR = (1 << SPE);	// SPI aktivieren, Slave-modus
}

uint8_t SPI_receive()
{
	while (!(SPSR & (1 << SPIF))); // wir warten bis Übertragung abgeschlossen
	return SPDR;
}

int main(void)
{
    init_ports();
	init_SPI_slave();
	
	uint8_t receivedData = 0;
	
    while (1) 
    {
		receivedData = SPI_receive(); // warten auf Daten vom Master
		
		PORTC = receivedData; // setzen des blinkmusters
		_delay_ms(200);
		PORTC = 0x00;
		_delay_ms(200);
    }
}

