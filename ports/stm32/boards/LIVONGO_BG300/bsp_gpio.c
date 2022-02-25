/**
 * @file    bsp_gpio.c
 * @brief   Livongo BG300 GPIO driver module.
 * @author  Gene Kozin <geko@statusbits.com>
 * ----------------------------------------------------------------------------
 * @attention
 * <h2><center>&copy; Copyright (c) 2022 Statusbits.com</center></h2>
 */

#include "bg300.h"

#ifndef BSP_NUM_GPIO
# define BSP_NUM_GPIO   GPIO_MAX_PORT
#endif

// GPIO port handle map
static GPIO_TypeDef * const gpio_handle[BSP_NUM_GPIO] =
{
    GPIOA, GPIOB, GPIOC, GPIOD, GPIOE
};

// GPIO pin mask map
static uint16_t const gpio_pins[16] =
{
    GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,  GPIO_PIN_3,
    GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,
    GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};

// Returns GPIO port handle for a given GPIO pin ID
static inline GPIO_TypeDef * gpio_get_handle(pin_id_t pin_id)
{
    unsigned port = (pin_id >> 4) & 0x07;
    return (port < BSP_NUM_GPIO) ? gpio_handle[port] : NULL;
}

// Returns GPIO pin mask for a given GPIO pin ID
static inline uint16_t gpio_get_pin(pin_id_t pin_id)
{
    return gpio_pins[pin_id & 0xF];
}

// Initialize GPIO pins.
void gpio_init(gpio_conf_t const * conf)
{
    // Enable GPIO clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    // Configure GPIO pins
    if (conf) {
        while (conf->pin != GPIO_INVALID_ID) {
            gpio_configure(conf->pin, conf->mode, conf->speed, conf->pud, conf->state);
            conf++;
        }
    }
}

// De-initialize GPIO pin.
void gpio_deinit(pin_id_t pin_id)
{
    register GPIO_TypeDef * gpio = gpio_get_handle(pin_id);
    register uint16_t pin = gpio_get_pin(pin_id);
    GPIO_InitTypeDef gpio_init;

    if (gpio != NULL) {
        HAL_GPIO_DeInit(gpio, pin);

        // Put the pin in low-power mode
        gpio_init.Pin       = pin;
        gpio_init.Mode      = GPIO_MODE_ANALOG;
        gpio_init.Pull      = GPIO_NOPULL;
        gpio_init.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio_init.Alternate = 0;
        HAL_GPIO_Init(gpio, &gpio_init);
    }
}

// Configure GPIO pin.
void gpio_configure(pin_id_t pin_id, uint32_t mode, uint8_t speed, uint8_t pud, int state)
{
    register GPIO_TypeDef * gpio = gpio_get_handle(pin_id);
    register uint16_t pin = gpio_get_pin(pin_id);
    GPIO_InitTypeDef gpio_init;

    if (gpio == NULL) {
        // Error: invalid pin ID
        BSP_PANIC();
        return;
    }

    gpio_init.Pin       = (uint32_t)pin;
    gpio_init.Mode      = (uint32_t)mode;
    gpio_init.Pull      = (uint32_t)pud;
    gpio_init.Speed     = (uint32_t)speed;
    gpio_init.Alternate = 0;
    HAL_GPIO_Init(gpio, &gpio_init);

    // Set initial GPIO state
    HAL_GPIO_WritePin(gpio, pin, state);
}

// Read GPIO pin state.
int gpio_read(pin_id_t pin_id)
{
    register GPIO_TypeDef * gpio = gpio_get_handle(pin_id);

    if (gpio == NULL) {
        // Error: invalid pin ID
        BSP_PANIC();
        return -1;
    }

    return (gpio_port_read(gpio) & gpio_get_pin(pin_id)) == 0 ? 0 : 1;
}

// Set the selected GPIO pin state.
void gpio_write(pin_id_t pin_id, int state)
{
    register GPIO_TypeDef * gpio = gpio_get_handle(pin_id);
    register uint16_t pin = gpio_get_pin(pin_id);

    if (gpio == NULL) {
        // Error: invalid pin ID
        BSP_PANIC();
        return;
    }

    if (state != 0) {
        gpio_port_set(gpio, pin);
    } else {
        gpio_port_clear(gpio, pin);
    }
}

// Toggle the selected GPIO pin state.
void gpio_toggle(pin_id_t pin_id)
{
    register GPIO_TypeDef * gpio = gpio_get_handle(pin_id);

    if (gpio == NULL) {
        // Error: invalid pin ID
        BSP_PANIC();
        return;
    }

    gpio_port_toggle(gpio, gpio_get_pin(pin_id));
}
