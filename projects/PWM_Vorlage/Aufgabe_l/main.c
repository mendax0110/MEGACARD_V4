/*
 * Aufgabe_l.c
 *
 * Created: 16.12.2023 11:02:31
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define F_CPU 12000000UL

#define NUM_SAMPLES 100
#define MAX_VALUE 255

volatile uint8_t index = 0;
uint8_t sineWave[NUM_SAMPLES];

void init()
{
	DDRB |= (1 << PB3); 
	TCCR0 |= (1 << COM01) | (1 << WGM00) | (1 << WGM01) | (1 << CS00);
	TIMSK |= (1 << TOIE0); 
	sei(); 
}

void generateSineWave()
{
	for (uint8_t i = 0; i < NUM_SAMPLES; ++i)
	{
		sineWave[i] = round((MAX_VALUE / 2) * (1 + sin(2 * M_PI * i / NUM_SAMPLES)));
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0 = sineWave[index];
	index++;
	
	if (index >= NUM_SAMPLES)
	{
		index = 0;
	}
}

int main(void)
{
	generateSineWave();
	init();

	while (1)
	{
	}
}
