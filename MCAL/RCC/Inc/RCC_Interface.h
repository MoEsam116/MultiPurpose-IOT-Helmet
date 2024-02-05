/*******************************************************************************
 * Filename              :   RCC_Interface.h
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

#ifndef RCC_RCC_INTERFACE_H_
#define RCC_RCC_INTERFACE_H_
/*==============================================================================================================================================
 * PLL Multiplication
 *==============================================================================================================================================*/
#define PLLMUL2                        0        // PLL input clock x 2
#define PLLMUL3                        1        // PLL input clock x 3
#define PLLMUL4                        2        // PLL input clock x 4
#define PLLMUL5                        3        // PLL input clock x 5
#define PLLMUL6                        4        // PLL input clock x 6
#define PLLMUL7                        5        // PLL input clock x 7
#define PLLMUL8                        6        // PLL input clock x 8
#define PLLMUL9                        7        // PLL input clock x 9
#define PLLMUL10                       8        // PLL input clock x 10
#define PLLMUL11                       9        // PLL input clock x 11
#define PLLMUL12                       10       // PLL input clock x 12
#define PLLMUL13                       11       // PLL input clock x 13
#define PLLMUL14                       12       // PLL input clock x 14
#define PLLMUL15                       13       // PLL input clock x 15
#define PLLMUL16                       14       // PLL input clock x 16
/*==============================================================================================================================================
 * AHB Prephiral
 *==============================================================================================================================================*/
#define AHP_SDIO             10
#define AHP_FSMC             8
#define AHP_CRC              6
#define AHP_FLITF            4
#define AHP_SRAM             2
#define AHP_DMA2             1
#define AHP_DMA1             0
/*==============================================================================================================================================
 * APB2 Prephiral
 *==============================================================================================================================================*/
#define APB2_TIM11               21
#define APB2_TIM10               20
#define APB2_TIM9                19
#define APB2_ADC3                15
#define APB2_USART1              14
#define APB2_TIM8                13
#define APB2_SPI1                12
#define APB2_TIM1                11
#define APB2_ADC2                10
#define APB2_ADC1                9
#define APB2_IOPG                8
#define APB2_IOPF                7
#define APB2_IOPE                6
#define APB2_IOPD                5
#define APB2_IOPC                4
#define APB2_IOPB                3
#define APB2_IOPA                2
#define APB2_AFIO                0
/*==============================================================================================================================================
 * APB1 Prephiral
 *==============================================================================================================================================*/
#define APB1_DAC                    29
#define APB1_PWR                    28
#define APB1_BKP                    27
#define APB1_CAN                    25
#define APB1_USB                    23
#define APB1_I2C2                   22
#define APB1_I2C1                   21
#define APB1_UART5                  20
#define APB1_UART4                  19
#define APB1_USART3                 18
#define APB1_USART2                 17
#define APB1_SPI3                   15
#define APB1_SPI2                   14
#define APB1_WWDG                   11
#define APB1_TIM14                   8
#define APB1_TIM13                   7
#define APB1_TIM12                   6
#define APB1_TIM7                    5
#define APB1_TIM6                    4
#define APB1_TIM5                    3
#define APB1_TIM4                    2
#define APB1_TIM3                    1
#define APB1_TIM2                    0
/*==============================================================================================================================================
 * Structs
 *==============================================================================================================================================*/
typedef struct
{
	uint8_t PLLMUL;
	uint8_t PLL_SRC;
}PLL_CONFIG;
typedef struct
{
	uint8_t HSE_BYP_STATUS;
	uint8_t HSE_2_PLL_PRES;
}HSE_CONFIG;
/*==============================================================================================================================================
 * Some Defines for Structs
 *==============================================================================================================================================*/
#define HSI        0
#define HSE        1
#define PLL        2
#define CLKON      1
#define CLKOFF     0

#define BYPASS_ON   1
#define BYPASS_OFF  0

#define HSE_2_PLL_NODIV        0
#define HSE_2_PLL_DIVBY2       1

#define PLLSRC_HSI_DIV_2     0
#define PLLSRC_HSE           1

/*
 * Prototype   : uint8_t RCC_setCLKStatus(uint8_t CLK_TYPE ,uint8_t Status)
 * Description : Set clock status
 * Arguments   : CLK_TYPE : takes only HSI, HSE,PLL
 *               Status : CLKOM , CLKOFF
 * return      : uint8_t number used for error handling
 *			     (1) means no error,(0) means Timeout for ready flag
 */
uint8_t RCC_setCLKStatus(uint8_t CLK_TYPE ,uint8_t Status);
/*
 * Prototype   : void RCC_SetSYSCLK(uint8_t CLK_TYPE)
 * Description : Set System Clock
 * Arguments   : CLK_TYPE : takes only HSI, HSE,PLL
 *
 * return      : void
 */
void RCC_SetSYSCLK(uint8_t CLK_TYPE);
/*
 * Prototype   : void RCC_HSEConfig(HSE_CONFIG * HSE_USERCONFIG)
 * Description : Set HSE Configuration
 * Arguments   : HSE_CONFIG : 1- HSE_BYP_STATUS : Takes BYPASS_ON , BYPASS_OFF
 *                            2- HSE_2_PLL_PRES : Takes HSE_2_PLL_NODIV , HSE_2_PLL_DIVBY2
 * return      : void
 */
void RCC_HSEConfig(HSE_CONFIG * HSE_USERCONFIG);
/*
 * Prototype   : void RCC_PLLConfig(PLL_CONFIG * PLL_USERCONFIG)
 * Description : Set PLL Configuration
 * Arguments   : PLL_CONFIG : 1- PLLMUL  : Takes PLLMULi , i is from 2 to 16
 *                            2- PLL_SRC : Takes PLLSRC_HSE , PLLSRC_HSI_DIV_2
 * return      : void
 */
void RCC_PLLConfig(PLL_CONFIG * PLL_USERCONFIG);
/*
 * Prototype   : void RCC_AHBEnableCLK(uint8_t Prephiral)
 * Description : Enable Required AHB Peripheral
 * Arguments   : Prephiral : Takes AHP_SDIO ,AHP_FSMC ,AHP_CRC  ,AHP_FLITF,AHP_SRAM ,AHP_DMA2 ,AHP_DMA1
 * return      : void
 */
void RCC_AHBEnableCLK(uint8_t Prephiral);
/*
 * Prototype   : void RCC_AHBDisableCLK(uint8_t Prephiral)
 * Description : Disable Required AHB Peripheral
 * Arguments   : Prephiral : Takes AHP_SDIO ,AHP_FSMC ,AHP_CRC  ,AHP_FLITF,AHP_SRAM ,AHP_DMA2 ,AHP_DMA1
 * return      : void
 */
void RCC_AHBDisableCLK(uint8_t Prephiral);
/*
 * Prototype   : void RCC_APB2EnableCLK(uint8_t Prephiral)
 * Description : Enable Required APB2 Peripheral
 * Arguments   : Prephiral : Takes APB2_TIM11 ,APB2_TIM10 ,APB2_TIM9  ,APB2_ADC3  ,APB2_USART1,APB2_TIM8  ,APB2_SPI1  ,APB2_TIM1
 *                                ,APB2_ADC2  ,APB2_ADC1  ,APB2_IOPG  ,APB2_IOPF  ,APB2_IOPE  ,APB2_IOPD  ,APB2_IOPC  ,APB2_IOPB
 *                                ,APB2_IOPA  ,APB2_AFIO
 * return      : void
 */
void RCC_APB2EnableCLK(uint8_t Prephiral);
/*
 * Prototype   : void RCC_APB2DisableCLK(uint8_t Prephiral)
 * Description : Disable Required APB2 Peripheral
 * Arguments   : Prephiral : Takes APB2_TIM11 ,APB2_TIM10 ,APB2_TIM9  ,APB2_ADC3  ,APB2_USART1,APB2_TIM8  ,APB2_SPI1  ,APB2_TIM1
 *                                ,APB2_ADC2  ,APB2_ADC1  ,APB2_IOPG  ,APB2_IOPF  ,APB2_IOPE  ,APB2_IOPD  ,APB2_IOPC  ,APB2_IOPB
 *                                ,APB2_IOPA  ,APB2_AFIO
 * return      : void
 */
void RCC_APB2DisableCLK(uint8_t Prephiral);
/*
 * Prototype   : void RCC_APB1EnableCLK(uint8_t Prephiral)
 * Description : Enable Required APB1 Peripheral
 * Arguments   : Prephiral : Takes ,APB1_DAC   ,APB1_PWR   ,APB1_BKP   ,APB1_CAN   ,APB1_USB   ,APB1_I2C2  ,APB1_I2C1  ,APB1_UART5
 *                                 ,APB1_UART4 ,APB1_USART3,APB1_USART2,APB1_SPI3  ,APB1_SPI2  ,APB1_WWDG  ,APB1_TIM14 ,APB1_TIM13
                                   ,APB1_TIM12 ,APB1_TIM7  ,APB1_TIM6  ,APB1_TIM5  ,APB1_TIM4  ,APB1_TIM3  ,APB1_TIM2
 * return      : void
 */
void RCC_APB1EnableCLK(uint8_t Prephiral);
/*
 * Prototype   : void RCC_APB1DisableCLK(uint8_t Prephiral)
 * Description : Disable Required APB1 Peripheral
 * Arguments   : Prephiral : Takes ,APB1_DAC   ,APB1_PWR   ,APB1_BKP   ,APB1_CAN   ,APB1_USB   ,APB1_I2C2  ,APB1_I2C1  ,APB1_UART5
 *                                 ,APB1_UART4 ,APB1_USART3,APB1_USART2,APB1_SPI3  ,APB1_SPI2  ,APB1_WWDG  ,APB1_TIM14 ,APB1_TIM13
                                   ,APB1_TIM12 ,APB1_TIM7  ,APB1_TIM6  ,APB1_TIM5  ,APB1_TIM4  ,APB1_TIM3  ,APB1_TIM2
 * return      : void
 */
void RCC_APB1DisableCLK(uint8_t Prephiral);




#endif /* RCC_RCC_INTERFACE_H_ */
