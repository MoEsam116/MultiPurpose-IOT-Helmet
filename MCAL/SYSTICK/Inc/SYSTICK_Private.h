/*
 ******************************************************************************
 * @file           : SYSTICK_Private.h
 * @Author         : Ayman77
 * @brief          : SYSTICK PROVIDER PRIVATE FILE
 * @Date           : May 12, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 ******************************************************************************
 */
#ifndef SYSTICK_INC_SYSTICK_PRIVATE_H_
#define SYSTICK_INC_SYSTICK_PRIVATE_H_

#include "SYSTICK_Interface.h"

/*==============================================================================================================================================
 * EXTERNAL VARIABLES
 *==============================================================================================================================================*/
extern SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG ;

/*==============================================================================================================================================
 * MACROS
 *==============================================================================================================================================*/
#define AHB_TICK_TIME     	1.0/ SYSTICK_TIMER_CONFIG.CPU_FREQUENCY
#define AHB_BY8_TICK_TIME 	8.0/ SYSTICK_TIMER_CONFIG.CPU_FREQUENCY

#define _10POW3 1000UL
#define _10POW6 1000000UL

typedef enum
{
	STK_MOD_NONE , STK_MOD_SINGLE_INTERVAL , STK_MOD_PERIODIC_INTERVAL
}STK_MOD_t;

#endif /* SYSTICK_INC_SYSTICK_PRIVATE_H_ */
