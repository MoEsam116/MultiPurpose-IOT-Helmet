/*
 ******************************************************************************
 * @file           : EXTI_Private.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Nov 11, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef EXTI_INC_EXTI_PRIVATE_H_
#define EXTI_INC_EXTI_PRIVATE_H_

/*==============================================================================================================================================
 * PRIVATE DEFINES SECTION
 *==============================================================================================================================================*/
#define EXTI_MAX_NUMBER		20U


/*==============================================================================================================================================
 * PRIVATE FUNCTIONS SECTION
 *==============================================================================================================================================*/


/**
 * @fn 			: _eClearPendingFlag(EXTI_LINE_t)
 * @brief 		: THIS FUNCTION CLEARS THE CORRESPONDING PENDING FLAG
 *
 * @param[in] 	: EXTILine		=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 								CHECK FOR OPTIONS @EXTI_LINE_t
 * @return		: ERROR STATUS
 * @note 		: PRIVATE FUNCTION
 */
static ERRORS_t _eClearPendingFlag( EXTI_LINE_t EXTILine ) ;


/**
 * @fn 			: _eISPendingFlagSet(EXTI_LINE_t, EXTI_PFLAG_t*)
 * @brief 		: THIS FUNCTION CHECKS IF PENDING BIT IS SET OR NOT
 *
 * @param[in] 	: EXTILINE					=> EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 											CHECK FOR OPTIONS @EXTI_LINE_t
 * @param[out] 	: Copy_pPendingFlagStatus	=> RETURN TO THE USER THE STATE OF THE PENDING FLAG
 * @return		: ERROR STATUS
 * @note		: PRIVATE FUNCTION
 */
static ERRORS_t _eISPendingFlagSet( EXTI_LINE_t EXTILine , EXTI_PFLAG_t * Copy_pPendingFlagStatus ) ;


#endif /* EXTI_INC_EXTI_PRIVATE_H_ */
