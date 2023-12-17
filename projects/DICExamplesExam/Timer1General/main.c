/*
 * Timer1General.c
 *
 * Created: 17.12.2023 11:27:34
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_4.h"

long int ending_edge = 0;
long int starting_edge = 0;
long int clocks = 0;
long int Time = 0;
char displayBuffer[16];

volatile long int Timer1Counter = 0;

ISR(TIMER1_CAPT_vect)
{
	ending_edge = 256 * ICR1H + ICR1L;
	clocks = ending_edge - starting_edge + Timer1Counter * 65535; // Timer in ms (12Mhz/8) -> 1 500 000 / 1500 -> 1000Hz, das entspricht 1 ms
	Time = clocks / 1500;
	Timer1Counter = 0;
	starting_edge = ending_edge;
}

ISR(TIMER0_OVF_vect)
{
	Timer1Counter++;
}

void initPorts()
{
	DDRC |= 0xFF;
	PORTC = 0x00;
	
	DDRA &= ~(1 << PA0)|(1 << PA1);
	PORTA |= (1 << PA0)|(1 << PA1);
}

void initTimer1()
{
	TCCR1A = 0x00;
	TCCR1B |= (1 << ICNC1)|(1 << CS11);
	TIMSK |= (1 << TICIE1)|(1 << TOIE1);
	
}

int main(void)
{
    cli();
	initPorts();
	initTimer1();
	lcd_init();
	sei();
	
	lcd_pos(0,0);
	
    while (1) 
    {
		printf("%s", Time);
		printf("%", )
		_delay_ms(1000);
    }
}

