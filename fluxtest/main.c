/*
 * fluxtest.c
 *
 * Created: 12/11/2016 17:50:55
 * Author : fadhlika
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "libuart.h"
#include "i2c_master.h"

#define DP_ADDRESS 0x81

volatile uint8_t lvl;
volatile unsigned int timer;
volatile unsigned int ovft;
volatile unsigned int ovf;
volatile bool intflag;
int readsdp();
volatile int dp;
volatile char cmd;

int main(void)
{
	MCUCR &= ~(1 << WDRF);
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	WDTCSR = 0x00;
	
	lvl = 0;		//set count as zero initially
	ovft = 0;		//set overflow as zero initially
	ovf = 0;
	intflag = false; // set interrupt flag as false initially
	dp = 0;

	EICRA = 0x05; //Any logical change will trigger interrupt
	EIMSK = 0x03; //enable both INT0 and INT1
	TCCR1B = 0x05; //Using precaler 1024
	TIMSK1 = 0x01;
	
	

	sei(); //Enable global interrupt'
	usart_init(1000000); //Usart initialization
	i2c_init(); // Two wire initialization

	printf("Start Up\n");	//Print "start up" when start to indicate the device booted;
    while (1) 
    {
		//print data if intflag set true in interrupt routine
		if(intflag) { 
			if(lvl == 1) { ovf = 0; timer = 0; }
			printf("%u;%u;%u;%i\n", lvl, ovf, timer, dp);
			intflag = false;
		}
		if(cmd == 'a'){
			WDTCSR |= (1 << WDCE) | (1 << WDE);
			while(1);
		}
    }
}

int readsdp(){
	i2c_start(0x80);
	i2c_write(0xF1);
	i2c_start(0x81);
	int hi = i2c_read_ack();
	int lo = i2c_read_nack();
	i2c_stop();
	int value = (hi << 8) | lo;
	return value;
}

ISR(INT1_vect){
	timer = TCNT1;
	ovf = ovft;
	dp = readsdp();
	ovft = 0;
	TCNT1 = 0;
	lvl++;
	intflag = true;
}

ISR(INT0_vect){
	timer = TCNT1;
	ovf = ovft;
	TCNT1 = 0;
	ovft = 0;
	lvl++;
	intflag = true;
}

ISR(TIMER1_OVF_vect){
	ovft++;
}

ISR(USART_RX_vect){
	cmd = UDR0;
}