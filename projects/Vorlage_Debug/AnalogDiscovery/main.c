/*
 * AnalogDiscovery.c
 *
 * Created: 14.12.2023 08:16:34
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/portpins.h>

void InitPorts()
{
	DDRC = 0xFF;
}

int main(void)
{
	InitPorts();
	
	uint8_t counter = 0;

	while(1)
	{
		counter++;

		PORTC = counter;

		_delay_ms(500);
		
		if (counter == 255)
		{
			counter = 0;
		}
	}
}


