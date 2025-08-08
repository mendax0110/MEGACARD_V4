/*
 * Matura_SPI.c
 *
 * Created: 07.08.2025 20:56:51
 * Author : Adrian
 */
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void init_ports()
{
	DDRB |= (1 << PB5) | (1 << PB7); // MOSI und SCK als Ausgang setzen
	DDRB &= ~(1 << PB7); // MISO als Eingang
	
	DDRD |= (1 << PD7); // SS - softwaregesteuert slave select
	PORTD |= (1 << PD7); // SS aus High setzen (inaktiv)
	
	DDRC = 0xFF; // portd als ausgang für LED's
	PORTC = (1 << PC3); // Indicator LED setzen
}

void init_SPI_master()
{
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // SPI als Master aktivieren
	SPSR |= (1 << SPI2X); // setzten von double-speed
}

void SPI_send(uint8_t data)
{
	PORTD &= ~(1 << PD7); // SS auf low setzen -> aktiviere den slave
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	PORTD |= (1 << PD7); // SS wieder auf HIGH setzen
}

int main(void)
{
	init_ports();
	init_SPI_master();
	
	uint8_t pattern[] = { 0xAA, 0x55, 0xF0, 0x0F, 0xFF, 0x00 };
	uint8_t i = 0;
	
	while (1)
	{
		SPI_send(pattern[i]);
		i = (i + 1) % 6;
		_delay_ms(1000);
	}
}