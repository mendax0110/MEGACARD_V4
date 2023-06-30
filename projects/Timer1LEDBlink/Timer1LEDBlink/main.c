/*
 * Timer1LEDBlink.c
 *
 * Created: 30.06.2023 12:25:14
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t timerCount = 0;
volatile uint8_t blinkState = 0;

void initPorts()
{
    DDRC |= 0xFF;  // Port C als Ausgang
    PORTC = 0x00; // Alle LEDs ausschalten
	
    // for S0 and S1
    DDRA &= ~((1 << PA0) | (1 << PA1));
    PORTA |= ((1 << PA0) | (1 << PA1));
}

void initTimer1()
{
    TCCR1B |= (1 << CS10) | (1 << CS11); // Prescaler 64
    TIMSK |= (1 << TOIE1); // Overflow Interrupt aktivieren
}

void setBlinkSpeed()
{
    uint8_t switchState = PINA & ((1 << PA1) | (1 << PA0));

    if (switchState == 0x00) 
	{
        // S0 und S1 aus
        TCCR1B |= (1 << CS10) | (1 << CS11); // Prescaler 64
    } 
	else if (switchState == (1 << PA0)) 
	{
        // S0 an, S1 aus
        TCCR1B |= (1 << CS11); // Prescaler 8
        TCCR1B &= ~(1 << CS10);
    } 
	else if (switchState == (1 << PA1)) 
	{
        // S0 aus, S1 an
        TCCR1B |= (1 << CS10); // Prescaler 1
        TCCR1B &= ~(1 << CS11);
    } 
	else if (switchState == (1 << PA1) | (1 << PA0))
	{
        // S0 und S1 an
        TCCR1B |= (1 << CS10); // Prescaler 1
        TCCR1B |= (1 << CS11); // Prescaler 8
    }
}

ISR(TIMER1_OVF_vect)
{
    timerCount++; // Timer erhöhen

    if (timerCount == 60)
	{
        blinkState = 1; // Blinken aktivieren
    }
}

int main(void)
{
    initPorts();
    initTimer1();
    sei(); // Interrupts aktivieren

    while (1)
    {
        setBlinkSpeed();

        if (blinkState)
        {
            PORTC ^= 0xFF; // Alle LEDs umschalten
            _delay_ms(500);
        }
        else
        {
            PORTC = 0xFF; // Alle LEDs ausschalten
        }
    }

    return 0;
}
