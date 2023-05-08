/*
 * PWMFrequency.c
 *
 * Created: 06.05.2023 11:10:15
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

#include "ledPatterns/ledPatterns.h"
#include "ledControl/ledControl.h"
#include "InitFunctions/InitFunctions.h"

ISR(TIMER0_COMP_vect)
{
	// empty
}

int main(void)
{	
	cli();    // disable global interrupts
	
	init_ports(); // call the InitFunctions
	init_timer0_pwm();
	sei();    // enable global interrupts

	int pattern = 1;
	int direction = 1;

	while (1)
	{
		change_pattern(&pattern, &direction);
		
		switch (pattern)
		{
			case 1:
				led_pattern_1();
				break;
			case 2:
				led_pattern_2();
				break;
			case 3:
				led_pattern_3();
				break;
			default:
			// invalid pattern number
				break;
		}
	}
}