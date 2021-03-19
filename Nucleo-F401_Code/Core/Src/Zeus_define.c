/*
 * Zeus_define.c
 *
 *  Created on: 2021. 3. 20.
 *      Author: maste
 */


#include "Zeus_define.h"


// =================  printf function for debugging ======================
extern UART_HandleTypeDef huart2;
int _write(int file, char *data, int len)
{
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2,(uint8_t *)data,len,1000);
	return (status == HAL_OK ? len : 0);
}

// =================  Buzzer function ======================
void Buzzer_OnOff(int times)
{
	for(int i=0;i< times ; i++)
	{
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET); HAL_Delay(10);
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET); HAL_Delay(10);
	}
}

// 코드참조 : 윤덕용교수님저서 STM32F745정복
// =================  Key function  ======================


unsigned char key_flag = 0;

unsigned char Key_input(void)			// input key KEY1~KEY4
{
  unsigned char key;

  key = GPIOB->IDR & 0x000000F0;		// any key pressed ?
  if(key == 0xF0)						// if no key, check key off
    { if(key_flag == 0)
        return key;
      else
        { HAL_Delay(20);
          key_flag = 0;
          return key;
        }
    }
  else									// if key input, check continuous key
    { if(key_flag != 0)					// if continuous key, treat as no key input
        //return 0xF0;
    	return key;
      else								// if new key, beep and delay for debounce
        { Buzzer_OnOff(1);
          key_flag = 1;
          return key;
        }
    }
}
// =================  End of Key function  ====================
