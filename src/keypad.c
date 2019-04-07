/* Andrew Iliescu
 * 12/22/18
 * Initializes and provides basic keypad functions
 */
#include "keypad.h"
#include "delay.h"
#include "gpio.h"

static volatile GPIO* GPIO_C = 0x40020800;
static volatile int GPIOC_EN = 2;
static volatile int key = 0;

void key_init() {	//Init keypad
	//Enable GPIOC with RCC
	*(RCC_AHB1ENR ) = *(RCC_AHB1ENR ) | (1 << GPIOC_EN);
	//Row pins 4-7 to input
	//Col pins 0-3 to output
	GPIO_C->MODER &= ~0x0000FFFF;
	GPIO_C->MODER |= 0x00000055;
	//PUPDR to pull up
	GPIO_C->PUPDR &= ~0x0000FFFF;
	GPIO_C->PUPDR |= 0x00005555;
}

int key_getkey() {	//Returns the value of the pressed key (1-16)
	int input = 0;
	key = 0;

	while (key == 0) { //Checks if a key is pressed
		key = key_getkey_noblock();
	}
	input = key; //Makes copy of key
	while (key != 0) { //Waits until key is released making it on pull up config
		key = key_getkey_noblock();
	}
	return input;
}

int key_getkey_noblock() {	//Checks if a key is pressed
	int rowMap[] = { 0, 0, 4, 0, 8, 0, 0, 0, 12 };
	int colMap[] = { 0, 1, 2, 0, 3, 0, 0, 0, 4 };
	int row = (0xF & (~(GPIO_C->IDR & 0x000000F0) >> 4));

	if (row == 0b0000) {	//Checks which row the pressed key if from
		return 0; //Keys not pressed
	} else {	//Checks where the key is pressed and returns location
		GPIO_C->MODER &= ~0x0000FFFF;
		GPIO_C->MODER |= 0x00005500;
		delay_1us(1);
		int col = (0xF & (~(GPIO_C->IDR & 0x0000000F)));
		row = rowMap[row];
		col = colMap[col];
		GPIO_C->MODER &= ~0x0000FFFF;
		GPIO_C->MODER |= 0x00000055;
		return row + col;
	}
}

char key_getchar() {	//Converts the pressed key back to ASCII to be displayed
	key = 0;
	key = key_getkey(); //Gets the key that was pressed
	char keycode[17] = {'\0', '1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8',
			'9', 'C', '*', '0', '#', 'D'};
	return keycode[key];	//Replaces the pressed key with its ASCII value
}
