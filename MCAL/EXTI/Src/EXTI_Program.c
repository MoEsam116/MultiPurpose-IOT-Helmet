/*
 ******************************************************************************
 * @file           : EXTI_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Nov 11, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */


/*==============================================================================================================================================
 * INCLUDES SECTION
 *==============================================================================================================================================*/

#include <stdint.h>

#include "../../../LIB/ErrType.h"
#include "../../../LIB/STM32F103xx.h"

#include "../Inc/EXTI_Interface.h"
#include "../Inc/EXTI_Private.h"

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION
 *==============================================================================================================================================*/
void (*EXTI_PTR_TO_FUNC[EXTI_MAX_NUMBER])(void) = { NULL } ;


/*==============================================================================================================================================
 * IMPLEMENTATION SECTION
 *==============================================================================================================================================*/

/**
 * @fn	 	: MEXTI_eEnableEXTILine(EXTI_LINE_t, EXTI_TRIGGER_t)
 * @brief 	: THIS FUNCTION ENABLES EXTI ON A SPECIFIC LINE WITH A SPECIFIC TRIGGER SELECTED
 *
 * @param   : EXTILine		=> EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 								CHECK FOR OPTIONS @EXTI_LINE_t
 * @param 	: EXTITrigger	=> EXTI TRIGGER SELECTION TO ALLOW EXTI CIRCIUT TO DETECT IT
 * 								CHECK FOR OPTIONS &EXTI_TRIGGER_t
 * @return	: ERROR STATUS
 */
ERRORS_t MEXTI_eEnableEXTILine( EXTI_LINE_t EXTILine , EXTI_TRIGGER_t EXTITrigger )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV ) )
	{
		return NOK ;
	}
	else if( ( EXTITrigger < EXTI_TRIGGER_FALLING ) || ( EXTITrigger > EXTI_TRIGGER_ON_CHANGE ) )
	{
		return NOK ;
	}
	else
	{
		/* RIGHT PARAMETERS */

		/* TRIGGER SELECTION */
		switch( EXTITrigger )
		{
		case EXTI_TRIGGER_FALLING   :

			EXTI->EXTI_FTSR |= ( 1 << EXTILine ) ;
			EXTI->EXTI_RTSR &= ( ~ ( 1 << EXTILine ) ) ;
			break ;

		case EXTI_TRIGGER_RISING    :

			EXTI->EXTI_FTSR &= ( ~ ( 1 << EXTILine ) ) ;
			EXTI->EXTI_RTSR |= ( 1 << EXTILine ) ;
			break ;

		case EXTI_TRIGGER_ON_CHANGE :

			EXTI->EXTI_FTSR |= ( 1 << EXTILine ) ;
			EXTI->EXTI_RTSR |= ( 1 << EXTILine ) ;
			break ;
		}

		/* UN-MASK INTERRUPT ON EXTI LINE */
		EXTI->EXTI_IMR |= ( 1 << EXTILine ) ;

	}

	return Local_ErrorStatus ;
}

/**
 * @fn 			: MEXTI_SetCallBack(EXTI_LINE_t, void(*)(void))
 * @brief 		: THIS FUNCTION SETS CALL BACK FUNCTION TO INVOKE WHEN INTERRUPT REQUEST IS OCCURED
 *
 * @param[in] 	: EXTILine 				=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 										CHECK FOR OPTIONS @EXTI_LINE_t
 * @param[in] 	: Copy_pvCallBackFunc	=>  CALL BACK FUNCTION TO INVOKE WHEN INTERRUT IS REQUESTED
 * @return		: ERROR STATUS
 */
ERRORS_t MEXTI_SetCallBack( EXTI_LINE_t EXTILine , void(*Copy_pvCallBackFunc)(void) )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV  ) )
	{
		return NOK ;
	}
	else if( Copy_pvCallBackFunc == NULL )
	{
		return NULL_POINTER ;
	}
	else
	{
		EXTI_PTR_TO_FUNC[ EXTILine ] = Copy_pvCallBackFunc ;
	}

	return Local_ErrorStatus ;
}

/**
 * @fn 			: MEXTI_eDisableEXTILine(EXTI_LINE_t)
 * @brief 		: THIS FUNCTION DISABLES EXTI LINE GENERATION OF INTERRUPT REQUEST
 *
 * @param[in] 	: EXTILine		=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 									CHECK FOR OPTIONS @EXTI_LINE_t
 * @return		: ERROR STATUS
 */
ERRORS_t MEXTI_eDisableEXTILine( EXTI_LINE_t EXTILine )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV  ) )
	{
		return NOK ;
	}
	else
	{
		EXTI->EXTI_IMR &= ( ~ ( 1 << EXTILine ) ) ;
	}

	return Local_ErrorStatus ;
}

/**
 * @fn	 		: MEXTI_eChangeTrigger(EXTI_LINE_t, EXTI_TRIGGER_t)
 * @brief 		: THIS FUNCTION CHANGES TRIGGER SELECTION TO WHICH EXTI CIRCUIT DETECT
 *
 * @param[in]	: EXTILine			=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 										CHECK FOR OPTIONS @EXTI_LINE_t
 * @param[in] 	: TriggerSelection	=> EXTI TRIGGER SELECTION TO ALLOW EXTI CIRCIUT TO DETECT IT
 * 										CHECK FOR OPTIONS &EXTI_TRIGGER_t
 * @return		: ERROR STATUS
 */
ERRORS_t MEXTI_eChangeTrigger( EXTI_LINE_t EXTILine , EXTI_TRIGGER_t TriggerSelection )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV  ) )
	{
		return NOK ;
	}
	else
	{
		/* TRIGGER SELECTION */
		switch( TriggerSelection )
		{
		case EXTI_TRIGGER_FALLING   :

			EXTI->EXTI_FTSR |= ( 1 << EXTILine ) ;
			EXTI->EXTI_RTSR &= ( ~ ( 1 << EXTILine ) ) ;
			break ;

		case EXTI_TRIGGER_RISING    :

			EXTI->EXTI_FTSR &= ( ~ ( 1 << EXTILine ) ) ;
			EXTI->EXTI_RTSR |= ( 1 << EXTILine ) ;
			break ;

		case EXTI_TRIGGER_ON_CHANGE :

			EXTI->EXTI_FTSR |= ( 1 << EXTILine ) ;
			EXTI->EXTI_RTSR |= ( 1 << EXTILine ) ;
			break ;
		}

	}

	return Local_ErrorStatus ;
}

/*==============================================================================================================================================
 * PRIVATE FUNCTIONS SECTION
 *==============================================================================================================================================*/

/**
 * @fn 		: _eClearPendingFlag(EXTI_LINE_t)
 * @brief 	: THIS FUNCTION CLEARS THE CORRESPONDING PENDING FLAG
 *
 * @param 	: EXTILine		=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 								CHECK FOR OPTIONS @EXTI_LINE_t
 * @return	: ERROR STATUS
 * @note 	: PRIVATE FUNCTION
 */
static ERRORS_t _eClearPendingFlag( EXTI_LINE_t EXTILine )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV  ) )
	{
		return NOK ;
	}
	else
	{
		EXTI->EXTI_PR |= ( 1 << EXTILine ) ;
	}

	return Local_ErrorStatus ;
}

/**
 * @fn 			: _eISPendingFlagSet(EXTI_LINE_t, EXTI_PFLAG_t*)
 * @brief 		: THIS FUNCTION CHECKS IF PENDING BIT IS SET OR NOT
 *
 * @param[in] 	: EXTILINE					=> EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 											CHECK FOR OPTIONS @EXTI_LINE_t
 * @param[out] 	: Copy_pPendingFlagStatus	=> RETURN TO THE USER THE STATE OF THE PENDING FLAG
 * @return		: ERROR STATUS
 * @note		: PRIVATE FUNCTION
 */
static ERRORS_t _eISPendingFlagSet( EXTI_LINE_t EXTILine , EXTI_PFLAG_t * Copy_pPendingFlagStatus )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV  ) )
	{
		return NOK ;
	}
	else
	{
		/* CHECK ON PENDING FLAG */
		if( ( ( EXTI->EXTI_PR >> EXTILine ) & 1U ) )
		{
			*Copy_pPendingFlagStatus = EXTI_PFLAG_SET ;
		}
		else
		{
			*Copy_pPendingFlagStatus = EXTI_PFLAG_RESET ;
		}
	}
	return Local_ErrorStatus ;
}



/*==============================================================================================================================================
 * INTERRUPT HANDLE SECTION
 *==============================================================================================================================================*/

ERRORS_t MEXTI_eIRQHandle( EXTI_LINE_t EXTILine )
{
	ERRORS_t Local_ErrorStatus = OK ;

	if( ( EXTILine < EXTI_LINE_0 ) || ( EXTILine > EXTI_LINE_19_ETHERNET_WAKEUP_EV  ) )
	{
		return NOK ;
	}
	else
	{
		/* Clear Pending Flag */
		Local_ErrorStatus = _eClearPendingFlag(EXTILine) ;

		/* Invoke Call Back Function */
		if( EXTI_PTR_TO_FUNC[ EXTILine ] != NULL )
		{
			EXTI_PTR_TO_FUNC[ EXTILine ]( ) ;
		}
		else
		{
			return NULL_POINTER ;
		}

	}

	return Local_ErrorStatus ;
}


/*==============================================================================================================================================
 * ISR SECTIONS
 *==============================================================================================================================================*/

/* EXTI0 */
void EXTI0_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_0 ) ;
}

/* EXTI1 */
void EXTI1_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_1 ) ;
}

/* EXTI2 */
void EXTI2_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_2 ) ;
}

/* EXTI3 */
void EXTI3_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_3 ) ;
}

/* EXTI4 */
void EXTI4_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_4 ) ;
}

/* EXTI 5-9 */
void EXTI9_5_IRQHandler(void)
{
	EXTI_PFLAG_t Local_PendingStatus = EXTI_PFLAG_RESET ;

	/* EXTI 5 */
	_eISPendingFlagSet( EXTI_LINE_5 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_5 ) ;
	}

	/* EXTI 6 */
	_eISPendingFlagSet( EXTI_LINE_6 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_6 ) ;
	}

	/* EXTI 7 */
	_eISPendingFlagSet( EXTI_LINE_7 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_7 ) ;
	}

	/* EXTI 8 */
	_eISPendingFlagSet( EXTI_LINE_8 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_8 ) ;
	}

	/* EXTI 9 */
	_eISPendingFlagSet( EXTI_LINE_9 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_9 ) ;
	}
}

/* EXTI 10-15 */
void EXTI15_10_IRQHandler(void)
{
	EXTI_PFLAG_t Local_PendingStatus = EXTI_PFLAG_RESET ;

	/* EXTI 10 */
	_eISPendingFlagSet( EXTI_LINE_10 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_10 ) ;
	}

	/* EXTI 11 */
	_eISPendingFlagSet( EXTI_LINE_11 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_11 ) ;
	}

	/* EXTI 12 */
	_eISPendingFlagSet( EXTI_LINE_12 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_12 ) ;
	}

	/* EXTI 13 */
	_eISPendingFlagSet( EXTI_LINE_13 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_13 ) ;
	}

	/* EXTI 14 */
	_eISPendingFlagSet( EXTI_LINE_14 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_14 ) ;
	}

	/* EXTI 15 */
	_eISPendingFlagSet( EXTI_LINE_15 ,&Local_PendingStatus ) ;

	if( Local_PendingStatus == EXTI_PFLAG_SET )
	{
		MEXTI_eIRQHandle( EXTI_LINE_15 ) ;
	}
}

/* EXTI 16 */
void PVD_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_16_PVD_OUTPUT ) ;
}

/* EXTI 17 */
void RTCAlarm_IRQHandler(void)
{
	MEXTI_eIRQHandle( EXTI_LINE_17_RTC_ALARM_EV ) ;
}

