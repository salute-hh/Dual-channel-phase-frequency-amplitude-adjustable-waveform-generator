#ifndef __KEY44_H
#define __KEY44_H
#include "sys.h"

//8个引脚 4个为行 4个为列
//行输出端口定义
#define X1_GPIO_PORT GPIOB
#define X2_GPIO_PORT GPIOB
#define X3_GPIO_PORT GPIOB
#define X4_GPIO_PORT GPIOB
//列输入端口定义
#define Y1_GPIO_PORT GPIOB
#define Y2_GPIO_PORT GPIOD
#define Y3_GPIO_PORT GPIOC
#define Y4_GPIO_PORT GPIOC

//行输出引脚定义
#define X1_GPIO_PIN GPIO_Pin_7
#define X2_GPIO_PIN GPIO_Pin_6
#define X3_GPIO_PIN GPIO_Pin_5
#define X4_GPIO_PIN GPIO_Pin_4

//列输入引脚定义
#define Y1_GPIO_PIN GPIO_Pin_3
#define Y2_GPIO_PIN GPIO_Pin_2
#define Y3_GPIO_PIN GPIO_Pin_12
#define Y4_GPIO_PIN GPIO_Pin_11

//行输出时钟定义
#define X1_RCC RCC_APB2Periph_GPIOB
#define X2_RCC RCC_APB2Periph_GPIOB
#define X3_RCC RCC_APB2Periph_GPIOB
#define X4_RCC RCC_APB2Periph_GPIOB

//列输入时钟定义
#define Y1_RCC RCC_APB2Periph_GPIOB
#define Y2_RCC RCC_APB2Periph_GPIOD
#define Y3_RCC RCC_APB2Periph_GPIOC
#define Y4_RCC RCC_APB2Periph_GPIOC

void KEY_Init44(void);
int KEY_Scan44(void);
#endif
