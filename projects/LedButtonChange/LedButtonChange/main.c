/*
 * LedButtonChange.c
 *
 * Created: 20.12.2022 20:36:49
 * Author : Adrian
 */ 
#include <avr/io.h>        //I/O-Deklarationen
#include <avr/interrupt.h> //Interrupt Deklarationen

int main(void)
{
	
	DDRA=0x00;  //Tasterport: Eingang (default)
	PORTA=0xFF; //Pullup aktivieren für Taster S0, S1
	DDRC=0xFF;  //LED-Port: Ausgang
	PORTC=0x00; //LED0 ein, LED1...7 aus
	
    while(1) //Endlosschleife
    {
        if(!(PINA & 0x01)) PORTC=0xFF; //LED0 ein wenn S0 gedrückt
		if(!(PINA & 0x02)) PORTC=0x00;	//LED0 aus wenn S1 gedrückt
    }
}