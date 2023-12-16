/*
 * Aufgabe_k.c
 *
 * Created: 16.12.2023 09:15:51
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 12000000UL
#define PWM_PIN PB3
#define S0_PIN PA0
#define S1_PIN PA1

volatile uint8_t rampFlag = 0;
volatile uint8_t rampValue = 0;

void init()
{
	DDRB |= (1 << PWM_PIN);
	
	DDRA &= ~((1 << S0_PIN) | (1 << S1_PIN));
	PORTA |= (1 << S0_PIN) | (1 << S1_PIN);

	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	TCCR0 |= (1 << COM01);
	TCCR0 |= (1 << CS00);

	OCR0 = 57;

	TIMSK |= (1 << OCIE0);
	sei();
}

ISR(TIMER0_COMP_vect)
{
	OCR0++;
}

int main(void)
{
	init();

	while (1)
	{

	}
}

