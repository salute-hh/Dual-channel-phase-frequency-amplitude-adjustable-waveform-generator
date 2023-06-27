#include "dac.h"
#include "math.h"
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
//DAC通道1输出初始化
#define h 1024

float data[n];
float data1[n];
u16 dma_data[n];
u16 dma_data1[n];
//可调恒定电压
void data_lin_init()
{
	u16 i;
	for(i=0;i<n;i++)
	{
			data[i]=4095*u/3.3;
			dma_data[i]=data[i];
			//printf("%d\r\n",dma_data[i]);
	}
}

//三角波信号数组
void data_tri_init()   
{
	u16 i,j=n/2;
	for(i=0;i<n;i++)
	{
		if(i<j)
		{
			data1[i]=(i*((1.0/f)/n))*(4095.0/(0.5/f));  //1.0真的很重要，没有的话1/f的值会被当做整型
			dma_data1[i]=data1[i];
			//printf("%d\r\n",dma_data[i]);
		}
		else
		{
			data1[i]=4095*2-(i*((1.0/f)/n))*(4095/(0.5/f));
			dma_data1[i]=data1[i];
			//printf("%d\r\n",dma_data[i]);
		}
	}
}
              
//方波信号数组，占空比可调
void data_squ_init()   
{
	u16 i;
	for(i=0;i<n;i++)
	{
		if(i<k*n)
			dma_data[i]=4095;
		
		else 
			dma_data[i]=0;
		
			//printf("%d\r\n",dma_data[i]);
	}
}
//锯齿波信号数组
void data_saw_init()   
{
	u16 i;
	for(i=0;i<n;i++)
	{
			data[i]=(i*((1.0/f)/n))*(4095.0/(1.0/f));
			dma_data[i]=data[i];
			//printf("%d\r\n",dma_data[i]);
	}
}

//正玄波信号数组
void data_sin_init()   
{
	u16 i;
	for(i=0;i<n;i++)
	{
		data[i]=1800*sin(i*2*pi/n)+2000;
		dma_data[i]=data[i];
		//printf("%d\r\n",dma_data[i]);
	}
}
                                                   
void tim_init() //time6中断输出dac
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period =2400000/(f+f/1500) ; 
	TIM_TimeBaseInitStructure.TIM_Prescaler =0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM6,ENABLE); //使能外设
	
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period =2400000/(f+f/1500) ; 
	TIM_TimeBaseInitStructure.TIM_Prescaler =0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM4,ENABLE); //使能外设
	
	TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_Update);
}
void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	DAC_DeInit();
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;    //输出管脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;//定时器6触发
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//没有波形
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//没有缓存
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//关闭幅值
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);//结构体
	DAC_Cmd(DAC_Channel_1, ENABLE);//使能
	//DAC_SetChannel1Data(DAC_Align_12b_R,0);//输出函数
	DAC_DMACmd(DAC_Channel_1, ENABLE);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T4_TRGO;//定时器6触发
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//没有波形
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//没有缓存
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//关闭幅值
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);//结构体
	DAC_Cmd(DAC_Channel_2, ENABLE);//使能
	//DAC_SetChannel1Data(DAC_Align_12b_R,0);//输出函数
	DAC_DMACmd(DAC_Channel_2, ENABLE);

}
void dma_init()  //dma配置
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
	
	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)DAC_DHR12RD_Address;//DMA外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&dma_data;//DMA内存地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//内存作为数据传输的来源
	DMA_InitStructure.DMA_BufferSize= n ;//指定DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//外设数据宽度16  
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//存储数据宽度16
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;//工作在循环缓存模式	 
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMA通道x拥有高优先级
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA2_Channel3,&DMA_InitStructure);	//dac在DMA2通道3内   DAC1
	DMA_Cmd(DMA2_Channel3,ENABLE);//使能DMA2
	//DMA_ITConfig(DMA2_Channel3, DMA_IT_TC, ENABLE); 
	
	
	DMA_DeInit(DMA2_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)DAC_DHR12LD_Address;//DMA外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&dma_data1;//DMA内存地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//内存作为数据传输的来源
	DMA_InitStructure.DMA_BufferSize= n ;//指定DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//外设数据宽度16  
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//存储数据宽度16
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;//工作在循环缓存模式	 
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMA通道x拥有高优先级
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA2_Channel4,&DMA_InitStructure);	//dac在DMA2通道1内   DAC2
	DMA_Cmd(DMA2_Channel4,ENABLE);//使能DMA2

}
//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}




















































