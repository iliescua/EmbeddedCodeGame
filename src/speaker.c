/*
 * Andrew Iliescu
 * 1/24/19
 * Code for the speaker to init and run func
 */
#include "delay.h"
#include "gpio.h"
#include "timer.h"
#include "speaker.h"

static volatile GPIO* GPIOB = 0x40020400;
static volatile TIM* TIM3 = 0x40000400;
static volatile NOTE correct[] = { { Bb, eighthNote }, { C, eighthNote } };
static volatile NOTE wrong[] = { { G, eighthNote }, { F, eighthNote } };

static NOTE* pointer;

void speaker_init() {
	*(RCC_AHB1ENR ) |= (1 << GPIOB_EN); //Eanbles RCC and configures GPIOB
	*(RCC_APB1ENR ) |= (1 << TIM3_EN);

	GPIOB->MODER &= ~0x00003000; //Sets alt func
	GPIOB->MODER |= 0x00000200;

	GPIOB->AFRL &= ~0x00030000; //Maps pin to timer
	GPIOB->AFRL |= 0x00020000;

	TIM3->CCMR1 &= ~0x00000078; //Set PWM and enable CCRM1
	TIM3->CCMR1 |= 0x00000078;

	TIM3->PSC = 15; //Slows timer sampling
}

void playCorrect() { //Method called to play the notes for a right code
	pointer = &correct[0];
	for (int i = 0; i < 2; i++) { //Loop to run through the whole array
		playNote(pointer->dur, pointer->freq);
		pointer++;
	}
}

void playWrong() { //Method called to play the notes for a wrong code
	pointer = &wrong[0];
	for (int i = 0; i < 2; i++) { //Loop to run through the whole array
		playNote(pointer->dur, pointer->freq);
		pointer++;
	}
}

void playNote(int dur, int freq) {	//Plays a specific note from song
	setFreq(freq);

	TIM3->CCER |= 0x1; //Start timer count
	TIM3->CR1 |= 0x1;

	delay_1ms(dur); //Creates delay of the note played

	TIM3->CCER &= ~(0x1); //End timer count
	TIM3->CR1 &= ~(0x1);
}

void setFreq(int freq) { //Sets tone for each freq
	float tone = 1000000 / freq;
	TIM3->ARR = tone;
	tone = tone / 2;
	TIM3->CCR1 = tone;
}
