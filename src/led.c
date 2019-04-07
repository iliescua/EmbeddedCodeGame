/*
 * led.c
 *  Created on: Dec 1, 2018
 *      Author: livingston
 *      Updated: Andrew Iliescu
 */

#include "led.h"
#include "delay.h"
#include <inttypes.h>
#include <stdio.h>

#define MODER_MASK 0x55155400
#define LED_on 0x0000F7E0
#define LED_off 0x0000FFFF

//Init speed and level
static int speed= 100;
static int level = 2;

//Init the LED by configuring pins
void led_init(){
*(RCC_AHB1ENR) = *(RCC_AHB1ENR) &~ 0x00000002;
*(RCC_AHB1ENR) = *(RCC_AHB1ENR) | (1 << GPIOBEN);
*(GPIOB_MODER) = *(GPIOB_MODER) &~ 0xFF3FFC00;
*(GPIOB_MODER) = *(GPIOB_MODER) | MODER_MASK;
}

//Turns on all LED
void led_allOn(){
*(GPIOB_ODR) = *(GPIOB_ODR) &~ 0x0000F7E0;
*(GPIOB_ODR) = *(GPIOB_ODR) | LED_on;
}

//Turns off all the LED
void led_allOff(){
*(GPIOB_ODR) = *(GPIOB_ODR) &~ 0x0000F7E0;
}

//Turns on just one LED
void led_on(uint8_t ledIndex){
*(GPIOB_BSRR) = 1 << ledIndex;
}

//Turns off one LED
void led_off(uint8_t ledIndex){
*(GPIOB_ODR) = (0 << ledIndex);
}

//Moves LED's back and forth #Knightrider
void led_scan(){
	for(int i = 5; i < 16; i++){
		if(i == 15){
			led_on(i);
			delay_1ms(speed);
		}else if(i != 11){
			led_on(i);
			delay_1ms(speed);
			led_off(i);
	}
}//Go right with LED's
	for(int i = 15; i > 4; i--){
		if(i == 15){
			led_off(i);
		}else if(i != 11){
			led_on(i);
			delay_1ms(speed);
			led_off(i);
		}
	}
}

//Pulses the LED
void led_flash(){
	for(int i = 0; i < 5; i++){
		led_allOn();
		delay_1ms(speed);
		led_allOff();
		delay_1ms(speed);
	}
}

//Sets the speed of the scan
void led_setSpeed(uint8_t speed){
speed = (uint32_t)speed;
}

//Increases the level of speed by 1 til 9
void led_incSpeed(){
	level += 1;
	if(level <= 9){
		speed= speed / 2;
	} else {
		level = 9;
		printf("Max High Speed \n");
	}
}

//Decreases the level of speed by 1 til 9
void led_decSpeed(){
	level -= 1;
	if(level >= 0){
		speed= speed * 2;
	} else {
		level = 0;
		printf("Max Low Speed \n");
	}
}

//Gets the current level of speed
uint8_t getCurrentSpeed()
{
return ((uint8_t)level);
}

