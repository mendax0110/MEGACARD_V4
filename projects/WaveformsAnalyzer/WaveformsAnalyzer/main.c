/*
 * TCAnalyzerSimple.c
 *
 * Created: 28.03.2023 21:37:53
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

#define WAVEFORM_PERIOD 1000

int main(void)
{
    DDRB |= (1 << PB3); // Set PB3 as output

    while(1)
    {
        // generate a square wave on PB3
        for(int i = 0; i < WAVEFORM_PERIOD; i++)
        {
            PORTB |= (1 << PB3);
            _delay_us(500);
            PORTB &= ~(1 << PB3);
            _delay_us(500);
        }
    }
}
