/******************************************************************
Title: Treiber fuer LCD-Anzeige, Datenbreite 4 Bit
Autor: lau 2021
File:  lcd_4.c

Achtung:  Vor dem ersten Download muss zur erstmaligen Initialisierung
des LCD (nur einmal) die USB-Verbindung unterbrochen werden!

Verwendung der Routinen:
lcd_init();
lcd_pos(x,y);				//Zeile,Spalte
printf("V= %4d", val);


printf: unterstützte Formatierungszeichen
%c.......char (Zeichen)
%d.......int
%u.......unsigned int
%ld......Long
%lf,%f...nicht unterstützt
%4d......4Zeichen rechtsbündig
%04d.....führende 0en, 4stellen
%s.......String

********************************************************************/

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

