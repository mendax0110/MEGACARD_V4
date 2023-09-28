/*
 * 4J.c
 *
 * Created: 21.09.2023 10:43:54
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void initPorts()
{
	DDRC = 0xFF;
}

int main(void)
{
	initPorts();
	uint8_t pattern = 0x01;
	uint8_t direction = 1;

	while (1)
	{
		if (direction)
		{
			// move the LED pattern forward
			pattern <<= 1;

			if (pattern == 0x00)
			pattern = 0x01;
		}
		else
		{
			// move the LED pattern backward
			pattern >>= 1;

			if (pattern == 0x00)
			pattern = 0x80;
		}

		// show the LED pattern
		PORTC = pattern;
		_delay_ms(166); // Wait for 166 ms 3Hz

		// if pattern reaches end, change direction
		if (pattern == 0x01 || pattern == 0x80)
		{
			direction = !direction; // Toggle direction
		}
	}
}


