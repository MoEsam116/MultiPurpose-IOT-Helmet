/*
 ******************************************************************************
 * @file           : DHT11_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Nov 15, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 ******************************************************************************
 */

/*==============================================================================================================================================
 * INCLUDES SECTION
 *==============================================================================================================================================*/

#include <stdint.h>
#include <stdlib.h>
//#include <stdio.h>
#include "../../../Library/ErrType.h"
#include "../../../Library/STM32F103xx.h"

#include "../../../MCAL/EXTI/Inc/EXTI_Interface.h"
#include "../../../MCAL/SYSTICK/Inc/SYSTICK_Interface.h"
#include "../../../MCAL/GPIO/Inc/GPIO_Interface.h"
#include "../../../MCAL/AFIO/Inc/AFIO_Interface.h"
#include "../../../MCAL/UART/Inc/UART_Interface.h"
#include "../Inc/DHT11_Interface.h"
#include "../Inc/DHT11_Prv.h"

/*==============================================================================================================================================
 * INCLUDES SECTION
 *==============================================================================================================================================*/

PORT_t PORT_NUMBER;

/*AKA EXTILine */
Pin_t PIN_NUMBER;

_vo uint8_t DATA_TO_PROCESS[DHT11_ARRAY_SIZE] = {0};

_vo uint8_t IS_TempReadyToRead = NOT_READY;

/* INDICATOR VARIABLE FOR FIRST FALLING EDGE OR SECOND FALLING EDGE */
_vo uint8_t _u8Indicator = FIRST_EDGE;

/* COUNTER FOR TRACING DATA ARRAY */
_vo uint8_t _u8Counter = 0;
/*==============================================================================================================================================
 * IMPLEMENTATION SECTION
 *==============================================================================================================================================*/

/**
 * @fn 		: HDHT11_eInit(EXTI_LINE_t, Port_t)
 * @brief 	: THIS FUNCTION INITIALIZES DHT11 SENSOR FOR THE USED DATA LINE ON WHICH PORT & WHAT EXTI LINE WILL BE USED
 *
 * @param 	: EXTILine		=> EXTI LINE CHOOSEN BY USER ( ALSO EQUIVELANT TO PIN NUMBER ) CHECK FOR OPTIONS @EXTI_LINE_t
 * @param   : PortNumber	=> PORT NUMBER CHOOSEN TO WHICH EXTI CIRCUIT WILL DETECT CHANGES
 * @return	: ERROR STATUS
 * @note	: YOU SHOULD ENABLE AFIO & GPIO FOR THE CHOOSEN PORT FOR EX. IF YOU CHOOSE PORTA YOU HAVE TO ENABLE GPIOA
 * 				THROUGH RCC REGISTERS BEFORE CALLING THIS FUNCION
 */
ERRORS_t HDHT11_eInit(EXTI_LINE_t EXTILine, PORT_t PortNumber)
{
	ERRORS_t Local_ErrorStatus = OK;

	/* CHECK ON FUNCITON PARAMETERS */
	if ((EXTILine < EXTI_LINE_0) || (EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV))
	{
		return NOK;
	}
	else if ((PortNumber < PORTA) || (PortNumber > PORTC))
	{
		return NOK;
	}
	else
	{
		/* GOOD PARAMETERS */

		/* INITIALIZE GLOBALLY */
		PORT_NUMBER = PortNumber;
		PIN_NUMBER = EXTILine;

		/* DATA PIN CONIFGURATION */
		Pin_Config_t DATAPIN =
			{
				.Mode = Input, .PinNum = PIN_NUMBER, .Port = PORT_NUMBER, .InputMode = Floating_Input};

		/* INITIALIZE GPIO PIN */
		GPIO_u8PinInit(&DATAPIN);

		/* CONFIGURING EXTI PORT MUX SELECTION THROUGH AFIO REGISTERS */
		AFIO_U8SetEXTIPort(EXTILine, PORT_NUMBER);

		/* SET EXTI LINE CALL BACK */
		MEXTI_SetCallBack(EXTILine, _vCallBackFunc);

		/* ENABLE EXTI LINE WITH FALLING EDGE TRIGGER */
		MEXTI_eEnableEXTILine(PIN_NUMBER, EXTI_TRIGGER_FALLING);
	}

	return Local_ErrorStatus;
}

/**
 * @fn 			: HDHT11_eGetTempHumidity(float_t*, float_t*)
 * @brief 		: THIS FUNCTION READS TEMPERATURE & HUMIDITY FROM DHT11 SENSOR
 *
 * @param[out]  : Copy_pf32Temp		=> RETURN TO THE USER TEMPERATURE VALUE IN CELSIUS
 * @param[out]	: Copy_pf32Humidity	=> RETURN TO THE USER HUMIDITY VALUE IN PERCENTAGE
 * @return		: ERROR STATUS
 */
ERRORS_t HDHT11_eGetTempHumidity(float *Copy_pf32Temp, float *Copy_pf32Humidity)
{
	/* ERROR STATUS */
	ERRORS_t Local_ErrorStatus = OK;

	/* VARIABLES TO HOLD TEMPERATURE & HUMIDITY , INTEGRAL & DECIMAL VALUES */
	uint8_t Local_u8IntegralHumidity = 0, Local_u8IntegralTemperature = 0,
			Local_u8DecimalHumidity = 0, Local_u8DecimalTemperature = 0,
			Local_u8CheckSum = 0;
	uint32_t TimeOut = 0;

	/* SEND START SIGNAL TO DHT11 */
	_vSendStartSignal();

	/* WAIT UNTILL DATA IS TRANSMITTID FULLY FROM DHT11 SENSOR TO MCU */

	while (IS_TempReadyToRead != READY);

	/* DATA IS TRANSMITTED FULLY FROM DH11 TO THE MCU */

	/* CONVERT FROM TIMINGS TO BITS IN THE GLOBAL ARRAY */
	_vTimingsToBits();
	//UART_SendBufferSynchronous("DHT Done 2 \r\n");

	/* CONVERT BITS TO BYTES OF USEFUL DATA */
	_vBitsToBytes(&Local_u8IntegralTemperature, &Local_u8DecimalTemperature, &Local_u8IntegralHumidity, &Local_u8DecimalHumidity, &Local_u8CheckSum);

	if (Local_u8CheckSum != (Local_u8DecimalHumidity + Local_u8DecimalTemperature + Local_u8IntegralHumidity + Local_u8IntegralTemperature))
	{
		return NOK;
	}
	else
	{
		/* CHECK SUM VALUE IS CORRECT */

		uint8_t Local_u8DigitsCounter = 1;

		uint8_t Local_u8Temp = Local_u8DecimalTemperature;

		while (Local_u8Temp != 0)
		{
			Local_u8Temp /= 10;
			Local_u8DigitsCounter *= 10;
		}

		/* RETURNING TEMP */
		*Copy_pf32Temp = (float)((float)Local_u8IntegralTemperature + ((float)Local_u8DecimalTemperature / (float)Local_u8DigitsCounter));

		Local_u8Temp = Local_u8DecimalHumidity;
		Local_u8DigitsCounter = 1;

		while (Local_u8Temp != 0)
		{
			Local_u8Temp /= 10;
			Local_u8DigitsCounter *= 10;
		}

		/* RETURNING HUMIDITY */
		*Copy_pf32Humidity = (float)((float)Local_u8IntegralHumidity + ((float)Local_u8DecimalHumidity / (float)Local_u8DigitsCounter));

		/* RESET VARIABLE */
		IS_TempReadyToRead = NOT_READY;

	}

	return Local_ErrorStatus;
}

/**
 * @fn 			: _vBitsToBytes(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*)
 * @brief 		: THIS FUNCTION CONVERTS BITS IN DATA ARRAY INTO USEFUL DATA : INTEGRAL TEMP , INTEGRAL HUMIDITY , CHECK SUM
 *
 * @param[out] 	: Copy_pu8IntegralTemp		=> AS A RETURN FOR USER INTEGRAL PART OF TEMPERATURE
 * @param[out]	: Copy_pu8DecimalTemp		=> AS A RETURN FOR USER DECIMAL PART OF TEMPERATURE
 * @param[out]	: Copy_pu8IntegralHumidity	=> AS A RETURN FOR USER INTEGRAL PART OF HUMIDITY
 * @param[out]	: Copy_pu8DecimalHumidity	=> AS A RETURN FOR USER Decimal PART OF HUMIDITY
 * @param[out]	: Copy_pu8CheckSum			=> AS A RETURN FOR USER TO CHECK ON CHECK SUM VALUE
 *
 * @note 		: PRIVATE FUNCTION
 */
static void _vBitsToBytes(uint8_t *Copy_pu8IntegralTemp, uint8_t *Copy_pu8DecimalTemp, uint8_t *Copy_pu8IntegralHumidity, uint8_t *Copy_pu8DecimalHumidity, uint8_t *Copy_pu8CheckSum)
{
	uint8_t Local_u8Counter = 0;

	for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
	{
		/* GET HUMIDITY INTEGRAL PART */
		*Copy_pu8IntegralHumidity |= (DATA_TO_PROCESS[Local_u8Counter + INT_HUMIDITY_BASE] << (7 - Local_u8Counter));

		/* GET HUMIDITY DECIMAL PART */
		*Copy_pu8DecimalHumidity |= (DATA_TO_PROCESS[Local_u8Counter + DEC_HUMIDITY_BASE] << (7 - Local_u8Counter));

		/* GET TEMPERATURE INTEGRAL PART */
		*Copy_pu8IntegralTemp |= (DATA_TO_PROCESS[Local_u8Counter + INT_TEMP_BASE] << (7 - Local_u8Counter));

		/* GET TEMPERATURE DECIMAL PART */
		*Copy_pu8DecimalTemp |= (DATA_TO_PROCESS[Local_u8Counter + DEC_TEMP_BASE] << (7 - Local_u8Counter));

		/* CHECK SUM */
		*Copy_pu8CheckSum |= (DATA_TO_PROCESS[Local_u8Counter + CHECK_SUM_BASE] << (7 - Local_u8Counter));
	}
}

/**
 * @fn 		: _vTimingsToBits(void)
 * @brief 	: THIS FUNCTION TRANSFER TIMINGS IN THE DATA ARRAY INTO BITS
 * 					ACCORDING TO SENSOR SPECIFICATION & TEST CASES
 *
 * @note	: PRIVATE FUNCTION
 */
static void _vTimingsToBits(void)
{
	uint8_t Local_u8Counter = 0;

	/* CONVERSION FROM TIMINGS TO BITS */
	for (Local_u8Counter = 0; Local_u8Counter < 42; Local_u8Counter++)
	{
		if (DATA_TO_PROCESS[Local_u8Counter] < 60)
		{
			/* "0" INDICATION */
			DATA_TO_PROCESS[Local_u8Counter] = 0;
		}
		else if ((DATA_TO_PROCESS[Local_u8Counter] > 80) && (DATA_TO_PROCESS[Local_u8Counter] < 120))
		{
			/* "1" INDICATION */
			DATA_TO_PROCESS[Local_u8Counter] = 1;
		}
		else if (DATA_TO_PROCESS[Local_u8Counter] > 130)
		{
			/* START INDICATION */
			DATA_TO_PROCESS[Local_u8Counter] = START_PULSE;
		}
	}
}

/**
 * @fn 		:  _vSendStartSignal(void)
 * @brief 	: THIS FUNCTION SENDS START SIGNAL TO THE DHT11 SENSOR TO PREPARE FOR DATA TRASMITION
 *
 * @note	: PRIVATE FUNCTION
 */
static void _vSendStartSignal(void)
{
	/* MCU Sends Start Signal Pull Data Line LOW */
	GPIO_PIN_OUTPUT_LOW(PORT_NUMBER, PIN_NUMBER);

	/* WAIT FOR 20 ms FOR DHT11 TO DETECT THE SIGNAL */
	SYSTICK_Delayms(20u);

	/* REALEASE THE SIGNAL */
	GPIO_PIN_INPUT_FLOATING(PORT_NUMBER, PIN_NUMBER);
}

/**
 * @fn 		: _vCallBackFunc(void)
 * @brief 	: EXTI CALL BACK FUNCTION THAT TRIGGERS EVERY FALLING EDGE ON EXTI LINE ON SELECTED PORT
 * 			 -THIS FUNCTION CALCULATES TIME BETWEEN EVERY TO FALLING EDGES ( PERIOD TIME ) & SAVE IT
 * 			 	IN ORDER TO PROCESS ON THIS DATA WHEN PULSES ARE FINISH
 *
 * @note	: PRIVATE FUNCTION
 */
static void _vCallBackFunc(void)
{
	if (_u8Indicator == FIRST_EDGE)
	{
		/* Start Timer */
		SYSTICK_vSetIntervalSingle(500000U, &_vDataReadToRead);

		/* First Edge is Over */
		_u8Indicator = NOT_FIRST_EDGE;
	}
	else
	{
		/* Get Elapsed Time Between Two Falling Edges */
		DATA_TO_PROCESS[_u8Counter] = SYSTICK_u32GetElapsedTimeus();

		/* Start Timer Again */
		SYSTICK_vSetIntervalSingle(500000U, &_vDataReadToRead);

		/* Increment Array Counter */
		_u8Counter++;
	}
}

/**
 * @fn 		: _vDataReadToRead(void)
 * @brief 	: THIS FUNCITON SETS A VARIABLE AS INDICATION OF DATA IS READY TO READ ( TRANSMITION IS COMPLETE )
 *
 */
static void _vDataReadToRead(void)
{
	/* DATA READY TO PROCESS */
	IS_TempReadyToRead = READY;

	/* RESET VARIABLES */
	_u8Indicator = FIRST_EDGE;
	_u8Counter = 0;
}
