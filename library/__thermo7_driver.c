/*
    __thermo7_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__thermo7_driver.h"
#include "__thermo7_hal.c"

/* ------------------------------------------------------------------- MACROS */

// registers
const uint8_t _THERMO7_REG_AMBIENT_TEMPERATURE      = 0x00;
const uint8_t _THERMO7_REG_CONFIGURATION            = 0x01;
const uint8_t _THERMO7_REG_HYSTERESIS_TEMPERATURE   = 0x02;
const uint8_t _THERMO7_REG_TEMPERATURE_LIMIT_SET    = 0x03;

// config register
const uint8_t _THERMO7_CONFIG_ONE_SHOT_ENABLE            = 0x01 << 7;
const uint8_t _THERMO7_CONFIG_ONE_SHOT_DISABLE           = 0x00 << 7;
const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_9bit        = 0x00 << 5;
const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_10bit       = 0x01 << 5;
const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_11bit       = 0x02 << 5;
const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_12bit       = 0x03 << 5;
const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_1         = 0x00 << 3;
const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_2         = 0x01 << 3;
const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_4         = 0x02 << 3;
const uint8_t _THERMO7_CONFIG_FAULT_QUEUE_MODE_6         = 0x03 << 3;
const uint8_t _THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH = 0x01 << 2;
const uint8_t _THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_LOW  = 0x00 << 2;
const uint8_t _THERMO7_CONFIG_COMPARATOR_MODE            = 0x00 << 1;
const uint8_t _THERMO7_CONFIG_INTERRUPT_MODE             = 0x01 << 1;
const uint8_t _THERMO7_CONFIG_SHUTDOWN_ENABLE            = 0x01 ;
const uint8_t _THERMO7_CONFIG_SHUTDOWN_DISABLE           = 0x00;



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __THERMO7_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __THERMO7_DRV_SPI__

void thermo7_spiDriverInit(T_THERMO7_P gpioObj, T_THERMO7_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __THERMO7_DRV_I2C__

void thermo7_i2cDriverInit(T_THERMO7_P gpioObj, T_THERMO7_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __THERMO7_DRV_UART__

void thermo7_uartDriverInit(T_THERMO7_P gpioObj, T_THERMO7_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif


/* ----------------------------------------------------------- IMPLEMENTATION */

float thermo7_readAmbientTemperature()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 2 ] = {0};
    float Temp_msb;
    uint8_t Temp_lsb;
    
    writeReg[ 0 ] = _THERMO7_REG_AMBIENT_TEMPERATURE;
    
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 2, END_MODE_STOP );
    Delay_100ms();
    
    Temp_msb = readReg[ 0 ];
    Temp_lsb = readReg[ 1 ] & 0xF0;

    if( temp_lsb & 0x80 ) Temp_msb += 0.50;
    if( temp_lsb & 0x40 ) Temp_msb += 0.25;
    if( temp_lsb & 0x20 ) Temp_msb += 0.125;
    if( temp_lsb & 0x10 ) Temp_msb += 0.0625;
    return Temp_msb;

}

void thermo7_setConfiguration(uint8_t configuration)
{
    uint8_t writeReg[ 2 ];
    
    writeReg[ 0 ] = _THERMO7_REG_CONFIGURATION;
    writeReg[ 1 ] = configuration;
    
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 2, END_MODE_STOP );
    Delay_100ms();
}

int16_t thermo7_getHysteresisTemperature()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 2 ] = {0};
    int16_t hysteresisTemperature;
    writeReg[ 0 ] = _THERMO7_REG_HYSTERESIS_TEMPERATURE;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 2, END_MODE_STOP );
    Delay_100ms();

    hysteresisTemperature =  readReg[ 0 ];
    hysteresisTemperature <<= 8;
    hysteresisTemperature |= ( readReg[ 1 ] & 0x80 );

    return hysteresisTemperature;
}

void thermo7_setHysteresisTemperature(int8_t temperature)
{
    uint8_t writeReg[ 3 ];
    uint8_t negativeLower = 0;
    
    if (temperature < 0)
        negativeLower = 1;
        
    writeReg[ 0 ] = _THERMO7_REG_HYSTERESIS_TEMPERATURE;
    writeReg[ 1 ] = ( temperature & 0x7F ) | (negativeLower << 7);
    writeReg[ 2 ] = 0x00;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 3, END_MODE_STOP );
    Delay_100ms();
}

int16_t thermo7_getLimitTemperature()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 2 ] = {0};
    int16_t LimitTemperature;
    writeReg[ 0 ] = _THERMO7_REG_TEMPERATURE_LIMIT_SET;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 2, END_MODE_STOP );
    Delay_100ms();

    LimitTemperature =  readReg[ 0 ];
    LimitTemperature <<= 8;
    LimitTemperature |= ( readReg[ 1 ] & 0x80 );

    return LimitTemperature;
}

void thermo7_setLimitTemperature(int16_t temperature)
{
    uint8_t writeReg[ 3 ];
    uint8_t negativeUpper = 0;

    if (temperature < 0)
        negativeUpper = 1;

    writeReg[ 0 ] = _THERMO7_REG_TEMPERATURE_LIMIT_SET;
    writeReg[ 1 ] = ( temperature & 0x7F ) | (negativeUpper << 7);
    writeReg[ 2 ] = 0x00;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 3, END_MODE_STOP );
    Delay_100ms();
}

uint8_t thermo7_getInterrupt()
{
    return hal_gpio_intGet();
}

void thermo7_setResolution(uint8_t resolution)
{
    uint8_t writeReg[ 2 ];
    uint8_t readReg[ 1 ];

    writeReg[0] = _THERMO7_REG_CONFIGURATION;
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );
    Delay_100ms();
    
    writeReg[ 1 ] = readReg[ 0 ] | resolution;
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 2, END_MODE_STOP );
    Delay_100ms();
}


/* -------------------------------------------------------------------------- */
/*
  __thermo7_driver.c

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