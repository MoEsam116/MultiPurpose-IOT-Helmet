/*******************************************************************************
 * Filename              :   RCC_Private.h
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
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_
/******************************************************************************
* MicroController clock output
*******************************************************************************/
#define CFGR_MCO_NoClock             Ob000         //  No clock
#define CFGR_MCO_SYSCLK              Ob100         //  System clock (SYSCLK) selected101
#define CFGR_MCO_HSI                 Ob101         //  HSI clock selected
#define CFGR_MCO_HSE                 Ob110         //  HSE clock selected
#define CFGR_MCO_PLL_DIV_2           Ob111         //  PLL clock divided by 2 selected
/******************************************************************************
* PLL multiplication factor
*******************************************************************************/
#define CFGR_PLLMUL2                       0b0000   // PLL input clock x 2
#define CFGR_PLLMUL3                       0b0001   // PLL input clock x 3
#define CFGR_PLLMUL4                       0b0010   // PLL input clock x 4
#define CFGR_PLLMUL5                       0b0011   // PLL input clock x 5
#define CFGR_PLLMUL6                       0b0100   // PLL input clock x 6
#define CFGR_PLLMUL7                       0b0101   // PLL input clock x 7
#define CFGR_PLLMUL8                       0b0110   // PLL input clock x 8
#define CFGR_PLLMUL9                       0b0111   // PLL input clock x 9
#define CFGR_PLLMUL10                      0b1000   // PLL input clock x 10
#define CFGR_PLLMUL11                      0b1001   // PLL input clock x 11
#define CFGR_PLLMUL12                      0b1010   // PLL input clock x 12
#define CFGR_PLLMUL13                      0b1011   // PLL input clock x 13
#define CFGR_PLLMUL14                      0b1100   // PLL input clock x 14
#define CFGR_PLLMUL15                      0b1101   // PLL input clock x 15
#define CFGR_PLLMUL16                      0b1110   // PLL input clock x 16
/******************************************************************************
* ADC Prescaler
*******************************************************************************/
#define CFGR_ADCPRE_DIV_2             0b00     // PCLK2 divided by 2
#define CFGR_ADCPRE_DIV_4             0b01     // PCLK2 divided by 4
#define CFGR_ADCPRE_DIV_6             0b10     // PCLK2 divided by 6
#define CFGR_ADCPRE_DIV_8             0b11     // PCLK2 divided by 8
/******************************************************************************
* APB high-speed prescaler (APB2)
*******************************************************************************/
#define CFGR_PPRE2_NO_DIV             0b000   // HCLK not divided
#define CFGR_PPRE2_DIV_2              0b100   // HCLK divided by 2
#define CFGR_PPRE2_DIV_4              0b101   // HCLK divided by 4
#define CFGR_PPRE2_DIV_8              0b110   // HCLK divided by 8
#define CFGR_PPRE2_DIV_16             0b111   // HCLK divided by 16
/******************************************************************************
* APB low-speed prescaler (APB1)
*******************************************************************************/
#define CFGR_PPRE1_NO_DIV             0b000   // HCLK not divided
#define CFGR_PPRE1_DIV_2              0b100   // HCLK divided by 2
#define CFGR_PPRE1_DIV_4              0b101   // HCLK divided by 4
#define CFGR_PPRE1_DIV_8              0b110   // HCLK divided by 8
#define CFGR_PPRE1_DIV_16             0b111   // HCLK divided by 16
/******************************************************************************
* AHB prescaler
*******************************************************************************/
#define CFGR_HPRE_NO_DIV              0b0000      // SYSCLK not divided
#define CFGR_HPRE_DIV_2               0b1000      // SYSCLK divided by 2
#define CFGR_HPRE_DIV_4               0b1001      // SYSCLK divided by 4
#define CFGR_HPRE_DIV_8               0b1010      // SYSCLK divided by 8
#define CFGR_HPRE_DIV_16              0b1011      // SYSCLK divided by 16
#define CFGR_HPRE_DIV_64              0b1100      // SYSCLK divided by 64
#define CFGR_HPRE_DIV_128             0b1101      // SYSCLK divided by 128
#define CFGR_HPRE_DIV_256             0b1110      // SYSCLK divided by 256
#define CFGR_HPRE_DIV_512             0b1111      // SYSCLK divided by 512
/******************************************************************************
* System clock switch status
*******************************************************************************/
#define CFGR_SWS_HSI                   0b00     // HSI oscillator used as system clock
#define CFGR_SWS_HSE                   0b01     // HSE oscillator used as system clock
#define CFGR_SWS_PLL                   0b10     // PLL used as system clock
/******************************************************************************
* System clock switch
*******************************************************************************/
#define CFGR_SW                        0  // System clock switch
#define CFGR_SW_HSI                  0b00 // HSI selected as system clock
#define CFGR_SW_HSE                  0b01 // HSE selected as system clock
#define CFGR_SW_PLL                  0b10 // PLL selected as system clock











#endif /* RCC_PRIVATE_H_ */
