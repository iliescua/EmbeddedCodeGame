/*
 * Andrew Iliescu
 * 2/7/19
 * Main file that provides the logic for the game
 */
#include <stdio.h>
#include <stdlib.h>
#include "speaker.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "gpio.h"
#include "led.h"
#include "rotary.h"

static char possibleKey[16] = "123A456B789C*0#D"; //Array that holds all possible keys
static char code[4]; //The array that stores the generated code
static char key[2]; //The key for what the user entered
static int score = 0; //Player's score
static int userIn; //The number the player enters at the start to give seed to random code generator
static int entered = 0; //Value to keep track if rotary is entered
static int track = 0; //Keeps track of whether all values in arrays match up

int main() { //Main method
	lcd_init();	//Initializes the different components used
	key_init();
	speaker_init();
	led_init();
	rotary_init();

	int compare = 0; //Variable that checks if the codes are the same
	introScreen();	//Method that displays the intro prompt
	newCode(); //Method that displays the random code generated

	while (score != 5) { //Loop to run until proper score is reached
		compare = compare_Array(); //Sets the whether the codes are the same to compare
		if (compare == 1) { //If codes are equal
			score++; //increment player score
			lcd_set_position(15, 1); //Places all of the displays properly
			lcd_print_num(score);
			delay_1ms(300);
			enterRight();
			compare = 0; //Sets compare to false so it can check again
			newCode(); //Calls the method to generate a new rand code
		} else { //If codes are not equal
			score = 0; //Player score is wiped
			lcd_set_position(15, 1); //Places displays properly for wrong code entered
			lcd_print_num(score);
			enterWrong();
			newCode();
		}
	}

	lcd_clear(); //Runs when player wins
	lcd_set_position(0, 0);
	lcd_print_string("Congratulations!");
	lcd_set_position(0, 1);
	lcd_print_string("You Beat My Game");

	return 0;
}

int compare_Array() { //Method compares the codes
	int returnVal = 0;
	lcd_set_position(0, 0);
	lcd_print_string("Enter Your Code:");
	lcd_set_position(0, 1);
	for (int i = 0; i < 4; i++) { //Checks each value in the codes against each other
		key[0] = key_getchar();
		if (key[0] == code[i]) {
			lcd_print_string(key);
			track++;
		} else {
			track = 0;
			lcd_print_string(key);
		}
	}
	returnVal = isEntered();
}

void generate_Random() { //Method generates a random code
	int num = 0;
	for (int i = 0; i < 4; i++) {
		num = (rand() % 16);
		code[i] = possibleKey[num];
	}
	code[4] = '\0';
}

void newCode() { //Method that prints out when a new code is generated
	if (score != 5) {
		lcd_clear();
		lcd_set_position(1, 0);
		lcd_print_string("Remember This!");
		delay_1ms(1000);
		generate_Random();
		lcd_set_position(6, 1);
		lcd_print_string(code);
		delay_1ms(500);
		lcd_clear();
		lcd_set_position(9, 1);
		lcd_print_string("Score:");
		lcd_set_position(15, 1);
		lcd_print_num(score);
	} else {
	}
}

void enterRight() { //If the player enter correct code, perform these operations
	playCorrect();
	lcd_clear();
	lcd_set_position(3, 0);
	lcd_print_string("Great Job!");
	led_flash();
	led_on(score + 4);
}

void enterWrong() { //If the player enters an invalid code, perform these operations
	playWrong();
	lcd_clear();
	lcd_set_position(3, 0);
	lcd_print_string("Try Again!");
	led_allOn();
	delay_1ms(1000);
	led_allOff();
}

void introScreen() { //The initial start screen of the game that runs once
	lcd_set_position(0, 0);
	lcd_print_string("Welcome to The");
	lcd_set_position(0, 1);
	lcd_print_string("Memory Challenge");
	delay_1ms(2000);
	lcd_clear();
	lcd_set_position(0, 0);
	lcd_print_string("Enter A Value In");
	lcd_set_position(0, 1);
	lcd_print_string("The Range 1-9:");
	userIn = key_getchar();
	srand(userIn); //Sets the start seed for the random code generator
}

int isEntered() {//Recursive method for looping while rotary isn't pressed
	entered = get_pressed();
	delay_1ms(1);
	if (entered == 1) {
		if (track == 4) { //If codes match return 1
			return 1;
		} else { //If codes don't match, return 0
			return 0;
		}
	}else {
		isEntered();
	}
}
