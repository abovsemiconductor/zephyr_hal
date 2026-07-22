/**
 *******************************************************************************
 * @file        evb_a31c144_rln_adk_a.h
 * @author      ABOV R&D Division
 * @brief       EVB (Evaluation Board on which A31C144RLN is mounted)
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _EVB_A31C144_RLN_ADK_A_H_
#define _EVB_A31C144_RLN_ADK_A_H_

/* LED */
#define LED_PORT                    1    /* Port B */
#define LED0_PIN_ID                 8
#define LED1_PIN_ID                 9
#define LED2_PIN_ID                 10
#define LED3_PIN_ID                 11

/* I2C0 Port / LED Driver (AL8700) */
#define LED_DRV_SCL_PORT            3    /* Port D */
#define LED_DRV_SCL_PIN_ID          0
#define LED_DRV_SCL_MUX_ID          1
#define LED_DRV_SDA_PORT            3    /* Port D */
#define LED_DRV_SDA_PIN_ID          1
#define LED_DRV_SDA_MUX_ID          1
#define LED_DRV_RESET_PORT          3    /* Port D */
#define LED_DRV_RESET_PIN_ID        7

/* I2C1 Port / Sensor (A96H115) */
#define SENSOR_SCL_PORT             0    /* Port A */
#define SENSOR_SCL_PIN_ID           1
#define SENSOR_SCL_MUX_ID           1
#define SENSOR_SDA_PORT             0    /* Port A */
#define SENSOR_SDA_PIN_ID           0
#define SENSOR_SDA_MUX_ID           1

/* I2C2 Port / EEPROM */
#define E2PROM_SCL_PORT             2    /* Port C */
#define E2PROM_SCL_PIN_ID           6
#define E2PROM_SCL_MUX_ID           1
#define E2PROM_SDA_PORT             2    /* Port C */
#define E2PROM_SDA_PIN_ID           5
#define E2PROM_SDA_MUX_ID           1

/* UART1 Port / RS-232*/
#define SERIAL_TX_PORT              1    /* Port B */
#define SERIAL_TX_PIN_ID            6
#define SERIAL_TX_MUX_ID            1
#define SERIAL_RX_PORT              1    /* Port B */
#define SERIAL_RX_PIN_ID            7
#define SERIAL_RX_MUX_ID            1

/* USART1 SPI Port / NOR Flash */
#define FLASH_SS_PORT               3    /* Port D */
#define FLASH_SS_PIN_ID             5
#define FLASH_SS_MUX_ID             4
#define FLASH_SCK_PORT              3    /* Port D */
#define FLASH_SCK_PIN_ID            4
#define FLASH_SCK_MUX_ID            4
#define FLASH_MOSI_PORT             3    /* Port D */
#define FLASH_MOSI_PIN_ID           2
#define FLASH_MOSI_MUX_ID           4
#define FLASH_MISO_PORT             3    /* Port D */
#define FLASH_MISO_PIN_ID           3
#define FLASH_MISO_MUX_ID           4

/* USART2 SPI Port / OLED (SSD1309) */
#define DISPLAY_SS_PORT             4    /* Port E */
#define DISPLAY_SS_PIN_ID           11
#define DISPLAY_SS_MUX_ID           4
#define DISPLAY_SCK_PORT            4    /* Port E */
#define DISPLAY_SCK_PIN_ID          10
#define DISPLAY_SCK_MUX_ID          4
#define DISPLAY_MOSI_PORT           4    /* Port E */
#define DISPLAY_MOSI_PIN_ID         8
#define DISPLAY_MOSI_MUX_ID         4
#define DISPLAY_MISO_PORT           4    /* Port E */
#define DISPLAY_MISO_PIN_ID         9
#define DISPLAY_MISO_MUX_ID         4

/* ADC0 Port / Analog Potentiometer */
#define ANALOG_PORT                 4    /* Port E */
#define ANALOG_PIN_ID               3
#define ANALOG_MUX_ID               7

/* TIMER14 Port / Buzzer */
#define BUZZER_PORT                 4    /* Port E */
#define BUZZER_PIN_ID               5
#define BUZZER_MUX_ID               2

/* GPIO Port / IR Receiver */
#define IR_RECEIVER_PORT            2    /* Port C */
#define IR_RECEIVER_PIN_ID          4
#define IR_RECEIVER_MUX_ID          0

/* GPIO Port / Button1 */
#define BUTTON1_PORT                2    /* Port C */
#define BUTTON1_PIN_ID              7
#define BUTTON1_MUX_ID              0

/* GPIO Port / Button2 */
#define BUTTON2_PORT                2    /* Port C */
#define BUTTON2_PIN_ID              8
#define BUTTON2_MUX_ID              0

/* GPIO Port / Level Shifter */
#define LEVEL_SHIFTER_PORT          3    /* Port D */
#define LEVEL_SHIFTER_PIN_ID        6

#endif /* _EVB_A31C144_RLN_ADK_A_H_ */
