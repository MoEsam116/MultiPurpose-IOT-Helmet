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

#include "ErrType.h"

#include "../MCAL/UART/Inc/UART_Interface.h"
#include "../MCAL/SYSTICK/Inc/SYSTICK_Interface.h"


/* For Options Refer To Interface @SYSTICK_EXCEPTION_t  &  @SYSTICK_CLK_SOURCE_t */

SYSTICK_CONFIG_t SYSTICK_TIMER_CONFIG =
{
   .CLK = SYSTICK_AHB_BY8 , .CPU_FREQUENCY = 8000000UL
};

const UART_Init_t UART_Configuration = {
    .BaudRate = UART_115200,
    .Parity = UART_No_Parity,
    .StopBits = UART_One_Stop_Bit,
    .WordLength = UART_8_WORD_LENGTH,
    .RXNEIE = UART_RXNEIE_EN
};