/*******************************************************************/
/*  Author : Mohammed Gaafar                                       */
/*  Date : 7 / 5 / 2023                                            */
/*  Version : V1.0                                                 */
/*******************************************************************/

/*==============================================================================================================================================
 * INCLUDES SECTION START
 *==============================================================================================================================================*/
#include <stdint.h>
#include "../Library/STM32F103xx.h"
#include "../Library/ErrType.h"
#include "../Inc/NVIC_Private.h"
#include "../Inc/NVIC_Interface.h"
#include "../Library/Config.h"
/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/


/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/


/**
 * @brief Initialize the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function initializes the NVIC, enabling it to handle interrupts with the preconfigured Groub and sub priority system.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t NVIC_Init(void){
    SCB->AIRCR = NVIC_Priority_Grouping;
	return OK;
}

/**
 * @brief Enable a specific interrupt in the NVIC.
 *
 * @param Copy_u8InterruptNumber The interrupt number to enable eg. NVIC_EXTI0, NVIC_USART1.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t NVIC_EnableInterrupt(uint8_t Copy_u8InterruptNumber){
    ERRORS_t Local_enumState = NOK;
    if(Copy_u8InterruptNumber >=0 && Copy_u8InterruptNumber <=32){
        NVIC_ISER[0] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else if(Copy_u8InterruptNumber >=32 && Copy_u8InterruptNumber <=59){
        Copy_u8InterruptNumber -= 32;
        NVIC_ISER[1] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else{
        Local_enumState = OUT_OF_RANGE;
    }
    return Local_enumState;
}




/**
 * @brief Disable a specific interrupt in the NVIC.
 *
 * @param Copy_u8InterruptNumber The interrupt number to disable. eg. NVIC_EXTI0, NVIC_USART1.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t NVIC_DisableInterrupt(uint8_t Copy_u8InterruptNumber){
    ERRORS_t Local_enumState = NOK;
    if(Copy_u8InterruptNumber >=0 && Copy_u8InterruptNumber <=32){
        NVIC_ICER[0] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else if(Copy_u8InterruptNumber >=32 && Copy_u8InterruptNumber <=59){
        Copy_u8InterruptNumber -= 32;
        NVIC_ICER[1] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else{
        Local_enumState = OUT_OF_RANGE;
    }
    return Local_enumState;
}

/**
 * @brief Set the pending flag for a specific interrupt in the NVIC.
 *
 * @param Copy_u8InterruptNumber The interrupt number for which to set the pending flag. eg. NVIC_EXTI0, NVIC_USART1.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t NVIC_SetPendingFlag(uint8_t Copy_u8InterruptNumber){
    ERRORS_t Local_enumState = NOK;
    if(Copy_u8InterruptNumber >=0 && Copy_u8InterruptNumber <=32){
        NVIC_ISPR[0] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else if(Copy_u8InterruptNumber >=32 && Copy_u8InterruptNumber <=59){
        Copy_u8InterruptNumber -= 32;
        NVIC_ISPR[1] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else{
        Local_enumState = OUT_OF_RANGE;
    }
    return Local_enumState;
}

/**
 * @brief Clear the pending flag for a specific interrupt in the NVIC.
 *
 * @param Copy_u8InterruptNumber The interrupt number for which to clear the pending flag. eg. NVIC_EXTI0, NVIC_USART1.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t NVIC_ClearPendingFlag(uint8_t Copy_u8InterruptNumber){
    ERRORS_t Local_enumState = NOK;
    if(Copy_u8InterruptNumber >=0 && Copy_u8InterruptNumber <=32){
        NVIC_ICPR[0] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else if(Copy_u8InterruptNumber >=32 && Copy_u8InterruptNumber <=59){
        Copy_u8InterruptNumber -= 32;
        NVIC_ICPR[1] = (1<<Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else{
        Local_enumState = OUT_OF_RANGE;
    }
    return Local_enumState;
}



/**
 * @brief Get the active flag status for a specific interrupt in the NVIC.
 *
 * @param Copy_u8InterruptNumber The interrupt number for which to check the active flag. eg. NVIC_EXTI0, NVIC_USART1.
 * @param[out] Copy_pu8ActiveFlag Pointer to store the active flag status.
 *
 * @return ERRORS_t status indicating success or failure.
 */
ERRORS_t NVIC_GetActiveFlag(uint8_t Copy_u8InterruptNumber,uint8_t *Copy_pu8ActiveFlag){
    ERRORS_t Local_enumState = NOK;
    if(Copy_u8InterruptNumber >=0 && Copy_u8InterruptNumber <=32){
        *Copy_pu8ActiveFlag = GET_BIT(NVIC_IABR[0],Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else if(Copy_u8InterruptNumber >=32 && Copy_u8InterruptNumber <=59){
        Copy_u8InterruptNumber -= 32;
        *Copy_pu8ActiveFlag = GET_BIT(NVIC_IABR[1],Copy_u8InterruptNumber);
        Local_enumState = OK;
    }
    else{
        Local_enumState = OUT_OF_RANGE;
    }
    return Local_enumState;
}

/**
 * @brief Set the priority for a specific interrupt in the NVIC.
 *
 * @param Copy_s8InterruptNumber The interrupt number to set the priority for. eg. NVIC_EXTI0, NVIC_USART1.
 * @param Copy_u8GroupPriority The group priority for the interrupt. eg. 0,1.
 * @param Copy_u8SubPriority The sub-priority for the interrupt. eg. 0,1,2,3.
 *
 * @return ERRORS_t status indicating success or failure.
 */

    //TODO : add conditions for wrong inputs of GROUP and SUB priority
ERRORS_t NVIC_SetIntPriority(int8_t Copy_s8InterruptNumber,uint8_t Copy_u8GroupPriority,uint8_t Copy_u8SubPriority){
    ERRORS_t Local_enumState = NOK;
    uint8_t Local_u8Priority = Copy_u8SubPriority|Copy_u8GroupPriority<<((NVIC_Priority_Grouping - 0x05FA0300)/256);
    /*  For internal Peripheral */
    //TODO: Test the software priority for internal peripherals
    if(Copy_s8InterruptNumber < 0 && Copy_s8InterruptNumber >=-6){
        if(Copy_s8InterruptNumber == NVIC_MEMORY_MANAGE || Copy_s8InterruptNumber == NVIC_BUS_FAULT || Copy_s8InterruptNumber == NVIC_USAGE_FAULT){
            Copy_s8InterruptNumber += 3;
            SCB->SHPR1 = Local_u8Priority << (8 * Copy_s8InterruptNumber + 4); 
        }
        else if(Copy_s8InterruptNumber == NVIC_SV_CALL){
            Copy_s8InterruptNumber += 7;
            SCB->SHPR2 = Local_u8Priority << (8 * Copy_s8InterruptNumber + 4); 
        }
        else if(Copy_s8InterruptNumber == NVIC_SYSTICK || Copy_s8InterruptNumber == NVIC_PEND_SV){
            Copy_s8InterruptNumber += 8;
            SCB->SHPR3 = Local_u8Priority << (8 * Copy_s8InterruptNumber + 4); 
        }
    }
    /*  For External Peripheral */
    else if(Copy_s8InterruptNumber >= 0 && Copy_s8InterruptNumber <=59){
        NVIC_IPR[Copy_s8InterruptNumber] = Local_u8Priority << 4;
			Local_enumState = OK	;
    }
    else{
        Local_enumState = OUT_OF_RANGE;
    }
    SCB->AIRCR = NVIC_Priority_Grouping;
	return Local_enumState;
}
