/*
 ******************************************************************************
 * @file           : Config.c
 * @Author         :
 * @brief          : LINK TIME CONFIGURATION FILE
 * @Date           : Nov 5, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 .
 * All rights reserved.
 ******************************************************************************
 */

#include <stdint.h>

#include "../MCAL/SYSTICK/Inc/SYSTICK_Interface.h"


/* For Options Refer To Interface @SYSTICK_EXCEPTION_t  &  @SYSTICK_CLK_SOURCE_t */

SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG =
{
   .CLK = SYSTICK_AHB_BY8 , .CPU_FREQUENCY = 8000000UL
};


