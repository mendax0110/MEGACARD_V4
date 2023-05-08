// led_patterns.c
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int pattern = 1;
int direction = 1;

void led_pattern_1()
{
	for(int i=0; i<8; i++)
	{
		PORTC |= (1<<i);   // turn on pin i
		_delay_ms(100);     // delay for 100ms
		PORTC &= ~(1<<i);  // turn off pin i
	}
}

void led_pattern_2()
{
	for(int i=7; i>=0; i--)
	{
		PORTC |= (1<<i);   // turn on pin i
		_delay_ms(100);     // delay for 100ms
		PORTC &= ~(1<<i);  // turn off pin i
	}
}

void led_pattern_3()
{
	for(int i=0; i<4; i++)
	{
		PORTC |= (1<<i);   // turn on pin i
		PORTC |= (1<<(7-i));   // turn on pin (7-i)
		_delay_ms(100);     // delay for 100ms
		PORTC &= ~(1<<i);  // turn off pin i
		PORTC &= ~(1<<(7-i));  // turn off pin (7-i)
	}
}