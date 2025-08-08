/******************************************************************
Title: Treiber fuer LCD-Anzeige, Datenbreite 4 Bit
Autor: lau 2015
File:  lcd_4.c
******************************************************************/
#include "lcd_4.h"

void lcd_init(void)
/******************************************************************
4-Bit-Initialisierung mit Void lcd_init(void)
    Warten > 15 ms
R/W  RS DB7 DB6 DB5 DB4
 0   0   0   0   1   1		Function Set A: 8-Bit-Interface
    Warten > 4,1 ms
 0   0   0   0   1   1		Function Set B: 8-Bit-Interface 
    Warten > 100 us
 0   0   0   0   1   1		Function Set C: 8-Bit-Interface
    Warten > 15 ms
 0   0   0   0   1   0		Function Set D: 4-Bit-Interface
 0   0   0   0   1   DL		Function Set High Byte 	DL: 1 = 8-Bit Interface   / 0 = 4-Bit Interface
 0   0   N   F   x   x		Function Set Low Byte  	F:  1 = 5x10 Zeichenfont  / 0 = 5x7 Zeichenfont
                                              		N:  1 = 2-Zeilen Display  / 0 = 1-Zeilen Display
 0   0   0   0   0   0    Display On High Byte   	D:  1 = Display On        / 0 = Display =Off
 0   0   1   D   C   B		Display On Low Byte    	C:  1 = Cursor unsichtbar / 0 = Cursor sichtbar
		  	 								       										B:  1 = Cursor blinkt     / 0 = Blinken aus
 0   0   0   0   0   0   	Display Clear High Byte
 0   0   0   0   0   1    Display Clear Low Byte
 0   0   0   0   0   0	  Entry Mode Set High Byte I/D: 1 = Adresspointer inkrement / 0 = Adressp. dekrement
 0   0   0   1  I/D  S		Entry Mode Set Low Byte	   S: 1 = Displayinhalt Schieben  / 0 = nicht schieben		   
******************************************************************/
{
	DDRA|= 1<<RS  | 1<<EN ;
	DDRB|= 1<<DB7 | 1<<DB6 | 1<<DB5 | 1<<DB4;
	PORTA&=~(1<< EN);
	PORTA&=~(1<< RS);

	_delay_ms(15); lcd_zToLCD(0x03);        // Function Set A
	_delay_ms(10); lcd_zToLCD(0x03);        // Function Set B
	_delay_ms(1); lcd_zToLCD(0x03);         // Function Set C
	_delay_ms(1); lcd_zToLCD(0x02);         // Function Set D
	
	lcd_zToLCD(0x02);       // Funktion Set High Byte
	lcd_zToLCD(0x08);       
	
	lcd_zToLCD(0x00);       // Display On 1 High Byte
	lcd_zToLCD(0x0C);       // Display On 2 Low Byte	

	lcd_zToLCD(0x00);       // Display Clear High Byte
	lcd_zToLCD(0x01);       // Display Clear Low Byte	

	lcd_zToLCD(0x00);       // Entry Mode Set High Byte
	lcd_zToLCD(0x06);       // Entry Mode Set Low Byte
	_delay_ms(1);

	//_delay_ms(2);	lcd_zToLCD(0x00);      	// LCD-Return-Home 1
	//_delay_ms(2);	lcd_zToLCD(0x02);       // LCD-Return-Home 2
	init_printf(NULL,putc);
}

void lcd_zToLCD(char dataD)
/******************************************************************
Mit Void lcd_home(char dataD) wird EN auf 1 gesetzt, dann erfolgt
die Datenausgabe. Mit 0 werden die Daten in das DD-Ram uebernommen.
Zuerst wird das High Byte, dann das Low Byte übertragen.
******************************************************************/
{
	if (dataD & 0x10) PORTA|= (1<<RS); 	
	else              PORTA&=~(1<<RS);	
	_delay_us(200);		
	PORTA|=1<< EN;
	_delay_us(10);		
	
	PORTB&=~(1<<DB4 | 1<<DB5 | 1<<DB6 | 1<<DB7);
	if (dataD & 0x01) PORTB|=1<<DB4;;
	if (dataD & 0x02) PORTB|=1<<DB5;
	if (dataD & 0x04) PORTB|=1<<DB6;
	if (dataD & 0x08) PORTB|=1<<DB7;
	_delay_us(50);		

	PORTA &= ~(1<< EN);
	_delay_us(10);		
}

/**********************************************************************
Ausgabe eines Textes. Der Pointer zeigt mit ZText=*&Text2 zum Beginn
des Textes. Der Pointer wird 16 mal erhöht (Ausgabe von 16 ASCII-Zeichen).
Die Ausgabe wird vorzeitig mit '\0' beendet. Zuerst erfolgt die Ausgabe
des High Bytes, dann das Low Byte.

Die 1. Zeile beginnt mit der DD-Adresse 0x00.
Die 2. Zeile beginnt mit der DD-Adresse 0x40.
**********************************************************************/
void lcd_pos(unsigned char zeile, unsigned char Pos)
{
	unsigned char Zeichen;

	if (zeile) Pos+=0x40;	
  	Zeichen=Pos;			    //Ausgabe der DD-Ram-Adresse
	Zeichen>>=4;
	Zeichen|=0x08;		
	//_delay_us(200);       //Wartezeit 200us
	lcd_zToLCD(Zeichen);    //Zeichenausgabe High Bytes
	Zeichen=Pos;
	Zeichen&=0x0F;	
	//_delay_us(200);       //Wartezeit 200us
	lcd_zToLCD(Zeichen);    //Zeichenausgabe Low Byte
}

void putc ( void* p, char c)
{
	unsigned char Zeichen;

  Zeichen = c;
	Zeichen>>=4;
	Zeichen|=0x10;		
	//_delay_us(200);       //Wartezeit 200us
	lcd_zToLCD(Zeichen);  //Zeichenausgabe High Bytes
	Zeichen = c;
	Zeichen&=0x0f;
	Zeichen|=0x10;
	//_delay_us(200);       //Wartezeit 200us
	lcd_zToLCD(Zeichen);  //Zeichenausgabe Low Byte
}
