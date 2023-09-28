/*
 * 4H.c
 *
 * Created: 21.09.2023 09:39:59
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

const uint8_t matrixPattern[5] = {
	0b00111100,
	0b01000010,
	0b10011001,
	0b10000001,
	0b10011001,
};

void initPorts() 
{
	DDRC = 0xFF;
}

void displayMatrixPattern(const uint8_t *pattern) 
{
	for (int i = 0; i < 5; i++) 
	{
		PORTC = pattern[i];
		_delay_ms(500);
	}
}

int main(void) 
{
	initPorts();

	while (1) 
	{
		displayMatrixPattern(matrixPattern);
		_delay_ms(2000);
	}
}

