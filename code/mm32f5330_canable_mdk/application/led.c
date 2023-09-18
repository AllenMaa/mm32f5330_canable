//
// LED: Handles blinking of status light
//

#include "led.h"
#include "hal_gpio.h"

// Private variables
static uint32_t led_blue_laston = 0;
static uint32_t led_green_laston = 0;
static uint32_t led_blue_lastoff = 0;
static uint32_t led_green_lastoff = 0;

volatile uint32_t uwTick =0;


// Initialize LED GPIOs
void led_init()
{
    SysTick_Config(CLOCK_SYS_FREQ/1000);

    led_blink(2);
}

// Turn green LED on
void led_green_on(void)
{
    // Make sure the LED has been off for at least LED_DURATION before turning on again
    // This prevents a solid status LED on a busy canbus
    if(led_green_laston == 0 && (uwTick - led_green_lastoff) > LED_DURATION)
    {
        // Invert LED
        GPIO_WriteBit(LED_GREEN, 0);
        led_green_laston = uwTick;
    }
}



// Turn green LED off
void led_green_off(void)
{
    GPIO_WriteBit(LED_GREEN, 1);
}


// Blink LED (blocking)
void led_blink(uint8_t numblinks)
{
    uint8_t i;
    for(i=0; i<numblinks; i++)
    {
        GPIO_WriteBit(LED_BLUE, 0);
        GPIO_WriteBit(LED_GREEN, 0);
        HAL_Delay(100);
        GPIO_WriteBit(LED_BLUE, 1);
        GPIO_WriteBit(LED_GREEN, 1);
        HAL_Delay(100);
    }
}


// Attempt to turn on status LED
void led_blue_on(void)
{
    // Make sure the LED has been off for at least LED_DURATION before turning on again
    // This prevents a solid status LED on a busy canbus
    if(led_blue_laston == 0 && (uwTick - led_blue_lastoff) > LED_DURATION)
    {
        GPIO_WriteBit(LED_BLUE, 0);
        led_blue_laston = uwTick;
    }
}

// Attempt to turn off status LED
void led_blue_off(void)
{
    GPIO_WriteBit(LED_BLUE, 1);
}

// Process time-based LED events
void led_process(void)
{
    // If LED has been on for long enough, turn it off
    if(led_blue_laston > 0 && uwTick - led_blue_laston > LED_DURATION)
    {
        GPIO_WriteBit(LED_BLUE, 1);
        led_blue_laston = 0;
        led_blue_lastoff = uwTick;
    }

    // If LED has been on for long enough, turn it off
    if(led_green_laston > 0 && uwTick- led_green_laston > LED_DURATION)
    {
        GPIO_WriteBit(LED_GREEN, 1);
        led_green_laston = 0;
        led_green_lastoff = uwTick;
    }
}

void HAL_Delay(uint32_t delay)
{
    uint32_t tick_start = uwTick;
    uint32_t wait = delay;

    if (wait < HAL_MAX_DELAY)
    {
        wait += 1;
    }

    while ((uwTick - tick_start) < wait)
    {
    }

}

// Handle SysTick interrupt
void SysTick_Handler(void)
{
    uwTick++;
}