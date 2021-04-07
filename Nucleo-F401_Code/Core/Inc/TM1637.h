/*
 * TM1637.h
 *
 *  Created on: Apr 7, 2021
 *      Author: maste
 */

#ifndef INC_TM1637_H_
#define INC_TM1637_H_

#endif /* INC_TM1637_H_ */

void delay_usec(uint16_t usec);
void TM1637_Clk_High();
void TM1637_Clk_Low();
void TM1637_Dio_High();
void TM1637_Dio_Low();
void TM1637_Start();
void TM1637_Send_Byte(uint8_t byte);
void TM1637_Read_Ack();
void TM1637_Stop();
void TM1637_bright(uint8_t num);
void TM1637_Display_4digit(uint8_t brightness, uint16_t num);
void TM1637_count_down(uint16_t num);

