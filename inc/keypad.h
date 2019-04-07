/*
 * Andrew Iliescu
 * 12/22/18
 * Holds all the methods for the keypad.c file
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
//Init keypad
void key_init();
//Returns the key pressed as 1-16 val
int key_getkey();
//Checks what key was pressed
int key_getkey_noblock();
//Turns the pressed key back to ASCII to be displayed
char key_getchar();

#endif
