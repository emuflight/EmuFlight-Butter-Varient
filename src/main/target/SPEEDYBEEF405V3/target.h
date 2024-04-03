/*
 * This file is part of EmuFlight. It is derived from Betaflight.
 *
 * This is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */
 
// This resource file generated using https://github.com/nerdCopter/target-convert
// Commit: 1bce24c 

#pragma once

#define TARGET_MANUFACTURER_IDENTIFIER "SPBE"
#define USBD_PRODUCT_STRING "SPEEDYBEEF405V3"

#define FC_TARGET_MCU     STM32F405     // not used in EmuF
#define TARGET_BOARD_IDENTIFIER "S405"  // generic ID

#define USE_GYRO
#define USE_ACC
#define USE_ACCGYRO_BMI270
#define USE_MAX7456
#define USE_SDCARD
#define USE_BARO_DPS310
#define USE_BARO
#define USE_SDCARD_SPI
#define USE_SPI_GYRO
#define USE_BARO

#define USE_VCP
#define USE_OSD

#define USE_LED
#define LED0_PIN             PC8
#define LED_STRIP_PIN        PC9
#define USE_BEEPER
#define BEEPER_PIN           PC5
#define BEEPER_INVERTED
#define CAMERA_CONTROL_PIN   PB3

#define USE_SPI
#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN         PA5
#define SPI1_MISO_PIN        PA6
#define SPI1_MOSI_PIN        PA7
#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN         PB13
#define SPI2_MISO_PIN        PB14
#define SPI2_MOSI_PIN        PB15

#define USE_EXTI // notice - REQUIRED when USE_GYRO_EXTI
#define USE_GYRO_EXTI

#define GYRO_1_ALIGN         CW0_DEG
#define ACC_1_ALIGN          CW0_DEG
#define GYRO_1_CS_PIN        PA4
#define GYRO_1_EXTI_PIN      PC4
#define GYRO_1_SPI_INSTANCE SPI1
#define MPU_INT_EXTI         PC4

#define USE_SPI_GYRO
#define ACC_BMI270_ALIGN         CW0_DEG
#define GYRO_BMI270_ALIGN        CW0_DEG
#define BMI270_CS_PIN            PA4
#define BMI270_SPI_INSTANCE      SPI1

#define USE_UART1
#define UART1_TX_PIN         PA9
#define UART1_RX_PIN         PA10
#define USE_UART2
#define UART2_TX_PIN         PA2
#define UART2_RX_PIN         PA3
#define USE_UART3
#define UART3_TX_PIN         PC10
#define UART3_RX_PIN         PC11
#define USE_UART4
#define UART4_TX_PIN         PA0
#define UART4_RX_PIN         PA1
#define USE_UART5
#define UART5_TX_PIN         PC12
#define UART5_RX_PIN         PD2
#define USE_UART6
#define UART6_TX_PIN         PC6
#define UART6_RX_PIN         PC7
#define MSP_DISPLAYPORT_UART    SERIAL_PORT_USART1
#define SERIALRX_UART           SERIAL_PORT_USART2
#define SERIAL_PORT_COUNT 7

#define USE_I2C
#define USE_I2C_DEVICE_2
#define I2C_DEVICE        (I2CDEV_2)
#define MAG_I2C_INSTANCE (I2CDEV_2)
#define BARO_I2C_INSTANCE (I2CDEV_2)
#define DASHBOARD_I2C_INSTANCE (I2CDEV_2)
#define I2C2_SCL PB10
#define I2C2_SDA PB11

#define USE_SDCARD_SDIO
#define SDCARD_SPI_CS_PIN    PA15
#define SDCARD_SPI_INSTANCE SPI2
#define SDCARD_DMA_CHANNEL          0
#define SDCARD_DMA_CHANNEL_TX       DMA1_Stream4 //# SPI_MOSI 2: DMA1 Stream 4 Channel 0
#define ENABLE_BLACKBOX_LOGGING_ON_SDCARD_BY_DEFAULT
#define DEFAULT_BLACKBOX_DEVICE     BLACKBOX_DEVICE_SDCARD
#define SDCARD_SPI_FULL_SPEED_CLOCK_DIVIDER     4
#define SDCARD_SPI_INITIALIZATION_CLOCK_DIVIDER 256

#define MAX7456_SPI_CS_PIN   PB12
#define MAX7456_SPI_INSTANCE SPI2

#define USE_ADC
#define VBAT_ADC_PIN PC0
#define CURRENT_METER_ADC_PIN PC1
#define RSSI_ADC_PIN PC2
#define ADC1_DMA_OPT        0
#define ADC1_DMA_STREAM DMA2_Stream0 //# ADC 1: DMA2 Stream 0 Channel 0
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE 386

#define ENABLE_DSHOT_DMAR true

#define PINIO1_PIN           PC3
#define PINIO1_CONFIG 129
#define PINIO1_BOX 0

#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD 0xffff
// notice - masks were programmatically generated - please verify last port group for 0xffff or (BIT(2))

#define DEFAULT_FEATURES       (FEATURE_OSD | FEATURE_TELEMETRY | FEATURE_AIRMODE | FEATURE_RX_SERIAL)
#define DEFAULT_RX_FEATURE     FEATURE_RX_SERIAL

#define USABLE_TIMER_CHANNEL_COUNT 12
#define USED_TIMERS ( TIM_N(1) | TIM_N(2) | TIM_N(3) | TIM_N(4) | TIM_N(5) | TIM_N(8) )

// notice - this file was programmatically generated and may be incomplete.
