/*
 * TimerCounter1.c
 *
 * Created: 06.03.2023 18:52:33
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

#define TASTER1 PA0
#define TASTER2 PA1
#define T_PRELL 20

int main(void)
{
	// configure ports
	DDRA &= ~(1<<TASTER1); // input
	DDRA &= ~(1<<TASTER2); // input
	PORTA |= (1<<TASTER1)|(1<<TASTER2); // pull-up
	DDRC |= 0xFF; // output
	PORTC |= 0x01; // LED on

	// init timer and counter
	uint8_t counter = 0;
	uint16_t timer = 0;

	while(1)
	{
		if(!(PINA & (1 << TASTER1)))
		{
			_delay_ms(T_PRELL);

			while(!(PINA & (1 << TASTER1)))
			_delay_ms(T_PRELL);

			counter++;

			if(counter > 7) counter = 7;

			PORTC = (1 << counter);
		}

		if(!(PINA & (1 << TASTER2)))
		{
			_delay_ms(T_PRELL);

			while(!(PINA & (1 << TASTER2)))
			_delay_ms(T_PRELL);

			timer += 100;
		}

		// check timer and blink LED
		if(timer > 100)
		{
			timer = 0;
			PORTC ^= 0xFF;
		}

		_delay_ms(10);
	}

	return 0;
}

