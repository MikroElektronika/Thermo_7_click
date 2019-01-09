![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Thermo7 Click

- **CIC Prefix**  : THERMO7
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : Mar 2018.

---

### Software Support

We provide a library for the Thermo7 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2367/thermo-7-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines I2C bus drivers and driver functions that offer a choice for writing data in registers and reading data
from registers. 
The library offers the possibility of setting the upper and lower temperature limits, and the main thing is reading the ambient temperature.
ADC resolution can be set to 9bit, 10bit, 11bit or 12bit, with an accuracy of 0.5 C, 0.25 C, 0.125 C or 0.0625 C.
The user can adjust the state and behavior of interrupt pins in the set modes. Modes that can be set are Interrupt mode and Comparator mode.

Key functions :

- ``` float thermo7_readAmbientTemperature() ``` - Function reads ambient temperature 
- ``` void thermo7_setConfiguration(uint8_t configuration) ``` - Function for configuration chip and measurement
- ``` void thermo7_setResolution(uint8_t resolution) ``` - Function sets ADC resolution measurement

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets INT pin as INPUT.
- Application Initialization - Initializes driver init and configuration chip and measurement resolutions.
- Application Task - (code snippet) - Reads ambient temperature and logs to USBUART every 1 second.


```.c
void applicationTask()
{
    AmbientTemperature = thermo7_readAmbientTemperature();
    FloatToStr( AmbientTemperature, tempText );
    mikrobus_logWrite( " Ambient temperature : ", _LOG_TEXT );
    mikrobus_logWrite( tempText, _LOG_TEXT );
    mikrobus_logWrite( " °C", _LOG_LINE );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2367/thermo-7-click) page.

Other mikroE Libraries used in the example:

- Conversions
- I2C
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
