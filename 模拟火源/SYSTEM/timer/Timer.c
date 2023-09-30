#include "stm32f10x.h"                  // Device header



void Timer_Init(void)
{
	//����TIMʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//����TIMʱ��Դ
	TIM_InternalClockConfig(TIM2);
	
	//TIM��ʼ�����ṹ������ʱ����Ԫ����Ƶ72MHz����ʱ������Ƶ�ʣ�1 / ��100*720�� = 1 kHz
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 100-1;		//����ֵ
		TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;	//Ԥ��Ƶ
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 5;//�߼���ʱ����Ч
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//�����ʼ�������ı�־λ
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	//ʹ���жϿ���
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//��ʼ��NVIC������Ϊ�����ж�
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStructure);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2, ENABLE);
	
}



//�ж�ִ�к���д��key.c�ļ���
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		
//		
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//		
//	}
//}






