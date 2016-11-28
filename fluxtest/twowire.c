/*
 * twowire.c
 *
 * Created: 27/11/2016 22:11:33
 * Author : fadhlika
 */ 
#include "twowire.h"

void tw_init(){
	TWBR = 0x0C;
	TWSR = 0x00;
	TWCR = (1 << TWEN);
}

void tw_start(){
	TWCR |= (1 << TWINT) | (1 << TWSTA);
	while ((TWCR & (1 << TWINT)) == 0);
}

void tw_stop(){
	TWCR |= (1 << TWINT) | (1 << TWSTO);
}

void tw_write(uint8_t data){
	TWDR = data;
	TWCR |= (1 << TWINT);
	while ((TWCR & (1 << TWINT)) == 0);
}

uint8_t tw_read_ack(void){
	TWCR |= (1 << TWINT) | (1 << TWEA);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

uint8_t tw_read_nack(void){
	TWCR |= (1 << TWINT);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

uint8_t tw_status(void){
	uint8_t status;
	status = TWSR & 0xF8;
	return status;
}