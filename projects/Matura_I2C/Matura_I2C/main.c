/*
 * Matura_I2C.c
 *
 * Created: 07.08.2025 21:34:34
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

#define F_SCL 100000UL
#define TWBR_VAL (((F_CPU/F_SCL)-16)/2)
#define SLAVE_ADDR 0x20

void init_ports(void)
{
	DDRC = 0xFF;
	PORTC |= (1 << PC4);
}

void TWI_init(void)
{
	TWBR = (uint8_t)TWBR_VAL;
}

void TWI_start(void)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void TWI_stop(void)
{
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	_delay_ms(1);
}

void TWI_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

int main(void)
{
	init_ports();
	TWI_init();
	
	uint8_t data[] = { 0xAA, 0x55, 0xF0, 0x0F };
	uint8_t i = 0;
	
    while (1) 
    {
		TWI_start();
		TWI_write(SLAVE_ADDR << 1);
		TWI_write(data[i]);
		TWI_stop();
		
		i = (i + 1) % 4;
		_delay_ms(1000);
    }
}

