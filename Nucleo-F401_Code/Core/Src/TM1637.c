/*
 * TM1637.c
 *
 *  Created on: Apr 7, 2021
 *      Author: maste
 */
#include "main.h"
#include "TM1637.h"

#define cmd_write_data	0x40
#define cmd_disp_on		0x88
#define cmd_disp_off	0x80

void TM1637_Clk_High() 	{ HAL_GPIO_WritePin(FND_CLK_GPIO_Port, FND_CLK_Pin, GPIO_PIN_SET); }
void TM1637_Clk_Low()   { HAL_GPIO_WritePin(FND_CLK_GPIO_Port, FND_CLK_Pin, GPIO_PIN_RESET); }
void TM1637_Dio_High()	{ HAL_GPIO_WritePin(FND_DIO_GPIO_Port, FND_DIO_Pin, GPIO_PIN_SET); }
void TM1637_Dio_Low()	{ HAL_GPIO_WritePin(FND_DIO_GPIO_Port, FND_DIO_Pin, GPIO_PIN_RESET); }

uint8_t tick =1;
const char fnd[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

void delay_usec(uint16_t usec)
{
	volatile uint32_t i,j;
	for( i=0; i < usec*2 ; i++ ) {
		for( j=0 ; j< 84 ; j++) {
			//__asm__ __volatile__("nop\n\t":::"memory");
			asm("NOP");
		}
	}
}

void TM1637_Start()
{
	TM1637_Clk_High();
	TM1637_Dio_High(); delay_usec(tick);
	TM1637_Dio_Low(); delay_usec(tick);
	TM1637_Clk_Low();
}

void TM1637_Send_Byte(uint8_t byte)
{
	for( uint8_t i=0 ; i <8 ; i++ ) {
		TM1637_Clk_Low();

		if( byte & 0x01 ) {TM1637_Dio_High();}
		else TM1637_Dio_Low();

		delay_usec(tick);
		TM1637_Clk_High();
		delay_usec(tick);
		byte >>=1;
	}
}

void TM1637_Read_Ack()
{
	TM1637_Clk_Low();
	TM1637_Dio_Low(); delay_usec(tick);
	TM1637_Clk_High(); delay_usec(tick);
}

void TM1637_Stop()
{
	TM1637_Clk_Low();
	TM1637_Dio_Low(); delay_usec(tick);
	TM1637_Clk_High(); delay_usec(tick);
}

void TM1637_bright(uint8_t num)
{
	TM1637_Start();
	TM1637_Send_Byte(0x87 + num);
	TM1637_Read_Ack();
	TM1637_Stop();
}

void TM1637_Display_4digit(uint16_t num)
{
	uint8_t digit[4], i;
	for( i = 0; i < 4 ; i++ ) {
		digit[i] = num %10;
		num = num/10;
	}
	// command1 => write data
	TM1637_Start();
	TM1637_Send_Byte(cmd_write_data);
	TM1637_Read_Ack();
	TM1637_Stop();

	// command2 => address
	TM1637_Start();
	TM1637_Send_Byte(0xc0);
	TM1637_Read_Ack();

	// data1...data4
	for( i = 0; i < 4 ; i++ ) {
		TM1637_Start();
		TM1637_Send_Byte( fnd[ digit[3-i] ]);
		TM1637_Read_Ack();
	}

	// command3 => control display
	TM1637_Start();
	TM1637_Send_Byte(0x88);
	TM1637_Read_Ack();
	TM1637_Stop();
}
