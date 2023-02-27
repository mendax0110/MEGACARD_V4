/*
 * LEDButtonVoltage.c
 *
 * Created: 27.02.2023 20:09:58
 * Author : Adrian
 */ 
#define F_CPU 12000000UL		// freq of quarz
#define VOLTAGE_THRESHOLD 100	// voltage threshold in mv

#include <avr/io.h>         // include avr header
#include <util/delay.h>     // include delay header
#include <avr/interrupt.h>  // include interrupt header
#include <avr/sleep.h>      // include sleep header
#include <avr/portpins.h>   // include portpins header

// define the LED pin
#define LED_1 PC0
#define LED_2 PC1
#define LED_3 PC2
#define LED_4 PC3

// define the button pin
#define BUTTON_1 PD3

// define the voltage pin
#define VOLTAGE_PIN PB0

// delay time in ms
#define DELAY_TIME 500

volatile uint8_t led_counter = 0;	// counter for the led
volatile uint8_t button_pressed = 0;	// flag for the button
volatile uint16_t voltage = 0;		// voltage value

// ISR for the button
ISR(INT1_vect)
{
    // check button pressed
    if(!(PIND & (1 << BUTTON_1)))
    {
        // set flag
        button_pressed = 1;
    }
}

ISR(ADC_vect)
{
    // read the voltage
    voltage = (ADCL | (ADCH << 8));
}

void init_interrupt()
{
    // enable interrupts
    GICR |= (1 << INT1);
    MCUCR |= (1 << ISC11);

    // enable global interrupts
    sei();
}

void init_ports()
{
    // set the led pins as output
    DDRC |= (1 << LED_1) | (1 << LED_2) | (1 << LED_3) | (1 << LED_4);

    // set button pin as input
    DDRD &= ~(1 << BUTTON_1);
    PORTD |= (1 << BUTTON_1);

    // set voltage pin as input
    DDRB &= ~(1 << VOLTAGE_PIN);
}

void init_adc()
{
    // ADC voltage reference
    ADMUX |= (1 << REFS0);

    // ADC prescaler
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // enable ADC
    ADCSRA |= (1 << ADIE) | (1 << ADEN);

    // start ADC
    ADCSRA |= (1 << ADSC);

    // start ADC conversion
    ADCSRA |= (1 << ADSC);
}

int main(void)
{
    init_ports();
    init_interrupt();
    init_adc();

    // set sleep mode
    set_sleep_mode(SLEEP_MODE_IDLE);

    while(1)
    {
        // enter sleep mode
        sleep_mode();

        // check if button is pressed
        if(button_pressed)
        {
           led_counter++;

            // check if led counter is greater than 4
            if(led_counter > 3)
            {
                led_counter = 0;
            }
            
            button_pressed = 0;
        }

        // check if voltage is greater than threshold
        if(voltage > VOLTAGE_THRESHOLD)
        {
            // turn on led
            PORTC |= (1 << led_counter);
        }
        else
        {
            // turn off led
            PORTC &= ~(1 << led_counter);
        }
    }
}