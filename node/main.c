/*
 * node.c
 *
 * Created: 12/11/2016 17:55:40
 * Author : fadhlika
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//Variable declaration
//n - number of interrupt
volatile uint8_t n;

int main(void)
{
	//Variable initialization
	n = 0;														//set initial zero
	
	MCUCR |= (1 << PUD);

	//PCINT register 
    PCICR = 0x07;		//enable all three PCINT
    PCMSK1 = (1  << PCINT12);
	PORTB = 0xFF;
	PORTC = 0x7F;
	PORTD = 0xFF;
    
	//GPIO
	DDRC = (1 << PORTC5);										//Set PORTC5 as output
	PORTC |= (1 << PORTC5);

    sei();														//enable global interrupt
    while (1);
}

ISR(PCINT1_vect){
	PCIFR = (1 << PCIF1);
	switch(n){
		case 0 : PCMSK1 ^= (1  << PCINT12);
				 PORTC ^= (1 << PORTC5);
				 PCMSK1 ^= (1  << PCINT11);
				 n++;
				 break;
		case 1 : PCMSK1 ^= (1  << PCINT11);
				 PORTC ^= (1 << PORTC5);
				 PCMSK1 ^= (1  << PCINT10);
				 n++;	
				 break;
		case 2 : PCMSK1 ^= (1  << PCINT10); 
				 PORTC ^= (1 << PORTC5);
				 PCMSK1 ^= (1  << PCINT9);
				 n++;
				 break;
		case 3 : PCMSK1 ^= (1  << PCINT9);
				 PORTC ^= (1 << PORTC5);
				 PCMSK1 ^= (1  << PCINT8);
				 n++;
				 break;
		case 4 : PCMSK1 ^= (1  << PCINT8);
				 PORTC ^= (1 << PORTC5);
				 PCMSK0 ^= (1  << PCINT5);
				 n++;
				 break;
		default: break;
	}
	PCIFR = (1 << PCIF1);
}

ISR(PCINT0_vect){
PCIFR = (1 << PCIF0);
	switch(n){
		case 5 : PCMSK0 ^= (1  << PCINT5);
				 PORTC ^= (1 << PORTC5);
				 PCMSK0 ^= (1  << PCINT4);
				 n++;
				 break;
		case 6 : PCMSK0 ^= (1  << PCINT4);
				 PORTC ^= (1 << PORTC5);
				 PCMSK0 ^= (1  << PCINT3);
				 n++;
				 break;
		case 7 : PCMSK0 ^= (1  << PCINT3);
				 PORTC ^= (1 << PORTC5);
				 PCMSK0 ^= (1  << PCINT2);
				 n++;
				 break;
		case 8 : PCMSK0 ^= (1  << PCINT2);
				 PORTC ^= (1 << PORTC5);
				 PCMSK0 ^= (1  << PCINT1);
				 n++;
				 break;
		case 9 : PCMSK0 ^= (1  << PCINT1);
				 PORTC ^= (1 << PORTC5);
				 PCMSK2 ^= (1  << PCINT16);
				 n++;
				 break;
		case 15 : PCMSK0 ^= (1  << PCINT6);
				  PORTC ^= (1 << PORTC5);
				  PCMSK0 ^= (1  << PCINT7);
				  n++;	
		  		  break;
		case 16 : PCMSK0 ^= (1  << PCINT7);
				  PORTC ^= (1 << PORTC5);
				  PCMSK2 ^= (1  << PCINT21);
				  n++;
				  break;
		default: break;
	}
	PCIFR = (1 << PCIF0);
}

ISR(PCINT2_vect){
	PCIFR = (1 << PCIF2);
	switch(n){
		case 10 : PCMSK2 ^= (1  << PCINT16);
				  PORTC ^= (1 << PORTC5);
				  PCMSK2 ^= (1  << PCINT17);
				  n++;
				  break;
		case 11 : PCMSK2 ^= (1  << PCINT17);
				  PORTC ^= (1 << PORTC5);
				  PCMSK2 ^= (1  << PCINT18);
				  n++;
				  break;
		case 12 : PCMSK2 ^= (1  << PCINT18);
				  PORTC ^= (1 << PORTC5);
				  PCMSK2 ^= (1  << PCINT19);
				  n++;
				  break;
		case 13 : PCMSK2 ^= (1  << PCINT19);
				  PORTC ^= (1 << PORTC5);
				  PCMSK2 ^= (1  << PCINT20);
				  n++;
				  break;
		case 14 : PCMSK2 ^= (1  << PCINT20);
				  PORTC ^= (1 << PORTC5);
				  PCMSK0 ^= (1  << PCINT6);
				  n++;
				  break;
		case 17 : PCMSK2 ^= (1  << PCINT21);
				  PORTC ^= (1 << PORTC5);
		          PCMSK2 ^= (1  << PCINT22);
				  n++;
				  break;
		case 18 : PCMSK2 ^= (1  << PCINT22);
				  PORTC ^= (1 << PORTC5);
				  PCMSK2 ^= (1  << PCINT23);
				  n++;
				  break;
		case 19 : PCMSK2 ^= (1  << PCINT23);
				  PORTC ^= (1 << PORTC5);
				  break;
		default: break;
	}
	PCIFR = (1 << PCIF2);
}