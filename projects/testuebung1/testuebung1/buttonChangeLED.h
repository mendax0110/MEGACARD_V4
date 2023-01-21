#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	DDRC = 0b11111111;
	PORTC = 0b00000000;
	
	char keyboard_in;
	
	
	if(keyboard_in = PINA)
	{
		PORTC = PORTA | 0b00001111;
		_delay_ms(1000);
		PORTC = PORTA & 0b00000000;

		PORTC = PORTA | 0b11110000;
		_delay_ms(1000);
		PORTC = PORTA & 0b00000000;
	}
}