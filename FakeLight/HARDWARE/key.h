#ifndef __KEY_H
#define __KEY_H

#define KEY0 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)

#define KEY0_PRESS 1
#define KEY1_PRESS 2

void KEY_Init(void) ;
uint8_t KEY_Scan(void) ;

#endif
