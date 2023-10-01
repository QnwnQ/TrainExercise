#ifndef __STEP_H
#define __STEP_H
#include "stm32f10x.h"                  // Device header

#define Step_En GPIO_Pin_0
#define Step_Stp GPIO_Pin_1
#define Step_Dir GPIO_Pin_2

void Step_Init(void);
void Step_SetAngle(uint8_t Dir, uint16_t Angle);
void Step_SetSpeed(uint8_t Dir, uint16_t Speed);

#endif