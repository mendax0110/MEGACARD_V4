/********************************************************************
 *    Title:    lcd	
 *    Author:   lau
 *    Date:     05/2013
 *    Purpose:  LCD-Ansteuerung
 *    Purpose:  Ansteuerung eines HD44780 LCDs im 4-Bit-Modus
 *              Funktioniert für das LCD der Megacard Version 4
 *              Achtung:  Vor dem ersten Download muss zur erstmaligen 
 * 				Initialisierung des LCD (nur einmal) die USB-Verbindung 
 *				unterbrochen werden!
 *    Software: AVR-GCC / AVR Studio 4.12
 *    Hardware: ATmega16/Megacard
 *    Note:     fclk=12MHz
 ********************************************************************/
#include "lcd_4.h"
#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint16_t hundredths = 0; // Hundertstel-Sekunden
volatile uint8_t seconds = 0;     // Sekunden
volatile uint8_t running = 0;     // Laufende Stoppuhr


void initPorts()
{
	DDRA = 0x00; // button as input
	PORTA = 0xFF; // set Pull-Up resistors
}

void updateDisplay()
{
	printf("%02d:%02d.%02d\r\n", seconds / 60, seconds % 60, hundredths);
}

void startStopwatch()
{
	running = 1;
	hundredths = 0;
	seconds = 0;
	updateDisplay();
}

void stopStopwatch()
{
	running = 0;
}

void resetStopwatch()
{
	running = 0;
	hundredths = 0;
	seconds = 0;
	updateDisplay();
}

int main(void)
{
	initPorts();
	lcd_init();
	
	while (1)
	{
		if (!(PINA & (1 << PA0))) // S0: Start
		{
			if (!running)
			{
				startStopwatch();
			}
		}
		else if (!(PINA & (1 << PA1))) // S1: Stop
		{
			if (running)
			{
				stopStopwatch();
			}
		}
		else if (!(PINA & (1 << PA2))) // S2: Reset
		{
			resetStopwatch();
		}
		else if (!(PINA & (1 << PA3))) // S3: Start/Stop
		{
			if (running)
			{
				stopStopwatch();
			}
			else
			{
				startStopwatch();
			}
		}
		
		if (running)
		{
			_delay_ms(10); // delay of 10 Millisec for the hundredths-Sec
			hundredths++;
			
			if (hundredths >= 100)
			{
				hundredths = 0;
				seconds++;
			}
			
			updateDisplay();
		}
	}
}

