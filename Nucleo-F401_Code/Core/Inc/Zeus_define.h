/*
 * Zeus_define.h
 *
 *  Created on: 2021. 3. 20.
 *      Author: maste
 */

#ifndef INC_ZEUS_DEFINE_H_
#define INC_ZEUS_DEFINE_H_

#include "stm32f4xx_hal.h"


#endif /* INC_ZEUS_DEFINE_H_ */

#define KEY_DOWN			0xe0
#define KEY_UP				0xb0
#define KEY_LEFT			0x70
#define KEY_RIGHT			0xd0
#define Buzzer_GPIO_Port 	GPIOB
#define Buzzer_Pin  		GPIO_PIN_1


int _write(int file, char *data, int len);
void Buzzer_OnOff(int times);

unsigned char Key_input(void);

uint16_t Average_ADC(uint16_t NumSum, uint8_t NumAvg, uint16_t *Adc);
float Debouce_Value(uint16_t NumSum,uint8_t NumAvg, float *value);
