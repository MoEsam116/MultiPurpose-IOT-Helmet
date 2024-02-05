/*******************************************************************************
 * Filename              :   GPIO_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   May 10, 2023
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :   None
 **
 *******************************************************************************/
/************************ SOURCE REVISION LOG *********************************
 *
 *    Date    Version   Author             Description
 *  14/10/20   1.0.0   Mohamemd Waleed   Initial Release.
 *
 *******************************************************************************/
#include <stdint.h>
#include "../../../Library/STM32F103xx.h"
#include "../../../Library/ErrType.h"

#include "../Inc/GPIO_Interface.h"
#include "../Inc/GPIO_Private.h"

static GPIO_REG_t *GPIO_PORT[3] = {GPIOA, GPIOB, GPIOC};
/*
 * Prototype   : uint8_t GPIO_u8PinInit(const Pin_Config_t *PinConfig)
 * Description : Set Mode of a Pin
 * Arguments   : Pin_Config_t : PORT(PORTA , PORTB,PORTC)
 *                              PinNum(PIN1 ..... PIN15)
 *                              InputMode( Input_Analog ,Floating_Input,Input_PU,Input_PD)
 *                              OutputMode(  PushPull,OpenDrain,AFPP,AFOD)
 *                              Mode(Input,Output_10MHZ,Output_2MHZ,Output_50MHZ)
 * return      : uint8_t number used for error handling
 *			     OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8PinInit(const Pin_Config_t *PinConfig)
{
	/* */
	uint8_t Local_u8ErrorStatus = OK;
	if (PinConfig != NULL)
	{
		uint8_t Local_RegNum = (PinConfig->PinNum) / 8;
		uint8_t Local_BitNum = ((PinConfig->PinNum) % 8) * 4;

		/*Selecting Mode */
		GPIO_PORT[PinConfig->Port]->GPIO_CR[Local_RegNum] &= ~(TWO_BIT_MASKING << Local_BitNum);
		GPIO_PORT[PinConfig->Port]->GPIO_CR[Local_RegNum] |= ((PinConfig->Mode) << Local_BitNum);

		/*Selecting Mode Type*/
		if (PinConfig->Mode > Input)
		{
			GPIO_PORT[PinConfig->Port]->GPIO_CR[Local_RegNum] &= ~(TWO_BIT_MASKING << (Local_BitNum + 2));
			GPIO_PORT[PinConfig->Port]->GPIO_CR[Local_RegNum] |= ((PinConfig->OutputMode) << (Local_BitNum + 2));
		}
		else
		{
			GPIO_PORT[PinConfig->Port]->GPIO_CR[Local_RegNum] &= ~(TWO_BIT_MASKING << (Local_BitNum + 2));
			GPIO_PORT[PinConfig->Port]->GPIO_CR[Local_RegNum] |= ((PinConfig->InputMode) << (Local_BitNum + 2));
			if (PinConfig->InputMode == Input_PD)
			{
				GPIO_PORT[PinConfig->Port]->GPIO_ODR &= ~(ONE_BIT_MASKING << (PinConfig->PinNum));
			}
			else if (PinConfig->InputMode == Input_PU)
			{
				GPIO_PORT[PinConfig->Port]->GPIO_ODR |= (ONE_BIT_MASKING << (PinConfig->PinNum));
			}
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
/*
 * Prototype   : uint8_t GPIO_u8SetPinValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal)
 * Description : Set Value of a Pin
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *               PinNum(PIN1 ..... PIN15)
 *               PinVal(PinHigh,PinLow)
 * return      : uint8_t number used for error handling
 *			     OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8SetPinValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal)
{
	uint8_t Local_u8ErrorStatus = OK;
	if ((Port <= PORTC) && (PinNum <= PIN15))
	{
		if (PinVal == PinHigh)
		{
			GPIO_PORT[Port]->GPIO_ODR |= (ONE_BIT_MASKING << PinNum);
		}
		else if (PinVal == PinLow)
		{
			GPIO_PORT[Port]->GPIO_ODR &= ~(ONE_BIT_MASKING << PinNum);
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
/*
 * Prototype   : void GPIO_u8SetFourPortValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal)
 * Description : Set Value of 4 Pins
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *               PinNum(PIN1 ..... PIN15)
 *               pinVal(0x00 to 0x0F)
 * return      : void
 */
void GPIO_u8SetFourPortValue(PORT_t Port, Pin_t PinNum, uint8_t PinVal)
{
	uint32_t Value = 0;
	GPIO_PORT[Port]->GPIO_ODR &= ~(FOUR_BIT_MASKING << PinNum);
	Value = GPIO_PORT[Port]->GPIO_ODR | (PinVal << PinNum);
	GPIO_PORT[Port]->GPIO_ODR = Value;
}
/*
 * Prototype   : uint8_t GPIO_u8TogglePinValue(PORT_t Port, Pin_t PinNum)
 * Description : Toggle Value of a Pin
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *          	 PinNum(PIN1 ..... PIN15)
 * return      : uint8_t number used for error handling
 * 			     OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8TogglePinValue(PORT_t Port, Pin_t PinNum)
{
	uint8_t Local_u8ErrorStatus = OK;
	if ((Port <= PORTC) && (PinNum <= PIN15))
	{
		GPIO_PORT[Port]->GPIO_ODR ^= (ONE_BIT_MASKING << PinNum);
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
/*
 * Prototype   : uint8_t GPIO_u8ReadPinValue(PORT_t Port, Pin_t PinNum, PinVal_t *PinVal)
 * Description : Read Value of a Pin
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *              PinNum(PIN1 ..... PIN15)
 * return      : uint8_t number used for error handling
 *                  OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8ReadPinValue(PORT_t Port, Pin_t PinNum, PinVal_t *PinVal)
{
	uint8_t Local_u8ErrorStatus = OK;
	if ((Port <= PORTC) && (PinNum <= PIN15))
	{
		*PinVal = (GPIO_PORT[Port]->GPIO_IDR >> PinNum) & ONE_BIT_MASKING;
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
