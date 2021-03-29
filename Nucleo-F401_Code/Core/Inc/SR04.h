/*
 * SR04.h
 *
 *  Created on: 2020. 4. 8.
 *      Author: master
 */

#ifndef SR04_H_
#define SR04_H_



#endif /* SR04_H_ */

#include "main.h"
#include "stdio.h"



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

float SR04_Trigger_out(char microSec);


