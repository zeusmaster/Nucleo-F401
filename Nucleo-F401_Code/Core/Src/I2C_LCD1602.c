/*
 * LCD1602.c
 *
 *  Created on: 2020. 3. 27.
 *      Author: zeusmaster
 *
 * Refterences : Mohamed Yaqoob's Code.
 */
#include "I2C_LCD1602.h"
#define LCD1_address 		0x4E // A0,A1,A2 OPEN->E

extern I2C_HandleTypeDef hi2c1;

void I2C_LCD1602_Send_Command(unsigned char command)
{
	char command_MSB, command_LSB;
	uint8_t I2C_cmd[4];
	command_MSB = ( command & 0xf0 );
	command_LSB = ( (command << 4) & 0xf0 ) ;

	I2C_cmd[ 0 ] = command_MSB | 0x0c ; // P3(lcd on) =1, enable = 1, rs = 0
	I2C_cmd[ 1 ] = command_MSB | 0x08 ; // P3(lcd on) =1, enable = 0, rs = 0
	I2C_cmd[ 2 ] = command_LSB | 0x0c ; // P3(lcd on) =1, enable = 1, rs = 0
	I2C_cmd[ 3 ] = command_LSB | 0x08 ; // P3(lcd on) =1, enable = 0, rs = 0

	HAL_I2C_Master_Transmit( &hi2c1, LCD1_address, (uint8_t *) I2C_cmd, 4, 100 );
}

void I2C_LCD1602_Send_Data(unsigned char data)
{
	char data_MSB, data_LSB;
	uint8_t I2C_data[4];
	data_MSB = ( data & 0xf0 ) ;
	data_LSB =  ( (data << 4) & 0xf0 ) ;

	I2C_data[ 0 ] = data_MSB | 0x0d ; // P3(lcd on) =1, enable = 1, rs = 1
	I2C_data[ 1 ] = data_MSB | 0x09 ; // P3(lcd on) =1, enable = 0, rs = 1
	I2C_data[ 2 ] = data_LSB | 0x0d ; // P3(lcd on) =1, enable = 1, rs = 1
	I2C_data[ 3 ] = data_LSB | 0x09 ; // P3(lcd on) =1, enable = 0, rs = 1

	HAL_I2C_Master_Transmit( &hi2c1, LCD1_address, (uint8_t *) I2C_data, 4, 100 );
}

void I2C_LCD1602_Init(void)
{
	HAL_Delay(50);

	I2C_LCD1602_Send_Command( INTERFACE8BIT ); HAL_Delay(5);
	I2C_LCD1602_Send_Command( INTERFACE8BIT ); HAL_Delay(5);
	I2C_LCD1602_Send_Command( INTERFACE8BIT ); HAL_Delay(5);
	I2C_LCD1602_Send_Command( MODE4bit ); HAL_Delay(5);

	I2C_LCD1602_Send_Command(FUNCTIONSET ); HAL_Delay(5); // 4bit 2line font5x10
	I2C_LCD1602_Send_Command( DISPLAYON ); HAL_Delay(5);
	I2C_LCD1602_Send_Command( ALLCLR ); HAL_Delay(5);
	I2C_LCD1602_Send_Command( ENTMODE ); HAL_Delay(5);
}

void I2C_LCD1602_Send_string( char *string)
{
	while( * string ) I2C_LCD1602_Send_Data( *string++ );
}
void I2C_LCD1602_GotoXY(char x, char y)
{
	if( !y ) I2C_LCD1602_Send_Command( 0x80 | x );
	else I2C_LCD1602_Send_Command( 0xC0 | x );
}

void I2C_LCD1602_Send_String_XY( char x, char y, char *string )
{
	I2C_LCD1602_GotoXY( x , y );
	I2C_LCD1602_Send_string( string );
}
void I2C_LCD1602_BlinkOn(void) 		{ I2C_LCD1602_Send_Command( DISPLAYON | 0x01); }
void I2C_LCD1602_BlinkOff(void) 	{ I2C_LCD1602_Send_Command( DISPLAYON & ~0x01); }
void I2C_LCD1602_CursorOn(void) 	{ I2C_LCD1602_Send_Command( DISPLAYON | 0x02); }
void I2C_LCD1602_CursorOff(void) 	{ I2C_LCD1602_Send_Command( DISPLAYON & ~0x02); }

void I2C_LCD1602_Clear()
{
/*	I2C_LCD1602_Send_Command (0x80);
	for (int i=0; i<70; i++)
	{
		I2C_LCD1602_Send_Data (' ');
	}*/
	I2C_LCD1602_Send_Command(ALLCLR); HAL_Delay(1);
	I2C_LCD1602_Send_Command(0x80); HAL_Delay(1);
}
