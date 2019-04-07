/*
 * Andrew Iliescu
 * 1/23/19
 * File that defines the methods for the speaker.c file
 */
#ifndef SPEAKER_H_
#define SPEAKER_H_

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define GPIOB_EN 1
#define TIM3_EN 1

//Duration of the different notes
#define halfNote 800
#define quarterNote 400
#define dottedQuarterNote 600
#define eighthNote 200

//Notes for Ode to Joy
#define A 880
#define Bb 932
#define C 1046
#define G 784
#define F 698

//Init Speaker
void speaker_init();
//Plays sound when correct code is entered
void playCorrect();
//Plays sound when wrong code is entered
void playWrong();
//Method that plays an individual note for a set duration
void playNote(int dur, int freq);
//Method to set the notes freq
void setFreq(int freq);

typedef struct { //The parameters for what a note needs
	int freq;
	int dur;
} NOTE;

#endif
