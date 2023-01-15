/*
 * AusgabeMaskierung.h
 *
 * Created: 15.01.2023 12:31:06
 *  Author: Adrian
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC |= 0b10000001;
	PORTC|= 0b10000000;
	
	_delay_ms(2000);
	
	PORTC &= ~(0b10000000);
	
	PORTC |= 0b000000001;
	
	while(1)
	{
		
	}
}
 AUSGABEMASKIERUNG_H_ */