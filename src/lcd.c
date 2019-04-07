/* Andrew Iliescu
 * 12/22/18
 * Initializes and provides basic lcd functions
 */
#include "delay.h"
#include "lcd.h"
#include "gpio.h"

static volatile GPIO* GPIOC = 0x40020800;
static volatile GPIO* GPIOA = 0x40020000;
static int GPIOAEN = 0;
static int GPIOCEN = 2;
static uint8_t LCD_TWOLINE = 0x38;
static uint8_t LCD_CLEAR = 0x01;
static uint8_t LCD_HOME = 0x02;
static uint8_t LCD_ENTRY = 0x06;
static uint8_t LCD_DISP = 0x0F;


void lcd_init() {	//Init the lcd
	delay_1ms(50);	//Power delay

	//Enable GPIO pins A and C using RCC
	*(RCC_AHB1ENR ) = *(RCC_AHB1ENR ) | (1 << GPIOAEN);
	*(RCC_AHB1ENR ) = *(RCC_AHB1ENR ) | (1 << GPIOCEN);
	//Set selet pins to ouputs
	GPIOA->MODER &= ~0x00FFFF00;
	GPIOA->MODER |= 0x00555500;
	GPIOC->MODER &= ~0x003F0000;
	GPIOC->MODER |= 0x00150000;


	lcd_cmd((uint8_t) LCD_TWOLINE);	//Init both lines on lcd
	lcd_cmd((uint8_t) LCD_CLEAR);	//Clear lcd
	delay_1ms(2);

	lcd_cmd((uint8_t) LCD_HOME);	//Take cursor back to start spot
	delay_1ms(2);
	lcd_cmd((uint8_t) LCD_ENTRY);
	lcd_cmd((uint8_t) LCD_DISP);	//Turn on lcd
}

void lcd_clear() {	//Clears lcd
	lcd_cmd((uint8_t) LCD_CLEAR);
	delay_1ms(2);
}

void lcd_home() {	//Sets cursor back to start position
	lcd_cmd((uint8_t) LCD_HOME);
	delay_1ms(2);
}

void lcd_set_position(int row, int column) {	//Sets the location of the cursor on the screen
	lcd_home();	//Places cursor at start
	if (row >= 0 && row < 16) {
		if (column == 1) {	//Checks to see desired row
			row += 0x40;
		}
		row = row | (1 << 7);
		lcd_cmd(row);
		delay_1ms(2);
	} else {	//Data too large
		char *error = "Position Err\n";
		lcd_print_string(error);
		while (1 == 1) {
		}
	}
}

void lcd_print_num(int num) {	//Prints nums to lcd
	int arraySize = 16;
	char numList[16] = { 0 };
	int numDisp = 0;

	sprintf(numList, "%i", num);
	for (int i = 0; i < arraySize; i++) {
		if (numList[i] > 0) {
			lcd_data((uint8_t) numList[i]);
			numDisp++;
		} else {
		}
	}
}

void lcd_print_string(char* string) {	//Prints chars to lcd
	int arraySize = 16;
	int charDisp = 0;
	for (int i = 0; i < arraySize; i++) {
		if (string[i] != '\0') {
			lcd_data((uint8_t) string[i]);
			charDisp++;
		} else {
			i = arraySize;
		}
	}
}

void lcd_cmd(uint8_t data) {	//Sets lcd up to do commands
	GPIOC->BSRR |= (1 << 9) << 16; //rw
	GPIOC->BSRR |= (1 << 8) << 16; //rs
	lcd_exec(data);
}

void lcd_data(uint8_t data) {	//Preps lcd for data
	GPIOC->BSRR |= (1 << 9) << 16; //rw
	GPIOC->BSRR |= (1 << 8); //rs
	lcd_exec(data);
}

void lcd_exec(uint8_t data) {	//Executes the command
	lcd_set(data);
	lcd_latch();	//Pulses enable bit
	delay_1us(100);
}

void lcd_set(uint8_t data) {	//Sets data to output
	GPIOA->ODR &= ~0xFF0;
	GPIOA->ODR |= data << 4;
}

void lcd_latch() {	//Pulses enable bit so data can be sent
	GPIOC->BSRR |= (1 << 10); //Pulse E high
	delay_1us(10);
	GPIOC->BSRR |= (1 << 10) << 16; //Pulse E low
	delay_1us(10);
}
