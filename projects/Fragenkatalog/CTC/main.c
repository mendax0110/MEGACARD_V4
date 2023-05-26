#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 149;

ISR(TIMER0_COMP_vect)
{
	PORTC ^= (1 << PC7);	// indicator LED
	OCR0 = OCR0Var;
	// OCR = (F_CPU/(2*64*F_OUT)-1 =
	// F_OUT = (F_CPU/(2*64*OCR) -1 =
}

void init_Ports()
{
	DDRC = 0xFF;
	PORTC ^= (1 << PC6);	// indicator LED
	
	DDRB |= (1 << PB3);		// output signal
	
	// for LED 
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_Timer0_CTC()
{
	PORTC ^= (1 << PC5);	// indicator LED
	
	TCCR0 |= (1 << WGM01)|(1 << COM00)|(1 << CS00)|(1 << CS01); // vorteiler 64
	
	OCR0 = OCR0Var;
	TCNT0 = 0;
	
	TIMSK |= (1 << OCIE0);	// register
}

int main(void)
{
	cli();
	init_Ports();
	init_Timer0_CTC();
	sei();
	
	while(1)
	{
		if((PINA & (1 << PA0)) == 0)
		{
			PORTC ^= (1 << PC0);
			OCR0Var = 78;
			_delay_ms(100);
		}
		else if((PINA & (1 << PA1)) == 0)
		{
			PORTC ^= (1 << PC1);
			OCR0Var = 50;
			_delay_ms(100);
		}
	}
}