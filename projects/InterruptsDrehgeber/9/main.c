/*
 * 9.c
 *
 * Created: 12.10.2023 09:18:49
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LCD_4.h"

// Pinbelegung
#define CLK_PIN   PD3
#define DIR_PIN   PD2
#define LED_PORT  PORTC

volatile uint16_t impulsesForSingleRotation = 0;
volatile uint16_t maxImpulsesForSingleRotation = 0;
volatile uint8_t rotationCompleted = 0;
volatile uint16_t printfCount = 0;

// Software-Vorteiler
#define SOFTWARE_PRESCALER 10

// Initialize ports
void InitPorts()
{
    // Port D: DIR-Pin als Eingang
    DDRD &= ~(1 << DIR_PIN);

    // Port C: LEDs als Ausgänge
    DDRC = 0xFF;
}

int main(void)
{
    InitPorts();
    lcd_init();

    // Deaktiviere den externen INT1 (PD3 wird als Eingang genutzt)
    GICR &= ~(1 << INT1);

    // PD3 (CLK-Pin) als Eingang mit Pull-Up-Widerstand
    DDRD &= ~(1 << CLK_PIN);
    PORTD |= (1 << CLK_PIN);

    uint8_t previousState = (PIND & (1 << CLK_PIN)) ? 1 : 0;
    uint8_t currentState;

    while (1)
    {
        currentState = (PIND & (1 << CLK_PIN)) ? 1 : 0;

        // Erkenne steigende Flanke (alter Zustand=0 und neuer Zustand=1)
        if (previousState == 0 && currentState == 1)
        {
            impulsesForSingleRotation++;

            // software vortieler für sensitivität
            if (impulsesForSingleRotation % SOFTWARE_PRESCALER == 0)
            {
                // cceckt max impulse
                if (impulsesForSingleRotation > maxImpulsesForSingleRotation)
                {
                    maxImpulsesForSingleRotation = impulsesForSingleRotation;
                }

                PORTC = impulsesForSingleRotation;
                lcd_pos(0, 1);
                //printf("Impulse: %d", impulsesForSingleRotation);
				printf("Count: %d ", printfCount);
            }
        }

        previousState = currentState;
    }
}

