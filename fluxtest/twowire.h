/*
 * twowire.h
 *
 * Created: 28/11/2016 08:11:32
 *  Author: fadhlika
 */ 


#ifndef TWOWIRE_H_
#define TWOWIRE_H_
#include <avr/io.h>
#include <util/twi.h>
void tw_init();
void tw_start();
void tw_stop();
void tw_write(uint8_t data);
uint8_t tw_read_ack(void);
uint8_t tw_read_nack(void);
uint8_t tw_status(void);
#endif /* TWOWIRE_H_ */