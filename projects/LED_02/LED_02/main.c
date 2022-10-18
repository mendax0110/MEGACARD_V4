/*
 * LED_02.c
 *
 * Created: 13.10.2022 22:20:28
 * Author : Adrian
 */ 

#define F_CPU 12000000UL     //define the frequency
#include <avr/io.h>			//default AVR lib with SFR regs and bit definitions
#include <util/delay.h>     //lib for delay functions

// main function
  int main(void) 
  {
	  DDRC=0xFF;	//LED-Port (PortC): Output
	  PORTC=0x55;	//LEDs 0,2,4,6 turn on
	  while(1)		//start with loop
	  {
		  PORTC = ~PORTC;	//change all LED's
		  _delay_ms(200);	//wait 200ms
	  }						//end loop
  } //end main

