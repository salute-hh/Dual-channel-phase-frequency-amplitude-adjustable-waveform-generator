#ifndef __KEY44_H
#define __KEY44_H
#include "sys.h"

//8������ 4��Ϊ�� 4��Ϊ��
//������˿ڶ���
#define X1_GPIO_PORT GPIOB
#define X2_GPIO_PORT GPIOB
#define X3_GPIO_PORT GPIOB
#define X4_GPIO_PORT GPIOB
//������˿ڶ���
#define Y1_GPIO_PORT GPIOB
#define Y2_GPIO_PORT GPIOD
#define Y3_GPIO_PORT GPIOC
#define Y4_GPIO_PORT GPIOC

//��������Ŷ���
#define X1_GPIO_PIN GPIO_Pin_7
#define X2_GPIO_PIN GPIO_Pin_6
#define X3_GPIO_PIN GPIO_Pin_5
#define X4_GPIO_PIN GPIO_Pin_4

//���������Ŷ���
#define Y1_GPIO_PIN GPIO_Pin_3
#define Y2_GPIO_PIN GPIO_Pin_2
#define Y3_GPIO_PIN GPIO_Pin_12
#define Y4_GPIO_PIN GPIO_Pin_11

//�����ʱ�Ӷ���
#define X1_RCC RCC_APB2Periph_GPIOB
#define X2_RCC RCC_APB2Periph_GPIOB
#define X3_RCC RCC_APB2Periph_GPIOB
#define X4_RCC RCC_APB2Periph_GPIOB

//������ʱ�Ӷ���
#define Y1_RCC RCC_APB2Periph_GPIOB
#define Y2_RCC RCC_APB2Periph_GPIOD
#define Y3_RCC RCC_APB2Periph_GPIOC
#define Y4_RCC RCC_APB2Periph_GPIOC

void KEY_Init44(void);
int KEY_Scan44(void);
#endif
