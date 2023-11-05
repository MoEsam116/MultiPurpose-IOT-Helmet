/*
 ******************************************************************************
 * @file           : SYSTICK_Interface.h
 * @Author         : Ayman77
 * @brief          : SYSTICK USER INTERFACE FILE
 * @Date           : May 12, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman .
 * All rights reserved.
 ******************************************************************************
 */
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/* ======================================================================
 * SYSTICK Option Enums
 * ====================================================================== */

/* *************
 *  @SYSTICK_CLK_SOURCE_t
 *
 *
 **/
typedef enum
{
    SYSTICK_AHB_BY8 = 0,
    SYSTICK_AHB

} SYSTICK_CLK_SOURCE_t;

/* ---------------------------------------------------------------------------------------- */
/* ------------------------------- SYSTICK CONFIG STRUCTURE ------------------------------- */
/* ---------------------------------------------------------------------------------------- */

/* Link Time Configuration */
typedef struct
{
    SYSTICK_CLK_SOURCE_t CLK;
    uint32_t CPU_FREQUENCY;
} SYSTICK_CONFIG_t;

/**
 * @fn			                    : SYSTICK_Delayms
 * @brief		                    : Fuction That Makes Delay in Software Based on Passed Number of Milliseconds
 * @param     Copy_u32TimeInMillis  : Time Passed To Delay in Milliseconds
 * @retval		                    : VOID
 * @note	                        : -> IN SYSTICK_CLK_AHB Maximum Delay is 2000ms ( 2 Seconds )
 *                                    -> IN SYSTICK_CLK_AHB_BY8 Maximum Delay is 16000ms ( 16 Seconds )
 *                                   !< These Two Rules Occur When Using 8MHZ Clock Only , Rules May differ If You Change the Clock >!
 **/

void SYSTICK_Delayms(uint32_t Copy_u32TimeInMillis);

/**
 * @fn			                   		 : SYSTICK_Delayus
 * @brief		                    	 : Fuction That Makes Delay in Software Based on Passed Number of MicroSeconds
 * @param     Copy_u32TimeInMicroSeconds : Time Passed To Delay in MicroSeconds
 * @retval		                   		 : VOID
 **/

void SYSTICK_Delayus(uint32_t Copy_u32TimeInMicroSeconds);

/**
 * @fn   				 : SYSTICK_vSetIntervalSingle
 * @brief  				 : Function that Calls the Required User App Function after the Ticks is Passed is Finished
 *
 * @param Copy_u32Ticks  : uint32_t Variable to Hold Tick To Wait For
 * @param pvCallBackFunc : Function Required to Be Called After Ticks Provided Finish
 */
void SYSTICK_vSetIntervalSingle( uint32_t Copy_u32Ticks , void(*pvCallBackFunc)(void) ) ;

/**
 * @fn   				 : SYSTICK_vSetPeriodicInterval
 * @brief  				 : Function that Calls the Required User App Function Every Ticks Passed Finish
 *
 * @param Copy_u32Ticks  : uint32_t Variable to Hold Ticks To Wait For
 * @param pvCallBackFunc : Function Required to Be Called After Ticks Provided Finish
 */
void SYSTICK_vSetPeriodicInterval( uint32_t Copy_u32Ticks , void(*pvCallBackFunc)(void) ) ;

/**
 * @fn   				 : SYSTICK_vStopInterval
 * @brief  				 : Function that Stop the Running Periodic Interval
 *
 */
void SYSTICK_vStopInterval( void );

/**
 * @fn 		: SYSTICK_u32GetElapsedTime
 * @brief   : Function that gets the total Elapsed Time in the form of MilliSeconds which is the Load Value Minus the Current Value
 *
 * @return  : Total Elapsed Time in the Form of MilliSeconds
 */
uint32_t SYSTICK_u32GetElapsedTimems(void);

/**
 * @fn 		: SYSTICK_u32GetElapsedTimeus
 * @brief   : Function that gets the total Elapsed Time in the form of MicroSeconds which is the Load Value Minus the Current Value
 *
 * @return  : Total Elapsed Time in the Form of MicroSeconds
 */
uint32_t SYSTICK_u32GetElapsedTimeus (void);

/**
 * @fn 		: SYSTICK_u32GetRemainingTimems
 * @brief   : Function that gets The Remaining Time in the Form of MilliSeconds whick is The Current Value
 *
 * @return  : Total Remaining Time in the Form of MilliSeconds
 */
uint32_t SYSTICK_u32GetRemainingTimems (void) ;

/**
 * @fn 		: SYSTICK_u32GetRemainingTimeus
 * @brief   : Function that gets The Remaining Time in the Form of MicroSeconds whick is The Current Value
 *
 * @return  : Total Remaining Time in the Form of MicroSeconds
 */
uint32_t SYSTICK_u32GetRemainingTimeus (void) ;

#endif /* SYSTICK_INTERFACE_H_ */
