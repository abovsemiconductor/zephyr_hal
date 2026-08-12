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

// <q> RTC (Real-Time Clock)
//  <i> - Real-Time Clock (RTC) is an internal block that measures the passage of time.
//  <i> - It must keep accurate time-of-day.
//  <i> - Programmable alarm or automatic wake-up can be implemented by it.
#define CONFIG_HAL_RTC         0

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

// <q> LPUART (Low Power Universal Asynchronus Receiver Transmitter)
//  <i> - Low Power Universal Asynchronous Receiver/Transmitter (LPUART) is asynchronous serial communication protocol.
//  <i> - It is capable of a half and full-duplex asynchronous serial communication by configuring baud-rate, data bit, parity bit and stop bit.
//  <i> - The communiation status is available via line status information such as Parity error, Overrun, Frame error.
#define CONFIG_HAL_LPUART      0

// <q> USART (Universal Synchronous and Asynchronous Receiver Transmitter)
//  <i> - Universal Synchronous and Asynchronous Receiver/Transmitter (USART) is synchronus or asynchronus communication protocol.
//  <i> - It is capable of three different serial communication modes below.
//  <i>  * UART
//  <i>  * USRT
//  <i>  * SPI
#define CONFIG_HAL_USART       0

// <q> USB (Universal Serial Bus)
//  <i> - Universal Serial Bus (USB) is a digital data transmission protocol between a host and connected devices.
//  <i> - It defines the electrical signaling, communication protocol, and device enumeration process.
//  <i>  * USB 1.1 Full-Speed Specification (FS, 12Mbps)
//  <i>  * Configurable number of endpoints from 1 to 5
#define CONFIG_HAL_USB         0

// <q> QEI (Quadrature Encoder Interface)
//  <i> - Quadrature Encoder Interface (QEI) generates a mechanical position signal.
//  <i> - It is capable of detecting position and speed of rotating motion systems such as Motor.
#define CONFIG_HAL_QEI         0

// <q> QSPI (Quad Serial Peripheral Interface)
//  <i> -  specialized communication interface targeting single, dual or quad QSPI NOR flash memories
//  <i> - QSPI extends the standard SPI protocol by utilizing four data lines (IO0 to IO3) instead of one, allowing for higher data transfer rates.
//  <i> - It can operate in any of the two following modes:
//  <i> - Memory-Mapped Mode: In this mode,
//  <i>  * the QSPI flash memory is mapped into the microcontroller's address space,
//  <i>  * allowing for direct access to the flash memory as if it were regular RAM or ROM.
//  <i>  * This mode is particularly useful for executing code directly from the flash memory (eXecute In Place, XIP) or for reading large data sets without the need for explicit read commands.
//  <i> - Indirect Mode: In this mode,
//  <i>  * the microcontroller communicates with the QSPI flash memory using specific commands to read from or write to the memory.
//  <i>  * This mode is typically used for operations that require more control over the data transfer process, such as writing data to the flash memory or performing erase operations.
#define CONFIG_HAL_QSPI        1

// </h> Connectivity & Communication Group

// <h> Analog Group

// <q> ADC (Analog-to-Digital Converter)
//  <i> - Analog-to-Digital Converter (ADC) converts an analog signal into a digital signal.
//  <i> - It has N-bit resolution and multiple indedpendent channels on which the converting operates.
//  <i> - Moreover, it is triggered by the specific interrupt of Timer or MPWM sampling a voltage level on the channel.
#define CONFIG_HAL_ADC         0

// <q> DAC (Digital-to-Analog Converter)
//  <i> - Digital-to-Analog Converter (DAC) converts a digital signal into an analog signal.
//  <i> - N-bit digital value is transformed to an analog output based on successive approximation logic.
#define CONFIG_HAL_DAC         0

// <q> CMP (Comparator)
//  <i> - Comparator compares levels of both an input analogue voltage and an external reference voltage/internal reference voltage.
//  <i> - It provides an binary value as the comparision result.
#define CONFIG_HAL_CMP         0

// <q> PGA (Programmable Gain Amplifier)
//  <i> - Programmable Gain Amplifier (PGA) is used to amplify an insufficient signal level of an analog input to the sufficient level.
#define CONFIG_HAL_PGA         0

// </h> Analog Group

// <h> Security & Integrity Group

// <q> CRC (Cyclic Redundancy Check)
//  <i> - Cyclic Redundancy Check (CRC) generates an error-detection code which is calcucated based on polynomials.
//  <i> - The error-detection code is used to examine the integrity of data transmission, storage or flash memory.
//  <i> - CRC-7, CRC-8, CRC-16 and CRC32 can be available.
#define CONFIG_HAL_CRC         0

// <q> RNG (Random Number Generator)
//  <i> - Random Number Generator (RNG) generates a random number from on a specific seed.
//  <i> - Because a random number has to be unpredicatable, it is used for cryptography function or a variety of security applications.
#define CONFIG_HAL_RNG         0

// <q> AES (Advanced Encryption Standard)
//  <i> - Advanced Encryption Standard (AES) encrypts and decrypts data based on a symmetric-key alogrithm.
//  <i> - It is used to protect private or sensitive information.
//  <i> - Size of data block and key are 128bit.
#define CONFIG_HAL_AES         0

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

// <h> Display Group

// <q> LCD (Liquied Crystal Display)
//  <i> - Liquied Crystal Display (LCD) controller is capable of driving Mono Twisted Nematic(TN)/Super Twisted Nematic(STN) LCD device.
#define CONFIG_HAL_LCD         0

// </h> Display Group

// <h> Miscellaneous Group

// <q> VREFBUF (Voltage Reference Buffer)
//  <i> - Voltage Reference Buffer (VREFBUF) provides a stable reference voltage for ADC, DAC.
//  <i> - It improves measurement accuracy by reducing the influence of supply voltage and noise on analog conversions.
#define CONFIG_HAL_VREFBUF     0

// </h> Miscellaneous Group

// </h> End of ABOV example configuration

/*
//------------- <<< end of configuration section >>> --------------------------
*/

#endif /* ABOV_MODULE_CONFIG_H_ */
/** @} */ /* End of group ABOV MODULE CONFIG */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
