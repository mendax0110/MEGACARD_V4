/*
 * Matura_I2C_Slave.c
 *
 * Created: 07.08.2025 21:34:59
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

#define SLAVE_ADDR 0x20

void init_ports(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;
}

void TWI_slave_init(uint8_t address)
{
	TWAR = address << 1; // 7 bit addresse
	TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT); // TWI aktiv, ACK aktiv
}

uint8_t TWI_slave_receive(void)
{
	while (!(TWCR & (1 << TWINT))); // warten auf daten
	if ((TWSR & 0xF8) != 0x60 && (TWSR & 0xF8) != 0x80) return 0;
	
	uint8_t data = TWDR;
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT); // für nächste übertragung vorbereiten
	return data;
}

int main(void)
{
	PORTC |= (1 << PC0) | (1 << PC1);
		
	TWI_slave_init(SLAVE_ADDR);
	
	init_ports();
	
    while (1) 
    {
		uint8_t value = TWI_slave_receive();
		PORTC = value;
		_delay_ms(200);
		PORTC = 0x00;
		_delay_ms(200);
    }
}

