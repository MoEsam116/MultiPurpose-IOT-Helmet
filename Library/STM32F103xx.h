/*
 ******************************************************************************
 * @file           : STM32F103xx.h
 * @Author         :
 * @brief          : Register File
 * @version        : 1.0.1
 * @Date           : Apr 10, 2023
 * @Target         : STM32F103xx
 ******************************************************************************
 */


#ifndef STM32F103XX_H_
#define STM32F103XX_H_

/* ---------------------------------------------------------------------- */
/* ------------------------------- MACROS ------------------------------- */
/* ---------------------------------------------------------------------- */
#define NULL ((void *)0)
#define _vo	 volatile


/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- AHB PERIPHERAL BASE ADDRESSES ------------------------------- */
/* --------------------------------------------------------------------------------------------- */

#define RCC_BASE_ADDRESS 					0x40021000UL

#define AFIO_BASE_ADDRESS        			0x40010000UL

/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- APB1 PERIPHERAL BASE ADDRESSES ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- APB2 PERIPHERAL BASE ADDRESSES ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */

#define EXTI_BASE_ADDRESS				    0x40010400UL

#define ADC1_BASE_ADDRESS                   0x40012400UL
#define ADC2_BASE_ADDRESS                   0x40012800UL

#define TIMER1_BASE_ADDRESS					0x40012C00UL

#define GPIOA_BASE_ADDRESS 					0x40010800
#define GPIOB_BASE_ADDRESS 					0x40010C00
#define GPIOC_BASE_ADDRESS 					0x40011000

/* ------------------------------------------------------------------------------------------------------------- */
/* ------------------------------- CORTEX-M3 INTERNAL PERIPHERALS BASE ADDRESSES ------------------------------- */
/* ------------------------------------------------------------------------------------------------------------- */

#define SYSTICK_BASE_ADDRESS 			    0xE000E010UL


/* -------------------------------------------------------------------------------------------------- */
/* ------------------------------- ADC REGISTERS Definition Structure ------------------------------ */
/* -------------------------------------------------------------------------------------------------- */
typedef struct {
	volatile uint32_t	ADC_SR;
	volatile uint32_t	ADC_CR1;
	volatile uint32_t	ADC_CR2;
	volatile uint32_t	ADC_SMPR[2];
	volatile uint32_t	ADC_JOFR[4];
	volatile uint32_t	ADC_HTR;
	volatile uint32_t	ADC_LTR;
	volatile uint32_t	ADC_SQR[3];
	volatile uint32_t	ADC_JSQR;
	volatile uint32_t	ADC_JDR[4];
	volatile uint32_t	ADC_DR;
}ADC_REG_t;

/* ------------------------------------------------------------------------------------------ */
/* ------------------------------- ADC Peripheral Definition ------------------------------- */
/* ------------------------------------------------------------------------------------------ */

#define ADC1					((ADC_REG_t * )(ADC1_BASE_ADDRESS))
#define ADC2					((ADC_REG_t * )(ADC2_BASE_ADDRESS))

/* -------------------------------------------------------------------------------------------------- */
/* ------------------------------- EXTI REGISTERS Definition Structure ------------------------------ */
/* -------------------------------------------------------------------------------------------------- */
typedef struct
{
	_vo uint32_t EXTI_IMR  ; /*!< INTERRUPT MASK REGISTER			 >!*/
	_vo uint32_t EXTI_EMR  ; /*!< EVENT MASK REGISTER 	 			 >!*/
	_vo uint32_t EXTI_RTSR ; /*!< RISING TRIGGER SELECTION REGISTER  >!*/
	_vo uint32_t EXTI_FTSR ; /*!< FALLING TRIGGER SELECTION REGISTER >!*/
	_vo uint32_t EXTI_SWIER; /*!< SOFTWARE INTERRUPT EVENT REGISTER	 >!*/
	_vo uint32_t EXTI_PR   ; /*!< PENDING REGISTER					 >!*/
}EXTI_RegDef_t;


/* ------------------------------------------------------------------------------------------ */
/* ------------------------------- EXTI Peripheral Definition ------------------------------- */
/* ------------------------------------------------------------------------------------------ */

#define EXTI  ( ( EXTI_RegDef_t* ) EXTI_BASE_ADDRESS )


/* -------------------------------------------------------------------------------------------------- */
/* ------------------------------- RCC REGISTERS Definition Structure ------------------------------ */
/* -------------------------------------------------------------------------------------------------- */
typedef struct
{
    volatile uint32_t RCC_CR;
    volatile uint32_t RCC_CFGR;
    volatile uint32_t RCC_CIR;
    volatile uint32_t RCC_APB2RSTR;
    volatile uint32_t RCC_APB1RSTR;
    volatile uint32_t RCC_AHBENR;
    volatile uint32_t RCC_APB2ENR;
    volatile uint32_t RCC_APB1ENR;
    volatile uint32_t RCC_BDCR;
    volatile uint32_t RCC_CSR;
} RCC_REG_t;

/* ------------------------------------------------------------------------------------------ */
/* ------------------------------- RCC Peripheral Definition -------------------------------- */
/* ------------------------------------------------------------------------------------------ */

#define RCC ((RCC_REG_t*)RCC_BASE_ADDRESS)

/*==============================================================================================================================================
 * Clock Control Register definition (CR)
 *==============================================================================================================================================*/

#define CR_PLLRDY 25 // PLL Ready flag
#define CR_PLLON 24	 // PLL Enable
#define CR_CSSON 19	 // Clock security system enable
#define CR_HSEBYP 18 // HSE Bypass on
#define CR_HSERDY 17 // HSE Ready flag
#define CR_HSEON 16	 // HSE Enable
#define CR_HSIRDY 1	 // HSI Ready flag
#define CR_HSION 0	 // HSI Enable
/*==============================================================================================================================================
 * Clock Configuration Register definition (CFGR)
 *==============================================================================================================================================*/
#define CFGR_USBPRE 22	 // USB prescaler
#define CFGR_PLLMUL 18	 // PLL multiplication factor
#define CFGR_PLLXTPRE 17 // HSE divider for PLL entry
#define CFGR_PLLSRC 16	 // PLL entry clock source
/* ------------------------------------------------------------------------------------------------------ */
/* ------------------------------- SYSTICK REGISTERS Definition Structure ------------------------------- */
/* ------------------------------------------------------------------------------------------------------ */

typedef struct
{
	volatile uint32_t SYST_CSR;	  /*<! SYSTICK Control and Status Register  >!*/
	volatile uint32_t SYST_RVR;	  /*<! SYSTICK Reload Value Register        >!*/
	volatile uint32_t SYST_CVR;	  /*<! SYSTICK Current Value Register       >!*/
	volatile uint32_t SYST_CALIB; /*<! SYSTICK Calibration Value Register   >!*/
} SYSTICK_RegDef_t;

/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- SYSTICK Peripheral Definition ------------------------------- */
/* --------------------------------------------------------------------------------------------- */

#define SYSTICK ((SYSTICK_RegDef_t *)SYSTICK_BASE_ADDRESS)

/* -------------------------------------------------------------------------------------- */
/* ------------------------------- SYSTICK REGISTERS Bits ------------------------------- */
/* -------------------------------------------------------------------------------------- */

/* SYST_CSR */
#define CSR_COUNTFLAG 16
#define CSR_CLKSOURCE 2
#define CSR_TICKINT 1
#define CSR_ENABLE 0


/* ------------------------------------------------------------------------------------------------------ */
/* ------------------------------- NVIC REGISTERS Definition Structure ---------------------------------- */
/* ------------------------------------------------------------------------------------------------------ */

#define NVIC_ISER   ((volatile uint32_t*) 0xE000E100)
#define NVIC_ICER   ((volatile uint32_t*) 0xE000E180)
#define NVIC_ISPR   ((volatile uint32_t*) 0xE000E200)
#define NVIC_ICPR   ((volatile uint32_t*) 0xE000E280)
#define NVIC_IABR   ((volatile uint32_t*) 0xE000E300)
#define NVIC_IPR    ((volatile uint8_t *) 0xE000E400)



/* ------------------------------------------------------------------------------------------------------ */
/* ------------------------------- SCB REGISTERS Definition Structure ----------------------------------- */
/* ------------------------------------------------------------------------------------------------------ */
typedef struct{

    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR1;
    volatile uint32_t SHPR2;
    volatile uint32_t SHPR3;
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t RESERVED;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;

}SCB_Type;

/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- SCB Peripheral Definition ----------------------------------- */
/* --------------------------------------------------------------------------------------------- */

#define SCB ((volatile SCB_Type *) 0xE000ED00 )

/* --------------------------------------------------------------------------------------------------- */
/* ------------------------------- USART REGISTERS Definition Structure ------------------------------ */
/* --------------------------------------------------------------------------------------------------- */

typedef struct{

    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;

}USART_t;

/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- USART Peripheral Definition --------------------------------- */
/* --------------------------------------------------------------------------------------------- */

#define USART1 ( ( volatile USART_t *) 0x40013800 )


/* --------------------------------------------------------------------------------------------------- */
/* ------------------------------- AFIO REGISTERS Definition Structure ------------------------------- */
/* --------------------------------------------------------------------------------------------------- */

typedef struct
{
	volatile uint32_t EVCR ;        /* Event control register                          */
	volatile uint32_t MAPR ;        /* SYSCFG memory remap register                    */
	volatile uint32_t EXTICR[4] ;   /*SYSCFG external interrupt configuration register */
	uint32_t Reserved1;             /* offset                                          */
	volatile uint32_t MAPR2 ;       /* AF remap and debug I/O configuration register2  */

}AFIO_RegDef_t;


/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- AFIO Peripheral Definition ---------------------------------- */
/* --------------------------------------------------------------------------------------------- */
#define 	AFIO            	    ((AFIO_RegDef_t * )(AFIO_BASE_ADDRESS))


/* --------------------------------------------------------------------------------------------------- */
/* ------------------------------- TIMER REGISTERS Definition Structure ------------------------------ */
/* --------------------------------------------------------------------------------------------------- */

typedef struct
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t RCR;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t BDTR;
	uint32_t DCR;
	uint32_t DMAR;
}TIM1_REG_t;


/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- TIMER Peripheral Definition --------------------------------- */
/* --------------------------------------------------------------------------------------------- */

#define TIMER1 				((TIM1_REG_t*)(TIMER1_BASE_ADDRESS))

/* --------------------------------------------------------------------------------------------------- */
/* ------------------------------- GPIO REGISTERS Definition Structure ------------------------------- */
/* --------------------------------------------------------------------------------------------------- */

typedef struct
{
    volatile uint32_t GPIO_CR[2];
    volatile uint32_t GPIO_IDR;
    volatile uint32_t GPIO_ODR;
    volatile uint32_t GPIO_BSRR;
    volatile uint32_t GPIO_BRR;
    volatile uint32_t GPIO_LCKR;
} GPIO_REG_t;

/* --------------------------------------------------------------------------------------------- */
/* ------------------------------- GPIO Peripheral Definition ---------------------------------- */
/* --------------------------------------------------------------------------------------------- */

#define GPIOA 		((GPIO_REG_t *)GPIOA_BASE_ADDRESS)
#define GPIOB 		((GPIO_REG_t *)GPIOB_BASE_ADDRESS)
#define GPIOC 		((GPIO_REG_t *)GPIOC_BASE_ADDRESS)

#endif
