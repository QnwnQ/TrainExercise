#ifndef __STEP_H
#define __STEP_H
#include "stm32f10x.h"                  // Device header

#define Step1_GPIO 		GPIOA
#define Step1_RCC_GPIO 	RCC_APB2Periph_GPIOA
#define Step1_En 		GPIO_Pin_10
#define Step1_Stp 		GPIO_Pin_9
#define Step1_Dir		GPIO_Pin_8
#define Step1_EnMode	Bit_SET

#define Step2_GPIO 		GPIOB
#define Step2_RCC_GPIO 	RCC_APB2Periph_GPIOB
#define Step2_En 		GPIO_Pin_12
#define Step2_Stp 		GPIO_Pin_13
#define Step2_Dir 		GPIO_Pin_15
#define Step2_EnMode	Bit_SET

#define MotType 		(float)1.8	//步进角
#define MStep 			(uint16_t)16//细分

#define Speed_H 		(uint32_t)500	//低速旋转
#define Speed_M 		(uint32_t)1000	//中速旋转
#define Speed_L 		(uint32_t)2000	//低速旋转

void Step_Init(void);
void Step1_SetAngle(uint8_t Dir, float Angle);
void Step2_SetAngle(uint8_t Dir, float Angle);

#endif