/*
 * fluxtest.c
 *
 * Created: 12/11/2016 17:50:55
 * Author : fadhlika
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include "libuart.h"

#define period 0.000064
#define space 0.005

volatile uint8_t count;
volatile uint16_t timer;
char output[50];
int main(void)
{
	count = 0;
	MCUCR |= (1 << PUD);
	PORTD = (1 << PORTD3) | (1 << PORTD2) ;

	EICRA = 0x05; //Any logical change will trigger interrupt
	EIMSK = 0x03; //enable both INT0 and INT1
	TCCR1B = 0x05; //Using precaler 1024
	
	sei();
	usart_init();
	printf("Starting Up\n");
    while (1) 
    {
		
    }
}

ISR(INT1_vect){
	if(count == 0){
		TCNT1 = 0;
		printf("Start\n");
	} else {
		timer = TCNT1;
		TCNT1 = 0;
		float timers = timer*period;
		sprintf(output, "%u\t%u\t%.6f\t%.6f\n", count, timer, timers, space/timers );
		printf(output);
	}
	count++;
}

ISR(INT0_vect){
	timer = TCNT1;
	if(count == 37){
		EIMSK = 0x00;
	}
	TCNT1 = 0;
	float timers = timer*period;
	sprintf(output, "%u\t%u\t%.6f\t%.6f\n", count, timer, timers, space/timers );
	printf(output);
	count++;
}