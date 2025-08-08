/*
 * Matura_PWM_Helligkeit_Fast.c
 *
 * Created: 05.08.2025 12:03:03
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/portpins.h>

volatile uint8_t pwm_value = 128;

void init_ports()
{
	DDRB |= (1 << PB3); // ausgang PWM signal
	DDRA &= ~((1 << PA0) | (1 << PA1));
	PORTA |= (1 << PA0) | (1 << PA1);
}

void init_PWM()
{
	// Fast PWM, Non-Inverting, VT 64
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01) | (1 << CS00);
	OCR0 = pwm_value;
}

int main(void)
{
    init_ports();
	init_PWM();
	
    while (1) 
    {
		if (!(PINA & (1 << PA0)))
		{
			_delay_ms(20);
			if (pwm_value < 255)
				pwm_value += 5;
			while(!(PINA & (1 << PA0)));
			OCR0 = pwm_value;
		}
		
		if (!(PINA & (1 << PA1)))
		{
			_delay_ms(20);
			if (pwm_value > 0)
				pwm_value -= 5;
			while (!(PINA & (1 << PA1)));
			OCR0 = pwm_value;
		}
    }
}

