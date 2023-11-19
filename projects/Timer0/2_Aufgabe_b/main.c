/*
 * 2_Aufgabe_b.c
 *
 * Created: 16.11.2023 09:10:42
 * Author : Adrian
 */ 
#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int c = 0;
volatile int Ton = 150;

ISR(TIMER0_COMP_vect)  // fISR=100KHz
{
	c++;  // LED PC0 toggle-Mode
}

void init()
{
	DDRC |= 0xFF;
	PORTC = 0x01;
	DDRA &= 0xF0;       // Taster
	PORTA |= 0x0F;      // Pullup

	TCCR0 |= (1 << WGM01) | (1 << COM00) | (1 << CS00);
	TCCR0 &= ~(1 << WGM00);  // CTC-Mode
	TIMSK |= (1 << OCIE0);   // Overflow Interrupt Enable
	OCR0 = 119;              // Output Compare Register 12MHz/100KHz --> 120 Takte
}

int main(void)
{
	cli();
	init();
	sei();
	while (1)
	{
		if ((PINA & 0x01) == 0)
		{      
			if ((PINA & 0x01) == 0)
			{
				Ton = 100;  // Set TH (Ton) to 1ms
			}
		}

		if ((PINA & 0x02) == 0)
		{
			if ((PINA & 0x02) == 0)
			{
				Ton = 200;  // Set TH (Ton) to 2ms
			}
		}

		if (c == 0)
		{
			PORTC = 0x01;
		}
		if (c == Ton)
		{
			PORTC = 0x00;
		}
		if (c == 2000)
		{
			PORTC = 0x01;
			c = 0;
		}
	}
	return 0;
}


