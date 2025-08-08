/*
 * Matura_Timer1_Zeitmessung_LCD_PA0.c
 *
 * Created: 05.08.2025
 * Author : Adrian
 */

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_4.h"

volatile uint8_t messung_aktiv = 0;
volatile uint32_t overflow_counter = 0;
volatile uint16_t start_ticks = 0;
volatile uint16_t end_ticks = 0;
volatile uint32_t zeit_ms = 0;

void initPorts(void)
{
    DDRC = 0xFF;      // LEDs Ausgang
    PORTC = 0x00;     // LEDs aus

    DDRA &= ~(1 << PA0);  // PA0 als Eingang (Taster)
    PORTA |= (1 << PA0);  // Pull-Up aktivieren
}

void initTimer1(void)
{
    TCCR1A = 0x00; // Normalmodus
    TCCR1B = (1 << CS11); // Prescaler 8 ? 1.5 MHz
    TIMSK |= (1 << TOIE1); // Overflow Interrupt aktivieren
    TCNT1 = 0;
}

ISR(TIMER1_OVF_vect)
{
    overflow_counter++;
}

uint8_t buttonPressed(void)
{
    if (!(PINA & (1 << PA0))) // Taster gedrückt (LOW)
    {
        _delay_ms(50); // Entprellen
        if (!(PINA & (1 << PA0)))
            return 1;
    }
    return 0;
}

int main(void)
{
    cli();
    initPorts();
    initTimer1();
    lcd_init();
    sei();

    while (1)
    {
        if (buttonPressed())
        {
            if (!messung_aktiv)
            {
                // Start der Messung
                TCNT1 = 0;
                overflow_counter = 0;
                start_ticks = 0; // sicherheitshalber
                messung_aktiv = 1;
                PORTC = 0xFF; // LEDs an
            }
            else
            {
                // Stop der Messung
                end_ticks = TCNT1;
                messung_aktiv = 0;
                PORTC = 0x00; // LEDs aus

                uint32_t total_ticks = (overflow_counter * 65536UL) + end_ticks;
                zeit_ms = total_ticks / 1500; // 12MHz / 8 = 1.5MHz = 0.666µs/Tick
				
                lcd_pos(0, 0);
                printf("Zeit: %4lu ms", zeit_ms);
            }

            // Warte bis Taster losgelassen ist
            while (!(PINA & (1 << PA0))) {}
            _delay_ms(50); // Nach-Entprellung
        }
    }
}
