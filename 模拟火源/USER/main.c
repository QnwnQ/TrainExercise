#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "led.h"
#include "Timer.h"
#include "AD.h"



uint16_t ADValue;
float Voltage;

int main(void)
{
	//初始化列表
	AD_Init();
	OLED_Init();
	LED_Init();
	Timer_Init();
	
	OLED_ShowString(1,1,"Name:Lei Zuhao");
	OLED_ShowString(2,1,"ADValue:0000");
	OLED_ShowString(3,1,"Voltage:0.00V");
	while(1)
	{	
		ADValue =  AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3.3;
		OLED_ShowNum(2,9,ADValue,4);
		OLED_ShowNum(3,9,Voltage,1);
		OLED_ShowNum(3,11, (uint16_t)(Voltage * 100) % 100, 2);
		Delay_ms(500);
	}

}
