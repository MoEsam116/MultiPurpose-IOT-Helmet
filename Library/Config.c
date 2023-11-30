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
#include "UART_Interface.h"



/*	UART Configrations to Work with ESP8266	*/
const UART_Init_t UART_Configuration = {
    .BaudRate = UART_115200,
    .Parity = UART_No_Parity,
    .StopBits = UART_One_Stop_Bit,
    .WordLength = UART_8_WORD_LENGTH,
    .RXNEIE = UART_RXNEIE_EN
};


