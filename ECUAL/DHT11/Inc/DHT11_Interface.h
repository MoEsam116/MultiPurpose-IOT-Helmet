/*
 ******************************************************************************
 * @file           : DHT11_Interface.h
 * @Author         : Mohammed Ayman Shalaby
 * @brief          : Main program body
 * @Date           : Nov 15, 2023
 ******************************************************************************
 * @attention
 ******************************************************************************
 */
#ifndef DHT11_INTERFACE_H_
#define DHT11_INTERFACE_H_

/*==============================================================================================================================================
 * PROTOTYPES SECTION
 *==============================================================================================================================================*/

/**
 * @fn 		: HDHT11_eInit(EXTI_LINE_t, Port_t)
 * @brief 	: THIS FUNCTION INITIALIZES DHT11 SENSOR FOR THE USED DATA LINE ON WHICH PORT & WHAT EXTI LINE WILL BE USED
 *
 * @param 	: EXTILine		=> EXTI LINE CHOOSEN BY USER ( ALSO EQUIVELANT TO PIN NUMBER ) CHECK FOR OPTIONS @EXTI_LINE_t
 * @param   : PortNumber	=> PORT NUMBER CHOOSEN TO WHICH EXTI CIRCUIT WILL DETECT CHANGES
 * @return	: ERROR STATUS
 * @note	: YOU SHOULD ENABLE AFIO & GPIO FOR THE CHOOSEN PORT FOR EX. IF YOU CHOOSE PORTA YOU HAVE TO ENABLE GPIOA
 * 				THROUGH RCC REGISTERS BEFORE CALLING THIS FUNCION
 */
ERRORS_t HDHT11_eInit(EXTI_LINE_t EXTILine, PORT_t PortNumber);

/**
 * @fn 			: HDHT11_eGetTempHumidity(float_t*, float_t*)
 * @brief 		: THIS FUNCTION READS TEMPERATURE & HUMIDITY FROM DHT11 SENSOR
 *
 * @param[out]  : Copy_pf32Temp		=> RETURN TO THE USER TEMPERATURE VALUE IN CELSIUS
 * @param[out]	: Copy_pf32Humidity	=> RETURN TO THE USER HUMIDITY VALUE IN PERCENTAGE
 * @return		: ERROR STATUS
 */
ERRORS_t HDHT11_eGetTempHumidity(float *Copy_pf32Temp, float *Copy_pf32Humidity);

#endif /* DHT11_INTERFACE_H_ */
