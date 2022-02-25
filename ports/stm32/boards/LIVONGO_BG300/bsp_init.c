//#include STM32_HAL_H
#include "bg300.h"

// GPIO pin configuration
static gpio_conf_t const pin_conf[] = {
    // Output pins          mode                    speed                   pud             state
    { BSP_PIN_SHUTDOWN,     GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    1 },
    { BSP_PIN_PERIPHERAL,   GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    1 },
    { BSP_PIN_BRIGHTNESS,   GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_TOUCH_RESET,  GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_MODEM_ONOFF,  GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_MODEM_RESET,  GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_MODEM_DTR,    GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    1 },
    { BSP_PIN_MODEM_RTS,    GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    1 },
    { BSP_PIN_BGM_POWER,    GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_STRIP_BGM,    GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    1 },
    { BSP_PIN_STRIP_MCU,    GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_LED,          GPIO_MODE_OUTPUT_PP,    GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    1 },
    // Input pins
    { BSP_PIN_POWER_BTN,    GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_PGOOD,        GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_FG_ALERT,     GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_CHARGING,     GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_SDCARD_IN,    GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_TOUCH_INT,    GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_MODEM_PWRMON, GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_MODEM_STATUS, GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_MODEM_DSR,    GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_BGSTRIP_IN,   GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    { BSP_PIN_BOARD_REV,    GPIO_MODE_INPUT,        GPIO_SPEED_FREQ_LOW,    GPIO_PULLUP,    0 },
    // Unused pins
    { BSP_PIN_BACKLIGHT,    GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_ACCEL_CS,     GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_ACCEL_INT1,   GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { BSP_PIN_RTC_ALARM,    GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { GPIO_B2,              GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    { GPIO_B7,              GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    //{ GPIO_C13,             GPIO_MODE_ANALOG,       GPIO_SPEED_FREQ_LOW,    GPIO_NOPULL,    0 },
    // End of table
    { GPIO_INVALID_ID,      0,                      0,                      0,              0 }
};

void bsp_init(void)
{
    // Configure GPIO pins
    gpio_init(pin_conf);

    // Initialize the beeper
    beeper_init();

    // Make a sound
    beeper_beep(100);
}
