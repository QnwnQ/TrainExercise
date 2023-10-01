#include "stm32f10x.h" // Device header
#include "Step.h"
#include "Delay.h"
#include "OLED.h"

uint16_t Speed = 1;//    （0-150）（r/min）
uint8_t Dir=0; 
uint16_t Angle=90;
FlagStatus ControlFlag;
int main(void)
{

	Step_Init();
	OLED_Init();
	Delay_ms(1000);

	OLED_ShowString(1, 1, "Speed:");
	OLED_ShowString(2, 1, "Dir:");
	OLED_ShowNum(1, 7, Speed, 3);
	OLED_ShowNum(2, 5, Dir, 1);
	//Step_SetSpeed(Dir, Speed);
	//Step_SetAngle(Dir, 90);
	while (1)
	{
		if(ControlFlag == SET){
		Step_SetAngle(Dir, Angle);
		Delay_ms(1000);
		ControlFlag = RESET;
		}
	}
}
