/*
 * Simple_WatchDog_Example.c
 *
 * Created: 19.09.2024 14:07:33
 * Author : Adrian
 */
// Definitionen
#define F_CPU 12000000

#define LED_PORT		PORTC
#define Key_PORT		PORTA
#define Key_PORT_READ	PINA

#define LED_PORT_DIR	DDRC
#define Key_PORT_DIR	DDRA

#define LED_Flash_ON	0xFF
#define LED_Flash_OFF	0x00
#define LED_Flash_Time  500

#define WDTMaximiumCount 1000
unsigned char wdtcounter = 0;

// verwendete Bibliotheken
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>

void init()
{
	LED_PORT_DIR = 0xFF;	// alle Bits auf Ausgang
	LED_PORT = 0x00;		// keine Pull-ups
	
	Key_PORT_DIR = 0x00;	// alle Bits auf Eingang
	Key_PORT = 0x0F;		// S0 ... S3 mit Pull-ups
	
	LEDFlash();
}

void LEDFlash()
{
	LED_PORT = LED_Flash_ON;
	_delay_ms(LED_Flash_Time);
	LED_PORT = LED_Flash_OFF;
	_delay_ms(LED_Flash_Time);
	LED_PORT = LED_Flash_ON;
	_delay_ms(LED_Flash_Time);
	LED_PORT = LED_Flash_OFF;
	_delay_ms(LED_Flash_Time);
	LED_PORT = LED_Flash_ON;
	_delay_ms(LED_Flash_Time);
	LED_PORT = LED_Flash_OFF;
	_delay_ms(LED_Flash_Time);
}

int main(void)
{
	init();
	
    while((Key_PORT_READ & 0x01))
    {
        
    }
	
	// WatchDog aktivieren
	WDTCR = 0x0B;			// 0000 1010  ->  Teilerfaktor 128 000, Watchdog arbeitet mit 1MHz
	LED_PORT = 0xFF;
	
	while(!(Key_PORT_READ & 0x01))
	{
		// WatchDog zurücksetzen
		wdt_reset();
		
		wdtcounter++;
		if (wdtcounter >= WDTMaximiumCount)
		{
			LED_PORT = 0xAA;
			wdtcounter = 0;
		}
		
		if (!(PINA & 0x03))
		{
			// WatchDog disable
			WDTCR = 0x18;
			WDTCR = 0x00;
			
			LED_PORT = 0xAA;
		}
	}
	
	// WatchDog führt RESET aus, weil er nicht zurückgesetzt wird
	
	/* Spezielle Befehle
	WDT_ENABLE(WDTO_500ms);
	WDT_DISABLE();
	*/
}