/*
 * fluxtest.c
 *
 * Created: 12/11/2016 17:50:55
 * Author : fadhlika
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "libuart.h"
#include "twowire.h"

#define DP_ADDRESS 0x81

volatile uint8_t count;
volatile uint16_t timer;
volatile uint8_t ovf;
volatile bool intflag;
uint16_t dp;
void read_dp();

int main(void)
{
	count = 0;		//set count as zero initially
	ovf = 0;		//set overflow as zero initially
	dp = 0;			//set dp initially zero
	intflag = false; // set interrupt flag as false initially

	MCUCR |= (1 << PUD); // Pull-up disable
	PORTD = (1 << PORTD3) | (1 << PORTD2) ; //Pull up PD3 and PD2

	EICRA = 0x05; //Any logical change will trigger interrupt
	EIMSK = 0x03; //enable both INT0 and INT1
	TCCR1B = 0x05; //Using precaler 1024
	
	sei(); //Enable global interrupt'
	usart_init(); //Usart initialization
	tw_init(); // Two wire initialization

	printf("Start Up\n");	//Print "start up" when start to indicate the device booted;
    while (1) 
    {
		//print data if intflag set true in interrupt routine
		if(intflag) { 
			read_dp();
			printf("%u\t%u\t%u\t%u\n", count, ovf, timer, dp);
			ovf = 0;
			dp = 0;
			intflag = false;
		}
    }
}

void read_dp(){
	tw_start();
	tw_write(DP_ADDRESS);
	tw_write(0xFE);
	tw_start();
	tw_write(DP_ADDRESS);
	tw_write(0xF1);
	tw_start();
	tw_write(DP_ADDRESS | TW_READ);
	uint8_t temp = tw_read_ack();
	dp = (temp << 8) | tw_read_ack();
	uint8_t check = tw_read_ack();
	tw_stop();
}

ISR(INT1_vect){
	timer = TCNT1;
	TCNT1 = 0;
	count++;
	if(count == 1){
		printf("Start\n");
	}else{
		intflag = true;
	}
}

ISR(INT0_vect){
	timer = TCNT1;
	TCNT1 = 0;
	count++;
	intflag = true;
	if(count == 38){
		EIMSK = 0x00;
	}
}

ISR(TIMER1_OVF_vect){
	ovf++;
}