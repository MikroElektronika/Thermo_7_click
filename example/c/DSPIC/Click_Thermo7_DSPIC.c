/*
Example for Thermo7 Click

    Date          : Mar 2018.
    Author        : Katarina Perendic

Test configuration dsPIC :
    
    MCU                : P33FJ256GP710A
    Dev. Board         : EasyPIC Fusion v7
    dsPIC Compiler ver : vCANT_FIND_VERSION

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets INT pin as INPUT
- Application Initialization - Initializes driver init and configuration chip and measurement resolutions.
- Application Task - (code snippet) - Reads ambient temperature and logs to USBUART every 1 seconds.

*/

#include "Click_Thermo7_types.h"
#include "Click_Thermo7_config.h"


float AmbientTemperature;
char tempText[256];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_i2cInit( _MIKROBUS1, &_THERMO7_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    Delay_ms( 100 );
}

void applicationInit()
{
    thermo7_i2cDriverInit( (T_THERMO7_P)&_MIKROBUS1_GPIO, (T_THERMO7_P)&_MIKROBUS1_I2C, 0x48 );
    thermo7_setConfiguration( _THERMO7_CONFIG_COMPARATOR_MODE | _THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH );
    thermo7_setResolution( _THERMO7_CONFIG_ADC_RESOLUTION_12bit );
}

void applicationTask()
{
    AmbientTemperature = thermo7_readAmbientTemperature();
    FloatToStr(AmbientTemperature, tempText);
    mikrobus_logWrite(" Ambient temperature : ", _LOG_TEXT );
    mikrobus_logWrite(tempText, _LOG_TEXT);
    mikrobus_logWrite(" °C", _LOG_LINE);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}
