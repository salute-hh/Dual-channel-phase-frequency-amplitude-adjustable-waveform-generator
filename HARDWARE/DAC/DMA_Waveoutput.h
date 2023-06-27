#ifndef  __DMA_Waveoutput_H
#define  __DMA_Waveoutput_H
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/*******************�õ�����Դ************************/
//GPIOA_Pin_4��GPIOA_Pin_5
//��ʱ��2����ʱ��6  //�������ģʽ
//DMA2ͨ��3��4	    //ѭ������ģʽ
//DACͨ��1��2       //��ʱ������ģʽ
/**************************�������ṩ���Ҳ��;�ݲ�********************************/
/**************���Զ������ڲ��Σ�д�����ݵ�ַ��DMA���ɲ�����Ӧ����*******************/
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "math.h"

#define PI  3.1415926
#define Vref 3.3		//0.1~3.3V�ɵ�
#define Um  (Vref/2)
#define N 256

/********����Ҫ�Ĳ���ע�͵�����**********/
#define  Sine_WaveOutput_Enable
#define  SawTooth_WaveOutput_Enable


#define  SinWave   			0x00	//���Ҳ�
#define  SawToothWave   0x01	//��ݲ�
#define  Wave_Channel_1   0x00	//ͨ��1
#define  Wave_Channel_2   0x01	//ͨ��2


/***********���Ҳ���ʼ��***************/
//Wave1������1ѡ��
//Wave1_Fre������1Ƶ��
//NewState1������1ʹ��
//Wave2������2ѡ��
//Wave2_Fre������2Ƶ��
//NewState2������2ʹ��
void SineWave_Init(u8 Wave1,u16 Wave1_Fre,float um,u8 NewState1,u8 Wave2,u16 Wave2_Fre,float um1,u8 NewState2);//void SineWave_Init(u8 Wave1,u16 Wave1_Fre,u8 NewState1,u8 Wave2,u16 Wave2_Fre,u8 NewState2);
/************��̬���ò���Ƶ��*************/
//Wave_Channel��ͨ��ѡ��
//fre��Ƶ��
void Set_WaveFre( u8 Wave_Channel ,u16 fre);


#endif

