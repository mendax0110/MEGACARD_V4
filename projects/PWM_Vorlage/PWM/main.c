/*
 * pwm.c
 *
 * Created: 03.10.2013 10:12:55
 *  Author: 
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 12000000UL
#define PWM_PIN PB3
#define S0_PIN PA0
#define S1_PIN PA1

void init()
{
	DDRB |= (1 << PWM_PIN);

	DDRA &= ~((1 << S0_PIN) | (1 << S1_PIN));
	PORTA |= (1 << S0_PIN) | (1 << S1_PIN);

	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	TCCR0 |= (1 << COM01);
	TCCR0 |= (1 << CS00);

	OCR0 = (255 * 25) / 100;

	TIMSK |= (1 << OCIE0);
	sei();
}

ISR(TIMER0_COMP_vect)
{
	
}

int main(void)
{
	init();

	while (1)
	{
		if (!(PINA & (1 << S0_PIN)))
		{
			OCR0 = (255 * 2) / 5;
		}
		else if (!(PINA & (1 << S1_PIN)))
		{
			OCR0 = (255 * 4) / 5;
		}
		else
		{
			OCR0 = (255 * 25) / 100;
		}
	}
}
