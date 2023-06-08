/*
 * StopWatchLED.c
 *
 * Created: 07.06.2023 23:08:19
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t seconds = 0;  
volatile uint8_t s0_Pressed = 0;  
volatile uint8_t s1_Pressed = 0; 
volatile uint8_t stopwatch_running = 0;  

ISR(TIMER0_COMP_vect)
{
    if (stopwatch_running)
    {
        seconds++;
    }
}

void init_Timer0()
{
    TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);
    
    OCR0 = 150;
    
    TIMSK |= (1 << OCIE0);
}

void update_leds()
{
    PORTC = (1 << (seconds % 8));   // Sekunden auf den LEDs PC0-PC7 anzeigen
}

void init_Ports()
{
    DDRC = 0xFF;    // LEDs PC0-PC7 als Ausgabe festlegen
    
    DDRA &= ~(1 << PA0) & ~(1 << PA1);  // Tasten PA0 und PA1 als Eingabe festlegen
    
    PORTA |= (1 << PA0) | (1 << PA1);   // Pull-Up-Widerstände für Tasten aktivieren
}

void start_stopwatch()
{
    stopwatch_running = 1;
}

void stop_stopwatch()
{
    stopwatch_running = 0;
}

void reset_stopwatch()
{
    stopwatch_running = 0;
    seconds = 0;
}

int main(void)
{
    cli();  
    init_Ports();   
    init_Timer0(); 
    sei();  
	
    while (1)
    {
        update_leds();  
        
        if (!(PINA & (1 << PA0)))
        {
            _delay_ms(50);  
            if (!(PINA & (1 << PA0)))  
            {
                if (stopwatch_running)
                {
                    stop_stopwatch();  
                }
                else
                {
                    start_stopwatch();  
                }
                _delay_ms(200);  
            }
        }
        
        if (!(PINA & (1 << PA1)))
        {
            _delay_ms(50); 
            if (!(PINA & (1 << PA1)))  
            {
                reset_stopwatch();  
                _delay_ms(200);  
            }
        }
    }
}
