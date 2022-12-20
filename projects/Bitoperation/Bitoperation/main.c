/*
 * Bitoperation.c
 *
 * Created: 20.12.2022 21:56:55
 * Author : Adrian
 */ 

#include <avr/io.h>

volatile unsigned	char x, y;		// global variable , memory-class voltatile
volatile signed		char z=-10;	// SRAM, not to optimize

int main(void)
{
	DDRA = 0xF0;	// SFR-Register
	
	x = 0xAB;
	y = 0x01;
	
    /* while loop*/
    while (1) 
    {
		DDRA ^= 0xff;	// 1-complement (reverse PORTA PIN)
		x ^= 0xff;		// 1-complement (bit-wise invert)
		y <<= 1;		// 1 bit shift left
		z >>= 1;		// 1-bit arithmetic shift right
    }
}

