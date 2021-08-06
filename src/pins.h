#ifndef __PINS_H_
#define __PINS_H_


/*
* Defines for Harware Limits
*
*/
#define MAX_VOLTAGE_HW 60
#define MIN_VOLTAGE_HW 

/*
* Defines for software limits 
*
*/
#define MAX_VOLTAGE_SW 70
#define MIN_VOLTAGE_SW 3

/*
*   Model Specific characteristics 
*
*/

#define RIDEN_MODEL 12
#define LCD_MDEL            ILI9341_2_DRIVER //TFT_eSPI specific 
#define DISP_W_MAX          320
#define DISP_H_MAX          240
#define SETTINGS_MEM        0x803F000
#define FACTORY_CALIB_MEM   0x803F800
#define ENTRY_VECTOR_BOOT   0x8000000
#define ENTRY_VECTOR_APP    0x8006000


typedef struct FACTORY_SETTINGS
{
    char check_value;
    char check_value_two;
    uint32_t serial_number;
    uint8_t lcd_type;
    int16_t unknown;

}FACT_TypeDef;


#ifdef __ARDUINO_
#define BUZZER          PC13 
#define V_BATT          PA0
#define TEMP_INT        PC0
#define V_INPUT         PC1
#define TEMP_EXT        PC2
#define DIGITAL_PAD_IRQ PC3
#define DTC_PIN         PA1
#define TTL_EN          PA6
#define VSET_LED        PC5
#define ISET_LED        PC4
#define LCD_BACKLIGHT   PB0
#define PWR_MAIN_LED    PC6
#define SHIFT_LED       PC7
#define MEM_LED         PC8
#define ON_OFF_LED      PC9
#define TTL_WIFI        Serial1
#define PWR_SERIAL      Serial2
#define FRONT_USB       Serial3
#define LCD_RESET       PA8
#define LCD_CS          PB12
#define LCD_RA          PA12 
#define LCD_CLK         PB13
#define LCD_SDO         PB14
#define LCD_SDI         PB15
#define LCD_SPI_PORT    Spi1
#define SPI_EEPROM      Spi2
#define RELAY_OUT       PC12
#define KEYPAD_II2C     I2C2
#define EEPROM          I2C1
#define FAN_OUT         PD2
#define ECODER_A        PB9
#define ECODER_B        PB8

#define CAP47           PA4
#define CAP220          PA5

#define W25Q32_DIO      PB4
#define W25Q32_DOI      PB5
#define W25Q32_CLK      PB3
#define W25Q32_CS       PA15


#define VOLTAGE_DIVIDER_VAL   14.2
#define NTC_B_CONST           4400 //currenlty assumed value based on tests
#ifdef __STM_HAL_MX
#define BUZZER_EN_Pin GPIO_PIN_13
#define BUZZER_EN_GPIO_Port GPIOC
#define TEMP_INT_Pin GPIO_PIN_0
#define TEMP_INT_GPIO_Port GPIOC
#define V_INPUT_Pin GPIO_PIN_1
#define V_INPUT_GPIO_Port GPIOC
#define TEMP_EXT_Pin GPIO_PIN_2
#define TEMP_EXT_GPIO_Port GPIOC
#define DP_Pin GPIO_PIN_3
#define DP_GPIO_Port GPIOC
#define DTC_Pin GPIO_PIN_1
#define DTC_GPIO_Port GPIOA
#define PWR_TX_Pin GPIO_PIN_2
#define PWR_TX_GPIO_Port GPIOA
#define PWR_RX_Pin GPIO_PIN_3
#define PWR_RX_GPIO_Port GPIOA
#define TTL_EN_PIN_Pin GPIO_PIN_6
#define TTL_EN_PIN_GPIO_Port GPIOA
#define VSET_LED_Pin GPIO_PIN_4
#define VSET_LED_GPIO_Port GPIOC
#define ISET_LED_Pin GPIO_PIN_5
#define ISET_LED_GPIO_Port GPIOC
#define LCD_BACKLIGH_EN_Pin GPIO_PIN_0
#define LCD_BACKLIGH_EN_GPIO_Port GPIOB
#define PWR_MAIN_LED_Pin GPIO_PIN_6
#define PWR_MAIN_LED_GPIO_Port GPIOC
#define SHIFT_LED_Pin GPIO_PIN_7
#define SHIFT_LED_GPIO_Port GPIOC
#define MEM_LED_Pin GPIO_PIN_8
#define MEM_LED_GPIO_Port GPIOC
#define ON_OFF_LED_Pin GPIO_PIN_9
#define ON_OFF_LED_GPIO_Port GPIOC
#define LCD_RESET_PIN_Pin GPIO_PIN_8
#define LCD_RESET_PIN_GPIO_Port GPIOA
#define TTL_WIFI_TX_Pin GPIO_PIN_9
#define TTL_WIFI_TX_GPIO_Port GPIOA
#define TTL_WFIF_RX_Pin GPIO_PIN_10
#define TTL_WFIF_RX_GPIO_Port GPIOA
#define UART_USB_TX_Pin GPIO_PIN_10
#define UART_USB_TX_GPIO_Port GPIOC
#define UART_USB_RX_Pin GPIO_PIN_11
#define UART_USB_RX_GPIO_Port GPIOC
#define RELAY_OUT_Pin GPIO_PIN_12
#define RELAY_OUT_GPIO_Port GPIOC
#define FAN_OUT_Pin GPIO_PIN_2
#define FAN_OUT_GPIO_Port GPIOD
#define ENCODER_B_Pin GPIO_PIN_8
#define ENCODER_B_GPIO_Port GPIOB
#define ENCODER_A_Pin GPIO_PIN_9
#define ENCODER_A_GPIO_Port GPIOB
#endif


#endif

#endif

