/*
 *@file		:	PWR_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program for PWR (Power Control)
 */

/******************* MAIN INCLUDES *********************/
#include <stdint.h>
#include "../../../Library/STM32F103xx.h"
#include "../../../Library/ErrType.h"
#include "../../../Library/BIT_MATH.h"


#include "../Inc/PWR_Interface.h"
#include "../Inc/PWR_Private.h"
/*******************************************************/


/****************** MAIN FUNCTIONS *********************/

/**
  * @func	: PWR_xEnterSleepMode
  * @brief 	: Enters Sleep mode.
  * @note  	: - In Sleep mode, all I/O pins keep the same state as in Run mode.
  * 		  -	Any Interrupt Acknowledged by the NVIC can wake up the device.
  * 		  - Before Calling this Function, Disable all interrupts via NVIC
  * 		  	Except the one which will be used to wake up the CPU.
  * @retval : void
  */
void PWR_xEnterSleepMode(void)
{

	/*Disable Tick interrupt to avoid exiting sleep mode after 1ms*/
	SYSTICK->SYST_CSR &= ~(1<<1);

	/*Clear DEEPSLEEP Bit in SCB (to enter in normal Sleep mode)*/
	SCB->SCR &= ~ (1<<DEEPSLEEP_BIT);

	/*Clear SLEEPONEXIT Bit in SCB ()*/
	SCB->SCR &= ~ (1<<SLEEPONEXIT_BIT);

	/*Execute WFI (Wait For Interrupt) Instruction to enter Sleep mode*/
	WFI();

	/*Enable Tick interrupt*/
	SYSTICK->SYST_CSR |= (1<<1);
}
/*******************************************************/
