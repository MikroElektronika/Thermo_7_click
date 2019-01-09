_systemInit:
;Click_Thermo7_STM.c,33 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Thermo7_STM.c,35 :: 		mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
MOVS	R2, #1
MOVS	R1, #7
MOVS	R0, #0
BL	_mikrobus_gpioInit+0
;Click_Thermo7_STM.c,36 :: 		mikrobus_i2cInit( _MIKROBUS1, &_THERMO7_I2C_CFG[0] );
MOVW	R0, #lo_addr(__THERMO7_I2C_CFG+0)
MOVT	R0, #hi_addr(__THERMO7_I2C_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_i2cInit+0
;Click_Thermo7_STM.c,37 :: 		mikrobus_logInit( _LOG_USBUART_A, 9600 );
MOVW	R1, #9600
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_Thermo7_STM.c,38 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_systemInit0:
SUBS	R7, R7, #1
BNE	L_systemInit0
NOP
NOP
NOP
;Click_Thermo7_STM.c,39 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_Thermo7_STM.c,41 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Thermo7_STM.c,43 :: 		thermo7_i2cDriverInit( (T_THERMO7_P)&_MIKROBUS1_GPIO, (T_THERMO7_P)&_MIKROBUS1_I2C, 0x48 );
MOVS	R2, #72
MOVW	R1, #lo_addr(__MIKROBUS1_I2C+0)
MOVT	R1, #hi_addr(__MIKROBUS1_I2C+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_thermo7_i2cDriverInit+0
;Click_Thermo7_STM.c,44 :: 		thermo7_setConfiguration( _THERMO7_CONFIG_COMPARATOR_MODE | _THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH );
MOVS	R0, __THERMO7_CONFIG_COMPARATOR_MODE
ORR	R0, R0, __THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH
BL	_thermo7_setConfiguration+0
;Click_Thermo7_STM.c,45 :: 		thermo7_setResolution( _THERMO7_CONFIG_ADC_RESOLUTION_12bit );
MOVS	R0, __THERMO7_CONFIG_ADC_RESOLUTION_12bit
BL	_thermo7_setResolution+0
;Click_Thermo7_STM.c,46 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_Thermo7_STM.c,48 :: 		void applicationTask()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Thermo7_STM.c,50 :: 		AmbientTemperature = thermo7_readAmbientTemperature();
BL	_thermo7_readAmbientTemperature+0
MOVW	R1, #lo_addr(_AmbientTemperature+0)
MOVT	R1, #hi_addr(_AmbientTemperature+0)
STR	R0, [R1, #0]
;Click_Thermo7_STM.c,51 :: 		FloatToStr(AmbientTemperature, tempText);
MOVW	R1, #lo_addr(_tempText+0)
MOVT	R1, #hi_addr(_tempText+0)
BL	_FloatToStr+0
;Click_Thermo7_STM.c,52 :: 		mikrobus_logWrite(" Ambient temperature : ", _LOG_TEXT );
MOVW	R0, #lo_addr(?lstr1_Click_Thermo7_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_Thermo7_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Thermo7_STM.c,53 :: 		mikrobus_logWrite(tempText, _LOG_TEXT);
MOVS	R1, #1
MOVW	R0, #lo_addr(_tempText+0)
MOVT	R0, #hi_addr(_tempText+0)
BL	_mikrobus_logWrite+0
;Click_Thermo7_STM.c,54 :: 		mikrobus_logWrite(" °C", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr2_Click_Thermo7_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_Thermo7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Thermo7_STM.c,55 :: 		Delay_ms( 1000 );
MOVW	R7, #6911
MOVT	R7, #183
NOP
NOP
L_applicationTask2:
SUBS	R7, R7, #1
BNE	L_applicationTask2
NOP
NOP
NOP
;Click_Thermo7_STM.c,56 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationTask
_main:
;Click_Thermo7_STM.c,58 :: 		void main()
;Click_Thermo7_STM.c,60 :: 		systemInit();
BL	_systemInit+0
;Click_Thermo7_STM.c,61 :: 		applicationInit();
BL	_applicationInit+0
;Click_Thermo7_STM.c,63 :: 		while (1)
L_main4:
;Click_Thermo7_STM.c,65 :: 		applicationTask();
BL	_applicationTask+0
;Click_Thermo7_STM.c,66 :: 		}
IT	AL
BAL	L_main4
;Click_Thermo7_STM.c,67 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
