/**
 * @file    bg300.h
 * @brief   Livongo BG300 board support package definitions.
 * @author  Gene Kozin <geko@statusbits.com>
 * ----------------------------------------------------------------------------
 * @attention
 * <h2><center>&copy; Copyright (c) 2022 Statusbits.com</center></h2>
 */

#ifndef __BG300_H__
#define __BG300_H__

#include "stdint.h"
#include STM32_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

// Default BSP debug flag
#ifndef BSP_DEBUG
# define BSP_DEBUG 1
#endif // BSP_DEBUG

// Critical error hangler
#define BSP_PANIC()     for(;;)

// Macro to convert a numeric value to a string
#ifdef __XSTRING
# define STRINGIFY(s)   __XSTRING(s)
#else
# define __STRING(s)    #s
# define STRINGIFY(s)   __STRING(s)
#endif // __XSTRING

/**
 * @brief  GPIO port ID's
 */
enum gpio_port_id {
    GPIO_A,
    GPIO_B,
    GPIO_C,
    GPIO_D,
    GPIO_E,
    GPIO_MAX_PORT
};

// GPIO pin ID type
typedef uint8_t     pin_id_t;   // GPIO pin ID

// Macro to make GPIO pin ID
#define BSP_GPIO_ID(port,pin)   ((((port) & 0x7) << 4) + ((pin) & 0xF))

// Invalid GPIO pin ID (used for terminating configuration table)
#define GPIO_INVALID_ID 0xFF

// GPIO Port A Pin IDs
#define GPIO_A0     BSP_GPIO_ID(GPIO_A, 0)
#define GPIO_A1     BSP_GPIO_ID(GPIO_A, 1)
#define GPIO_A2     BSP_GPIO_ID(GPIO_A, 2)
#define GPIO_A3     BSP_GPIO_ID(GPIO_A, 3)
#define GPIO_A4     BSP_GPIO_ID(GPIO_A, 4)
#define GPIO_A5     BSP_GPIO_ID(GPIO_A, 5)
#define GPIO_A6     BSP_GPIO_ID(GPIO_A, 6)
#define GPIO_A7     BSP_GPIO_ID(GPIO_A, 7)
#define GPIO_A8     BSP_GPIO_ID(GPIO_A, 8)
#define GPIO_A9     BSP_GPIO_ID(GPIO_A, 9)
#define GPIO_A10    BSP_GPIO_ID(GPIO_A, 10)
#define GPIO_A11    BSP_GPIO_ID(GPIO_A, 11)
#define GPIO_A12    BSP_GPIO_ID(GPIO_A, 12)
#define GPIO_A13    BSP_GPIO_ID(GPIO_A, 13)
#define GPIO_A14    BSP_GPIO_ID(GPIO_A, 14)
#define GPIO_A15    BSP_GPIO_ID(GPIO_A, 15)

// GPIO Port B Pin IDs
#define GPIO_B0     BSP_GPIO_ID(GPIO_B, 0)
#define GPIO_B1     BSP_GPIO_ID(GPIO_B, 1)
#define GPIO_B2     BSP_GPIO_ID(GPIO_B, 2)
#define GPIO_B3     BSP_GPIO_ID(GPIO_B, 3)
#define GPIO_B4     BSP_GPIO_ID(GPIO_B, 4)
#define GPIO_B5     BSP_GPIO_ID(GPIO_B, 5)
#define GPIO_B6     BSP_GPIO_ID(GPIO_B, 6)
#define GPIO_B7     BSP_GPIO_ID(GPIO_B, 7)
#define GPIO_B8     BSP_GPIO_ID(GPIO_B, 8)
#define GPIO_B9     BSP_GPIO_ID(GPIO_B, 9)
#define GPIO_B10    BSP_GPIO_ID(GPIO_B, 10)
#define GPIO_B11    BSP_GPIO_ID(GPIO_B, 11)
#define GPIO_B12    BSP_GPIO_ID(GPIO_B, 12)
#define GPIO_B13    BSP_GPIO_ID(GPIO_B, 13)
#define GPIO_B14    BSP_GPIO_ID(GPIO_B, 14)
#define GPIO_B15    BSP_GPIO_ID(GPIO_B, 15)

// GPIO Port C Pin IDs
#define GPIO_C0     BSP_GPIO_ID(GPIO_C, 0)
#define GPIO_C1     BSP_GPIO_ID(GPIO_C, 1)
#define GPIO_C2     BSP_GPIO_ID(GPIO_C, 2)
#define GPIO_C3     BSP_GPIO_ID(GPIO_C, 3)
#define GPIO_C4     BSP_GPIO_ID(GPIO_C, 4)
#define GPIO_C5     BSP_GPIO_ID(GPIO_C, 5)
#define GPIO_C6     BSP_GPIO_ID(GPIO_C, 6)
#define GPIO_C7     BSP_GPIO_ID(GPIO_C, 7)
#define GPIO_C8     BSP_GPIO_ID(GPIO_C, 8)
#define GPIO_C9     BSP_GPIO_ID(GPIO_C, 9)
#define GPIO_C10    BSP_GPIO_ID(GPIO_C, 10)
#define GPIO_C11    BSP_GPIO_ID(GPIO_C, 11)
#define GPIO_C12    BSP_GPIO_ID(GPIO_C, 12)
#define GPIO_C13    BSP_GPIO_ID(GPIO_C, 13)
#define GPIO_C14    BSP_GPIO_ID(GPIO_C, 14)
#define GPIO_C15    BSP_GPIO_ID(GPIO_C, 15)

// GPIO Port D Pins
#define GPIO_D0     BSP_GPIO_ID(GPIO_D, 0)
#define GPIO_D1     BSP_GPIO_ID(GPIO_D, 1)
#define GPIO_D2     BSP_GPIO_ID(GPIO_D, 2)
#define GPIO_D3     BSP_GPIO_ID(GPIO_D, 3)
#define GPIO_D4     BSP_GPIO_ID(GPIO_D, 4)
#define GPIO_D5     BSP_GPIO_ID(GPIO_D, 5)
#define GPIO_D6     BSP_GPIO_ID(GPIO_D, 6)
#define GPIO_D7     BSP_GPIO_ID(GPIO_D, 7)
#define GPIO_D8     BSP_GPIO_ID(GPIO_D, 8)
#define GPIO_D9     BSP_GPIO_ID(GPIO_D, 9)
#define GPIO_D10    BSP_GPIO_ID(GPIO_D, 10)
#define GPIO_D11    BSP_GPIO_ID(GPIO_D, 11)
#define GPIO_D12    BSP_GPIO_ID(GPIO_D, 12)
#define GPIO_D13    BSP_GPIO_ID(GPIO_D, 13)
#define GPIO_D14    BSP_GPIO_ID(GPIO_D, 14)
#define GPIO_D15    BSP_GPIO_ID(GPIO_D, 15)

// GPIO Port E Pins
#define GPIO_E0     BSP_GPIO_ID(GPIO_E, 0)
#define GPIO_E1     BSP_GPIO_ID(GPIO_E, 1)
#define GPIO_E2     BSP_GPIO_ID(GPIO_E, 2)
#define GPIO_E3     BSP_GPIO_ID(GPIO_E, 3)
#define GPIO_E4     BSP_GPIO_ID(GPIO_E, 4)
#define GPIO_E5     BSP_GPIO_ID(GPIO_E, 5)
#define GPIO_E6     BSP_GPIO_ID(GPIO_E, 6)
#define GPIO_E7     BSP_GPIO_ID(GPIO_E, 7)
#define GPIO_E8     BSP_GPIO_ID(GPIO_E, 8)
#define GPIO_E9     BSP_GPIO_ID(GPIO_E, 9)
#define GPIO_E10    BSP_GPIO_ID(GPIO_E, 10)
#define GPIO_E11    BSP_GPIO_ID(GPIO_E, 11)
#define GPIO_E12    BSP_GPIO_ID(GPIO_E, 12)
#define GPIO_E13    BSP_GPIO_ID(GPIO_E, 13)
#define GPIO_E14    BSP_GPIO_ID(GPIO_E, 14)
#define GPIO_E15    BSP_GPIO_ID(GPIO_E, 15)

// GPIO pin aliases
#define BSP_PIN_WAKEUP          GPIO_A0     // CPU wake-up
#define BSP_PIN_SHUTDOWN        GPIO_A1     // System shutdown
#define BSP_PIN_POWER_BTN       GPIO_C0     // Power On/Off button
#define BSP_PIN_PGOOD           GPIO_C1     // Charger sensor
#define BSP_PIN_BGSTRIP_IN      GPIO_C2     // BG strip sensor
#define BSP_PIN_RTC_ALARM       GPIO_C3     // RTC alarm (Rev.A only)
#define BSP_PIN_FG_ALERT        GPIO_B6     // Fuel Gauge alert
#define BSP_PIN_PERIPHERAL      GPIO_D12    // Peripheral power on/off
#define BSP_PIN_BGM_POWER       GPIO_D15    // BG module power on/off
#define BSP_PIN_STRIP_BGM       GPIO_D14    // Strip sensor mux -> BGM
#define BSP_PIN_STRIP_MCU       GPIO_D13    // Strip sensor mux -> MCU
#define BSP_PIN_MODEM_DSR       GPIO_D0     // GPRS/UMTS modem DSR
#define BSP_PIN_MODEM_DTR       GPIO_D1     // GPRS/UMTS modem DTR
#define BSP_PIN_MODEM_CTS       GPIO_D3     // GPRS/UMTS modem CTS
#define BSP_PIN_MODEM_RTS       GPIO_D4     // GPRS/UMTS modem RTS
#define BSP_PIN_MODEM_RESET     GPIO_D10    // GPRS/UMTS modem reset
#define BSP_PIN_MODEM_ONOFF     GPIO_D11    // GPRS/UMTS modem on/off
#define BSP_PIN_MODEM_PWRMON    GPIO_D9     // GPRS/UMTS modem power monitor
#define BSP_PIN_MODEM_STATUS    GPIO_D8     // GPRS/UMTS modem status
#define BSP_PIN_BRIGHTNESS      GPIO_B0     // LCD Backlight brightness
#define BSP_PIN_BACKLIGHT       GPIO_B1     // LCD Backlight power (Rev.A only)
#define BSP_PIN_LCD_RESET       GPIO_C4     // LCD controller reset
#define BSP_PIN_LCD_MODE        GPIO_C5     // LCD controller mode select
#define BSP_PIN_LCD_RS          GPIO_A7     // LCD controller register select
#define BSP_PIN_LCD_RD          GPIO_A5     // LCD controller read
#define BSP_PIN_LCD_WR          GPIO_A6     // LCD controller write
#define BSP_PIN_TOUCH_RESET     GPIO_D7     // Touch screen sensor Reset
#define BSP_PIN_TOUCH_INT       GPIO_A4     // Touch screen interrupt request
#define BSP_PIN_ACCEL_CS        GPIO_B12    // Accelerometer CS (Rev.A only)
#define BSP_PIN_ACCEL_INT1      GPIO_B10    // Accelerometer IRQ1 (Rev.A only)
#define BSP_PIN_SDCARD_IN       GPIO_A15    // SD Card inserted
#define BSP_PIN_CHARGING        GPIO_A2     // Battery charging indicator
#define BSP_PIN_BOARD_REV       GPIO_B5     // Board revision pin (1 - Rev.A, 0 - Rev.B/C)
#define BSP_PIN_LED             GPIO_C13    // Unused

// GPIO pin configuration data
typedef struct {
    pin_id_t    pin;    // Pin ID
    uint32_t    mode;   // Mode configuration
    uint8_t     speed;  // Speed configuration
    uint8_t     pud;    // Pull-up/down configuration
    uint8_t     state;  // Initial state
} gpio_conf_t;

/**
 * @brief   Set GPIO port mode to input.
 */
static inline void gpio_port_mode_input(GPIO_TypeDef * port)
{
    port->MODER = 0;
}

/**
 * @brief   Set GPIO port mode to output.
 */
static inline void gpio_port_mode_output(GPIO_TypeDef * port)
{
    port->MODER = 0x55555555;
}

/**
 * @brief   Read 16-bit GPIO port.
 */
static inline uint16_t gpio_port_read(GPIO_TypeDef * port)
{
    return port->IDR;
}

/**
 * @brief   Write 16-bit GPIO port.
 */
static inline void gpio_port_write(GPIO_TypeDef * port, uint16_t value)
{
    port->ODR = value;
}

/**
 * @brief   Set GPIO port pins.
 */
static inline void gpio_port_set(GPIO_TypeDef * port, uint16_t mask)
{
    port->BSRR = mask;
}

/**
 * @brief   Clear GPIO port pins.
 */
static inline void gpio_port_clear(GPIO_TypeDef * port, uint16_t mask)
{
    port->BSRR = (uint32_t)mask << 16;
}

/**
 * @brief	Toggle GPIO port pins.
 */
static inline void gpio_port_toggle(GPIO_TypeDef * port, uint16_t mask)
{
    port->ODR ^= mask;
}

/**
 * @brief   Read GPIO pin.
 */
static inline int gpio_pin_read(GPIO_TypeDef * port, uint16_t pin)
{
    return (port->IDR & pin) != 0 ? 1 : 0;
}

/**
 * @brief   Set GPIO pin(s).
 */
static inline void gpio_pin_set(GPIO_TypeDef * port, uint16_t pins)
{
    port->BSRR = pins;
}

/**
 * @brief   Clear GPIO pin(s).
 */
static inline void gpio_pin_clear(GPIO_TypeDef * port, uint16_t pins)
{
    port->BSRR = (uint32_t)pins << 16;
}

/**
 * @brief   Toggle GPIO pin(s).
 */
static inline void gpio_pin_toggle(GPIO_TypeDef * port, uint16_t pins)
{
    port->ODR ^= pins;
}

/**
 * @brief   Initialize GPIO pins.
 */
void gpio_init(gpio_conf_t const * conf);

/**
 * @brief   De-initialize GPIO pin.
 * @param   pin_id  Specifies the GPIO pin ID to configure.
 */
void gpio_deinit(pin_id_t pin_id);

/**
 * @brief   Configure GPIO pin.
 * @param   pin_id  Specifies the GPIO pin ID to configure.
 * @param   state   Specifies the GPIO pin state (0 or 1).
 */
void gpio_configure(pin_id_t pin_id, uint32_t mode, uint8_t speed, uint8_t pud, int state);

/**
 * @brief   Read GPIO pin state.
 * @param   pin_id  Specifies the GPIO pin ID to read.
 * @return  The GPIO pin state (0 or 1) or -1 if invalid pin ID.
 */
int gpio_read(pin_id_t pin_id);

/**
 * @brief   Set the selected GPIO pin state.
 * @param   pin_id  Specifies the GPIO pin ID to write.
 * @param   state   Specifies the GPIO pin state (0 or 1).
 */
void gpio_write(pin_id_t pin_id, int state);

/**
 * @brief   Toggle the selected GPIO pin state.
 * @param   pin_id  Specifies the GPIO pin ID to toggle.
 */
void gpio_toggle(pin_id_t pin_id);

/**
 * @brief   Initialize board.
 */
void bsp_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BG300_H__ */
