/*
 * Andrew Iliescu
 * 2/8/19
 * File that defines the methods for the rotary.c file
 */
#ifndef ROTARY_H_
#define ROTARY_H_
#include <inttypes.h>
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830

//Init the rotary encoder
void rotary_init();
//Returns if rotary encoder is pressed or not
int get_pressed();

#endif
