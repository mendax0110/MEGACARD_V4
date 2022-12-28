/*
 * LogicalOperators.c
 *
 * Created: 28.12.2022 19:16:28
 * Author : Adrian
 */ 
#define  F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK 250

int main(void)
{
    // Set PORTC as output
    DDRC = 0xFF;

    while (1)
    {
        // Turn on all LEDs
        PORTC = 0xFF;
        _delay_ms(BLINK);

        // Turn off all LEDs
        PORTC = 0x00;
        _delay_ms(BLINK);

        // Toggle all LEDs
        PORTC ^= 0xFF;
        _delay_ms(BLINK);

        // Turn on alternate LEDs using OR-Gatter
        PORTC |= 0x55;
        _delay_ms(BLINK);

        // Turn off alternate LEDs using AND-Gatter
        PORTC &= 0xAA;
        _delay_ms(BLINK);

        // Toggle alternate LEDs using EXOR-Gatter
        PORTC ^= 0x55;
        _delay_ms(BLINK);

        // Invert all LEDs
        PORTC =~ PORTC;
        _delay_ms(BLINK);

        // Turn on all LEDs using NAND-Gatter
        PORTC =~(PORTC & 0x00);
        _delay_ms(BLINK);

        // Turn off all LEDs using NOR-Gatter
        PORTC =~(PORTC | 0xFF);
        _delay_ms(BLINK);
    }
}

