/*
 * ExampleForTest.c
 *
 * Created: 21.12.2022 18:33:59
 * Author : Adrian
 */ 
#define  F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK 500

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0x0F;
	
	_delay_ms(BLINK);
	
	PORTC |= 0xF0;	// OR-Gatter
	
	_delay_ms(BLINK);
	
	PORTC &= 0b10101010;	// AND-Gatter
	
	_delay_ms(BLINK);
	
	PORTC ^= 0b01010101;	// EXOR-Gatter
	
	_delay_ms(BLINK);
	
	PORTC =~ PORTC;			// Inverter
	
	_delay_ms(BLINK);
	
	PORTC =~(PORTC & 0b0101010101);	// NAND-Gatter
	
	_delay_ms(BLINK);
	
	PORTC =~(PORTC|0b11111111);		// NOR-Gatter
	
	_delay_ms(BLINK);
	
	
	while(1)
	{
	}
}

