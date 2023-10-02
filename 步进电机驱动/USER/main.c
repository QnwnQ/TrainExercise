#include "stm32f10x.h" // Device header
#include "Step.h"
#include "Delay.h"
#include "OLED.h"

uint8_t Dir1=0; 
float Angle1=0;
uint8_t Dir2=0; 
float Angle2=0;
FlagStatus ControlFlag;

//上电机Dir（从屏幕方向看去）:0:逆时针,1:顺时针
//下电机Dir（俯视）:			0:顺时针，1逆时针

int main(void)
{

	Step_Init();
	OLED_Init();
	Delay_ms(1000);

	OLED_ShowString(1, 1, "Dir1:");
	OLED_ShowString(2, 1, "Step1:");
	OLED_ShowString(3, 1, "Dir2:");
	OLED_ShowString(4, 1, "Step2:");
	
	while (1)
	{
		if(ControlFlag == SET){
			
		
		Step1_SetAngle(Dir1, Angle1);
		Step2_SetAngle(Dir2, Angle2);
			
			
		Delay_ms(1000);
		ControlFlag = RESET;
		}
	}
}
