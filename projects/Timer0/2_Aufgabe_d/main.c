#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int c = 0;
volatile int Ton = 0;
volatile int s2_pressed = 0;
volatile int s3_pressed = 0;

ISR(TIMER0_COMP_vect)
{
	c++; // LED PC0 toggle-Mode

	if (c == 2000)
	{
		PORTC = 0x01;
		c = 0;
	}

	if (c == Ton)
	{
		PORTC = 0x00;
	}
}

void init()
{
	DDRC |= 0xFF;
	PORTC = 0x01;
	DDRA &= 0xF0;       // Taster
	PORTA |= 0x0F;      // Pullup

	// for S2and S
	DDRA &= ~((1 << PA2) | (1 << PA3));
	PORTA |= ((1 << PA2) | (1 << PA3));

	TCCR0 |= (1 << WGM01) | (1 << COM00) | (1 << CS00);
	TCCR0 &= ~(1 << WGM00); // CTC-Mode
	TIMSK |= (1 << OCIE0);  // Overflow Interrupt Enable
	OCR0 = 119;             // Output Compare Register 12MHz/100KHz --> 120 Takte
}

int main(void)
{
	cli();
	init();
	sei();
	while (1)
	{
		if ((PINA & (1 << PA2)) == 0)
		{
			_delay_ms(20);
			if ((PINA & (1 << PA2)) == 0)
			{
				s2_pressed = 1;
				while ((PINA & (1 << PA2)) == 0)
				{
					
				}
				_delay_ms(20);
			}
		}
		else
		{
			s2_pressed = 0;
		}

		if ((PINA & (1 << PA3)) == 0)
		{
			_delay_ms(20);
			if ((PINA & (1 << PA3)) == 0)
			{
				s3_pressed = 1;
				while ((PINA & (1 << PA3)) == 0)
				{
					
				}
				_delay_ms(20);
			}
		}
		else
		{
			s3_pressed = 0;
		}

		if (s2_pressed && Ton < 200)
		{
			Ton += 10; // Increase Ton by 10us (max. 2ms)
		}

		if (s3_pressed && Ton > 100)
		{
			Ton -= 10; // Decrease Ton by 10us (min. 1ms)
		}

		_delay_ms(20); // Adjustments every 20ms
	}
}
