/*
 * TestUebung2FastPWM.c
 *
 * Created: 19.05.2023 12:22:31
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;
volatile uint8_t timer = 0;

void init_Ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC0);	// Indicator LED init ports
	
	DDRB |= (1 << PB3);		// signal on PB3
	PORTB &= ~(1 << PB3);	
}

void init_Fast_PWM()
{
	TCCR0 |= (1 << WGM00)|(1 << COM01)|(1 << WGM01)|(1 << CS01)|(1 < CS00);	// non inverting mode
	
	while(1)
	{
		for(timer = 0; timer <= 10; timer++)
		{
			_delay_ms(1000);
			PORTC ^= (1 << PC1);
			OCR0Var = 150;
		}
		
		OCR0 = OCR0Var;
		_delay_ms(5000);
		
		for(timer = 0; timer <= 10; timer++)
		{
			_delay_ms(1000);
			PORTC ^= (1 << PC2);
			OCR0Var = 50;
		}
		
		OCR0 = OCR0Var;
		_delay_ms(5000);
	}
}

int main(void)
{
    cli();
	init_Ports();
	init_Fast_PWM();
	sei();
	
    while (1) 
    {
    }
}

