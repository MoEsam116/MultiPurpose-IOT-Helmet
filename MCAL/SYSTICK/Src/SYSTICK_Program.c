/*
 ******************************************************************************
 * @file           : SYSTICK_Program.c
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : SYSTICK MAIN PROGRAM FILE
 * @Date           : May 12, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */

/*==============================================================================================================================================
 * INCLUDES SECTION START
 *==============================================================================================================================================*/
#include <stdint.h>

#include "../../../Library/ErrType.h"
#include "../../../Library/STM32F103xx.h"

#include "../Inc/SYSTICK_Interface.h"
#include "../Inc/SYSTICK_Private.h"

/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/



/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION START
 *==============================================================================================================================================*/

extern SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG ;

void (*SYSTICK_CALL_BACK_PTR_TO_FUNC)(void) = NULL ;

volatile uint32_t STK_PeriodicValue ;

STK_MOD_t SYSTICK_MODE = STK_MOD_NONE  ;

float _f32TickTime ;

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION END
 *==============================================================================================================================================*/


/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/

/**
 * @fn			                    : SYSTICK_Delayms
 * @brief		                    : Fuction That Makes Delay in Software Based on Passed Number of Milliseconds
 * @param     Copy_u32TimeInMillis  : Time Passed To Delay in Milliseconds
 * @retval		                    : VOID
 * @note	                        : -> IN SYSTICK_CLK_AHB Maximum Delay is 2000ms ( 2 Seconds )
 *                                    -> IN SYSTICK_CLK_AHB_BY8 Maximum Delay is 16000ms ( 16 Seconds )
 *                                   !< These Two Rules Occur When Using 8MHZ Clock Only , Rules May differ If You Change the Clock >!
 **/

void SYSTICK_Delayms(uint32_t Copy_u32TimeInMillis)
{
	/* Variable To Carry RELOAD Value */
	uint32_t RELOAD_Value = 0 ;

	/* Check on TIMER_CLK  */
	if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB )
	{
		/* Set Reload Value */
		RELOAD_Value = ( Copy_u32TimeInMillis ) / ( _10POW3 * AHB_TICK_TIME ) ;

		/* Set Clock Source */
		( SYSTICK->SYST_CSR ) |= ( 1 << CSR_CLKSOURCE ) ;
	}
	else if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB_BY8 )
	{
		/* Set Reload Value */
		RELOAD_Value = ( Copy_u32TimeInMillis ) / ( _10POW3 * AHB_BY8_TICK_TIME ) ;

		/* Set Clock Source */
		( SYSTICK->SYST_CSR ) &= ( ~ ( 1 << CSR_CLKSOURCE ) ) ;
	}

	/* Setting Reload Value */
	( SYSTICK->SYST_RVR ) = RELOAD_Value ;

	/* Clear Current */
	( SYSTICK->SYST_CVR ) = 0 ;

	/* Disable Exception For Busy Waiting */
	( SYSTICK->SYST_CSR ) &= ( ~ ( 1 << CSR_TICKINT ) ) ;

	/* Enable Timer */
	( SYSTICK->SYST_CSR ) |= ( 1 << CSR_ENABLE ) ;

	/* Check on Flag */
	while( !( ( (SYSTICK->SYST_CSR)>>CSR_COUNTFLAG )&0x01) ) ;

	/* Disable Timer */
	( SYSTICK->SYST_CSR ) &= ~( 1 << CSR_ENABLE ) ;

}


/**
 * @fn			                   		 : SYSTICK_Delayus
 * @brief		                    	 : Fuction That Makes Delay in Software Based on Passed Number of MicroSeconds
 * @param     Copy_u32TimeInMicroSeconds : Time Passed To Delay in MicroSeconds
 * @retval		                   		 : VOID
 **/

void SYSTICK_Delayus(uint32_t Copy_u32TimeInMicroSeconds)
{
	/* Variable To Carry RELOAD Value */
	uint32_t RELOAD_Value = 0 ;

	/* Check on TIMER_CLK  */
	if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB )
	{
		/* Set Reload Value */
		RELOAD_Value = ( Copy_u32TimeInMicroSeconds )  / ( _10POW6 * AHB_TICK_TIME )  ;

		/* Set Clock Source */
		( SYSTICK->SYST_CSR ) |= ( 1 << CSR_CLKSOURCE ) ;
	}
	else if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB_BY8 )
	{
		/* Set Reload Value */
		RELOAD_Value = ( Copy_u32TimeInMicroSeconds )  / ( _10POW6 * AHB_BY8_TICK_TIME ) ;

		/* Set Clock Source */
		( SYSTICK->SYST_CSR ) &= ( ~ ( 1 << CSR_CLKSOURCE ) ) ;
	}

	/* Setting Reload Value */
	( SYSTICK->SYST_RVR ) = RELOAD_Value ;

	/* Clear Current */
	( SYSTICK->SYST_CVR ) = 0 ;

	/* Disable Exception For Busy Waiting */
	( SYSTICK->SYST_CSR ) &= ( ~ ( 1 << CSR_TICKINT ) ) ;

	/* Enable Timer */
	( SYSTICK->SYST_CSR ) |= ( 1 << CSR_ENABLE ) ;

	/* Check on Flag */
	while( !( ( (SYSTICK->SYST_CSR)>>CSR_COUNTFLAG )&0x01) ) ;

	/* Disable Timer */
	( SYSTICK->SYST_CSR ) &= ~( 1 << CSR_ENABLE ) ;
}

/**
 * @fn   				 : SYSTICK_vSetIntervalSingle
 * @brief  				 : Function that Calls the Required User App Function after the Ticks is Passed is Finished
 *
 * @param Copy_u32Ticks  : uint32_t Variable to Hold Tick To Wait For
 * @param pvCallBackFunc : Function Required to Be Called After Ticks Provided Finish
 */
void SYSTICK_vSetIntervalSingle( uint32_t Copy_u32Ticks , void(*pvCallBackFunc)(void) )
{
	static uint8_t Local_u8Indicator = 0 ;

	/* To Reset Timer When Function Called More Than once */
	SYSTICK->SYST_CSR &= (~(1<<CSR_ENABLE));
	SYSTICK->SYST_CVR = 0u ;

	/* To Ensure Setting Clock Source One Time Only */
	if( Local_u8Indicator == 0 )
	{
		/* Set Clock Source */
		if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB )
		{
			SYSTICK-> SYST_CSR |= ( 1 << CSR_CLKSOURCE ) ;
			_f32TickTime = AHB_TICK_TIME ;
		}
		else if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB_BY8 )
		{
			SYSTICK->SYST_CSR &= ( ~ ( 1 << CSR_CLKSOURCE ) ) ;
			_f32TickTime = AHB_BY8_TICK_TIME ;
		}

		Local_u8Indicator = 1 ;
	}

	/* Load Value */
	SYSTICK->SYST_RVR = Copy_u32Ticks ;

	/* Start Timer */
	SYSTICK->SYST_CSR |= (1<<CSR_ENABLE) ;

	/* Assign Call BAck Function */
	SYSTICK_CALL_BACK_PTR_TO_FUNC = pvCallBackFunc ;

	/* Assign MOde */
	SYSTICK_MODE = STK_MOD_SINGLE_INTERVAL ;

	/* Enable Systick Exception */
	SYSTICK->SYST_CSR |= (1<<CSR_TICKINT) ;

}

/**
 * @fn   				 : SYSTICK_vSetPeriodicInterval
 * @brief  				 : Function that Calls the Required User App Function Every Ticks Passed Finish
 *
 * @param Copy_u32Ticks  : uint32_t Variable to Hold Ticks To Wait For
 * @param pvCallBackFunc : Function Required to Be Called After Ticks Provided Finish
 */
void SYSTICK_vSetPeriodicInterval( uint32_t Copy_u32Ticks , void(*pvCallBackFunc)(void) )
{
	static uint8_t Local_u8Indicator = 0 ;

	/* To Reset Timer When Function Called More Than once */
	SYSTICK->SYST_CSR &= (~(1<<CSR_ENABLE));
	SYSTICK->SYST_CVR = 0u ;

	/* To Ensure Setting Clock Source One Time Only */
	if( Local_u8Indicator == 0 )
	{
		/* Set Clock Source */
		if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB )
		{
			SYSTICK-> SYST_CSR |= ( 1 << CSR_CLKSOURCE ) ;
			_f32TickTime = AHB_TICK_TIME ;

		}
		else if( SYSTICK_TIMER_CONFIG.CLK == SYSTICK_AHB_BY8 )
		{
			SYSTICK->SYST_CSR &= ( ~ ( 1 << CSR_CLKSOURCE ) ) ;
			_f32TickTime = AHB_BY8_TICK_TIME ;
		}

		Local_u8Indicator = 1 ;
	}


	/* Load Value */
	SYSTICK->SYST_RVR = Copy_u32Ticks ;

	/* Clear the Current */
	SYSTICK->SYST_CVR = 0 ;

	/* Assign Call BAck Function */
	SYSTICK_CALL_BACK_PTR_TO_FUNC = pvCallBackFunc ;

	/* Assign the Periodic Value */
	STK_PeriodicValue = Copy_u32Ticks ;

	/* Assign MOde */
	SYSTICK_MODE = STK_MOD_PERIODIC_INTERVAL ;

	/* Enable Systick Exception */
	SYSTICK->SYST_CSR |= (1<<CSR_TICKINT) ;

	/* Start Timer */
	SYSTICK->SYST_CSR |= (1<<CSR_ENABLE) ;
}

/**
 * @fn   				 : SYSTICK_vStopInterval
 * @brief  				 : Function that Stop the Running Periodic Interval
 *
 */
void SYSTICK_vStopInterval( void )
{
	/* Disable Systick Exception */
	SYSTICK->SYST_CSR &= (~(1<<CSR_TICKINT)) ;

	/* Disable Timer */
	SYSTICK->SYST_CSR &= (~(1<<CSR_ENABLE)) ;

	/* Clear Current */
	( SYSTICK->SYST_CVR ) = 0 ;

}

/**
 * @fn 		: SYSTICK_u32GetElapsedTime
 * @brief   : Function that gets the total Elapsed Time in the form of MilliSeconds which is the Load Value Minus the Current Value
 *
 * @return  : Total Elapsed Time in the Form of MilliSeconds
 */
uint32_t SYSTICK_u32GetElapsedTimems(void)
{
	uint32_t Local_u32ElapsedTime ;

	Local_u32ElapsedTime = ( ( ( SYSTICK->SYST_RVR ) - ( SYSTICK->SYST_CVR ) ) * _f32TickTime  * _10POW3 ) ;

	return Local_u32ElapsedTime ;
}

/**
 * @fn 		: SYSTICK_u32GetElapsedTimeus
 * @brief   : Function that gets the total Elapsed Time in the form of MicroSeconds which is the Load Value Minus the Current Value
 *
 * @return  : Total Elapsed Time in the Form of MicroSeconds
 */
uint32_t SYSTICK_u32GetElapsedTimeus (void)
{
	uint32_t Local_u32ElapsedTime  ;

	Local_u32ElapsedTime = (uint32_t)( ( (uint32_t)( SYSTICK->SYST_RVR ) - (uint32_t)( SYSTICK->SYST_CVR ) ) * ( _f32TickTime  * (float)_10POW6 ) ) ;

	return Local_u32ElapsedTime ;
}

/**
 * @fn 		: SYSTICK_u32GetRemainingTimems
 * @brief   : Function that gets The Remaining Time in the Form of MilliSeconds whick is The Current Value
 *
 * @return  : Total Remaining Time in the Form of MilliSeconds
 */
uint32_t SYSTICK_u32GetRemainingTimems (void)
{
	uint32_t Local_u32RemainingTime = 0 ;

	Local_u32RemainingTime = ( ( SYSTICK->SYST_CVR ) * _f32TickTime * _10POW3 ) ;

	return Local_u32RemainingTime ;
}

/**
 * @fn 		: SYSTICK_u32GetRemainingTimeus
 * @brief   : Function that gets The Remaining Time in the Form of MicroSeconds whick is The Current Value
 *
 * @return  : Total Remaining Time in the Form of MicroSeconds
 */
uint32_t SYSTICK_u32GetRemainingTimeus (void)
{
	uint32_t Local_u32RemainingTime = 0 ;

	Local_u32RemainingTime = ( ( SYSTICK->SYST_CVR ) * _f32TickTime * _10POW6 ) ;

	return Local_u32RemainingTime ;
}

/*==============================================================================================================================================
 * INTERRUPT SERVICE ROUTINE
 *==============================================================================================================================================*/
void SysTick_Handler(void)
{
	/* Single Interval Mode */
	if( SYSTICK_MODE == STK_MOD_SINGLE_INTERVAL )
	{
		/* Disable Timer */
		SYSTICK->SYST_CSR &= (~(1<<CSR_ENABLE)) ;

		/* Disable Interrupt */
		SYSTICK->SYST_CSR &= (~(1<<CSR_TICKINT)) ;

		/* Call Back Funtion Invoke */
		SYSTICK_CALL_BACK_PTR_TO_FUNC(  ) ;

		/* Clear */
		SYSTICK_MODE = STK_MOD_NONE ;
		SYSTICK_CALL_BACK_PTR_TO_FUNC = NULL ;

		/* Clear Current */
		( SYSTICK->SYST_CVR ) = 0 ;
	}
	/* Periodic Interval Mode */
	else if( SYSTICK_MODE == STK_MOD_PERIODIC_INTERVAL )
	{
		/* Disable Timer */
		SYSTICK->SYST_CSR &= (~(1<<CSR_ENABLE)) ;

		/* Invoke the CAll Back Function */
		SYSTICK_CALL_BACK_PTR_TO_FUNC(  );

		/* Clear Current */
		( SYSTICK->SYST_CVR ) = 0 ;

		/* Reload the Load Register */
		SYSTICK->SYST_CVR = STK_PeriodicValue ;

		/* Enable Timer */
		SYSTICK->SYST_CSR |= (1<<CSR_ENABLE) ;

	}
}
