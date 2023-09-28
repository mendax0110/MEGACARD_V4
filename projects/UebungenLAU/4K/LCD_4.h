#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/../string.h>
#include <avr/../stdlib.h>
#include "printf.h"

//========================================
//Definition wo das LCD angeschlossen ist:
//========================================
#define RS				6
#define EN				4
#define DB4				2
#define DB5				5
#define DB6				6
#define DB7				7

//Funktionsprototypen
void lcd_init(void);
void lcd_zToLCD(char dataD);
void lcd_pos(unsigned char zeile, unsigned char Pos);
void putc ( void* p, char c);

