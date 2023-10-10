#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "led.h"
#include "Timer.h"
#include "AD.h"

#define Background_Calibration_Time (uint8_t)100	//����У׼�ɼ�����
#define AD_lasting_Time (uint16_t)2000				//���������ſ�ʱ��


uint16_t ADValue;									//��ǰ����
uint16_t AD_BackgroundValue = 1000;					//��������

float Voltage;										//��Ӧ��ѹ
uint32_t AD_lasting ;								//��������ʱ��
FlagStatus AD_Flag;

//�����ʼ��
void Project_All_Init(void)
{
	AD_Init();
	OLED_Init();
	LED_Init();
	Timer_Init();
}


//OLED��ʾ�˵�
void OLED_MeunShow(void)
{
	OLED_ShowString(1, 1, "Lowest: 0000");
	OLED_ShowString(2, 1, "ADValue:0000");
	OLED_ShowString(3, 1, "Voltage:0.00V");
}


//OLEDʵʱ��ʾ
void OLED_VoltageShow(void)
{
	ADValue = AD_GetValue();
	Voltage = (float)ADValue / 4095 * 3.3;
	OLED_ShowNum(1, 9, AD_BackgroundValue, 4);
	OLED_ShowNum(2, 9, ADValue, 4);
	OLED_ShowNum(3, 9, Voltage, 1);
	OLED_ShowNum(3, 11, (uint16_t)(Voltage * 100) % 100, 2);
}


//����У׼����
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


//��ѭ��
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



//��ʱ���жϺ�����1KHz�ɼ�
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