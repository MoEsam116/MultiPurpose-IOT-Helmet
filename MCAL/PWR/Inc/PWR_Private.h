/*
 *@file		:	PWR_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Privates for PWR (Power Control)
 */
#ifndef PWR_INC_PWR_PRIVATE_H_
#define PWR_INC_PWR_PRIVATE_H_


#define SLEEPONEXIT_BIT			1
#define DEEPSLEEP_BIT			2
#define WFI()					__asm__ volatile ("wfi")
#endif /* PWR_INC_PWR_PRIVATE_H_ */
