/*
 *@file		:	PWR_INTERFACE.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for PWR (Power Control)
 */
#ifndef PWR_INC_PWR_INTERFACE_H_
#define PWR_INC_PWR_INTERFACE_H_

#include "../../../Library/STM32F103xx.h"
#include "../../../Library/ErrType.h"
#include "../../../Library/BIT_MATH.h"

/**
  * @func	: PWR_xEnterSleepMode
  * @brief 	: Enters Sleep mode.
  * @note  	: - In Sleep mode, all I/O pins keep the same state as in Run mode.
  * 		  -	Any Interrupt Acknowledged by the NVIC can wake up the device.
  * 		  - Before Calling this Function, Disable all interrupts via NVIC
  * 		  	Except the one which will be used to wake up the CPU.
  * @retval : void
  */
void PWR_xEnterSleepMode(void);

#endif /* PWR_INC_PWR_INTERFACE_H_ */
