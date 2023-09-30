#include "stm32f10x.h"                  // Device header
#include "led.h"

uint32_t AD_lasting = 0;
FlagStatus AD_Flag;

void AD_Init(void)
{
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	//配置ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//GPIO配置
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//配置规则组
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	//ADC配置
		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		
	ADC_Init(ADC1, &ADC_InitStructure);
	//ADC使能
	ADC_Cmd(ADC1, ENABLE);
	//ADC校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
}

//软件触发采集函数
uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
	
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		if(AD_GetValue() < 1000 && AD_Flag == RESET)
		{
			if(AD_lasting < 2000)
				AD_lasting++;
			else
				AD_Flag = SET;
		}
		else if(AD_Flag == SET)
		{
		AD_lasting = 0;
		LED0_Turn();
		AD_Flag = RESET;
		while(AD_GetValue() < 1000);
		}
		else
		AD_lasting =0 ;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
	}
}
