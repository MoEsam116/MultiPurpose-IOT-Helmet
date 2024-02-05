
/*
 ******************************************************************************
 * @file           : AFIO_Interface.h
 * @Author         : Ibrahim Mohamed
 * @brief          : AFIO Interface File
 * @Date           : Aug 24, 2023
 ******************************************************************************
 */

#ifndef AFIO_INTERFACE_H_
#define AFIO_INTERFACE_H_

/* ---------------------------------------- ENUMS ---------------------------------------- */

typedef enum
{
	AFIO_PortA = 0,
	AFIO_PortB,
	AFIO_PortC,
	AFIO_PortD,
	AFIO_PortE,
	AFIO_PortF,
	AFIO_PortG,
	AFIO_PortH
} AFIO_Port_t;

typedef enum
{
	AFIO_EXTI0 = 0,
	AFIO_EXTI1,
	AFIO_EXTI2,
	AFIO_EXTI3,
	AFIO_EXTI4,
	AFIO_EXTI5,
	AFIO_EXTI6,
	AFIO_EXTI7,
	AFIO_EXTI8,
	AFIO_EXTI9,
	AFIO_EXTI10,
	AFIO_EXTI11,
	AFIO_EXTI12,
	AFIO_EXTI13,
	AFIO_EXTI14,
	AFIO_EXTI15,

} AFIO_EXTI_Line;

/* ---------------------------------------- MACROS ---------------------------------------- */

#define Max_EXTI_Line 16

#define Max_GPIO_Port 8

/**
 * @fn    : SYSCFG_SetEXTIPort
 * @brief : This Function Sets A Specific Port for A Specific External Interrupt Line
 * @param : EXTI_Line -> Options of All Available EXTI Lines From enum ( @EXTI_t )
 * @param : GPIO_PORT -> Options of All Available Ports From enum ( @GPIO_PORT_t )
 * @return: ErrorStatus to Indicate if function Worked Correctly or NOT
 */
uint8_t AFIO_U8SetEXTIPort(AFIO_EXTI_Line EXTI_Line, AFIO_Port_t GPIO_Port);

#endif /* AFIO_INTERFACE_H_ */
