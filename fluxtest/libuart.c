/*
 * libuart.c
 *
 * Created: 23/11/2016 13:26:26
 * Author : fadhlika
 */ 

#include <avr/io.h>


#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include "libuart.h"

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);
void usart_init(void)
{
	/*UART INITIALIZATION*/
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01)|(1 << UCSZ00);
	stdout = &mystdout;
}

//USART
void usart_putchar(char data) {
	// Wait for empty transmit buffer
	while ( !(UCSR0A & (_BV(UDRE0))) );
	// Start transmission
	UDR0 = data;
}
char usart_getchar(void) {
	// Wait for incoming data
	while ( !(UCSR0A & (_BV(RXC0))) );
	// Return the data
	return UDR0;
}
unsigned char usart_kbhit(void) {
	//return nonzero if char waiting polled version
	unsigned char b;
	b=0;
	if(UCSR0A & (1<<RXC0)) b=1;
	return b;
}
void usart_pstr(char *s) {
	// loop through entire string
	while (*s) {
		usart_putchar(*s);
		s++;
	}
}

// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream) {
	// translate \n to \r for br@y++ terminal
	if (var == '\n') usart_putchar('\r');
	usart_putchar(var);
	return 0;
}
