/*
 ******************************************************************************
 * @file           : DHT11_Prv.h
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
#ifndef DHT11_PRV_H_
#define DHT11_PRV_H_

/*==============================================================================================================================================
 * PRIVATE DEFINES
 *==============================================================================================================================================*/

#define START_PULSE 0xAA

#define FIRST_EDGE		0
#define NOT_FIRST_EDGE	1

#define INT_HUMIDITY_BASE	2
#define DEC_HUMIDITY_BASE	10

#define INT_TEMP_BASE		18
#define DEC_TEMP_BASE		26

#define CHECK_SUM_BASE		34

#define NOT_READY	0
#define READY		1

#define DHT11_ARRAY_SIZE 	42


/*==============================================================================================================================================
 * PRIVATE FUNCITONS PROTOTYPES
 *==============================================================================================================================================*/

/**
 * @fn 		: _vCallBackFunc(void)
 * @brief 	: EXTI CALL BACK FUNCTION THAT TRIGGERS EVERY FALLING EDGE ON EXTI LINE ON SELECTED PORT
 * 			 -THIS FUNCTION CALCULATES TIME BETWEEN EVERY TO FALLING EDGES ( PERIOD TIME ) & SAVE IT
 * 			 	IN ORDER TO PROCESS ON THIS DATA WHEN PULSES ARE FINISH
 *
 * @note	: PRIVATE FUNCTION
 */
static void _vCallBackFunc( void );

/**
 * @fn 		:  _vSendStartSignal(void)
 * @brief 	: THIS FUNCTION SENDS START SIGNAL TO THE DHT11 SENSOR TO PREPARE FOR DATA TRASMITION
 *
 * @note	: PRIVATE FUNCTION
 */
static void _vSendStartSignal( void ) ;


/**
 * @fn 		: _vDataReadToRead(void)
 * @brief 	: THIS FUNCITON SETS A VARIABLE AS INDICATION OF DATA IS READY TO READ ( TRANSMITION IS COMPLETE )
 *
 */
static void _vDataReadToRead(void) ;


/**
 * @fn 		: _vTimingsToBits(void)
 * @brief 	: THIS FUNCTION TRANSFER TIMINGS IN THE DATA ARRAY INTO BITS
 * 					ACCORDING TO SENSOR SPECIFICATION & TEST CASES
 *
 * @note	: PRIVATE FUNCTION
 */
static void _vTimingsToBits( void ) ;

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
static void _vBitsToBytes( uint8_t * Copy_pu8IntegralTemp , uint8_t * Copy_pu8DecimalTemp , uint8_t * Copy_pu8IntegralHumidity , uint8_t * Copy_pu8DecimalHumidity , uint8_t * Copy_pu8CheckSum ) ;

#endif /* DHT11_PRV_H_ */
