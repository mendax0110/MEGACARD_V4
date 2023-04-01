/*
 * Sinewave.c
 *
 * Created: 01.04.2023 17:27:57
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include <math.h>

#define SAMPLE_RATE 40000
#define PRESCALER 64
#define TOP (F_CPU / SAMPLE_RATE / PRESCALER - 1)
#define PI 3.14159265358979323846

ISR(TIMER0_COMP_vect) 
{
	static uint16_t phase_accumulator = 0;
	static uint8_t output = 0;

	phase_accumulator += (uint16_t)(65536.0 * PI * 2.0 / SAMPLE_RATE);
	output = (uint8_t)(128 + 127.0 * sin(phase_accumulator * 2 * PI / 65536.0));

	OCR0 = output;
}

void init_timer0() 
{
	TCCR0 = (1 << WGM01)|(1 << WGM00)|(1 << COM01)|(1 << CS01)|(1 << CS00);
	OCR0 = 0;
	TIMSK = (1 << OCIE0);
	OCR0 = TOP;
}

void init_ports() 
{
	DDRB |= (1 << PB3);
}

int main(void) 
{
	cli();
	init_ports();
	init_timer0();
	sei();

	while (1) 
	{
		_delay_ms(100);
	}
}

