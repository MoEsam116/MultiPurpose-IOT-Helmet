/*******************************************************************************
 * Filename              :   MQ5_Interface.h
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   Nov 4, 2023
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :   None
 **
 *******************************************************************************/
/************************ SOURCE REVISION LOG *********************************
 *
 *    Date    Version   Author             Description
 *  14/10/20   1.0.0   Mohamemd Waleed   Initial Release.
 *
 *******************************************************************************/
#ifndef MQ5_INC_MQ5_INTERFACE_H_
#define MQ5_INC_MQ5_INTERFACE_H_

/*==============================================================================================================================================
 *                                                         Includes
 *==============================================================================================================================================*/
// uint16_t MQ5_u16GetR0(void);
/*==============================================================================================================================================
 *@fn           : MQ5_u16GetRatio
 *@brief        : This function used to get the Ratio of how much Air polluted to the clean Air
 *HINT          : The more the ratio the more the air is polluted
 *HINT          : The R0 of clean air is 6 and it has been measured in the first time the sensor is powered on
 *@paramter[in] : void
 *@retval       : Ratio : the ratio of how much Air polluted to the clean Air
 *==============================================================================================================================================*/
float MQ5_u16GetRatio(uint16_t MQR_Read);
#endif /* MQ5_INC_MQ5_INTERFACE_H_ */
