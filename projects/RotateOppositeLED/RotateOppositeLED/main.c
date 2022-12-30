/*
 * RotateOppositeLED.c
 *
 * Created: 30.12.2022 13:19:09
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#define TASTER PA0
#define	T_PRELL	20 // debounce time for button in ms

int main(void)
{
	DDRA = 0x00;	// button port: input
	PORTA = 0x0F;	// enable pull-ups for buttons S0, S1, S2, S3
	DDRC = 0xFF;	// LED port: output
	PORTC = 0x01;	// turn on LED0, turn off LED1..7
	
	while(1)
	{
		if(!(PINA & (1 << TASTER)))
		{
			// button Sx is pressed
			PORTC = (PORTC >> 1) | (PORTC << 7);	// rotate LED status on bit to the right
			_delay_ms(T_PRELL);	// debounce for button closing
			
			while(!(PINA & (1 << TASTER)));	// wait while button Sx is pressed
			_delay_ms(T_PRELL);	// debounce for button opening
		}
		else
		{
			// button Sx is not pressed, hold current LED pattern
			_delay_ms(100);	// delay for 100ms
		}
	}
}