/*
 * Andrew Iliescu
 * 2/9/19
 * Code for the rotary to init and run func
 */
#include "rotary.h"
#include "gpio.h"

static volatile GPIO* GPIO_A = 0x40020000;
void rotary_init() { //Init rotary encoder
	//Enable GPIOA with RCC
	*(RCC_AHB1ENR ) = *(RCC_AHB1ENR ) | (1);
	//Set P12 to input
	GPIO_A->MODER &= ~0x03000000;
	GPIO_A->MODER |= 0x00000000;
	//PUPDR to pull up
	GPIO_A->PUPDR &= ~0x03000000;
	GPIO_A->PUPDR |= 0x01000000;
}

int get_pressed(){ //Method to check if rotary encoder gets pressed
	int pressed = (GPIO_A->IDR);
	pressed &= (0x1000);
	pressed = pressed >> 12;
	if (pressed == 1){
		return 0;
	}else{
		return 1;
	}
}
