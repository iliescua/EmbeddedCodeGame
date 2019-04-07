/*
 * Andrew Iliescu
 * 12/22/18
 * Holds all the methods for the lcd.c file
 */

#ifndef LCD_H_
#define LCD_H_

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830

//Inits lcd
void lcd_init();
//Clears lcd screen
void lcd_clear();
//Places cursor back to start
void lcd_home();
//Places cursor at a certain lcd spot
void lcd_set_position();
//Prints nums to the lcd
void lcd_print_num();
//Prints strings to the lcd
void lcd_print_string();

#endif
