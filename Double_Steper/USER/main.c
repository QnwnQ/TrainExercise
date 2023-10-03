#include "stm32f10x.h" // Device header
#include "Step.h"
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "math.h"
uint8_t Dir1=0; 
float Angle1=0;
uint8_t Dir2=0; 
float Angle2=0;


FlagStatus ControlFlag;

uint8_t i ;
//上电机Dir（从屏幕方向看去）:0:逆时针,1:顺时针
//下电机Dir（俯视）:			0:顺时针，1逆时针

void FeatureShow(void)
{
	OLED_ShowSignedNum(2, 1, (int32_t)Feature.Step1_Angle, 3);
	OLED_ShowNum(2, 6, (uint32_t)( fabs(Feature.Step1_Angle) * 10 ) % 10, 1);
	OLED_ShowSignedNum(4, 1, (int32_t)Feature.Step2_Angle, 3);
	OLED_ShowNum(4, 6, (uint32_t)( fabs(Feature.Step2_Angle) * 10 ) % 10, 1);
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Step_Init();
	OLED_Init();
	KEY_Init();
	Delay_ms(1000);

	OLED_ShowString(1, 1, "Step1_Angle:");
	OLED_ShowString(2, 1, " 000.0");
	OLED_ShowString(3, 1, "Step2_Angle:");
	OLED_ShowString(4, 1, " 000.0");
	
	while (1)
	{
		i = KEY_Scan();
		FeatureShow();
		if(ControlFlag == SET){
			
		
		Step1_SetAngle(Dir1, Angle1);
			
		Step2_SetAngle(Dir2, Angle2);
		
		Delay_ms(1000);
		ControlFlag = RESET;
		}
	}
}
