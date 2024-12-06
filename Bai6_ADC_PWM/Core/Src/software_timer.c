/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1


uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;

uint16_t flag_timer_senduart = 0;
uint16_t timer_senduart_counter = 0;
uint16_t timer_senduart_MUL = 0;

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

void setTimer2(uint16_t duration){
	timer2_MUL = duration/TIMER_CYCLE_2;
	timer2_counter = timer2_MUL;
	flag_timer2 = 0;
}

void setTimerSendUart(uint16_t duration){
	timer_senduart_MUL = duration/TIMER_CYCLE_2;
	timer_senduart_counter = timer_senduart_MUL;
	flag_timer_senduart = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter == 0) {
				flag_timer2 = 1;
				timer2_counter = timer2_MUL;
			}
		}

		if(timer_senduart_counter > 0){
			timer_senduart_counter--;
			if(timer_senduart_counter == 0){
				flag_timer_senduart = 1;
				timer_senduart_counter = timer_senduart_MUL;
			}
		}

		led7_Scan();
	}
}

