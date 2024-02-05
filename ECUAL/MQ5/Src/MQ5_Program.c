/*******************************************************************************
 * Filename              :   MQ5_Program.c
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
#include <stdint.h>
#include "../Inc/MQ5_Interface.h"
#include "../Inc/MQ5_Private.h"
#include "../../../MCAL/ADC/Inc/ADC_Interface.h"

extern ADC_Configs_t ADC_Configs;

/*==============================================================================================================================================
 *@fn           : MQ5_u16GetResistance
 *@brief      : Get the resistance of the sensor
 *@paramter[in]  : void
 *@retval u16Resistance
 *==============================================================================================================================================*/
/*uint16_t MQ5_u16GetR0(void)
{
	uint16_t RES[100]={0} , RS_Air=0 , sum=0;
	float RS =0;
	uint8_t Iterator =0 ;

	for(Iterator=0; Iterator < 100 ; Iterator ++)
	{
		ADC_u8StartSingleConv(&ADC_Configs, (uint16_t *)&RES[Iterator]);
		sum+=RES[Iterator];
	}
	RS = sum / 100;

	RS= (RS * (float)3.3) / (float)4096  ;

	RS_Air = (3.3 - RS) / RS ;

	R0 = (RS_Air / (float)6.5) ;

	return R0;

}*/
/*==============================================================================================================================================
 *@fn           : MQ5_u16GetRatio
 *@brief        : This function used to get the Ratio of how much Air polluted to the clean Air
 *HINT          : The more the ratio the more the air is polluted
 *HINT          : The R0 of clean air is 6 and it has been measured in the first time the sensor is powered on
 *@paramter[in] : void
 *@retval       : Ratio : the ratio of how much Air polluted to the clean Air
 *==============================================================================================================================================*/
float MQ5_u16GetRatio(uint16_t MQR_Read)
{
    /* variable to store RS Air & Ratio */
    float RS_Air = 0, Ratio = 0;

    /* change the RS value from digital to analog by multiplying it by 3.3 and dividing it by 4096 */
    float RS = (MQR_Read * 3.3) / 4096;

    /* Calculate RS Air */
    RS_Air = (3.3 - RS) / RS;

    /* Calculate Ratio */
    Ratio = ((RS_Air - R0) / R0) * 100;

    return (Ratio * (-1.0));
}
