/*
 ******************************************************************************
 * @file           : ErrType.h
 * @Author         :
 * @brief          : ERROR TYPES FILE
 * @Date           : May 8, 2023
 ******************************************************************************

 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Reg,Bit)  			 	(Reg |=(1<<Bit))
#define CLR_BIT(Reg,Bit)   				(Reg &= ~(1<<Bit))
#define TOGGLE_BIT(Reg,Bit)  			(Reg ^=(1<<Bit))
#define GET_BIT(Reg,Bit)   				((Reg >>Bit)&1)

#endif /* BIT_MATH_H_ */
