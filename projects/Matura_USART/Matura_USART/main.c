/*
 * Matura_USART.c
 *
 * Created: 05.08.2025 12:19:24
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include "usart.h"



int main(void)
{
    usart_init();
    while (1) 
    {
		usart_putchar('A');
		usart_sendstring("Hallo Welt!");
		usart_sendstring("Hello, PC!");
		_delay_ms(1000);
    }
}

