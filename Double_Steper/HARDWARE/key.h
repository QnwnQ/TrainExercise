/************************头文件包含*************************/
#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header
/**********************************************************/


typedef struct{
	double Step1_Angle;
	double Step2_Angle;
}Feature_TypeDef;

extern Feature_TypeDef Feature;


/*******************************宏定义************************************/

#define KEY0_RCC_GPIO 				RCC_APB2Periph_GPIOA
#define KEY0_GPIO					GPIOA
#define KEY0 						GPIO_ReadInputDataBit(KEY0_GPIO,KEY0_GPIO_Pin)
#define KEY0_GPIO_Pin				GPIO_Pin_0

#define KEY1_RCC_GPIO 				RCC_APB2Periph_GPIOA
#define KEY1_GPIO					GPIOA
#define KEY1 						GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_Pin)
#define KEY1_GPIO_Pin				GPIO_Pin_1

#define KEY2_RCC_GPIO 				RCC_APB2Periph_GPIOB
#define KEY2_GPIO					GPIOB
#define KEY2 						GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_Pin)
#define KEY2_GPIO_Pin				GPIO_Pin_1

#define KEY3_RCC_GPIO 				RCC_APB2Periph_GPIOB
#define KEY3_GPIO					GPIOB
#define KEY3 						GPIO_ReadInputDataBit(KEY3_GPIO,KEY3_GPIO_Pin)
#define KEY3_GPIO_Pin				GPIO_Pin_0

#define MotType 					(float)1.8	//步进角
/**************************************************************************/


/*******************************模块函数************************************/
void KEY_Init(void) ;					//初始化函数
uint8_t KEY_Scan(void);

/**************************************************************************/




#endif
