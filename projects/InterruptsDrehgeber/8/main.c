/*
 * 8.c
 *
 * Created: 12.10.2023 09:12:19
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_4.h"

// Pinbelegung
#define CLK_PIN   PD3
#define DIR_PIN   PD2
#define LED_PORT  PORTC

volatile uint16_t impulsesPerRotation = 0;
volatile uint16_t impulsesForSingleRotation = 0;
volatile uint16_t maxImpulsesForSingleRotation = 0;  // To store the maximum impulses
volatile uint8_t rotationCompleted = 0;

// Software-Vorteiler
#define SOFTWARE_PRESCALER 10

// Initialize ports
void InitPorts()
{
    // Port D: CLK-Pin und DIR-Pin als Eingänge
    DDRD &= ~(1 << CLK_PIN);
    DDRD &= ~(1 << DIR_PIN);

    // Port C: LEDs als Ausgänge
    DDRC = 0xFF;
}

// INT1 ISR
ISR(INT1_vect)
{
    impulsesPerRotation++;
    
    // Apply software prescaler to reduce sensitivity
    if (impulsesPerRotation % SOFTWARE_PRESCALER == 0)
    {
        impulsesForSingleRotation++;
        
        // Check for maximum impulses in a single rotation
        if (impulsesForSingleRotation > maxImpulsesForSingleRotation)
        {
            maxImpulsesForSingleRotation = impulsesForSingleRotation;
        }
        
        PORTC = impulsesForSingleRotation;
        // Print the impulses in real-time
        lcd_pos(0, 1);
        printf("Impulse: %d", impulsesForSingleRotation);
    }
}

int main(void)
{
    InitPorts();
    lcd_init();

    cli();
    MCUCR |= (1 << ISC11) | (1 << ISC10); // Rising edge generates interrupt
    GICR |= (1 << INT1); // Enable INT1 interrupt
    sei(); // Enable global interrupts

    while (1)
    {
        if (rotationCompleted)
        {
            rotationCompleted = 0;
            impulsesForSingleRotation = 0;
        }
    }
}


