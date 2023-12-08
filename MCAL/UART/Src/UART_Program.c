/*******************************************************************/
/*  Author : Mohammed Gaafar                                       */
/*  Date : 15 / 8 / 2023                                            */
/*  Version : V1.0                                                 */
/*******************************************************************/

/*==============================================================================================================================================
 * INCLUDES SECTION START
 *==============================================================================================================================================*/

#include <stdint.h>
#include "../Library/STM32F103xx.h"
#include "../Library/ErrType.h"
#include "../Library/BIT_MATH.h"
#include "../Inc/UART_Private.h"
#include "../Inc/UART_Interface.h"
#include "../../Timer/Inc/Timer_Interface.h"

/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/


/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION START
 *==============================================================================================================================================*/
extern UART_Init_t UART_Configuration ;
uint8_t UART_State = UART_IDLE;
uint8_t UART_ISRSOURCE = UART_ISR_SOURCE_SEND_CHAR;
//Callback Function
void (*UART_PVCallBack)(void) = (void*)0;
uint8_t *UART_pu8Data = (void*)0;
uint8_t UART_BufferSize, UART_BufferCounter = 0;

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION END
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/


/**
 * @brief Initialize the UART communication module.
 *
 * @param No parameters.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t UART_Init(void){
    ERRORS_t Local_Error = NOK;
    //Clear Status Register
    USART1->SR = 0;
    //Configure Word Length
    if(UART_Configuration.WordLength == UART_8_WORD_LENGTH){
        CLR_BIT(USART1->CR1,12);
    }
    else if(UART_Configuration.WordLength == UART_9_WORD_LENGTH){
        SET_BIT(USART1->CR1,12);
    }
    else{
        Local_Error = OUT_OF_RANGE;
        return Local_Error;
    }
    
    //Setting Parity
    if(UART_Configuration.Parity == UART_No_Parity){
        CLR_BIT(USART1->CR1,10);
    }
    else if(UART_Configuration.Parity == UART_Even_Parity){
        SET_BIT(USART1->CR1,10);
        CLR_BIT(USART1->CR1,9);
    }
    else if(UART_Configuration.Parity == UART_Odd_Parity){
        SET_BIT(USART1->CR1,10);
        SET_BIT(USART1->CR1,9);
    }
    else{
        Local_Error = OUT_OF_RANGE;
        return Local_Error;
    }
    //Choosing Interrupts to Enable
    //Disable All Interrupts
    CLR_BIT(USART1->CR1,5);
    CLR_BIT(USART1->CR1,6);
    CLR_BIT(USART1->CR1,7);
    //Enable Interrupts
    if(UART_Configuration.TXEIE == UART_TXEIE_EN){
        SET_BIT(USART1->CR1,7);
    }
    if(UART_Configuration.RXNEIE == UART_RXNEIE_EN){
        SET_BIT(USART1->CR1,5);
    }
    if(UART_Configuration.TCIE == UART_TCIE_EN){
        SET_BIT(USART1->CR1,6);
    }
    //Enable Transmitting and Receiveing Blocks
     //Enable Transmitter Block
    SET_BIT(USART1->CR1,3);
    //Enable Reciever Block
    SET_BIT(USART1->CR1,2);

    //Stop Bits
 //Configure Number of StopBits
    if(UART_Configuration.StopBits == UART_One_Stop_Bit){
        CLR_BIT(USART1->CR2,12);
        CLR_BIT(USART1->CR2,13);
    }
    else if(UART_Configuration.StopBits == UART_Half_Stop_Bit){
        CLR_BIT(USART1->CR2,12);
        SET_BIT(USART1->CR2,13);
    }
    else if(UART_Configuration.StopBits == UART_Two_Stop_Bit){
        SET_BIT(USART1->CR2,12);
        CLR_BIT(USART1->CR2,13);
    }
    else if(UART_Configuration.StopBits == UART_One_And_Half_Stop_Bit){
        SET_BIT(USART1->CR2,12);
        SET_BIT(USART1->CR2,13);
    }
    else{
        Local_Error = OUT_OF_RANGE;
        return Local_Error;
    }
            //Setting BaudRate
    if(UART_Configuration.BaudRate == UART_9600){
        USART1->BRR = 0x341;
    }
    else if(UART_Configuration.BaudRate == UART_115200){
        USART1->BRR = 0x45;
    }
        //Enable UART Peripheral
        SET_BIT(USART1->CR1,13);
        Local_Error = OK;
    return Local_Error;
}


/**
 * @brief Send a character over UART synchronously.
 *
 * @param Copy_u8Data The character to send.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t UART_SendCharSynchronous(uint8_t Copy_u8Data){
    ERRORS_t Local_Error = NOK;
    if(UART_State == UART_BUSY){
        Local_Error = BUSY_FUNCTION;
    }
    else{
        UART_State = UART_BUSY;
        USART1->DR = Copy_u8Data;
        //Busy Wait
        while(!GET_BIT(USART1->SR,6));
		//UART_ClearFlags();
        UART_State = UART_IDLE;
        Local_Error = OK;
    }
    
    return Local_Error;
}
/**
 * @brief Send a buffer of data over UART synchronously.
 *
 * @param Copy_pu8Buffer Pointer to the data buffer to send.
 * @param BufferSize The size of the data buffer.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t UART_SendBufferSynchronous(uint8_t *Copy_pu8Buffer){
    ERRORS_t Local_Error = NOK;
    uint8_t LOC_u8Iterator = 0 ;

	while ( Copy_pu8Buffer[ LOC_u8Iterator ] != '\0' ){

		UART_SendCharSynchronous( Copy_pu8Buffer[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;
		Delay_ms(100);
	}
    return Local_Error;
}
/**
 * @brief  Set a callback function to be executed when a UART interrupt occurs.
 * 
 * @param Copy_PVCallBack  Pointer to the callback function.
 * @return ERRORS_t  status indicating success or failure.
 */
ERRORS_t UART_SetCallBack(void (*Copy_PVCallBack)(void)){
    ERRORS_t Local_Error = NOK;
    if(NULL == Copy_PVCallBack){
        Local_Error = NULL_POINTER;
    }
    else{
        UART_PVCallBack = Copy_PVCallBack;
        Local_Error = OK;
    }
    return Local_Error;
}
/**
 * @brief  Read the data register of the UART.
 * 
 * @return uint8_t  the data register value.
 */
uint8_t UART_ReadDataRegister(void){
    return (USART1->DR);
}
/**
 * @brief  Clear the status flags of the UART.
 * 
 * @return ERRORS_t  status indicating success or failure.
 */
ERRORS_t UART_ClearFlags(void){
    ERRORS_t Local_Error = NOK;
    USART1->SR = 0;
    Local_Error = OK;
    return Local_Error;
}

/*==============================================================================================================================================
 * INTERRUPT SERVICE ROUTINE
 *==============================================================================================================================================*/
void USART1_IRQHandler(void){
    UART_PVCallBack();
	UART_ClearFlags();
}


/*********************************************************************************
 *                                                                               *
 *                  Not Needed in this Application                               *
 *                                                                               *
*********************************************************************************/
/*
ERRORS_t UART_SendCharASynchronous(uint8_t *Copy_pu8Data, void (*Copy_PVCallBack)(void)){
    ERRORS_t Local_Error = NOK;
    if(UART_State == UART_BUSY){
        Local_Error = BUSY_FUNCTION;
    }
    else{
        if(NULL == Copy_pu8Data || NULL == Copy_PVCallBack){
            Local_Error = NULL_POINTER;
        }
        else{
        UART_ISRSOURCE = UART_ISR_SOURCE_SEND_CHAR;
        UART_State = UART_BUSY;
		UART_PVCallBack = Copy_PVCallBack;
        //Enable Transmit Interrupt
        SET_BIT(USART1->CR1,6);
        USART1->DR = *Copy_pu8Data;
        Local_Error = OK;
        }
    }
    return Local_Error;
}

ERRORS_t UART_SendBufferASynchronous(uint8_t *Copy_pu8Data,uint8_t BufferSize, void (*Copy_PVCallBack)(void)){
    ERRORS_t Local_Error = NOK;
    if(UART_State == UART_BUSY){
        Local_Error = BUSY_FUNCTION;
    }
    else{
        if(NULL == Copy_pu8Data || NULL == Copy_PVCallBack){
            Local_Error = NULL_POINTER;
        }
        else{
        UART_ISRSOURCE = UART_ISR_SOURCE_SEND_BUFFER;
        UART_State = UART_BUSY;
        UART_BufferCounter = 0;
        UART_BufferSize = BufferSize;
        UART_pu8Data = Copy_pu8Data;
        UART_PVCallBack = Copy_PVCallBack;
        //Enable Transmit Interrupt
        SET_BIT(USART1->CR1,6);
        USART1->DR = UART_pu8Data[UART_BufferCounter];
        Local_Error = OK;
        }
    }
    return Local_Error;
}

ERRORS_t UART_ReceiveCharSynchronous(uint8_t *Copy_u8Data){
    ERRORS_t Local_Error = NOK;
    uint32_t Local_u32Counter = 0;
    //Busy Wait
    while(!GET_BIT(USART1->SR,5) && (Local_u32Counter++ < 10000)){

    }
	*Copy_u8Data = USART1->DR;
    Local_Error = OK;
    return Local_Error;
}

void USART1_IRQHandler(void){
    if(GET_BIT(USART1->SR,6)){
        if(UART_ISRSOURCE == UART_ISR_SOURCE_SEND_CHAR){
        //Disable Transmit Interrupt
        CLR_BIT(USART1->CR1,6);
        UART_PVCallBack();
        CLR_BIT(USART1->SR,6);
        UART_State = UART_IDLE;
        }
        else if(UART_ISRSOURCE == UART_ISR_SOURCE_SEND_BUFFER){
            if(UART_BufferCounter < UART_BufferSize){
                USART1->DR = UART_pu8Data[UART_BufferCounter];
                UART_BufferCounter++;
            }
            else{
                //Disable Transmit Interrupt
                CLR_BIT(USART1->CR1,6);
                UART_PVCallBack();
                CLR_BIT(USART1->SR,6);
                UART_State = UART_IDLE;
            }
        }
}
*/
