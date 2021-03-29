/*
 * SR04.C
 *
 *  Created on: 2020. 4. 8.
 *      Author: master
 */

#include "SR04.h"

float SR04_Echo_HighTime= 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{	if( htim->Instance == TIM1 ) 	TIM1->SR =0;   }


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if( GPIO_Pin == SR04_ECHO_Pin )
	{
		TIM1->CNT =0;
		while( HAL_GPIO_ReadPin( SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) ) {
		}
		SR04_Echo_HighTime = TIM1->CNT ;
	}
}

float SR04_Trigger_out(char microSec)
{
	HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_RESET); // Trigger Pin Low
	TIM1->CNT =0;

	while ( TIM1->CNT  < microSec ) {
		HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_SET); // Trigger Pin High for 10u sec
	}

	HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_RESET); // Trigger Pin Low

	HAL_Delay(10);

	printf("%6.0f mm\r\n",SR04_Echo_HighTime*0.17 );

	return SR04_Echo_HighTime*0.17;
}
