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

unsigned int count=0;

int main(void){
	lcd_init();
	lcd_pos(0,0);
	printf("MEGACARD");

	for(;;)                 
	{
		count++;									
		lcd_pos(1,0);
		printf("T= %5d",count);
		_delay_ms(10);
	}
}
