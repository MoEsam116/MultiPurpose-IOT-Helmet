#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_


/* Configurations
        * 1- Baud Rate
        * 2- Parity
        * 3- Stop Bits
        * 4- Word Length
        * 5- Interrupt TXEIE        //Disabled if not configured
        * 6- Interrupt TCIE         //Disabled if not configured
        * 7- Interrupt RXNEIE       //Disabled if not configured
*/
typedef enum{
    UART_9600,
    UART_115200
}UART_BAUDRATE_t;

typedef enum{
    UART_One_Stop_Bit,
    UART_Half_Stop_Bit,
    UART_Two_Stop_Bit,
    UART_One_And_Half_Stop_Bit
}UART_StopBits_t;

typedef enum{
    UART_No_Parity,
    UART_Even_Parity,
    UART_Odd_Parity
}UART_Parity_t;
typedef enum{
    UART_8_WORD_LENGTH,
    UART_9_WORD_LENGTH
}UART_WordLen_t;
typedef enum{
    UART_NO_INT,
    UART_TXEIE_EN,
    UART_TCIE_EN,
    UART_RXNEIE_EN,
}Interrupts_config_t;
typedef struct 
{
    uint32_t BaudRate;
    UART_WordLen_t WordLength;
    UART_Parity_t Parity;
    UART_StopBits_t StopBits;
    Interrupts_config_t TXEIE;
    Interrupts_config_t TCIE;
    Interrupts_config_t RXNEIE;
}UART_Init_t;




/**
 * @brief Initialize the UART communication module.
 *
 * @param No parameters.
 * @param No parameters.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t UART_Init(void);

/**
 * @brief Send a character over UART synchronously.
 *
 * @param Copy_u8Data The character to send.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t UART_SendCharSynchronous(uint8_t Copy_u8Data);

/**
 * @brief Send a buffer of data over UART synchronously.
 *
 * @param Copy_pu8Buffer Pointer to the data buffer to send.
 * @param BufferSize The size of the data buffer.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t UART_SendBufferSynchronous(uint8_t *Copy_pu8Buffer);

/**
 * @brief  Set a callback function to be executed when a UART interrupt occurs.
 * 
 * @param Copy_PVCallBack  Pointer to the callback function.
 * @return ERRORS_t  status indicating success or failure.
 */
ERRORS_t UART_SetCallBack(void (*Copy_PVCallBack)(void));


/**
 * @brief  Read the data register of the UART.
 * 
 * @return uint8_t  the data register value.
 */

uint8_t UART_ReadDataRegister(void);


/**
 * @brief  Clear the status flags of the UART.
 * 
 * @return ERRORS_t  status indicating success or failure.
 */
ERRORS_t UART_ClearFlags(void);








/*********************************************************************************
 *                                                                               *
 *                  Not Needed in this Application                               *
 *                                                                               *
*********************************************************************************/
/**
 * @brief Send a character over UART asynchronously.
 *
 * @param Copy_pu8Data Pointer to the character to send.
 * @param Copy_PVCallBack Pointer to a callback function to execute when the operation is complete.
 *
 * @return ERRORS_t status indicating success or failure.
 */
//ERRORS_t UART_SendCharASynchronous(uint8_t *Copy_pu8Data, void (*Copy_PVCallBack)(void));

/**
 * @brief Send a buffer of data over UART asynchronously.
 *
 * @param Copy_pu8Data Pointer to the data buffer to send.
 * @param BufferSize The size of the data buffer.
 * @param Copy_PVCallBack Pointer to a callback function to execute when the operation is complete.
 *
 * @return ERRORS_t status indicating success or failure.
 */
//ERRORS_t UART_SendBufferASynchronous(uint8_t *Copy_pu8Data, uint8_t BufferSize, void (*Copy_PVCallBack)(void));



/**
 * @brief Receive a character over UART synchronously.
 *
 * @param[out] Copy_u8Data Pointer to store the received character.
 *
 * @return ERRORS_t status indicating success or failure.
 */
//ERRORS_t UART_ReceiveCharSynchronous(uint8_t *Copy_u8Data);
















#endif