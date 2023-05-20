/*
 * TestUebung3FastPWM.c
 *
 * Created: 20.05.2023 13:25:58
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;

void init_Ports()
{
	DDRC = 0xFF;
	PORTC ^= (1 << PC7);	// indicator led init ports
	
	DDRB |= (1 << PB3);		// output for signal
	PORTB &= ~(1 << PB3);
	
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_fast_PMW()
{
	TCCR0 |= (1 << WGM00)|(1 << COM01)|(1 << WGM01)|(1 << CS01)|(1 << CS00);
	
	OCR0 = OCR0Var;
}

int main(void)
{
	cli();
	init_Ports();
	
	while(1)
	{
		if((PINA & (1 << PA0)) == 0)
		{
			for(OCR0Var = 0; OCR0Var <= 150; OCR0Var++)
			{
				_delay_ms(10);
				PORTC ^= (1 << PC6);
				_delay_ms(10);
				PORTC ^= (1 << PC5);
				_delay_ms(10);
				PORTC ^= (1 << PC4);
				_delay_ms(10);
				PORTC ^= (1 << PC3);
				_delay_ms(10);
				PORTC ^= (1 << PC2);
				_delay_ms(10);
				PORTC ^= (1 << PC1);
				_delay_ms(10);
				PORTC ^= (1 << PC0);
				_delay_ms(10);
			}
		}
		else if((PINA & (1 << PA1)) == 0)
		{
			for(OCR0Var = 0; OCR0Var <= 150; OCR0Var--)
			{
				_delay_ms(10);
				PORTC ^= (1 << PC0);
				_delay_ms(10);
				PORTC ^= (1 << PC1);
				_delay_ms(10);
				PORTC ^= (1 << PC2);
				_delay_ms(10);
				PORTC ^= (1 << PC3);
				_delay_ms(10);
				PORTC ^= (1 << PC4);
				_delay_ms(10);
				PORTC ^= (1 << PC5);
				_delay_ms(10);
				PORTC ^= (1 << PC6);
				_delay_ms(10);
			}
			
			OCR0Var = 50;
		}
		
		
		init_fast_PMW();
		sei();
	}
}