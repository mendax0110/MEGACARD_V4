/*
 * VoltageDivInterrupt.c
 *
 * Created: 21.02.2023 20:32:06
 * Author : Adrian
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

// global variables
volatile float voltage = 0.0;
volatile uint8_t interruptFlag = 0;

// ADC conversion complete interrupt
ISR(ADC_vect)
{
    ADCSRA |= (1 << ADSC); // start next conversion
}

// pin change interrupt
ISR(PCINT0_vect)
{
    interruptFlag = 1;
}

int main(void)
{
	// set up the ADC
    ADMUX = (1 << REFS0)|(0 << MUX0); // Select ADC0 as input, Vcc as reference
    ADCSRA = (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); // Enable ADC, prescaler = 128

    // enable global interrupts
    sei();
    // 
    MCUCR |= (1 << ISC01)|(1 << ISC00); // set INT0 to trigger on rising edge
    PORTD |= (1 << PD0); // enable pull-up resistor on pin 0
	
    // set up the output pin
    DDRB |= (1 << PB0); // set pin 0 of port B as output

    while(1)
    {
        if(interruptFlag)
        {
            interruptFlag = 0;

            // perform voltage calculations
            float voltge = (float) ADC * 5.0 / 1024.0;
            uint8_t dutyCycle = (uint8_t) (voltage * 255.0 / 5.0);

            // output voltage as PWM signal
			
        }
    }
}


