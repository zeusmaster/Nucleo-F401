/*
 * LCD1602.h
 *
 *  Created on: 2020. 3. 27.
 *      Author: zeusmaster
 */

#ifndef LCD1602_H_
#define LCD1602_H_



#endif /* LCD1602_H_ */

#include "main.h"


// Define for LCD1602
#define	ALLCLR				0x01
#define 	ENTMODE			0x06
#define	DISPLAYON			0x0c
#define	LSHIFT					0x18
#define	FUNCTIONSET		0x2c 	// 4bit mode 2line
#define	INTERFACE8BIT	0x30
#define 	MODE4bit			0x20

void I2C_LCD1602_Send_Command(unsigned char command);
void I2C_LCD1602_Send_Data(unsigned char data);

void I2C_LCD1602_Init(void);
void I2C_LCD1602_Send_string( char *string);
void I2C_LCD1602_GotoXY(char x, char y);
void I2C_LCD1602_Send_String_XY( char x, char y, char *string );
void I2C_LCD1602_BlinkOn(void) ;
void I2C_LCD1602_BlinkOff(void) ;
void I2C_LCD1602_CursorOn(void) ;
void I2C_LCD1602_CursorOff(void) ;
void I2C_LCD1602_Clear() ;


