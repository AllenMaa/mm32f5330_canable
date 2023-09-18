#ifndef __LED_H
#define __LED_H

#include "stdint.h"
#include "board_init.h"

#define LED_DURATION        100u

#define HAL_MAX_DELAY       0xFFFFFFFFu

void led_init();
void led_blink(uint8_t numblinks);
void led_green_on(void);
void led_green_off(void);
void led_blue_on(void);
void led_blue_off(void);
void led_process(void);
void HAL_Delay(uint32_t delay);

#endif
