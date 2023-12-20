/*
 ******************************************************************************
 * @file           : LDR_Interface.c
 * @Author         : Ibrahim Mohamed 
 * @Date           : Dec 7, 2023
 ******************************************************************************
 */


#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_


/**
 * @fn 		: LDR_Init
 * @brief 	: THIS FUNCTION INITIALIZES LDR SENSOR 
 * @param 	: Void
 * @return	: ERROR STATUS
 */
ERRORS_t LDR_Init(void);

/**
 * @fn 			: LDR_Read
 * @brief 		: THIS FUNCTION INITIALIZES LDR SENSOR 
 * @param[out]  : Copy_pu16LDR_Reading  =>  RETURN TO THE Reading of LDR Sensor
 * @return		: ERROR STATUS
 */
ERRORS_t LDR_Read(uint16_t* Copy_pu16LDR_Reading);

/**
 * @fn 			: LDR_Checking
 * @brief 		: THIS FUNCTION INITIALIZES LDR SENSOR 
 * @param 		: Copy_u16LDR_Reading  =>  THE Reading of LDR Sensor
 * @param[out]  : Copy_Light_Status  =>  RETURN TO THE Status of Light
 * @return		: ERROR STATUS
 */
ERRORS_t LDR_Checking(uint16_t Copy_u16LDR_Reading ,uint8_t * Copy_Light_Status );


#endif /* LDR_INTERFACE_H_ */
