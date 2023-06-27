#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	    
#include "stm32f10x.h"	

 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DAC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
								    
#define DAC_DHR12RD_Address  (u32)&(DAC->DHR12R1)   //DACͨ��1����Ĵ�����ַ
#define DAC_DHR12LD_Address  (u32)&(DAC->DHR12R2)   //DACͨ��2����Ĵ�����ַ
#define pi 3.142
#define n 36       //����������
#define f 5000     //�Ƽ�Ƶ�� 37Hz--12KHz��TIM_Periodֵ�Ƽ�����200�����Ƶ�ʵĻ�����tim��ֵ���2.5MHz
#define k 0.7  //ռ�ձ�  ���ڷ���
#define u 2		 //�㶨��ѹ
void Dac1_Init(void);//�ػ�ģʽ��ʼ��		 	 
void Dac1_Set_Vol(u16 vol);
void tim_init(void);
void dma_init(void);
void data_tri_init(void);
void data_sin_init(void);
void data_saw_init(void);
void data_squ_init(void);
void data_lin_init(void);
#endif

















