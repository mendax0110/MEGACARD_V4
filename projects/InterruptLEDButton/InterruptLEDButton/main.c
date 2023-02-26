/*
 * InterruptLEDButton.c
 *
 * Created: 26.02.2023 08:44:17
 * Author : Adrian
 */ 
#define F_CPU 12000000UL // Frequency of quarz

#include <avr/io.h>			// Standard AVR library
#include <util/delay.h>		// Standard delay library
#include <avr/portpins.h>	// Standard portpin library
#include <avr/interrupt.h>	// Standard AVR interrupt library

// Define the LED pins
#define LED_1 PC0
#define LED_2 PC1
#define LED_3 PC2
#define LED_4 PC3

// Define the button pin
#define BUTTON PD3

// Define the delay between LED toggles
#define DELAY_MS 500

volatile uint8_t led_counter = 0;		// Counter to keep track of which LED to toggle
volatile uint8_t button_pressed = 0;	// Flag to indicate if the button has been pressed

ISR(INT1_vect)
{
	// Check if the button is pressed
	if(!(PIND & (1 << BUTTON)))
	{
		button_pressed = 1;
	}
}

void init_interrupt()
{
	// Enable interrupt 1 and set it to trigger on faling edge
	GICR |= (1 << INT1);
	MCUCR |= (1 << ISC11);
	
	// Enable global interrupts
	sei();
}

void init_ports()
{
	// Set the LED pins as outputs
	DDRC |= (1 << LED_1)|(1 << LED_2)|(1 << LED_3)|(1 << LED_4);
	
	// Set the button pin as input and enable the internal pull-up resistor
	DDRD &= ~(1 << BUTTON);
	PORTD |= (1 << BUTTON);
}

int main(void)
{
	init_ports();
	init_interrupt();
	
	while(1)
	{
		// If the button has been pressed, toggle the next LED and reset the flag
		if(button_pressed)
		{
			led_counter++;
			
			if(led_counter > 3)
			{
				led_counter = 0;
			}
			
			button_pressed = 0;
		}
		
		// Toggle the LED based on the current value of the counter
		switch(led_counter)
		{
			case 0: 
				PORTC ^= (1 << LED_1);
				break;
			case 1:
				PORTC ^= (1 << LED_2);
				break;
			case 2:
				PORTC ^= (1 << LED_3);
				break;
			case 3:
				PORTC ^= (1 << LED_4);
				break;
		}
		
		// Delay for a short period
		_delay_ms(DELAY_MS);
	}
}