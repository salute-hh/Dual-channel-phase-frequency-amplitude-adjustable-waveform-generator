#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	    
#include "stm32f10x.h"	

 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DAC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
								    
#define DAC_DHR12RD_Address  (u32)&(DAC->DHR12R1)   //DAC通道1输出寄存器地址
#define DAC_DHR12LD_Address  (u32)&(DAC->DHR12R2)   //DAC通道2输出寄存器地址
#define pi 3.142
#define n 36       //数组数据量
#define f 5000     //推荐频率 37Hz--12KHz，TIM_Period值推荐大于200，想改频率的话，改tim的值最高2.5MHz
#define k 0.7  //占空比  用于方波
#define u 2		 //恒定电压
void Dac1_Init(void);//回环模式初始化		 	 
void Dac1_Set_Vol(u16 vol);
void tim_init(void);
void dma_init(void);
void data_tri_init(void);
void data_sin_init(void);
void data_saw_init(void);
void data_squ_init(void);
void data_lin_init(void);
#endif

















