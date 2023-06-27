#ifndef  __DMA_Waveoutput_H
#define  __DMA_Waveoutput_H
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/*******************用到的资源************************/
//GPIOA_Pin_4、GPIOA_Pin_5
//定时器2、定时器6  //输出触发模式
//DMA2通道3、4	    //循环发送模式
//DAC通道1、2       //定时器触发模式
/**************************本例程提供正弦波和锯齿波********************************/
/**************可自定义周期波形，写入数据地址至DMA即可产生相应波形*******************/
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "math.h"

#define PI  3.1415926
#define Vref 3.3		//0.1~3.3V可调
#define Um  (Vref/2)
#define N 256

/********不需要的波形注释掉即可**********/
#define  Sine_WaveOutput_Enable
#define  SawTooth_WaveOutput_Enable


#define  SinWave   			0x00	//正弦波
#define  SawToothWave   0x01	//锯齿波
#define  Wave_Channel_1   0x00	//通道1
#define  Wave_Channel_2   0x01	//通道2


/***********正弦波初始化***************/
//Wave1：波形1选择
//Wave1_Fre：波形1频率
//NewState1：波形1使能
//Wave2：波形2选择
//Wave2_Fre：波形2频率
//NewState2：波形2使能
void SineWave_Init(u8 Wave1,u16 Wave1_Fre,float um,u8 NewState1,u8 Wave2,u16 Wave2_Fre,float um1,u8 NewState2);//void SineWave_Init(u8 Wave1,u16 Wave1_Fre,u8 NewState1,u8 Wave2,u16 Wave2_Fre,u8 NewState2);
/************动态设置波形频率*************/
//Wave_Channel：通道选择
//fre：频率
void Set_WaveFre( u8 Wave_Channel ,u16 fre);


#endif

