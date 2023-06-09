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

// gloabal variables, for the buttons, the seconds and the stopwatch
volatile uint8_t seconds = 0;  
volatile uint8_t s0_Pressed = 0;  
volatile uint8_t s1_Pressed = 0; 
volatile uint8_t stopwatch_running = 0;  

// Interrupt Service Routine for Timer0 Compare Match
ISR(TIMER0_COMP_vect)
{
    if (stopwatch_running)
    {
        seconds++;
    }
}

// Timer0 initialization, 8-bit, CTC, prescaler 1024
void init_Timer0()
{
    TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);
    
    OCR0 = 150;
    
    TIMSK |= (1 << OCIE0);
}

// update the LEDs, mod 8 because we only have 8 LEDs
void update_leds()
{
    PORTC = (1 << (seconds % 8));   // Sekunden auf den LEDs PC0-PC7 anzeigen
}

// initialize the ports
void init_Ports()
{
    DDRC = 0xFF;    // LEDs PC0-PC7 als Ausgabe festlegen
    
    DDRA &= ~(1 << PA0) & ~(1 << PA1);  // Tasten PA0 und PA1 als Eingabe festlegen
    
    PORTA |= (1 << PA0) | (1 << PA1);   // Pull-Up-Widerstände für Tasten aktivieren
}

// start the stopwatch
void start_stopwatch()
{
    stopwatch_running = 1;
}

// stop the stopwatch
void stop_stopwatch()
{
    stopwatch_running = 0;
}

// reset the stopwatch
void reset_stopwatch()
{
    stopwatch_running = 0;
    seconds = 0;
}

int main(void)
{
    cli();  	// disable interrupts
    init_Ports();   // initialize ports
    init_Timer0(); 	// initialize timer0
    sei();  	// enable interrupts
	
    while (1)
    {
		// update the LEDs
        update_leds();  
        
		// check if the buttons are pressed
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
        
		// check if the buttons are pressed
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