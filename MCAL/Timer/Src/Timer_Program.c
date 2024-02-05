/*
 ******************************************************************************
 * @file           : Timer_Program.c
 * @Author         : Ibrahim Mohamed
 * @brief          : Timer Program File
 * @Date           : Oct 29, 2023
 ******************************************************************************
*/


#include <stdint.h>
#include "../../../Library/STM32F103xx.h"
#include "../../../Library/ErrType.h"

#include "../Inc/Timer_Interface.h"


/***********************************
 * @function 		:	Delay_ms
 * @brief			:	Delay Function in milliseconds
 * @parameter[in]	:	Time in milliseconds
 * @retval			:	Void
 * *********************************
 */
void Delay_ms(uint16_t ms)
{
	/* Setup the counter to 0 */
	TIMER1->CNT = 0;

	/* Setup the prescaler */
	TIMER1->PSC = 7200-1;

	/* initialize the Auto reload register value */
	TIMER1->ARR = (ms-1);

	/* Enable the counter & OPM */
	TIMER1->CR1 |= 0x9;

	/* Wait until CE-bit = 0 */
	while(TIMER1->CR1 & 1);

}




/***********************************
 * @function 		:	Delay_ms
 * @brief			:	Delay Function in Microseconds
 * @parameter[in]	:	Time in milliseconds
 * @retval			:	Void
 * *********************************
 */
void Delay_Ms(uint16_t Ms)
{
	/* Setup the counter to 0 */
	TIMER1->CNT = 0;

	/* Setup the prescaler */
	TIMER1->PSC = 72-1;

	/* initialize the Auto reload register value */
	TIMER1->ARR = (Ms-1);

	/* Enable the counter & OPM */
	TIMER1->CR1 |= 0x9;

	/* Wait until CE-bit = 0 */
	while(TIMER1->CR1 & 1);

}

