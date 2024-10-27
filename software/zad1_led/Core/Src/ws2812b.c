/*
 * ws2812b.c
 *
 *  Created on: Oct 27, 2024
 *      Author: kamil
 */

/*
 *User sets the brightness of each led in led chain with ws2812b_set_color
 *to pass data to leds run ws2812b update
 *
 */





#include "ws2812b.h"
#include "tim.h"



#define BIT_0_TIME		60 // ~0.4us
#define BIT_1_TIME		120 // ~0.8us

#define RESET_LEN		45  // >50us
#define LED_N			1

// pulses time array for DMA
static uint8_t led_buffer[RESET_LEN + 24 * LED_N + 1];


//set values in array at position "pos"
static void set_byte(uint32_t pos, uint8_t value)
{
  int i;
  for (i = 0; i < 8; i++) {
    if (value & 0x80) {
      led_buffer[pos + i] = BIT_1_TIME;
    } else {
      led_buffer[pos + i] = BIT_0_TIME;
    }
    value <<= 1;
  }
}

// init led_buffer with reset command and zeros (reset leds and turn them off)
void ws2812b_init(void)
{
  int i;
  for (i = 0; i < RESET_LEN; i++)
    led_buffer[i] = 0;

  for (i = 0; i < 24 * LED_N; i++)
    led_buffer[RESET_LEN + i] = BIT_0_TIME;

  led_buffer[RESET_LEN + 24 * LED_N] = 0;

  HAL_TIM_Base_Start(&htim1);
  ws2812b_update();
}


//sends led_buffer to Timer with DMA
void ws2812b_update(void)
{
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)led_buffer, sizeof(led_buffer));
}

// set brightness of each color in selected led
void ws2812b_set_color(uint32_t led, uint8_t red, uint8_t green, uint8_t blue)
{
	if (led < LED_N)
	{
		set_byte(RESET_LEN + 24 * led, green);
		set_byte(RESET_LEN + 24 * led + 8, red);
		set_byte(RESET_LEN + 24 * led + 16, blue);
	}
}














