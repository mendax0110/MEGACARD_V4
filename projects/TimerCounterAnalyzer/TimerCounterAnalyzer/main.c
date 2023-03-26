/*
 * TimerCounterAnalyzer.c
 *
 * Created: 26.03.2023 18:30:43
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/portpins.h>

// LED parameters
#define LED_VOLTAGE 2.0
#define LED_CURRENT 30.0

// ADC parameters
#define ADC_VREF 5.0
#define ADC_MAX_VALUE 1023.0

// Timer parameters
#define TIMER_PRESCALER 1024.0
#define TIMER_TOP ((F_CPU / TIMER_PRESCALER) / 10) -1

// function prototypes
void init_adc();
void init_timer();
float adc_to_voltage(uint16_t adc_value);

ISR(TIMER0_OVF_vect)
{
	// calc
	uint16_t adc_value = ADC;
	float adc_voltage = adc_to_voltage(adc_value);
	float led_current = (adc_voltage / LED_VOLTAGE) * LED_CURRENT;

	OCR0 = (led_current / LED_CURRENT) * 255;
}

int main(void)
{
	cli();

	// init
	init_adc();
	init_timer();
	DDRC |= (1 << PB3); // set PB3 as output

	sei();

	while (1)
	{
		// do nothing
	}
}

// init adc
void init_adc()
{
	ADMUX = (1 << REFS0); // set reference voltage to AVCC
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // enable ADC, set prescaler to 128
}

void init_timer()
{
	TCCR1B = (1 << CS12) | (1 << CS10); // set prescaler to 1024

	OCR1A = TIMER_TOP; // set timer top

	TIMSK = (1 << TOIE1); // enable timer overflow interrupt
}

// convert adc value to voltage
float adc_to_voltage(uint16_t adc_value)
{
	return (adc_value / ADC_MAX_VALUE) * ADC_VREF;
}
