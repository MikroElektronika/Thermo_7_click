/*
    __thermo7_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __thermo7_driver.h
@brief    Thermo7 Driver
@mainpage Thermo7 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   THERMO7
@brief      Thermo7 Click Driver
@{

| Global Library Prefix | **THERMO7** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Mar 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _THERMO7_H_
#define _THERMO7_H_

/** 
 * @macro T_THERMO7_P
 * @brief Driver Abstract type 
 */
#define T_THERMO7_P    const uint8_t*

/** @defgroup THERMO7_COMPILE Compilation Config */              /** @{ */

//  #define   __THERMO7_DRV_SPI__                            /**<     @macro __THERMO7_DRV_SPI__  @brief SPI driver selector */
   #define   __THERMO7_DRV_I2C__                            /**<     @macro __THERMO7_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __THERMO7_DRV_UART__                           /**<     @macro __THERMO7_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup THERMO7_VAR Variables */                           /** @{ */

// registers
extern const uint8_t _THERMO7_REG_AMBIENT_TEMPERATURE;
extern const uint8_t _THERMO7_REG_CONFIGURATION;
extern const uint8_t _THERMO7_REG_HYSTERESIS_TEMPERATURE;
extern const uint8_t _THERMO7_REG_TEMPERATURE_LIMIT_SET;

// config register
extern const uint8_t _THERMO7_CONFIG_ONE_SHOT_ENABLE;
extern const uint8_t _THERMO7_CONFIG_ONE_SHOT_DISABLE; // def
extern const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_9bit; // def
extern const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_10bit;
extern const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_11bit;
extern const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_12bit;
extern const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_1;
extern const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_2;
extern const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_4;
extern const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_6;
extern const uint8_t _THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH;
extern const uint8_t _THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_LOW;
extern const uint8_t _THERMO7_CONFIG_COMPARATOR_MODE;
extern const uint8_t _THERMO7_CONFIG_INTERRUPT_MODE;
extern const uint8_t _THERMO7_CONFIG_SHUTDOWN_ENABLE;
extern const uint8_t _THERMO7_CONFIG_SHUTDOWN_DISABLE;

                                                                       /** @} */

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup THERMO7_INIT Driver Initialization */              /** @{ */

#ifdef   __THERMO7_DRV_SPI__
void thermo7_spiDriverInit(T_THERMO7_P gpioObj, T_THERMO7_P spiObj);
#endif
#ifdef   __THERMO7_DRV_I2C__
void thermo7_i2cDriverInit(T_THERMO7_P gpioObj, T_THERMO7_P i2cObj, uint8_t slave);
#endif
#ifdef   __THERMO7_DRV_UART__
void thermo7_uartDriverInit(T_THERMO7_P gpioObj, T_THERMO7_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void thermo7_gpioDriverInit(T_THERMO7_P gpioObj);
                                                                       /** @} */
/** @defgroup THERMO7_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions for configuration chip and measurement
 *
 * @param[in] configuration     data which be written in configuration register
 *
 * Options for configuration:
        ONE-SHOT ( Enable or Disable ),
        ADC RESOLUTION ( 9bit - 0.5 °C, 10bit - 0.25 °C, 11bit - 0.125 °C or 12bit - 0.0625 °C)
        FAULT QUEUE ( 1, 2, 4 or 6 )
        ALERT POLARITY ( Active HIGH or LOW )
        COMP/INT ( Interrupt mode or Comparator mode )
        SHUTDOWN ( Enable or Disable )
        
 * Power - up default:
        ONE-SHOT ( Disable ),
        ADC RESOLUTION ( 9bit - 0.5 °C )
        FAULT QUEUE ( 1 )
        ALERT POLARITY ( Active LOW )
        COMP/INT ( Comparator mode )
        SHUTDOWN ( Disable )
 *
 */
void thermo7_setConfiguration(uint8_t configuration);

/**
 * @brief Functions for settings ADC resolution measurement
 *
 * @param[in] resolution     resolution which be written in configuration register
 *
 * Options for configuration:
        ADC RESOLUTION:
           9bit - 0.5 C (Power-up default),
           10bit - 0.25 C,
           11bit - 0.125 C,
           12bit - 0.0625 C
 *
 */
void thermo7_setResolution(uint8_t resolution);

/**
 * @brief Functions for settings Hysteresis Temperature
 *
 * @param[in] temperature     data which be written in Hysteresis register
 *
 * This register is used to set a hysteresis for the Temperature set Limit. 
   Therefore, the data represents a minimum temperature limit.
   The power-up default value of THYST register is 75°C.
 *
 */
void thermo7_setHysteresisTemperature(int16_t temperature);

/**
 * @brief Functions for settings limit Temperature
 *
 * @param[in] temperature     data which be written in LimitTemperature register
 *
 * This data represents a maximum temperature limit.
   The power-up default value of the TSET register is 80°C.
 *
 */
void thermo7_setLimitTemperature(int16_t temperature);

/**
 * @brief Functions for reads ambient temperature
 *
 * @return ambient temperature in °C
 *
 * Temperature register that contains 9-bit to 12-bit temperature data. 
   (0.5°C to 0.0625°C resolutions, respectively)
   The lower limit of reading the temperature is -55 °C and the upper limit is 125 °C
 *
 */
float thermo7_readAmbientTemperature();

/**
 * @brief Functions for reads Hysteresis Temperature
 *
 * @return 9 bit Hysteresis Temperature data
 *
 * This register is used to set a hysteresis for the Temperature set Limit.
   Therefore, the data represents a minimum temperature limit.
   The power-up default value of THYST register is 75°C.
 *
 */
int16_t thermo7_getHysteresisTemperature();

/**
 * @brief Functions for reads setLimit Temperature
 *
 * @return 9 bit setLimit Temperature data
 *
 * This data represents a maximum temperature limit.
   The power-up default value of the TSET register is 80°C.
 *
 */
int16_t thermo7_getLimitTemperature();

/**
 * @brief Functions for reads state of interrupt pins
 *
 * @return state of interrupt pins
 *
 * The ALERT output can be configured with the setConfiguration function as a
   comparator output or as an interrupt output mode.
   Polarity can also be specified as active-high or actively low.
   
   In Comparator mode, the ALERT output is asserted
   when ambient temperature is greater than TSET. The pin remains active
   until ambient temperature is lower than THYST.
   
   In the interrupt mode, the ALERT output is confirmed when
   the ambient temperature is higher than the TSET. However, the output will be
   reset when a user reads from any one
   register.
 *
 */
uint8_t thermo7_getInterrupt();








                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Thermo7_STM.c
    @example Click_Thermo7_TIVA.c
    @example Click_Thermo7_CEC.c
    @example Click_Thermo7_KINETIS.c
    @example Click_Thermo7_MSP.c
    @example Click_Thermo7_PIC.c
    @example Click_Thermo7_PIC32.c
    @example Click_Thermo7_DSPIC.c
    @example Click_Thermo7_AVR.c
    @example Click_Thermo7_FT90x.c
    @example Click_Thermo7_STM.mbas
    @example Click_Thermo7_TIVA.mbas
    @example Click_Thermo7_CEC.mbas
    @example Click_Thermo7_KINETIS.mbas
    @example Click_Thermo7_MSP.mbas
    @example Click_Thermo7_PIC.mbas
    @example Click_Thermo7_PIC32.mbas
    @example Click_Thermo7_DSPIC.mbas
    @example Click_Thermo7_AVR.mbas
    @example Click_Thermo7_FT90x.mbas
    @example Click_Thermo7_STM.mpas
    @example Click_Thermo7_TIVA.mpas
    @example Click_Thermo7_CEC.mpas
    @example Click_Thermo7_KINETIS.mpas
    @example Click_Thermo7_MSP.mpas
    @example Click_Thermo7_PIC.mpas
    @example Click_Thermo7_PIC32.mpas
    @example Click_Thermo7_DSPIC.mpas
    @example Click_Thermo7_AVR.mpas
    @example Click_Thermo7_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __thermo7_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */