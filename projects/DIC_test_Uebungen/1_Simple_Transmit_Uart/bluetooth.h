/*
 * bluetooth.h
 *
 * Created: 14.11.2019 20:09:07
 *  Author: lau
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#endif /* USART_H_ */

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile unsigned char bt_rec;

void bt_init(unsigned long baudrate);
void bt_putchar(unsigned char data);
int bt_printf (const unsigned char *format, ...);




