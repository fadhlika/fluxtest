/*
 * libuart.h
 *
 * Created: 23/11/2016 13:26:54
 *  Author: fadhlika
 */ 

#ifndef LIBUART_H_
#define LIBUART_H_

#define BAUD 1000000
#define MYUBRR ((16000000/(BAUD*16UL))-1)
char usart_getchar( void );
void usart_init(void);
void usart_putchar( char data );
void usart_pstr (char *s);
unsigned char usart_kbhit(void);
int usart_putchar_printf(char var, FILE *stream);
#endif /* LIBUART_H_ */