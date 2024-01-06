/*
 * NormalWatchStopWatch.c
 *
 * Created: 04.01.2024 17:24:16
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_4.h"

volatile uint8_t milliseconds = 0;
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;
volatile uint8_t stopwatch_mode = 0;

// Timer 1 compare interrupt, for the stopwatch/watch
ISR(TIMER1_COMPA_vect)
{
	if(stopwatch_mode)
	{
		milliseconds++;
		
		if(milliseconds >= 100)
		{
			milliseconds = 0;
			seconds++;
		}
		if(seconds >= 60)
		{
			seconds = 0;
			minutes++;
		}
		if(minutes >= 60)
		{
			minutes = 0;
			hours++;
		}
		if(hours >= 24)
		{
			hours = 0;
		}
		updateStopwatchDisplay();
	}
	else
	{
		seconds++;
		
		if(seconds >= 60)
		{
			seconds = 0;
			minutes++;
			
			if(minutes >= 60)
			{
				minutes = 0;
				hours++;
				
				if(hours >= 24)
				{
					hours = 0;
				}
			}
		}
		updateDisplay();
	}
}

// clear/reset the timer variables
void resetTimerVariables()
{
	milliseconds = 0;
	seconds = 0;
	minutes = 0;
	hours = 0;
	stopwatch_mode = 0;
}

// init the leds and the buttons
void initPorts()
{
	DDRA &= ~(1 << PA0)|(1 << PA1);
	PORTA |= (1 << PA0)|(1 << PA1);
	DDRC = 0xFF;
	PORTC &= 0x00;
}

// init the registers for the timer1
void initTimer1()
{
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A = 11718;
    TIMSK |= (1 << OCIE1A);
    sei();
}

// update the display
void updateDisplay()
{
	lcd_pos(0,0);
	printf("TIME: %02d:%02d:%02d", hours, minutes, seconds);
}

// update the stopwatch on the display
void updateStopwatchDisplay()
{
	lcd_pos(0,0);
	printf("SW: %02d:%02d:%02d.%02d", hours, minutes, seconds, milliseconds);
}

// main function, call the init functions and start the main loop
int main(void)
{
	initPorts();
	initTimer1();
	lcd_init();
	
	while(1)
	{
        if(!(PINA & (1 << PA0)))
        {
	        _delay_ms(50);
	        if(!(PINA & (1 << PA0)))
	        {
		        stopwatch_mode = 0;
				//resetTimerVariables();
		        updateDisplay();
		        while(!(PINA & (1 << PA0))) {}
		        _delay_ms(50);
	        }
        }
        
        if(!(PINA & (1 << PA1)))
        {
	        _delay_ms(50);
	        if(!(PINA & (1 << PA1)))
	        {
		        stopwatch_mode = 1;
				//resetTimerVariables();
		        updateStopwatchDisplay();
		        while(!(PINA & (1 << PA1))) {}
		        _delay_ms(50);
	        }
        }
	}
}