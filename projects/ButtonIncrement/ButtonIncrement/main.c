/*
 * ButtonIncrement.c
 *
 * Created: 21.12.2022 19:00:35
 * Author : Adrian
 */ 
#define  F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK 500

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;
	
	DDRA = 0x00;
	PORTA = 0xFF;
	
	while(1)
	{
		if(!(PINA & 0x01))
		{
			PORTC++;
			_delay_ms(BLINK);
		}
		if(!(PINA & 0x02))
		{
			PORTC--;
			_delay_ms(BLINK);
		}
	}
}

