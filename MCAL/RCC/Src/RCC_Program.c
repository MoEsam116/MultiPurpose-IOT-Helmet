/*******************************************************************************
 * Filename              :   RCC_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   13/4/2023
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :   None
 **
 *******************************************************************************/
/************************ SOURCE REVISION LOG *********************************
 *
 *    Date    Version   Author             Description
 *  13/10/20   1.0.0   Mohamemd Waleed   Initial Release.
 *
 *******************************************************************************/

/*==============================================================================================================================================
 * Inculdes
 *==============================================================================================================================================*/
#include <stdint.h>

#include "../Inc/RCC_Interface.h"
#include "../Inc/RCC_Config.h"
#include "../Inc/RCC_Private.h"
#include "../../LIB/STM32F103xx.h"
/*
 * Prototype   : uint8_t RCC_setCLKStatus(uint8_t CLK_TYPE ,uint8_t Status)
 * Description : Set clock status
 * Arguments   : CLK_TYPE : takes only HSI, HSE,PLL
 *               Status : CLKOM , CLKOFF
 * return      : uint8_t number used for error handling
 *			     (1) means no error,(0) means Timeout for ready flag
 */
uint8_t RCC_setCLKStatus(uint8_t CLK_TYPE, uint8_t Status)
{
	/* variable to store time needed for clk to be ready */
	uint16_t Timeout = 0;
	/* check clk type and it's status */
	if (CLK_TYPE == HSE)
	{
		if (Status == CLKON)
		{
			/* HSE ON */
			RCC->RCC_CR |= (1 << CR_HSEON);
			/* Waiting until Clock is Ready or timeout is reached */
			while (((((RCC->RCC_CR) >> CR_HSERDY) & 1) == 0) && (Timeout <= TimeoutMax))
			{
				Timeout++;
			}
			/* check if timeout is reached */
			if (Timeout == TimeoutMax)
			{
				return 0;
			}
		}
		else if (Status == CLKOFF)
		{
			/*  HSE OFF */
			RCC->RCC_CR &= ~(1 << CR_HSEON);
		}
	}
	if (CLK_TYPE == HSI)
	{
		if (Status == CLKON)
		{
			/*  HSI ON */
			RCC->RCC_CR |= (1 << CR_HSION);
			/*  Waiting until Clock is Ready or timeout is reached */
			while (((((RCC->RCC_CR) >> CR_HSERDY) & 1) == 0) && Timeout <= TimeoutMax)
			{
				Timeout++;
			}
			/* check if timeout is reached */
			if (Timeout == TimeoutMax)
			{
				return 0;
			}
		}
		else if (Status == CLKOFF)
		{
			/*  HSI Off */
			RCC->RCC_CR &= ~(1 << CR_HSION);
		}
	}
	if (CLK_TYPE == PLL)
	{
		if (Status == CLKON)
		{
			/* PLL ON */
			RCC->RCC_CR |= (1 << CR_PLLON);
			/*  Waiting until Clock is Ready or timeout is reached */
			while (((((RCC->RCC_CR) >> CR_HSERDY) & 1) == 0) && Timeout <= TimeoutMax)
			{
				Timeout++;
			}
			/* check if timeout is reached */
			if (Timeout < TimeoutMax)
			{
				return 0;
			}
		}
		else if (Status == CLKOFF)
		{
			/* PLL OFF */
			RCC->RCC_CR &= ~(1 << CR_PLLON);
		}
	}
	return 1;
}

/*
 * Prototype   : void RCC_SetSYSCLK(uint8_t CLK_TYPE)
 * Description : Set System Clock
 * Arguments   : CLK_TYPE : takes only HSI, HSE,PLL
 *
 * return      : void
 */
void RCC_SetSYSCLK(uint8_t CLK_TYPE)
{
	/* Bit Masking */
	RCC->RCC_CFGR &= ~(0b11 << CFGR_SW);
	/* Check SYSCLK */
	if (CLK_TYPE == HSE)
	{
		/* SET HSE AS SYSCLK */
		RCC->RCC_CFGR |= (CFGR_SW_HSE << CFGR_SW);
	}
	else if (CLK_TYPE == HSI)
	{
		/* SET HSI AS SYSCLK */
		RCC->RCC_CFGR |= (CFGR_SW_HSI << CFGR_SW);
	}
	else if (CLK_TYPE == PLL)
	{
		/* SET PLL AS SYSCLK */
		RCC->RCC_CFGR |= (CFGR_SW_PLL << CFGR_SW);
	}
}
/*
 * Prototype   : void RCC_HSEConfig(HSE_CONFIG * HSE_USERCONFIG)
 * Description : Set HSE Configuration
 * Arguments   : HSE_CONFIG : 1- HSE_BYP_STATUS : Takes BYPASS_ON , BYPASS_OFF
 *                            2- HSE_2_PLL_PRES : Takes HSE_2_PLL_NODIV , HSE_2_PLL_DIVBY2
 * return      : void
 */
void RCC_HSEConfig(HSE_CONFIG *HSE_USERCONFIG)
{
	/* Chech bypass is on or not */
	if (HSE_USERCONFIG->HSE_BYP_STATUS == BYPASS_ON)
	{
		RCC->RCC_CR |= (1 << CR_HSEBYP);
	}
	else if (HSE_USERCONFIG->HSE_BYP_STATUS == BYPASS_OFF)
	{
		RCC->RCC_CR &= ~(1 << CR_HSEBYP);
	}
	/* HSE to PLL devider config */
	if (HSE_USERCONFIG->HSE_2_PLL_PRES == HSE_2_PLL_DIVBY2)
	{
		RCC->RCC_CFGR |= (1 << CFGR_PLLXTPRE);
	}
	else if (HSE_USERCONFIG->HSE_2_PLL_PRES == HSE_2_PLL_NODIV)
	{
		RCC->RCC_CFGR &= ~(1 << CFGR_PLLXTPRE);
	}
}
/*
 * Prototype   : void RCC_PLLConfig(PLL_CONFIG * PLL_USERCONFIG)
 * Description : Set PLL Configuration
 * Arguments   : PLL_CONFIG : 1- PLLMUL  : Takes PLLMULi , i is from 2 to 16
 *                            2- PLL_SRC : Takes PLLSRC_HSE , PLLSRC_HSI_DIV_2
 * return      : void
 */
void RCC_PLLConfig(PLL_CONFIG *PLL_USERCONFIG)
{
	/* bit masking */
	RCC->RCC_CFGR &= ~(0b1111 << CFGR_PLLMUL);
	/* Set PLL Multiplication Facto */
	RCC->RCC_CFGR |= ((PLL_USERCONFIG->PLLMUL) << CFGR_PLLMUL);
	/* check PLL CLK Source*/
	if (PLL_USERCONFIG->PLL_SRC == PLLSRC_HSE)
	{
		RCC->RCC_CFGR |= (1 << CFGR_PLLSRC);
	}
	else if (PLL_USERCONFIG->PLL_SRC == PLLSRC_HSI_DIV_2)
	{
		RCC->RCC_CFGR &= ~(1 << CFGR_PLLSRC);
	}
}
/*
 * Prototype   : void RCC_AHBEnableCLK(uint8_t Prephiral)
 * Description : Enable Required AHB Peripheral
 * Arguments   : Prephiral : Takes AHP_SDIO ,AHP_FSMC ,AHP_CRC  ,AHP_FLITF,AHP_SRAM ,AHP_DMA2 ,AHP_DMA1
 * return      : void
 */
void RCC_AHBEnableCLK(uint8_t Prephiral)
{
	/* Enable Required AHB Peripheral */
	RCC->RCC_AHBENR |= (1 << Prephiral);
}
/*
 * Prototype   : void RCC_AHBDisableCLK(uint8_t Prephiral)
 * Description : Disable Required AHB Peripheral
 * Arguments   : Prephiral : Takes AHP_SDIO ,AHP_FSMC ,AHP_CRC  ,AHP_FLITF,AHP_SRAM ,AHP_DMA2 ,AHP_DMA1
 * return      : void
 */
void RCC_AHBDisableCLK(uint8_t Prephiral)
{
	/* Disable Required AHB Peripheral */
	RCC->RCC_AHBENR &= ~(1 << Prephiral);
}
/*
 * Prototype   : void RCC_APB2EnableCLK(uint8_t Prephiral)
 * Description : Enable Required APB2 Peripheral
 * Arguments   : Prephiral : Takes APB2_TIM11 ,APB2_TIM10 ,APB2_TIM9  ,APB2_ADC3  ,APB2_USART1,APB2_TIM8  ,APB2_SPI1  ,APB2_TIM1
 *                                ,APB2_ADC2  ,APB2_ADC1  ,APB2_IOPG  ,APB2_IOPF  ,APB2_IOPE  ,APB2_IOPD  ,APB2_IOPC  ,APB2_IOPB
 *                                ,APB2_IOPA  ,APB2_AFIO
 * return      : void
 */
void RCC_APB2EnableCLK(uint8_t Prephiral)
{
	/* Enable Required APB2 Peripheral */
	RCC->RCC_APB2ENR |= (1 << Prephiral);
}
/*
 * Prototype   : void RCC_APB2DisableCLK(uint8_t Prephiral)
 * Description : Disable Required APB2 Peripheral
 * Arguments   : Prephiral : Takes APB2_TIM11 ,APB2_TIM10 ,APB2_TIM9  ,APB2_ADC3  ,APB2_USART1,APB2_TIM8  ,APB2_SPI1  ,APB2_TIM1
 *                                ,APB2_ADC2  ,APB2_ADC1  ,APB2_IOPG  ,APB2_IOPF  ,APB2_IOPE  ,APB2_IOPD  ,APB2_IOPC  ,APB2_IOPB
 *                                ,APB2_IOPA  ,APB2_AFIO
 * return      : void
 */
void RCC_APB2DisableCLK(uint8_t Prephiral)
{
	/* Disable Required APB2 Peripheral */
	RCC->RCC_APB2ENR &= ~(1 << Prephiral);
}
/*
 * Prototype   : void RCC_APB1EnableCLK(uint8_t Prephiral)
 * Description : Enable Required APB1 Peripheral
 * Arguments   : Prephiral : Takes ,APB1_DAC   ,APB1_PWR   ,APB1_BKP   ,APB1_CAN   ,APB1_USB   ,APB1_I2C2  ,APB1_I2C1  ,APB1_UART5
 *                                 ,APB1_UART4 ,APB1_USART3,APB1_USART2,APB1_SPI3  ,APB1_SPI2  ,APB1_WWDG  ,APB1_TIM14 ,APB1_TIM13
								   ,APB1_TIM12 ,APB1_TIM7  ,APB1_TIM6  ,APB1_TIM5  ,APB1_TIM4  ,APB1_TIM3  ,APB1_TIM2
 * return      : void
 */
void RCC_APB1EnableCLK(uint8_t Prephiral)
{
	/* Enable Required APB1 Peripheral */
	RCC->RCC_APB1ENR |= (1 << Prephiral);
}
/*
 * Prototype   : void RCC_APB1DisableCLK(uint8_t Prephiral)
 * Description : Disable Required APB1 Peripheral
 * Arguments   : Prephiral : Takes ,APB1_DAC   ,APB1_PWR   ,APB1_BKP   ,APB1_CAN   ,APB1_USB   ,APB1_I2C2  ,APB1_I2C1  ,APB1_UART5
 *                                 ,APB1_UART4 ,APB1_USART3,APB1_USART2,APB1_SPI3  ,APB1_SPI2  ,APB1_WWDG  ,APB1_TIM14 ,APB1_TIM13
								   ,APB1_TIM12 ,APB1_TIM7  ,APB1_TIM6  ,APB1_TIM5  ,APB1_TIM4  ,APB1_TIM3  ,APB1_TIM2
 * return      : void
 */
void RCC_APB1DisableCLK(uint8_t Prephiral)
{
	/* Disable Required APB1 Peripheral */
	RCC->RCC_APB1ENR &= ~(1 << Prephiral);
}
