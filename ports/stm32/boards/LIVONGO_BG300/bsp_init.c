//#include STM32_HAL_H
#include "bg300.h"

// STM32 MCU IDs
#define MCU_STM32F401   0x433   // STM32F401xD/E
#define MCU_STM32F412   0x441   // STM32F412

// Board hardware revisions
enum board_rev_t {
    BG300_REV_A = 0,    // BG300 Rev.A
    BG300_REV_B = 1,    // BG300 Rev.B
    BG300_REV_C = 2     // BG300 Rev.C
};

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

// Local data
static uint8_t board_rev;

void bsp_init(void)
{
    // Configure GPIO pins
    gpio_init(pin_conf);

    // Get board hardware revision
    uint32_t mcu_id = *(uint32_t *)0xE0042000 & 0xFFF;
    if (mcu_id == MCU_STM32F412) {
        // Rev.C uses F412 MCU variant
        board_rev = BG300_REV_C;
    } else if (gpio_read(BSP_PIN_BOARD_REV) == 0) {
        // Rev.B has BSP_PIN_BOARD_REV pin pulled low
        board_rev = BG300_REV_B;
    } else {
        // Otherwise it's Rev.A
        board_rev = BG300_REV_A;
    }

    // Configure hardware revision-specific pins
    if (board_rev == BG300_REV_A) {
        // Rev.A pin configuration
        gpio_configure(BSP_PIN_BACKLIGHT,  GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL, 0);
        gpio_configure(BSP_PIN_ACCEL_CS,   GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL, 1);
        gpio_configure(BSP_PIN_ACCEL_INT1, GPIO_MODE_INPUT,     GPIO_SPEED_FREQ_LOW, GPIO_PULLUP, 0);
        gpio_configure(BSP_PIN_RTC_ALARM,  GPIO_MODE_INPUT,     GPIO_SPEED_FREQ_LOW, GPIO_PULLUP, 0);
    }

    // Initialize the beeper
    beeper_init();

    // Make a sound
    beeper_beep(100);
}
