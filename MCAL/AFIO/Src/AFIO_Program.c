
/*
 ******************************************************************************
 * @file           : AFIO_Program.C
 * @Author         : Ibrahim Mohamed
 * @brief          : AFIO Program File
 * @Date           : Aug 24, 2023
 ******************************************************************************
 */
#include "stdint.h"
#include "../../LIBRARY/BitMath.h"
#include "../../LIBRARY/STM32F103xx.h"
#include "../../LIBRARY/ErrTypes.h"
#include "../Inc/AFIO_Interface.h"

/**
 * @fn    : AFIO_U8SetEXTIPort
 * @brief : This Function Sets A Specific Port for A Specific External Interrupt Line
 * @param : EXTI_Line -> Options of All Available EXTI Lines
 * @param : GPIO_Port -> Options of All Available Ports
 * @return: ErrorStatus to Indicate if function Worked Correctly or NOT
 */
uint8_t AFIO_U8SetEXTIPort( AFIO_EXTI_Line EXTI_Line, AFIO_Port_t GPIO_Port)
{
	uint8_t Error_State = OK;

	if ( (EXTI_Line < Max_EXTI_Line) && (GPIO_Port < Max_GPIO_Port) )
	{
		uint8_t REG_Number = EXTI_Line /4 ;

		uint8_t Bits_Number = (EXTI_Line %4 ) *4 ;

		/*Clear the Required 4 Bits*/
		AFIO->EXTICR[REG_Number] &=(~(0b1111 << Bits_Number));

		AFIO->EXTICR[REG_Number]= ( GPIO_Port << Bits_Number ) ;
	}
	else
	{
		Error_State = NOK;
	}
	return Error_State;
}


