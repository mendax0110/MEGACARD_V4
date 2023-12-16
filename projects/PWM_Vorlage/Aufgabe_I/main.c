/*
 * Aufgabe_I.c
 *
 * Created: 16.12.2023 08:43:41
 * Author : Adrian
 */ 
/*
 * Aufgabe_I.c
 *
 * Created: 16.12.2023 08:43:41
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 12000000UL
#define PWM_PIN PB3
#define S2_PIN PA2
#define S3_PIN PA3

volatile uint8_t OCR0_value = 127;
volatile uint8_t timer_count = 0;

void init()
{
	DDRB |= (1 << PWM_PIN);
	DDRA &= ~((1 << S2_PIN) | (1 << S3_PIN));
	PORTA |= (1 << S2_PIN) | (1 << S3_PIN);

	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	TCCR0 |= (1 << COM01);
	TCCR0 |= (1 << CS00);

	OCR0 = OCR0_value;

	TCCR1B |= (1 << CS10) | (1 << WGM12);
	OCR1A = 1199;
	TIMSK |= (1 << OCIE1A);
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	timer_count++;
	
	if (timer_count >= 50)
	{
		timer_count = 0;
		if (!(PINA & (1 << S2_PIN)) && OCR0_value < 255)
		{
			OCR0_value++;
		}
		else if (!(PINA & (1 << S3_PIN)) && OCR0_value > 0)
		{
			OCR0_value--;
		}
	}
}

int main(void)
{
	init();

	while (1)
	{
		OCR0 = OCR0_value;
	}
} 
