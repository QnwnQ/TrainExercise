#include "stm32f10x.h"                  // Device header
#include "Step.h"
#include "Delay.h"


//步进电机Dir和Stp引脚初始化
void Step_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Step_En | Step_Dir | Step_Stp ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, Step_En);
}

//步进电机速度控制函数
void Step_SetSpeed(uint8_t Dir , uint16_t Speed)
{
	if(Dir)
		GPIO_ResetBits(GPIOA, Step_Dir);
	else 
		GPIO_SetBits(GPIOA, Step_Dir);

	while(1)
	{
		if(Speed>=0.001)
		{
			GPIO_SetBits(GPIOA, Step_Stp);
			Delay_us( (uint32_t) ( 2500 / Speed ) );
			GPIO_ResetBits(GPIOA, Step_Stp);	
			Delay_us( (uint32_t) ( 2500 / Speed ) );
		}
	}
}

//步进电机角度控制函数
void Step_SetAngle(uint8_t Dir , uint16_t Angle)
{
	uint16_t PulseNum = (uint16_t)(Angle / 1.8);
	
	if( Dir )
		GPIO_ResetBits(GPIOA, Step_Dir);
	else 
		GPIO_SetBits(GPIOA, Step_Dir);
	

	for(uint16_t PulseNumCount = 0 ;PulseNumCount < PulseNum*16; PulseNumCount++)
	{
		GPIO_SetBits(GPIOA, Step_Stp);
		Delay_us(500);
		GPIO_ResetBits(GPIOA, Step_Stp);	
		Delay_us(500);
	}
	
	
	
}