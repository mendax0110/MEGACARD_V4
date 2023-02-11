/*
 * GCPInterrupt.c
 *
 * Created: 11.02.2023 13:03:23
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// quarz frequency

#include <avr/io.h>			// std avr lib input output
#include <avr/interrupt.h>	// std interrupt avr lib
#include <util/delay.h>		// delay lib

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

const uint8_t keypad_matrix[KEYPAD_ROWS][KEYPAD_COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

ISR(INT1_vect) {
	_delay_ms(10);
	uint8_t column = PINA & 0x0F;
	for (uint8_t i = 0; i < KEYPAD_COLS; i++) 
	{
		if (column & (1 << i)) 
		{
			for (uint8_t j = 0; j < KEYPAD_ROWS; j++) 
			{
				if (PINC & (1 << j)) 
				{
					char key = keypad_matrix[j][i];
					break;
				}
			}
			break;
		}
	}
}

void init_keypad() {
	DDRD &= ~(1 << PD3);
	PORTD |= (1 << PD3);
	DDRA &= ~(0x0F);
	PORTA |= (0x0F);
	DDRC |= (0x0F);
	PORTC &= ~(0x0F);
}

int main(void) {
	init_keypad();
	GICR |= (1 << INT1);
	MCUCR |= (1 << ISC11);
	sei();
	while (1) 
	{
		// ?
	}
}