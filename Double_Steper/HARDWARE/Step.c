#include "stm32f10x.h"                  // Device header
#include "Step.h"
#include "Delay.h"

//旋转速度
uint32_t Speed = Speed_M;


//步进电机Dir和Stp引脚初始化
void Step_Init(void)
{
	RCC_APB2PeriphClockCmd(Step1_RCC_GPIO | Step2_RCC_GPIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = Step1_En | Step1_Dir | Step1_Stp  ;
	GPIO_Init(Step1_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Step2_En | Step2_Dir | Step2_Stp ;
	GPIO_Init(Step2_GPIO, &GPIO_InitStructure);
	
	GPIO_WriteBit(Step1_GPIO, Step1_En, Step1_EnMode);
	GPIO_WriteBit(Step2_GPIO, Step2_En, Step2_EnMode);
}

//步进电机1角度控制函数
void Step1_SetAngle(uint8_t Dir , float Angle)
{
	uint16_t PulseNum = (uint16_t)(Angle * MStep / MotType);
	
	if( Dir )
		GPIO_ResetBits(Step1_GPIO, Step1_Dir);
	else 
		GPIO_SetBits(Step1_GPIO, Step1_Dir);
	

	for(uint16_t PulseNumCount = 0 ;PulseNumCount < PulseNum; PulseNumCount++)
	{
		GPIO_SetBits(Step1_GPIO, Step1_Stp);
		Delay_us(Speed);
		GPIO_ResetBits(Step1_GPIO, Step1_Stp);	
		Delay_us(Speed);
	}
}
//步进电机2角度控制函数
void Step2_SetAngle(uint8_t Dir , float Angle)
{
	uint16_t PulseNum = (uint16_t)(Angle * MStep / MotType);
	
	if( Dir )
		GPIO_ResetBits(Step2_GPIO, Step2_Dir);
	else 
		GPIO_SetBits(Step2_GPIO, Step2_Dir);
	for(uint16_t PulseNumCount = 0 ;PulseNumCount < PulseNum; PulseNumCount++)
	{
		GPIO_SetBits(Step2_GPIO, Step2_Stp);
		Delay_us(Speed);
		GPIO_ResetBits(Step2_GPIO, Step2_Stp);	
		Delay_us(Speed);
	}
}