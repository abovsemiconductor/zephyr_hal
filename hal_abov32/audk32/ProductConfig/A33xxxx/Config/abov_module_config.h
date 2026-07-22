/**
 *******************************************************************************
 * @file        abov_module_config.h
 * @author      ABOV R&D Division
 * @brief       Module(HAL) level configuration file
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/** @addtogroup VENDOR ABOV Semiconductor Co., Ltd.
  * @{
*/


/* @addtogroup ABOV MODULE CONFIG
  * @{
*/

#ifndef ABOV_MODULE_CONFIG_H_
#define ABOV_MODULE_CONFIG_H_

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -------------------
*/
// <h> ABOV Module(HAL) Configuration

//  <n> Note. Consider RAM & ROM size, and modify RAM & ROM size at linker file. (e.g scatter file, lds file etc)

// <h> System

// <n> SCU (System Core Unit Core) included by default
// <q> SCU CLK (System Core Unit Clock)
//  <i> - A SCU Clock is one of the System Control Unit(SCU) subsystem.
//  <i> - This system provides high/low speed clock oscillated by internal oscillator and external oscillator.
//  <i> - There is a Phase-Locked Loop (PLL) block that oscillates based on the high speed internal/external clock for more faster system and peripheral operating. 
#define CONFIG_HAL_SCU_CLK     0

// <q> SCU LVD (System Core Unit Low Voltage Detector)
//  <i> - A SCU Low Voltage Detector (LVD) is one of the System Control Unit(SCU) subsystem.
//  <i> - This system provides to detect unstable power supply and notifies the danger or generates system reset itself.
#define CONFIG_HAL_SCU_LVD     0

// <q> SCU PWR (System Core Unit Power)
//  <i> - A SCU Power is one of the System Control Unit(SCU) subsystem.
//  <i> - This system consists of some operating mode such as INIT mode, RUN mode, SLEEP mode, DEEP-SLEEP mode, DEEP-SLEEP2 Mode.
//  <i>   * INIT mode : An Initial state of the chip when a reset is asserted.
//  <i>   * RUN mode : The maximum performance with high-speed clock system.
//  <i>   * SLEEP mode : Used as a low power consumption mode by halting processor core.
//  <i>   * DEEP-SLEEP and DEEP-SLEEP2 mode : Used as a low power consumption mode by halting processor core and unused peripherals.
#define CONFIG_HAL_SCU_PWR     0

// </h> System

// <h> Port 

// <n> PCU / GPIO (Port Control Unit / General Port Input Output)
//  <i> - Port Control Unit (PCU) supports the two major functions below.
//  <i> - Port Control
//  <i>  * Configures an external signal direction
//  <i>  * Configures Interrupt trigger mode
//  <i>  * Controls Internal pull-up/down and open-drain
//  <i> - GPIO
//  <i>  * Outputs signal level (H/L) on a pin
//  <i>  * Sets an external interrupt mode up (Level, Rising edge, Falling edge, Both edge)
//  <i>  * Disables/enables pull-up/down

// </h> Port 
// <h> Timer Group

// <q> TIMER1 (16bit Timer)
//  <i> - The source clock prescaled by the dedicated prescaler is fed to Timer1.
//  <i> - Timer1 receives the prescaled source clock and produces 16bit counter.
//  <i> - Timer1 has four operation modes below.
//  <i>  * Periodic mode
//  <i>  * Pulse Width Modulation(PWM) mode
//  <i>  * One-shot mode
//  <i>  * Capture mode
#define CONFIG_HAL_TIMER1      0

// <q> WDT (Watch-Dog Timer)
//  <i> - A Watch-Dog Timer (WDT) rapidly detects CPU's malfunction such as endless looping caused by noise, and generates WDT signal.
//  <i> - The WDT signal can be used for resetting CPU or triggering interrupt.
//  <i> - If WDT function is disabled, it can be used as a normal timer to generate an interrupt at a fixed interval. 
#define CONFIG_HAL_WDT         0

// <q> FRT (Free-Run Timer)
//  <i> - Free-Run Timer (FRT) is a 32-bit up-count timer and generating a event at a certain interval.
#define CONFIG_HAL_FRT         0

// <q> MPWM (Motor Pulse Width Modulation)
//  <i> - Motor Pulse Width Modulation (MPWM) is a sort of ABOV terminology and a special PWM supporting motor control.
//  <i> - It has three operation modes below.
//  <i>  * Motor PWM mode for Motor control
//  <i>  * Normal PWM mode for a variety of PWM applications
//  <i>  * Individual PWM mode for specific applications like IH cooker.
//  <i> - Moreover, dead-time for half-bridge circuit and, detecting external protection and over-voltage event are supported.
#define CONFIG_HAL_MPWM        0

// <q> PWM (Pulse Width Modulation)
//  <i> - Pulse Width Modulation (PWM) refers to a modulation method that changes the pulse width of the signal to be transmitted.
//  <i> - It is used for motor control or voltage regulation.
#define CONFIG_HAL_PWM         0

// </h> Timer Group

// <h> Connectivity & Communication Group

// <q> I2C (Inter-Integrated Circuit)
//  <i> - Inter-Integrated Circuit (I2C) is a standard protocol using two wires to attach lower-speed peripheral ICs to processors/microcontroller.
//  <i> - It supprots transmitting and receiving data with Serial Data Line (SDA) and Serial Clock Line(SCL).
#define CONFIG_HAL_I2C         0

// <q> SPI (Serial Peripheral Interface)
//  <i> - Serial Peripheral Interface (SPI) is a synchronous serial communication interface specification used for short-distance communication using the four wires bleow.
//  <i>  * SS : chip select
//  <i>  * SCK : serial clock
//  <i>  * MOSI : master out slave in
//  <i>  * MISO : master in slave out
//  <i> - Master/slave mode and full-duplex communication are supported  
#define CONFIG_HAL_SPI         0

// <q> UART (Universal Asynchronus Receiver Transmitter)
//  <i> - Universal Asynchronous Receiver/Transmitter (UART) is asynchronous serial communication protocol.
//  <i> - It is capable of a full-duplex asynchronous serial communication by configuring baud-rate, data bit, parity bit and stop bit.
//  <i> - The communiation status is available via line status information such as Parity error, Overrun, Frame error.
#define CONFIG_HAL_UART        0

// <q> QEI (Quadrature Encoder Interface)
//  <i> - Quadrature Encoder Interface (QEI) generates a mechanical position signal.
//  <i> - It is capable of detecting position and speed of rotating motion systems such as Motor.
#define CONFIG_HAL_QEI         0

// </h> Connectivity & Communication Group

// <h> Analog Group

// <q> ADC (Analog-to-Digital Converter)
//  <i> - Analog-to-Digital Converter (ADC) converts an analog signal into a digital signal.
//  <i> - It has N-bit resolution and multiple indedpendent channels on which the converting operates.
//  <i> - Moreover, it is triggered by the specific interrupt of Timer or MPWM sampling a voltage level on the channel.
#define CONFIG_HAL_ADC         0

// <q> AFE (Analog Front End)
//  <i> - Analog Front End (AFE) is composed of an OPAMP and a comparator."
#define CONFIG_HAL_AFE         0

// </h> Analog Group

// <h> Security & Integrity Group

// <q> CRC (Cyclic Redundancy Check)
//  <i> - Cyclic Redundancy Check (CRC) generates an error-detection code which is calcucated based on polynomials.
//  <i> - The error-detection code is used to examine the integrity of data transmission, storage or flash memory.
//  <i> - CRC-7, CRC-8, CRC-16 and CRC32 can be available.
#define CONFIG_HAL_CRC         0

// </h> Security & Integrity Group

// <h> Memory Group

// <q> FLASH (Stand-Alone Example)
//  <i> - FMC
//  <i>  * Flash Memory Controller (FMC) interfaces an internal code and data flash.
//  <i>  * It is composed of Code Flash Memory Controller (CFCM) and Data Flash Memory Controller (DFMC) for the interfacees.
//  <i>  * The internal code/data flash is supposed to store execution code/data binaries basically.
//  <i>  * For a certain fuctionality, it can access System Flash located at inside of a device.
//  <i> - CFMC
//  <i>  * Code Flash Memory Controller (CFMC) is flash memory controller to interface an internal code flash.
//  <i>  * The internal code flash is supposed to store execution code binaries basically. 
//  <i>  * For a certain fuctionality, it can access System Flash located at inside of a device.
#define CONFIG_HAL_FMC         0

// </h> Memory Group

// </h> End of ABOV example configuration

/*
//------------- <<< end of configuration section >>> --------------------------
*/

#endif /* ABOV_MODULE_CONFIG_H_ */
/** @} */ /* End of group ABOV MODULE CONFIG */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
