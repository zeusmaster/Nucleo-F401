/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "I2C_LCD1602.h"
#include "Zeus_define.h"
#include "u8g_arm.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

static u8g_t u8g;
uint8_t Hour=0, Minute=0, Second=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void u8g_xyputs( uint8_t x, uint8_t y, char *str, uint8_t battery_status);
void Time_count()
{
	Second++;
	if( Second > 59 )	{
	  Minute ++;		Second = 0;
	}
	if (Minute > 59 ) 	{
	  Hour++;			 Minute =0;
	}
	if( Hour > 11) Hour = 0;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t Adc_Value[2];
	char str[16];


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)Adc_Value, 1);

  u8g_InitComFn(&u8g,&u8g_dev_ssd1306_128x64_i2c,u8g_com_hw_i2c_fn);

  I2C_LCD1602_Init();

  I2C_LCD1602_Send_String_XY( 0 , 0, "Welcom Zeus");
  I2C_LCD1602_Send_String_XY( 0 , 1, "I2C PCF8574");
  HAL_Delay(2000);
  I2C_LCD1602_Clear();

  sprintf( str, "start");
  I2C_LCD1602_Send_string(str);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Buzzer_OnOff(1);

  uint16_t AvgAdc=0;
  uint16_t count = 0;

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  u8g_xyputs( 10, 55, "Zeus SSD1306",count++);
	  	  Time_count();
	  	  if( count >100 ) count = 0;

	  AvgAdc = Average_ADC(200, 10,Adc_Value);

	  sprintf( str, "ADC : %4d", AvgAdc );
	  I2C_LCD1602_Send_String_XY( 0 , 0, str);

	  //HAL_Delay(500);



	  switch( Key_input() ) {
	  case KEY_UP:
		  I2C_LCD1602_Send_String_XY( 0 , 1, "UP    pressed");
		  break;

	  case KEY_DOWN:
		  I2C_LCD1602_Send_String_XY( 0 , 1, "DOWN  pressed");
		  break;

	  case KEY_RIGHT:
		  I2C_LCD1602_Send_String_XY( 0 , 1, "RIGHT pressed");
		  break;

	  case KEY_LEFT:
		  I2C_LCD1602_Send_String_XY( 0 , 1, "LEFT  pressed");
		  break;

	  default:
		  break;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void u8g_battery_status(uint8_t x, uint8_t y, uint8_t percentage)
{
	char str[5];
	u8g_DrawFrame(&u8g, x, y, 18, 7); // battery����
	u8g_DrawFrame(&u8g, x+18,y+(5/2), 2,3); //battery����ǥ��
	uint8_t battery_step = 5;
	if( percentage > 90 ) 		battery_step =5;
	else if (percentage <= 10 )	battery_step =0;
	else if (percentage <= 20 )	battery_step =1;
	else if (percentage <= 40 )	battery_step =2;
	else if (percentage <= 60 )	battery_step =3;
	else if (percentage <= 80 )	battery_step =4;

	switch( battery_step )
	{
	case 1:
		u8g_draw_box(&u8g,x+2,y+1,2,5);
		break;
	case 2:
		u8g_draw_box(&u8g,x+2,y+1,2,5);
		u8g_draw_box(&u8g,x+5,y+1,2,5);
		break;
	case 3:
		u8g_draw_box(&u8g,x+2,y+1,2,5);
		u8g_draw_box(&u8g,x+5,y+1,2,5);
		u8g_draw_box(&u8g,x+8,y+1,2,5);
		break;
	case 4:
		u8g_draw_box(&u8g,x+2,y+1,2,5);
		u8g_draw_box(&u8g,x+5,y+1,2,5);
		u8g_draw_box(&u8g,x+8,y+1,2,5);
		u8g_draw_box(&u8g,x+11,y+1,2,5);
		break;
	case 5:
		u8g_draw_box(&u8g,x+2,y+1,2,5);
		u8g_draw_box(&u8g,x+5,y+1,2,5);
		u8g_draw_box(&u8g,x+8,y+1,2,5);
		u8g_draw_box(&u8g,x+11,y+1,2,5);
		u8g_draw_box(&u8g,x+14,y+1,2,5);
		break;
	}
	u8g_SetFont( &u8g, u8g_font_courB08 );
	sprintf( str, "%d%%",percentage);
	u8g_DrawStr( &u8g,  x-25,  y+7, str );
}
void u8g_xyputs( uint8_t x, uint8_t y, char *str, uint8_t battery_status)
{
	char Str_HM[20],Str_Sec[10];
	sprintf( Str_HM, "%02d:%02d", Hour, Minute);
	sprintf( Str_Sec, "%02d", Second);
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont( &u8g, u8g_font_courB10 );
		u8g_DrawStr( &u8g,  x,  y, str );

		//u8g_DrawBitmap(&u8g,10,1,16,52,Zeus_logo);
		u8g_SetFont( &u8g, u8g_font_osb21 );
		u8g_DrawStr( &u8g, 35,40,&Str_HM[0]);

		u8g_SetFont( &u8g, u8g_font_gdb11 );
		u8g_DrawStr( &u8g, 108,38,&Str_Sec[0]);

		u8g_battery_status(100,6,battery_status);


		u8g_DrawFrame(&u8g,2,2,126,62);
		u8g_DrawFrame(&u8g,1,1,127,63);
	} while( u8g_NextPage(&u8g));
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
