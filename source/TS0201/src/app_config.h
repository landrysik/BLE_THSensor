#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#define VERSION 0x44	 // BCD format (0x34 -> '3.4')
#define EEP_SUP_VER 0x09 // EEP data minimum supported version

#define DEVICE_TS0201   	0x055B	// ZigBee TS0201, analog: IH-K009
/*
#define DEVICE_LYWSD03MMC   0x055B	// LCD display LYWSD03MMC
#define DEVICE_MHO_C122   	0x000B	// LCD display MHO_C122
#define DEVICE_MHO_C401   	0x0387	// E-Ink display MHO-C401 2020
#define DEVICE_MHO_C401N   	0x0008	// E-Ink display MHO-C401 2022
#define DEVICE_CGG1 		0x0B48  // E-Ink display CGG1-M "Qingping Temp & RH Monitor"
#define DEVICE_CGDK2 		0x066F  // LCD display "Qingping Temp & RH Monitor Lite"
#define DEVICE_MJWSD05MMC	0x2832  // LCD display MJWSD05MMC
*/

//#ifndef DEVICE_TYPE
#define DEVICE_TYPE			DEVICE_TS0201
//#endif

#define BLE_SECURITY_ENABLE 1 // = 1 support pin-code
#define BLE_EXT_ADV 		1 // = 1 support extension advertise (Test Only!)

#define USE_CLOCK 			1 // = 1 display clock, = 0 smile blinking
#define USE_TIME_ADJUST		1 // = 1 time correction enabled
#define USE_FLASH_MEMO		1 // = 1 flash logger enable

#define USE_SECURITY_BEACON 1 // = 1 support encryption beacon (bindkey)
#define USE_HA_BLE_BEACON	1 // = 1 https://github.com/custom-components/ble_monitor/issues/548
#define USE_MIHOME_BEACON	1 // = 1 Compatible with MiHome beacon
#define USE_BTHOME_BEACON	1

#define USE_KEYS_WAKEAP		1 // = 1 опрос кнопки с прерыванием

#define USE_OUT_AVERAGE_BATTERY	0 // = 1 Transmit averaged values

#define USE_EXT_OTA			0 // = 1 Compatible BigOTA

#define USE_DEVICE_INFO_CHR_UUID 	1 // = 1 enable Device Information Characteristics

#define USE_FLASH_SERIAL_UID 1

#define UART_PRINT_DEBUG_ENABLE		0 // =1 use u_printf() (PA7/SWS), source: SDK/components/application/print/u_printf.c

#if DEVICE_TYPE == DEVICE_TS0201
// GPIO_PB1 - TX
// GPIO_PB4 - LED
// GPIO_PB7 - RX
// GPIO_PC0 - KEY
// GPIO_PC2 - SDA
// GPIO_PC3 - SCL
// GPIO_PD7 - Alert

#define SHL_ADC_VBAT	1  // "B0P" in adc.h
#define GPIO_VBAT	GPIO_PB0 // missing pin on case TLSR8251F512ET24
#define PB0_INPUT_ENABLE	1
#define PB0_DATA_OUT		1
#define PB0_OUTPUT_ENABLE	1
#define PB0_FUNC			AS_GPIO

#define I2C_SCL 	GPIO_PC3
#define I2C_SDA 	GPIO_PC2
#define I2C_GROUP 	I2C_GPIO_GROUP_C2C3
#define PULL_WAKEUP_SRC_PC2	PM_PIN_PULLUP_10K
#define PULL_WAKEUP_SRC_PC3	PM_PIN_PULLUP_10K

#define GPIO_KEY			GPIO_PC0
#define PC0_INPUT_ENABLE	1
#define PC0_DATA_OUT		0
#define PC0_OUTPUT_ENABLE	0
#define PC0_FUNC			AS_GPIO
#define PULL_WAKEUP_SRC_PC0	PM_PIN_PULLUP_10K

#define GPIO_LED			GPIO_PB4
#define PB4_INPUT_ENABLE	1
#define PB4_DATA_OUT		1
#define PB4_OUTPUT_ENABLE	0
#define PB4_FUNC			AS_GPIO
#define PULL_WAKEUP_SRC_PB4	PM_PIN_PULLDOWN_100K

#else // DEVICE_TYPE
#error ("DEVICE_TYPE = ?")
#endif // DEVICE_TYPE == ?

#if UART_PRINT_DEBUG_ENABLE
#define PRINT_BAUD_RATE 1500000 // real ~1000000
#define DEBUG_INFO_TX_PIN	GPIO_PA7 // SWS
#define PA7_DATA_OUT		1
#define PA7_OUTPUT_ENABLE	1
#define PULL_WAKEUP_SRC_PA7 PM_PIN_PULLUP_1M
#define PA7_FUNC		AS_GPIO
#endif // UART_PRINT_DEBUG_ENABLE

#define MODULE_WATCHDOG_ENABLE		0 //
#define WATCHDOG_INIT_TIMEOUT		15000  //ms (min 5000 ms if pincode)

#define CLOCK_SYS_CLOCK_HZ  	24000000 // 16000000, 24000000, 32000000, 48000000
enum{
	CLOCK_SYS_CLOCK_1S = CLOCK_SYS_CLOCK_HZ,
	CLOCK_SYS_CLOCK_1MS = (CLOCK_SYS_CLOCK_1S / 1000),
	CLOCK_SYS_CLOCK_1US = (CLOCK_SYS_CLOCK_1S / 1000000),
};

#define pm_wait_ms(t) cpu_stall_wakeup_by_timer0(t*CLOCK_SYS_CLOCK_1MS);
#define pm_wait_us(t) cpu_stall_wakeup_by_timer0(t*CLOCK_SYS_CLOCK_1US);

#define RAM _attribute_data_retention_ // short version, this is needed to keep the values in ram after sleep

/* Flash map:
  0x00000 Firmware bin or OTA1 bin storage Area (OTA1_FADDR)
  0x20000 Firmware bin or OTA2 bin storage Area (OTA2_FADDR)
  0x40000 User Data Area (Logger, saving measurements) (FLASH_ADDR_START_MEMO)
  0x74000 Pair & Security info (CFG_ADR_BIND)
  0x76000 MAC address (CFG_ADR_MAC)
  0x77000 Customize freq_offset adjust cap value (CUST_CAP_INFO_ADDR)
  0x78000 free: Used Master BLE (CFG_ADR_PEER)
  0x7С000 EEP Data Area (FMEMORY_SCFG_BASE_ADDR)
  0x80000 End Flash (FLASH_SIZE)
 */
#define OTA1_FADDR 0x00000
#define OTA2_FADDR 0x20000
/* flash sector address with binding information */
#define	CFG_ADR_BIND	0x74000 //no master, slave device (blt_config.h)

#define BLE_HOST_SMP_ENABLE BLE_SECURITY_ENABLE

//#define CHG_CONN_PARAM	// test
#define DEV_NAME "TS0201" // not used (see SDK "blt_config.h")

#include "vendor/common/default_config.h"

#if defined(__cplusplus)
}
#endif