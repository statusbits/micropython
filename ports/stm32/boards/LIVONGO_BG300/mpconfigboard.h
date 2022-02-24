#define MICROPY_HW_BOARD_NAME   "LIVONGO-BG300"
#define MICROPY_HW_MCU_NAME     "STM32F401xE"

#define MICROPY_HW_HAS_SWITCH   (1)
#define MICROPY_HW_HAS_FLASH    (1)
#define MICROPY_HW_ENABLE_RTC   (1)
//#define MICROPY_HW_ENABLE_SERVO (1)

// HSE is 8MHz, HSI is 16MHz CPU freq set to 84MHz
// Default source for the clock is HSI.
// For revisions of the board greater than C-01, HSE can be used as a
// clock source by removing the #define MICROPY_HW_CLK_USE_HSE line
#define MICROPY_HW_CLK_USE_HSI  (1)

#if MICROPY_HW_CLK_USE_HSI
#define MICROPY_HW_CLK_PLLM     (16)
#else
#define MICROPY_HW_CLK_PLLM     (8)
#endif
#define MICROPY_HW_CLK_PLLN     (336)
#define MICROPY_HW_CLK_PLLP     (RCC_PLLP_DIV4)
#define MICROPY_HW_CLK_PLLQ     (7)

// UART config
#define MICROPY_HW_UART1_TX     (pin_A10)
#define MICROPY_HW_UART1_RX     (pin_A9)
#define MICROPY_HW_UART2_TX     (pin_D5)
#define MICROPY_HW_UART2_RX     (pin_D6)
#define MICROPY_HW_UART6_TX     (pin_C6)
#define MICROPY_HW_UART6_RX     (pin_C7)

// UART 1 is routed to the BG300 Debug header
#define MICROPY_HW_UART_REPL        PYB_UART_1
#define MICROPY_HW_UART_REPL_BAUD   115200

// I2C buses
#define MICROPY_HW_I2C1_SCL     (pin_B8)
#define MICROPY_HW_I2C1_SDA     (pin_B9)
#define MICROPY_HW_I2C3_SCL     (pin_A8)
#define MICROPY_HW_I2C3_SDA     (pin_B4)

// SPI bus
#define MICROPY_HW_SPI2_NSS     (pin_B12)
#define MICROPY_HW_SPI2_SCK     (pin_B13)
#define MICROPY_HW_SPI2_MISO    (pin_B14)
#define MICROPY_HW_SPI2_MOSI    (pin_B15)

// Power button is pulled high. Pressing the button makes the input go low.
#define MICROPY_HW_USRSW_PIN        (pin_C0)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLUP)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_FALLING)
#define MICROPY_HW_USRSW_PRESSED    (0)

// LEDs
#define MICROPY_HW_LED1         (pin_A5)
#define MICROPY_HW_LED_ON(pin)  (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin) (mp_hal_pin_low(pin))

// Board-specific initialization
#define MICROPY_BOARD_EARLY_INIT    bg300_init

// Function declarations
void bg300_init(void);
