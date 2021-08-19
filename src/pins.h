#ifndef __PINS_H_
#define __PINS_H_


/*
* Defines for Harware Limits
*
*/
#define MAX_VOLTAGE_HW 60
#define MIN_VOLTAGE_HW 3

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
#define BOOTLOAD_SETTINGS   0x8005000
#define ENTRY_VECTOR_APP    0x8006000


typedef struct FACTORY_SETTINGS
{
    uint16_t check_value;
    uint16_t check_value_two;
    uint32_t serial_number;
    uint16_t lcd_type;// lsb 8 bits
    uint16_t unknown;
    uint16_t unknown_two;
    uint16_t unknown_three;
    uint16_t unknown_four;
    uint16_t unknown_five;
    uint16_t unknown_six;
    uint16_t unknown_seven;


}FACT_TypeDef;


#ifdef __ARDUINO_
#define BUZZER          PC13 
#define V_BATT          PA0
#define TEMP_INT        PC0
#define V_INPUT         PC1
#define TEMP_EXT        PC2

#define DTC_PIN         PA1 //Dead Time Control of TL594 (pin 4)
#define TTL_EN          PA6
#define VSET_LED        PC4
#define ISET_LED        PC5
#define LCD_BACKLIGHT   PB0
#define PWR_MAIN_LED    PC6
#define SHIFT_LED       PC7
#define MEM_LED         PC8
#define ON_OFF_LED      PC9
#define TTL_WIFI        Serial1
#define PWR_SERIAL      Serial2
#define PWR_TX          PA2
#define PWR_RX          PA3
#define FRONT_USB       Serial3
#define LCD_RESET       PA8
#define LCD_CS          PB12
#define LCD_RA          PA12 
#define LCD_CLK         PB13
#define LCD_SDO         PB14
#define LCD_SDI         PB15
#define LCD_SPI_PORT    SPI1
#define SPI_EEPROM      SPI2
#define RELAY_OUT       PC12
#define KEYPAD_II2C     I2C2
#define KEYPAD_SDA      PB7
#define KEYPAD_SCL      PB6
#define KEYPAD_IRQ      PC3

#define EEPROM          I2C2
#define EEPROM_SDA      PB11
#define EEPROM_SCL      PB10
#define ADDR_Ax 0b000 //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax

#define FAN_OUT         PD2
#define ECODER_A        PB9
#define ECODER_B        PB8

#define CAP47           PA4 //Gate of Q41 SL2303
#define CAP220          PA5 //Gate of Q4 SL2303

#define W25Q32_DIO      PB4
#define W25Q32_DOI      PB5
#define W25Q32_CLK      PB3
#define W25Q32_CS       PA15


#define VOLTAGE_DIVIDER_VAL     14.2
#define VOLTAGE_DIVIDER_VAL_12B 56
#define NTC_B_CONST             4400 //currenlty assumed value based on tests


/*from eevblog - Unisoft
#define THERMISTORNOMINAL     10000   // resistance at 25 degrees C
#define TEMPERATURENOMINAL    25      // temp. for nominal resistance (almost always 25 C)
#define BCOEFFICIENT          3950    // The beta coefficient of the thermistor (usually 3000-4000)
const uint16_t g_colors[16] = {
      0,            // 0 - Default
      C_RED,        // 1  = 0xF800
      C_GREEN,      // 2  = 0x07E0
      C_BLUE,       // 3  = 0x001F
      C_WHITE,      // 4  = 0xFFFF
      C_YELLOW,     // 5  = 0xFFE0
      C_MAGENTA,    // 6  = 0xF81F
      C_CYAN,       // 7  = 0x07FF
      //
      C_LIGHT_BLUE, // 8  = 0x01CF
      C_GRAY,       // 9  = 0x8410
      C_BROWN,      // 10 = 0xA145
      C_ORANGE,     // 11 = 0xFD20
      C_OLIVE,      // 12 = 0x8400
      C_TEAL,       // 13 = 0x0410
      C_PINK,       // 14 = 0xFDF9
      C_MAROON      // 15 = 0x8000
    };

*/

/*
* taken from https://raw.githubusercontent.com/sigrokproject/libsigrok/master/src/hardware/rdtech-dps/protocol.c
*/
enum rdtech_dps_register {
	REG_DPS_USET       = 0x00, /* Mirror of 0x50 */
	REG_DPS_ISET       = 0x01, /* Mirror of 0x51 */
	REG_DPS_UOUT       = 0x02,
	REG_DPS_IOUT       = 0x03,
	REG_DPS_POWER      = 0x04,
	REG_DPS_UIN        = 0x05,
	REG_DPS_LOCK       = 0x06,
	REG_DPS_PROTECT    = 0x07,
	REG_DPS_CV_CC      = 0x08,
	REG_DPS_ENABLE     = 0x09,
	REG_DPS_BACKLIGHT  = 0x0A, /* Mirror of 0x55 */
	REG_DPS_MODEL      = 0x0B,
	REG_DPS_VERSION    = 0x0C,

	REG_DPS_PRESET     = 0x23, /* Loads a preset into preset 0. */

	/*
	 * Add (preset * 0x10) to each of the following, for preset 1-9.
	 * Preset 0 regs below are the active output settings.
	 */
	PRE_DPS_USET       = 0x50,
	PRE_DPS_ISET       = 0x51,
	PRE_DPS_OVPSET     = 0x52,
	PRE_DPS_OCPSET     = 0x53,
	PRE_DPS_OPPSET     = 0x54,
	PRE_DPS_BACKLIGHT  = 0x55,
	PRE_DPS_DISABLE    = 0x56, /* Disable output if 0 is copied here from a preset (1 is no change). */
	PRE_DPS_BOOT       = 0x57, /* Enable output at boot if 1. */
};
#define PRE_DPS_STRIDE 0x10

enum rdtech_dps_protect_state {
	STATE_NORMAL = 0,
	STATE_OVP    = 1,
	STATE_OCP    = 2,
	STATE_OPP    = 3,
};

enum rdtech_dps_regulation_mode {
	MODE_CV      = 0,
	MODE_CC      = 1,
};

enum rdtech_rd_register {
	REG_RD_MODEL = 0, /* u16 */
	REG_RD_SERIAL = 1, /* u32 */
	REG_RD_FIRMWARE = 3, /* u16 */
	REG_RD_TEMP_INT = 4, /* 2x u16 */
	REG_RD_TEMP_INT_F = 6, /* 2x u16 */
	REG_RD_VOLT_TGT = 8, /* u16 */
	REG_RD_CURR_LIM = 9, /* u16 */
	REG_RD_VOLTAGE = 10, /* u16 */
	REG_RD_CURRENT = 11, /* u16 */
	REG_RD_ENERGY = 12, /* u16 */
	REG_RD_POWER = 13, /* u16 */
	REG_RD_VOLT_IN = 14, /* u16 */
	REG_RD_PROTECT = 16, /* u16 */
	REG_RD_REGULATION = 17, /* u16 */
	REG_RD_ENABLE = 18, /* u16 */
	/*
	 * Battery at 32 == 0x20 pp:
	 * Mode, voltage, temperature, capacity, energy.
	 */
	/*
	 * Date/time at 48 == 0x30 pp:
	 * Year, month, day, hour, minute, second.
	 */
	/* Backlight at 72 == 0x48. */
	REG_RD_OVP_THR = 82, /* 0x52 */
	REG_RD_OCP_THR = 83, /* 0x53 */
	/* One "live" slot and 9 "memory" positions. */
	REG_RD_START_MEM = 84, /* 0x54 */
};



/*
*
* Buttons For TMC1650
*/
#define KEY_I_SET           0
#define KEY_MEM             1
#define KEY_MAIN_POWER      2
#define KEY_SHIFT           3
#define KEY_ZERO            4
#define KEY_ONE             5
#define KEY_FOUR            6
#define KEY_SEVEN           7
#define KEY_FULL_STOP       8
#define KEY_TWO             9
#define KEY_FIVE            10
#define KEY_EIGHT           11
#define KEY_LEFT            12
#define KEY_THREE           13
#define KEY_SIX             14
#define KEY_NINE            15
#define KEY_RIGHT           16
#define KEY_ENTER           17
#define KEY_DOWN            18
#define KEY_UP              19
#define KEY_ENCODER         20
#define KEY_V_SET           21

#define KEY_ON_OFF_POWER    23









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

