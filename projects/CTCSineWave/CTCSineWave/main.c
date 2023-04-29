/*
 * CTCSineWave.c
 *
 * Created: 29.04.2023 19:55:50
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

// define constants
#define PWM_FREQ_HZ 1000
#define PWM_PERIOD_US (1000000/PWM_FREQ_HZ) // period of PWM signal in microseconds
#define PWM_MAX_COUNT ((F_CPU/1024UL)*PWM_PERIOD_US/1000000UL) // maximum count for OCR0 to achieve desired PWM frequency
#define TABLE_SIZE 256 // size of lookup table

// define global variables
volatile uint8_t sineTable[TABLE_SIZE];
volatile uint8_t pwmDutyCycle = 0;

// ISR for the timer0 compare match A
ISR(TIMER0_COMPA_vect)
{
	static uint8_t index = 0;

	// set the PWM duty cycle based on the sine table value
	pwmDutyCycle = sineTable[index];

	// increment index and wrap around if needed
	index++;
	if (index == TABLE_SIZE) {
		index = 0;
	}
}

// init the ports
void init_ports()
{
	DDRB |= (1 << PB3); // OC0 - for Output PWM Signal
}

// init the timer0 in Fast PWM mode
void init_timer0_pwm()
{
	TCCR0 |= (1 << COM01) | (1 << WGM01) | (1 << WGM00); // Fast PWM mode, non-inverting mode
	TCCR0 |= (1 << CS02) | (1 << CS00); // clock division prescaler 1024
	OCR0 = 0; // initial duty cycle of 0%
	TIMSK |= (1 << OCIE0); // enable interrupt for compare match A
}

// init the sine table
void init_sine_table()
{
	for (uint16_t i = 0; i < TABLE_SIZE; i++) {
		sineTable[i] = (uint8_t)(127.0 + 127.0 * sin(2.0 * M_PI * i / TABLE_SIZE));
	}
}

// main, init and loop
int main(void)
{
	cli(); // interrupt lock
	init_ports(); // init the ports
	init_timer0_pwm(); // init the timer0 for PWM
	init_sine_table(); // init the sine table
	sei(); // interrupt release

	while (1)
	{
		// nothing to do
	}
}