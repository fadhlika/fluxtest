/*
 * libuart.c
 *
 * Created: 23/11/2016 13:26:26
 * Author : fadhlika
 */ 

#include "libuart.h"

FILE usart_str = FDEV_SETUP_STREAM(usart_send, usart_receive, _FDEV_SETUP_RW);

void usart_init(unsigned long baud)
{
	uint16_t myubrr = ((F_CPU/(baud*16UL))-1);
	/*UART INITIALIZATION*/
	UBRR0H = myubrr >> 8;
	UBRR0L = myubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01)|(1 << UCSZ00);
	stdin = stdout = &usart_str;
}

int usart_send(char data, FILE *stream){
	if(data == '\n'){
		usart_send('\r', 0);
	}
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
	return 0;
}

int usart_receive(FILE *stream){
	uint8_t data;
	while(!(UCSR0A & (1 << UDRE0)));
	data = UDR0;
	usart_send(data, stream);
	return data;
}