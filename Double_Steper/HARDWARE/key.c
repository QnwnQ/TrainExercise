#include "stm32f10x.h"                  // Device header
#include "key.h"
#include "Delay.h"
#include "Step.h"




Feature_TypeDef Feature;


/*******************************按键初始化函数************************************/
void KEY_Init(void)
{
	//时钟使能
	RCC_APB2PeriphClockCmd(KEY0_RCC_GPIO | KEY1_RCC_GPIO, ENABLE);
	
	//GPIO配置部分
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode 	= 	GPIO_Mode_IPU;//上拉输入模式
		GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin 	= 	KEY0_GPIO_Pin ;
	GPIO_Init(KEY0_GPIO, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin 	= 	KEY1_GPIO_Pin ;
	GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin 	= 	KEY2_GPIO_Pin ;
	GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin 	= 	KEY3_GPIO_Pin ;
	GPIO_Init(KEY3_GPIO, &GPIO_InitStructure);


}
/********************************************************************************/



uint8_t KEY_Scan(void)
{
	
	if(KEY0 == 0) 		
	{
		Delay_ms(2);
		Step1_SetAngle(0, 1.8);
		Feature.Step1_Angle += MotType;
		Delay_ms(2);
		return 1 ;
	}
	else if(KEY1 == 0) 	
	{
		Delay_ms(2);
		Step1_SetAngle(1, 1.8);
		Feature.Step1_Angle -= MotType;
		Delay_ms(2);
		return 2 ;
	}
	else if(KEY2 == 0) 	
	{
		Delay_ms(2);
		Step2_SetAngle(0, 1.8);
		Feature.Step2_Angle += MotType;
		Delay_ms(2);
		return 3 ;
	}
	else if(KEY3 == 0) 	
	{
		Delay_ms(2);
		Step2_SetAngle(1, 1.8);
		Feature.Step2_Angle -= MotType;
		Delay_ms(2);
		return 4 ;
	}
	return 0;
}














