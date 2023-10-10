#include "stm32f10x.h"                  // Device header
#include "key.h"
#include "Delay.h"

void KEY_Init(void)
{
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//构建结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	//结构体成员设置
	GPIO_InitStructure.GPIO_Mode 	= 	GPIO_Mode_IPU;//上拉输入模式
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= 	GPIO_Pin_1 | GPIO_Pin_11;
	
	//初始化
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

uint8_t KEY_Scan(void)
{
	
	if(KEY0 == 0) 		
	{
		Delay_ms(20);
		while(KEY0 == 0);//长按无效，松开为止
		Delay_ms(20);
		return 1 ;
	}
	else if(KEY1 == 0) 	
	{
		Delay_ms(20);
		while(KEY1 == 0);//长按无效，松开为止
		Delay_ms(20);
		return 2 ;
	}
	return 0;
}


