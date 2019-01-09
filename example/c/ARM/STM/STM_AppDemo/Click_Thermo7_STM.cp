#line 1 "C:/Users/katarina.perendic/Desktop/Thermo 7 click/example/c/ARM/STM/STM_AppDemo/Click_Thermo7_STM.c"
#line 1 "c:/users/katarina.perendic/desktop/thermo 7 click/example/c/arm/stm/stm_appdemo/click_thermo7_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 1 "c:/users/katarina.perendic/desktop/thermo 7 click/example/c/arm/stm/stm_appdemo/click_thermo7_config.h"
#line 1 "c:/users/katarina.perendic/desktop/thermo 7 click/example/c/arm/stm/stm_appdemo/click_thermo7_types.h"
#line 19 "c:/users/katarina.perendic/desktop/thermo 7 click/example/c/arm/stm/stm_appdemo/click_thermo7_config.h"
const uint32_t _THERMO7_I2C_CFG[ 1 ] =
{
 100000
};
#line 1 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 58 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
extern const uint8_t _THERMO7_REG_AMBIENT_TEMPERATURE;
extern const uint8_t _THERMO7_REG_CONFIGURATION;
extern const uint8_t _THERMO7_REG_HYSTERESIS_TEMPERATURE;
extern const uint8_t _THERMO7_REG_TEMPERATURE_LIMIT_SET;


extern const uint8_t _THERMO7_CONFIG_ONE_SHOT_ENABLE;
extern const uint8_t _THERMO7_CONFIG_ONE_SHOT_DISABLE;
extern const uint8_t _THERMO7_CONFIG_ADC_RESOLUTION_9bit;
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
#line 93 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
void thermo7_i2cDriverInit( const uint8_t*  gpioObj,  const uint8_t*  i2cObj, uint8_t slave);
#line 100 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
void thermo7_gpioDriverInit( const uint8_t*  gpioObj);
#line 126 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
void thermo7_setConfiguration(uint8_t configuration);
#line 141 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
void thermo7_setResolution(uint8_t resolution);
#line 153 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
void thermo7_setHysteresisTemperature(int16_t temperature);
#line 164 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
void thermo7_setLimitTemperature(int16_t temperature);
#line 176 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
float thermo7_readAmbientTemperature();
#line 188 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
int16_t thermo7_getHysteresisTemperature();
#line 199 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
int16_t thermo7_getLimitTemperature();
#line 220 "c:/users/katarina.perendic/desktop/thermo 7 click/library/__thermo7_driver.h"
uint8_t thermo7_getInterrupt();
#line 30 "C:/Users/katarina.perendic/Desktop/Thermo 7 click/example/c/ARM/STM/STM_AppDemo/Click_Thermo7_STM.c"
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
 thermo7_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, 0x48 );
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
