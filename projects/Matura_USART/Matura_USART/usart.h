/*
 * usart.h
 *
 * Created: 11.11.2019 19:38:19
 *  Author: lau
 */ 


#ifndef USART_H_
#define USART_H_

void usart_init ();
void usart_putchar(unsigned char data);
void usart_sendstring(char *s);
void usart_sendint(int num);
void process_command();

#endif /* USART_H_ */