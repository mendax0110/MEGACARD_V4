/*
 * PWMFrequency.c
 *
 * Created: 06.05.2023 11:10:15
 * Author : Adrian
 */ 
#define F_CPU 12000000UL   // define the CPU frequency as 12 MHz

#include <avr/io.h>   // include AVR input/output definitions
#include <avr/interrupt.h>   // include AVR interrupt definitions
#include <avr/portpins.h>   // include AVR port pin definitions

#include "ledPatterns/ledPatterns.h"   // include the header file for LED patterns
#include "ledControl/ledControl.h"   // include the header file for LED control
#include "InitFunctions/InitFunctions.h"   // include the header file for initialization functions

ISR(TIMER0_COMP_vect)
{
	// Interrupt Service Routine for the TIMER0 compare vector
	// empty implementation
}

int main(void)
{
	cli();   // disable global interrupts
	
	init_ports();   // initialize ports using the InitFunctions
	init_timer0_pwm();   // initialize timer0 for PWM
	sei();   // enable global interrupts

	int pattern = 1;   // variable to hold current pattern number
	int direction = 1;   // variable to hold current direction of pattern

	while (1)
	{
		change_pattern(&pattern, &direction);   // change the pattern and direction based on button input
		
		switch (pattern)
		{
			case 1:
			led_pattern_1();   // display LED pattern 1
			break;
			case 2:
			led_pattern_2();   // display LED pattern 2
			break;
			case 3:
			led_pattern_3();   // display LED pattern 3
			break;
			default:
			// invalid pattern number, do nothing
			break;
		}
	}
}