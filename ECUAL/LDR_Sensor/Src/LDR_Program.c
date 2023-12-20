/*
 ******************************************************************************
 * @file           : LDR_Program.c
 * @Author         : Ibrahim Mohamed 
 * @brief          : Main program body
 * @Date           : Dec 7, 2023
 ******************************************************************************
 */

/*==============================================================================================================================================
 * INCLUDES SECTION
 *==============================================================================================================================================*/

#include <stdint.h>

#include "../../../Library/ErrType.h"
#include "../../../Library/STM32F103xx.h"

#include "../../../MCAL/EXTI/Inc/ADC_Interface.h"

#include "../Inc/LDR_Interface.h"
#include "../Inc/LDR_Private.h"


extern ADC_Configs_t ADC_Configs;

/*==============================================================================================================================================
 * IMPLEMENTATION SECTION
 *==============================================================================================================================================*/

/**
 * @fn 		: LDR_Init
 * @brief 	: THIS FUNCTION INITIALIZES LDR SENSOR 
 * @param 	: Void
 * @return	: ERROR STATUS
 */
ERRORS_t LDR_Init(void)
{
	ERRORS_t Local_Error_Status=OK;

	ADC_u8Init(&ADC_Configs);

	return Local_Error_Status;
}

/**
 * @fn 			: LDR_Read
 * @brief 		: THIS FUNCTION INITIALIZES LDR SENSOR 
 * @param[out]  : Copy_pu16LDR_Reading  =>  RETURN TO THE Reading of LDR Sensor
 * @return		: ERROR STATUS
 */
ERRORS_t LDR_Read(uint16_t* Copy_pu16LDR_Reading)
{
	ERRORS_t Local_Error_Status=OK;

	if (Copy_pu16LDR_Reading != NULL)
	{
		ADC_u8StartSingleConv(&ADC_Configs, Copy_pu16LDR_Reading);
	}
	else
	{
		Local_Error_Status=NOK;
	}

	return Local_Error_Status;
}

/**
 * @fn 			: LDR_Checking
 * @brief 		: THIS FUNCTION INITIALIZES LDR SENSOR 
 * @param 		: Copy_u16LDR_Reading  =>  THE Reading of LDR Sensor
 * @param[out]  : Copy_Light_Status  =>  RETURN TO THE Status of Light
 * @return		: ERROR STATUS
 */
ERRORS_t LDR_Checking(uint16_t Copy_u16LDR_Reading ,uint8_t * Copy_Light_Status )
{
	ERRORS_t Local_Error_Status=OK;

	if (Copy_Light_Status != NULL)
	{
		if (Copy_u16LDR_Reading<2048)
		{
			* Copy_Light_Status = Light_ON;
		}
		else 
		{
			* Copy_Light_Status = Light_OFF;
		}
	}
	else
	{
		Local_Error_Status=NOK;
	}

	return Local_Error_Status;
}



