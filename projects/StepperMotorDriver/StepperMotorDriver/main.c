/*
 * StepperMotorDriver.c
 *
 * Created: 21.10.2023 11:12:09
 * Author : Adrian
 */ 
#define F_CPU 12000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

#define IC1_IN0 (1 << PB0) // Orange
#define IC1_PHASE (1 << PB1) // Schwarz
#define IC1_IN1 (1 << PB2) // grau
#define IC2_IN1 (1 << PB4) // gelb
#define IC2_PHASE (1 << PB5) // rot
#define IC2_IN0 (1 << PB6) // grau

void outportbyte(uint8_t portValue) 
{
	PORTB = portValue;
}

void initPorts()
{
	// Konfiguriere Pins am Port B als Ausgänge
	DDRB |= (IC1_IN0 | IC1_PHASE | IC1_IN1 | IC2_IN0 | IC2_PHASE | IC2_IN1);
}

int main(void)
{
	initPorts();
	
	while(1)
	{
		//int i = 0;
		//i++;
		
		for (int i = 1; i <= 10; i++)
		{
			outportbyte(80);
			_delay_ms(30 - i);

			outportbyte(05);
			_delay_ms(30 - i);

			outportbyte(82);
			_delay_ms(30 - i);

			outportbyte(37);
			_delay_ms(30 - i);
		}
	}
}

