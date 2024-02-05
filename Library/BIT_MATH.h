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


/*Function Like Macro*/
/*Mapping between Two Ranges and Returns The Value in The Other Range*/
#define MAP(INPUT_MIN,INPUT_MAX,OUTPUT_MIN,OUTPUT_MAX,INPUT_VALUE)    ( ( ( ( (int32_t)INPUT_VALUE - (int32_t)INPUT_MIN ) * ( (int32_t)OUTPUT_MAX - (int32_t)OUTPUT_MIN ) ) / ( (int32_t)INPUT_MAX - (int32_t)INPUT_MIN ) ) + (int32_t)OUTPUT_MIN )
#endif /* BIT_MATH_H_ */
