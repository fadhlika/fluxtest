/*
 * libuart.h
 *
 * Created: 23/11/2016 13:26:54
 *  Author: fadhlika
 */ 


#ifndef LIBUART_H_
#define LIBUART_H_
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/pgmspace.h>
#include <stdio.h>
void usart_init(unsigned long baud);
int usart_send(char data, FILE *stream);
int usart_receive(FILE *stream);
#endif /* LIBUART_H_ */