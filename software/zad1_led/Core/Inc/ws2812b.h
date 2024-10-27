/*
 * ws2812b.h
 *
 *  Created on: Oct 27, 2024
 *      Author: kamil
 */

#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_


#include<stdlib.h>
#include<stm32g474xx.h>


void ws2812b_init(void);

void ws2812b_set_color(uint32_t led, uint8_t red, uint8_t green, uint8_t blue);

void ws2812b_update(void);




#endif /* INC_WS2812B_H_ */
