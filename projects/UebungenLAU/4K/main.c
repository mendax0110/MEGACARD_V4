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

int main(void)
{
	lcd_init();

	int num = 42;
	
	while(1)
	{
		
		for (int i = 0; i <= 4; i++)
		{
			lcd_pos(0,0);
			switch(i)
			{
				case 0:
				{
					printf("Decimal:");
					lcd_pos(1,0);
					printf("%d", num);
					break;
				}
				case 1:
				{
					printf("Minimum width 5:");
					lcd_pos(1,0);
					printf("%5d", num);
					break;
				}
				case 2:
				{
					printf("Minimum 5 zeros:");
					lcd_pos(1,0);
					printf("%05d", num);
					break;
				}
				case 3:
				{
					printf("Hexadecimal(lowercase):");
					lcd_pos(1,0);
					printf("%x", num);
					break;
				}
				case 4:
				{
					printf("Hexadecimal(uppercase):");
					lcd_pos(1,0);
					printf("%X", num);
					break;
				}
			}
			_delay_ms(10000);
			printf("                  ");
		}
	}
}

