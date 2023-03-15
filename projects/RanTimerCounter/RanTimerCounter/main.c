/*
 * RanTimerCounter.c
 *
 * Created: 15.03.2023 17:49:52
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

// define LED pins
#define LED1_PIN PB0
#define LED2_PIN PB1

volatile uint8_t timer1_overflow_count = 0;

ISR(TIMER1_OVF_vect)
{
	timer1_overflow_count++;
}

void init_timer1()
{
	TCCR1B |= (1 << CS10); // start timer, no prescaler
	TIMSK |= (1 << TOIE1); // enable timer overflow interrupt
	sei(); // enable global interrupts
}

int main(void)
{
	DDRB |= (1 << LED1_PIN) | (1 << LED2_PIN); // set LED pins as output
	init_timer1(); // initialize Timer1

	while (1)
	{
		if (timer1_overflow_count >= 5)
		{
			// turn off both LEDs
			PORTB &= ~(1 << LED1_PIN);
			PORTB &= ~(1 << LED2_PIN);

			// wait for 1 second
			_delay_ms(1000);

			// turn on a random LED
			if (rand() % 2 == 0)
			{
				PORTB |= (1 << LED1_PIN);
			}
			else
			{
				PORTB |= (1 << LED2_PIN);
			}

			// reset overflow count
			timer1_overflow_count = 0;
		}
	}
}
