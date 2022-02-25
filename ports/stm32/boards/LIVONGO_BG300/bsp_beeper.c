/**
 * @file    bsp_beeper.c
 * @brief   Livongo BG300 beeper driver.
 * @author  Gene Kozin <geko@statusbits.com>
 * ----------------------------------------------------------------------------
 * @attention
 * <h2><center>&copy; Copyright (c) 2022 Statusbits.com</center></h2>
 */

#include "bg300.h"

// Beeper GPIO pin
#define BEEPER_GPIO_PORT        GPIOA
#define BEEPER_GPIO_PIN         GPIO_PIN_3
#define BEEPER_GPIO_AF          GPIO_AF1_TIM2

// Beeper Timer block
#define BEEPER_TIMER            TIM2
#define BEEPER_TIMER_CHANNEL    TIM_CHANNEL_4

// Enable clocks for all the hardware modules involved
#define BEEPER_CLK_ENABLE()             \
    do {                                \
        __HAL_RCC_TIM2_CLK_ENABLE();    \
    } while (0)

// Disable clocks for all the hardware modules involved
#define BEEPER_CLK_DISABLE()            \
    do {                                \
        __HAL_RCC_TIM2_CLK_DISABLE();   \
    } while (0)

#define BEEPER_COUNTER_CLOCK    1000000UL   // 1 MHz

// Calculate timer period for a given frequency in Hz
#define BEEPER_PERIOD(hz)       ((BEEPER_COUNTER_CLOCK / (hz)) - 1)

// Default beeper frequency in Hz
#define BEEPER_FREQUENCY        800U

// Timer device handle
static TIM_HandleTypeDef tim_handle;

// Initialize the beeper.
void beeper_init(void)
{
    GPIO_InitTypeDef gpio_init;
    TIM_OC_InitTypeDef oc_conf;
    uint32_t prescaler;
    uint32_t period;

    // Enable peripheral clocks.
    BEEPER_CLK_ENABLE();

    // Configure timer output pin.
    gpio_init.Pin = BEEPER_GPIO_PIN;
    gpio_init.Mode = GPIO_MODE_AF_PP;
    gpio_init.Pull = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    gpio_init.Alternate = BEEPER_GPIO_AF;

    HAL_GPIO_Init(BEEPER_GPIO_PORT, &gpio_init);

    // Compute the prescaler value to obtain the desired counter clock
    prescaler = (SystemCoreClock / BEEPER_COUNTER_CLOCK) - 1;

    // Compute the period value to obtain the desired output frequency
    period = BEEPER_PERIOD(BEEPER_FREQUENCY);

    // Configure the timer peripheral as follows:
    //  ClockDivision = 0
    //  Counter direction = Up
    tim_handle.Instance             = BEEPER_TIMER;
    tim_handle.Init.Prescaler       = prescaler;
    tim_handle.Init.Period          = period;
    tim_handle.Init.ClockDivision   = 0;
    tim_handle.Init.CounterMode     = TIM_COUNTERMODE_UP;

    if (HAL_TIM_PWM_Init(&tim_handle) != HAL_OK) {
        // Fatal error
        BSP_PANIC();
        return;
    }

    // Configure PWM channel
    oc_conf.OCMode      = TIM_OCMODE_PWM1;
    oc_conf.OCPolarity  = TIM_OCPOLARITY_HIGH;
    oc_conf.OCFastMode  = TIM_OCFAST_DISABLE;
    oc_conf.Pulse       = period / 2;           // 50% duty cycle
    if (HAL_TIM_PWM_ConfigChannel(&tim_handle, &oc_conf, BEEPER_TIMER_CHANNEL) != HAL_OK) {
        // Fatal error
        BSP_PANIC();
        return;
    }
}

// De-initialize the beeper.
void beeper_deinit(void)
{
    if (tim_handle.Instance != NULL) {
        // De-initalize timer peripheral
        HAL_TIM_PWM_DeInit(&tim_handle);
    }

    // Reset GPIOs
    HAL_GPIO_DeInit(BEEPER_GPIO_PORT, BEEPER_GPIO_PIN);

    // Disable peripheral clocks.
    BEEPER_CLK_DISABLE();
}

// Turn the beeper on.
void beeper_on(void)
{
    // Start timer channel
    HAL_TIM_PWM_Start(&tim_handle, BEEPER_TIMER_CHANNEL);
}

/**
* @brief    Turn the beeper off.
*/
void beeper_off(void)
{
    // Stop timer channel
    HAL_TIM_PWM_Stop(&tim_handle, BEEPER_TIMER_CHANNEL);
}

// Set the beeper tone frequency (pitch).
void beeper_freq(uint16_t hz)
{
    uint32_t period;
    TIM_OC_InitTypeDef oc_conf;

    // Compute new period value
    period = (BEEPER_COUNTER_CLOCK / hz) - 1;
    if (period < 2) {
        // Error: invalid frequency value
        return;
    }

    // Configure the timer
    tim_handle.Init.Period = period;
    if (HAL_TIM_PWM_Init(&tim_handle) != HAL_OK) {
        // Fatal error
        BSP_PANIC();
        return;
    }

    // Configure PWM channel
    oc_conf.OCMode      = TIM_OCMODE_PWM1;
    oc_conf.OCPolarity  = TIM_OCPOLARITY_HIGH;
    oc_conf.OCFastMode  = TIM_OCFAST_DISABLE;
    oc_conf.Pulse       = period / 2;           // 50% duty cycle
    if (HAL_TIM_PWM_ConfigChannel(&tim_handle, &oc_conf, BEEPER_TIMER_CHANNEL) != HAL_OK) {
        // Fatal error
        BSP_PANIC();
        return;
    }
}

// Make a beeping sound.
void beeper_beep(uint16_t ms)
{
    beeper_on();
    HAL_Delay(ms);
    beeper_off();
}
