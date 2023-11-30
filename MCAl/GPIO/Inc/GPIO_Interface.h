/*******************************************************************************
 * Filename              :   GPIO_Interface.h
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   May 10, 2023
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
#ifndef GPIO_INCLUDE_GPIO_INTERFACE_H_
#define GPIO_INCLUDE_GPIO_INTERFACE_H_
typedef enum
{
    PORTA = 0,
    PORTB,
    PORTC,
} PORT_t;
typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15
} Pin_t;
typedef enum
{
    Input_Analog = 0,
    Floating_Input,
    Input_PU,
    Input_PD
} Input_Mode_t;
typedef enum
{
    PushPull = 0,
    OpenDrain,
    AFPP,
    AFOD
} Output_Mode_t;
typedef enum
{
    Input = 0,
    Output_10MHZ,
    Output_2MHZ,
    Output_50MHZ
} Mode_t;

typedef enum
{
    PinLow,
    PinHigh
} PinVal_t;

typedef struct
{
    PORT_t Port;
    Pin_t PinNum;
    Input_Mode_t InputMode;
    Output_Mode_t OutputMode;
    Mode_t Mode;
} Pin_Config_t;
/*
 * Prototype   : uint8_t GPIO_u8PinInit(const Pin_Config_t *PinConfig)
 * Description : Set Mode of a Pin
 * Arguments   : Pin_Config_t : PORT(PORTA , PORTB,PORTC)
 *                              PinNum(PIN1 ..... PIN15)
 *                              InputMode( Input_Analog ,Floating_Input,Input_PU,Input_PD)
 *                              OutputMode(  PushPull,OpenDrain,AFPP,AFOD)
 *                              Mode(Input,Output_10MHZ,Output_2MHZ,Output_50MHZ)
 * return      : uint8_t number used for error handling
 *			     OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8PinInit(const Pin_Config_t *PinConfig);
/*
 * Prototype   : uint8_t GPIO_u8SetPinValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal)
 * Description : Set Value of a Pin
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *               PinNum(PIN1 ..... PIN15)
 *               PinVal(PinHigh,PinLow)
 * return      : uint8_t number used for error handling
 *			     OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8SetPinValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal);
/*
 * Prototype   : uint8_t GPIO_u8TogglePinValue(PORT_t Port, Pin_t PinNum)
 * Description : Toggle Value of a Pin
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *          	 PinNum(PIN1 ..... PIN15)
 * return      : uint8_t number used for error handling
 * 			     OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8TogglePinValue(PORT_t Port, Pin_t PinNum);
/*
 * Prototype   : uint8_t GPIO_u8ReadPinValue(PORT_t Port, Pin_t PinNum, PinVal_t *PinVal)
 * Description : Read Value of a Pin
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *              PinNum(PIN1 ..... PIN15)
 * return      : uint8_t number used for error handling
 *                  OK(0) means no error,NOK(1) means Undefined PORT Argument
 */
uint8_t GPIO_u8ReadPinValue(PORT_t Port, Pin_t PinNum, PinVal_t *PinVal);
/*
 * Prototype   : void GPIO_u8SetFourPortValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal)
 * Description : Set Value of 4 Pins
 * Arguments   : PORT(PORTA , PORTB,PORTC)
 *               PinNum(PIN1 ..... PIN15)
 *               pinVal(0x00 to 0x0F)
 * return      : void
 */
void GPIO_u8SetFourPortValue(PORT_t Port, Pin_t PinNum, uint8_t PinVal);
#endif /* GPIO_INCLUDE_GPIO_INTERFACE_H_ */
