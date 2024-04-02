/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */
 #pragma once

//#define USE_TARGET_CONFIG

#define TARGET_MANUFACTURER_IDENTIFIER "IFRC"
#define USBD_PRODUCT_STRING "IFLIGHT_BLITZ_F405"

#define FC_TARGET_MCU     STM32F405     // not used in EmuF
#define TARGET_BOARD_IDENTIFIER "S405"  // generic ID

#define LED0_PIN                PC15

#define USE_BEEPER
#define BEEPER_PIN              PB2
#define BEEPER_INVERTED

#define USE_EXTI
#define MPU_INT_EXTI            PC4
#define USE_MPU_DATA_READY_SIGNAL

#define USE_ACC
#define USE_ACC_SPI_MPU6000
#define USE_ACC_SPI_MPU6500
#define ACC_MPU6000_1_ALIGN     CW0_DEG
#define ACC_MPU6500_ALIGN     CW0_DEG

#define USE_GYRO
#define USE_GYRO_SPI_MPU6000
#define USE_GYRO_SPI_MPU6500
#define GYRO_MPU6000_ALIGN      CW0_DEG
#define GYRO_MPU6500_ALIGN    CW0_DEG

#define MPU6000_CS_PIN          PA4
#define MPU6000_SPI_INSTANCE    SPI1
#define MPU6500_CS_PIN         MPU6000_CS_PIN
#define MPU6500_SPI_INSTANCE   MPU6000_SPI_INSTANCE

//-------------------------------------SPI2 FLASH------------------------------
#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT
#define USE_FLASHFS
#define USE_FLASH_M25P16
#define USE_FLASH_W25M512
#define FLASH_CS_PIN            PA15
#define FLASH_SPI_INSTANCE      SPI3

//-------------------------------------SPI1 OSD--------------------------------
#define USE_OSD
#define USE_MAX7456
#define MAX7456_SPI_INSTANCE    SPI2
#define MAX7456_SPI_CS_PIN      PB12

//-------------------------------------IIC2 BMP280------------------------------
#define USE_BARO
#define USE_BARO_BMP280
#define USE_BARO_MS5611
#define USE_BARO_BMP085
#define BARO_I2C_INSTANCE       (I2CDEV_1)
#define DEFAULT_BARO_BMP280

//-------------------------------------IIC1 MAG5883------------------------------
//#define MAG_I2C_INSTANCE        (I2CDEV_1)
//#define USE_MAG
//#define USE_MAG_HMC5883
//#define USE_MAG_QMC5883

//-------------------------------------USART-----------------------------------
#define USE_VCP
#define USE_USB_DETECT
#define USB_DETECT_PIN          PC5

#define USE_UART1
#define UART1_TX_PIN            PA9
#define UART1_RX_PIN            PA10

#define USE_UART2
#define UART2_TX_PIN            PA2
#define UART2_RX_PIN            PA3

#define USE_UART3
#define UART3_TX_PIN            PC10
#define UART3_RX_PIN            PC11

#define USE_UART4
#define UART4_TX_PIN            PA0
#define UART4_RX_PIN            PA1

#define USE_UART6
#define UART6_TX_PIN            PC6
#define UART6_RX_PIN            PC7

#define SERIAL_PORT_COUNT       6

//-------------------------------------ADC METERE------------------------------
#define USE_ADC
#define ADC_INSTANCE			ADC1
#define ADC1_DMA_STREAM         DMA2_Stream0
#define CURRENT_METER_ADC_PIN   PC1
#define VBAT_ADC_PIN			PC2
//#define RSSI_ADC_PIN			NONE

//---------------------------------VTX&&CAM------------------------------------
//#define USE_PINIO
//#define PINIO1_PIN              PA13 // VTX power switcher
//#define PINIO2_PIN              PA14 // 2xCamera switcher
//#define USE_PINIOBOX

//-------------------------------------SPI------------------------------------
#define USE_SPI
#define USE_SPI_DEVICE_1		//GYRO
#define SPI1_SCK_PIN            PA5
#define SPI1_MISO_PIN           PA6
#define SPI1_MOSI_PIN           PA7

#define USE_SPI_DEVICE_2 // OSD
#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PB14
#define SPI2_MOSI_PIN           PB15

#define USE_SPI_DEVICE_3	//FLASH
#define SPI3_SCK_PIN            PB3
#define SPI3_MISO_PIN           PB4
#define SPI3_MOSI_PIN           PB5

//-------------------------------------IIC------------------------------------
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C_DEVICE              (I2CDEV_1)

#define I2C1_SCL                PB8
#define I2C1_SDA                PB9

//-------------------------------------FEATURES-------------------------------
#define DEFAULT_FEATURES        (FEATURE_OSD | FEATURE_TELEMETRY )

#define DEFAULT_RX_FEATURE     	FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER       SERIALRX_SBUS
#define SERIALRX_UART           SERIAL_PORT_USART2

#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define CURRENT_METER_SCALE_DEFAULT 200

#define USE_ESCSERIAL
#define USE_LED_STRIP

//--------------------------------BOARD RESOURCES-----------------------------
#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT 6
#define USED_TIMERS    (TIM_N(1)|TIM_N(2)|TIM_N(3)|TIM_N(8))
