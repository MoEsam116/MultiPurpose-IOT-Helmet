/*
 ******************************************************************************
 * @file           : EXTI_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : EXTI COMPONENT INTERFACE FILE
 * @Date           : Nov 11, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef EXTI_INC_EXTI_INTERFACE_H_
#define EXTI_INC_EXTI_INTERFACE_H_


/*==============================================================================================================================================
 * DEFINES & ENUMS SECTION
 *==============================================================================================================================================*/

/**
 * @enum	: @EXTI_LINE_t
 * @brief 	: SPECIFIES EXTI LINES AVAILABLE TO ENABLE
 *
 */
typedef enum
{
	EXTI_LINE_0 = 0           		,  /**< EXTI_LINE_0 */
	EXTI_LINE_1 	         	    ,  /**< EXTI_LINE_1 */
	EXTI_LINE_2		          		,  /**< EXTI_LINE_2 */
	EXTI_LINE_3               		,  /**< EXTI_LINE_3 */
	EXTI_LINE_4               		,  /**< EXTI_LINE_4 */
	EXTI_LINE_5               		,  /**< EXTI_LINE_5 */
	EXTI_LINE_6               		,  /**< EXTI_LINE_6 */
	EXTI_LINE_7               		,  /**< EXTI_LINE_7 */
	EXTI_LINE_8               		,  /**< EXTI_LINE_8 */
	EXTI_LINE_9     		  		,  /**< EXTI_LINE_9 */
	EXTI_LINE_10    		  		,  /**< EXTI_LINE_10 */
	EXTI_LINE_11  			  		,  /**< EXTI_LINE_11 */
	EXTI_LINE_12   			  		,  /**< EXTI_LINE_12 */
	EXTI_LINE_13   			  		,  /**< EXTI_LINE_13 */
	EXTI_LINE_14   	 		  		,  /**< EXTI_LINE_14 */
	EXTI_LINE_15    		  		,  /**< EXTI_LINE_15 */
	EXTI_LINE_16_PVD_OUTPUT   		,  /**< EXTI_LINE_16_PVD_OUTPUT */
	EXTI_LINE_17_RTC_ALARM_EV 		,  /**< EXTI_LINE_17_RTC_ALARM_EV */
	EXTI_LINE_18_USB_WAKEUP_EV		,  /**< EXTI_LINE_18_USB_WAKEUP_EV */
	EXTI_LINE_19_ETHERNET_WAKEUP_EV    /**< EXTI_LINE_19_ETHERNET_WAKEUP_EV */

}EXTI_LINE_t;

typedef enum
{
	EXTI_TRIGGER_FALLING = 0 ,
	EXTI_TRIGGER_RISING		 ,
	EXTI_TRIGGER_ON_CHANGE	 ,
}EXTI_TRIGGER_t;

typedef enum
{
	EXTI_PFLAG_SET 		= 1 ,
	EXTI_PFLAG_RESET	= 0
}EXTI_PFLAG_t;


/*==============================================================================================================================================
 * PROTOTYPES SECTION
 *==============================================================================================================================================*/

/**
 * @fn	 	: MEXTI_eEnableEXTILine(EXTI_LINE_t, EXTI_TRIGGER_t)
 * @brief 	: THIS FUNCTION ENABLES EXTI ON A SPECIFIC LINE WITH A SPECIFIC TRIGGER SELECTED
 *
 * @param   : EXTILine		=> EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 								CHECK FOR OPTIONS @EXTI_LINE_t
 * @param 	: EXTITrigger	=> EXTI TRIGGER SELECTION TO ALLOW EXTI CIRCIUT TO DETECT IT
 * 								CHECK FOR OPTIONS &EXTI_TRIGGER_t
 * @return	: ERROR STATUS
 */
ERRORS_t MEXTI_eEnableEXTILine( EXTI_LINE_t EXTILine , EXTI_TRIGGER_t EXTITrigger ) ;

/**
 * @fn 			: MEXTI_eDisableEXTILine(EXTI_LINE_t)
 * @brief 		: THIS FUNCTION DISABLES EXTI LINE GENERATION OF INTERRUPT REQUEST
 *
 * @param[in] 	: EXTILine		=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 									CHECK FOR OPTIONS @EXTI_LINE_t
 * @return		: ERROR STATUS
 */
ERRORS_t MEXTI_eDisableEXTILine( EXTI_LINE_t EXTILine ) ;

/**
 * @fn 			: MEXTI_SetCallBack(EXTI_LINE_t, void(*)(void))
 * @brief 		: THIS FUNCTION SETS CALL BACK FUNCTION TO INVOKE WHEN INTERRUPT REQUEST IS OCCURED
 *
 * @param[in] 	: EXTILine 				=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 										CHECK FOR OPTIONS @EXTI_LINE_t
 * @param[in] 	: Copy_pvCallBackFunc	=>  CALL BACK FUNCTION TO INVOKE WHEN INTERRUT IS REQUESTED
 * @return		: ERROR STATUS
 */
ERRORS_t MEXTI_SetCallBack( EXTI_LINE_t EXTILine , void(*Copy_pvCallBackFunc)(void) ) ;

/**
 * @fn	 		: MEXTI_eChangeTrigger(EXTI_LINE_t, EXTI_TRIGGER_t)
 * @brief 		: THIS FUNCTION CHANGES TRIGGER SELECTION TO WHICH EXTI CIRCUIT DETECT
 *
 * @param[in]	: EXTILine			=>  EXTI LINE SPECIFIED TO ENABLE IT TO GENERATE INTERRUPT REQUEST
 * 										CHECK FOR OPTIONS @EXTI_LINE_t
 * @param[in] 	: TriggerSelection	=> EXTI TRIGGER SELECTION TO ALLOW EXTI CIRCIUT TO DETECT IT
 * 										CHECK FOR OPTIONS &EXTI_TRIGGER_t
 * @return		: ERROR STATUS
 */
ERRORS_t MEXTI_eChangeTrigger( EXTI_LINE_t EXTILine , EXTI_TRIGGER_t TriggerSelection ) ;

#endif /* EXTI_INC_EXTI_INTERFACE_H_ */
