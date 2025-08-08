///*
 //* usart.c
 //* 
 //* Created: 11.11.2019 19:21:52
 //* 
 //* Author: lau
 //*/ 
//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "usart.h"

#define F_CPU 12000000UL  // Clock frequency of 12MHz
#define BAUD 115200
#define MYUBRR F_CPU/8/BAUD-1

#define BUFFER_SIZE 16   // Adjust buffer size as needed

volatile uint8_t rx_buffer[BUFFER_SIZE]; // Receive buffer
volatile uint8_t rx_head = 0;            // Index to the next byte to be written
volatile uint8_t rx_tail = 0;            // Index to the next byte to be read

void usart_init()
{
	unsigned int ubrr = MYUBRR;
	
	// Set baud rate
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	
	// Enable double speed mode
	UCSRA |= (1 << U2X);
	
	// Enable receiver and transmitter
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE); // Enable RX Complete Interrupt
	
	// Set frame format: 8 data bits, 1 stop bit
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	
	// Enable global interrupts
	sei();
}

void usart_putchar(unsigned char data)
{
	while (!(UCSRA & (1 << UDRE)));  // Wait until the transmit buffer is empty
	UDR = data;                      // Send the data
}

void usart_sendstring(char *s)
{
	while (*s)
	{
		usart_putchar(*s++);
	}
}

void usart_sendint(int num)
{
	char buffer[10];
	itoa(num, buffer, 10);
	usart_sendstring(buffer);
}

ISR(USART_RXC_vect)
{
	unsigned char received_char = UDR;
	
	rx_buffer[rx_head] = received_char;
	rx_head = (rx_head + 1) % BUFFER_SIZE;
}

void process_command()
{
	if ((rx_head - rx_tail + BUFFER_SIZE) % BUFFER_SIZE >= 4)
	{
		uint8_t command[4];
		for (int i = 0; i < 4; i++)
		{
			command[i] = rx_buffer[rx_tail];
			rx_tail = (rx_tail + 1) % BUFFER_SIZE;
		}
		
		if (command[0] == 0x47 && command[1] == 0xAA && command[2] == 0x55)
		{
			if (command[3] == 0x00)
			{
				DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3); // Set pins as output
				PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3); // Turn all LEDs on
			}
			else if (command[3] == 0x01)
			{
				DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3); // Set pins as output
				PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3)); // Turn all LEDs off
			}
		}
		rx_head = rx_tail = 0;
	}
}