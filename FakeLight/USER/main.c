#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "led.h"
#include "Timer.h"
#include "AD.h"

#define Background_Calibration_Time (uint8_t)100	//背景校准采集次数
#define AD_lasting_Time (uint16_t)2000				//持续照射门坎时间


uint16_t ADValue;									//当前亮度
uint16_t AD_BackgroundValue = 1000;					//背景亮度

float Voltage;										//对应电压
uint32_t AD_lasting ;								//持续照射时间
FlagStatus AD_Flag;

//外设初始化
void Project_All_Init(void)
{
	AD_Init();
	OLED_Init();
	LED_Init();
	Timer_Init();
}


//OLED显示菜单
void OLED_MeunShow(void)
{
	OLED_ShowString(1, 1, "Lowest: 0000");
	OLED_ShowString(2, 1, "ADValue:0000");
	OLED_ShowString(3, 1, "Voltage:0.00V");
}


//OLED实时显示
void OLED_VoltageShow(void)
{
	ADValue = AD_GetValue();
	Voltage = (float)ADValue / 4095 * 3.3;
	OLED_ShowNum(1, 9, AD_BackgroundValue, 4);
	OLED_ShowNum(2, 9, ADValue, 4);
	OLED_ShowNum(3, 9, Voltage, 1);
	OLED_ShowNum(3, 11, (uint16_t)(Voltage * 100) % 100, 2);
}


//背景校准函数
void Background_Calibration(void)
{
	uint8_t i = 0;
	while (i++ < Background_Calibration_Time)
	{
		if (AD_GetValue() < AD_BackgroundValue)
			AD_BackgroundValue = AD_GetValue();
		Delay_ms((uint32_t)(1000 / Background_Calibration_Time));
	}
}


//主循环
int main(void)
{
	Project_All_Init();
	OLED_MeunShow();
	Delay_ms(2000);
	Background_Calibration();
	while (1)
	{
		OLED_VoltageShow();
		Delay_ms(500);
	}
}



//定时器中断函数，1KHz采集
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		if (AD_GetValue() < AD_BackgroundValue-100 && AD_Flag == RESET)
		{
			if (AD_lasting < AD_lasting_Time)
				AD_lasting ++;
			else
				AD_Flag = SET;
		}
		else if (AD_Flag == SET)
		{
			AD_lasting = 0;
			LED0_Turn();
			
			AD_Flag = RESET;
			while (AD_GetValue() < AD_BackgroundValue -100)OLED_VoltageShow();
			Background_Calibration();
		}
		else
			AD_lasting = 0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}