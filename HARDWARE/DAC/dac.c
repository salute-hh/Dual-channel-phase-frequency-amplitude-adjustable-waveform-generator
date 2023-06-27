#include "dac.h"
#include "math.h"
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
//DACͨ��1�����ʼ��
#define h 1024

float data[n];
float data1[n];
u16 dma_data[n];
u16 dma_data1[n];
//�ɵ��㶨��ѹ
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

//���ǲ��ź�����
void data_tri_init()   
{
	u16 i,j=n/2;
	for(i=0;i<n;i++)
	{
		if(i<j)
		{
			data1[i]=(i*((1.0/f)/n))*(4095.0/(0.5/f));  //1.0��ĺ���Ҫ��û�еĻ�1/f��ֵ�ᱻ��������
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
              
//�����ź����飬ռ�ձȿɵ�
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
//��ݲ��ź�����
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

//�������ź�����
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
                                                   
void tim_init() //time6�ж����dac
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period =2400000/(f+f/1500) ; 
	TIM_TimeBaseInitStructure.TIM_Prescaler =0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM6,ENABLE); //ʹ������
	
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period =2400000/(f+f/1500) ; 
	TIM_TimeBaseInitStructure.TIM_Prescaler =0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM4,ENABLE); //ʹ������
	
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
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;    //����ܽ�
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;//��ʱ��6����
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//û�в���
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//û�л���
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//�رշ�ֵ
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);//�ṹ��
	DAC_Cmd(DAC_Channel_1, ENABLE);//ʹ��
	//DAC_SetChannel1Data(DAC_Align_12b_R,0);//�������
	DAC_DMACmd(DAC_Channel_1, ENABLE);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T4_TRGO;//��ʱ��6����
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//û�в���
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//û�л���
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//�رշ�ֵ
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);//�ṹ��
	DAC_Cmd(DAC_Channel_2, ENABLE);//ʹ��
	//DAC_SetChannel1Data(DAC_Align_12b_R,0);//�������
	DAC_DMACmd(DAC_Channel_2, ENABLE);

}
void dma_init()  //dma����
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
	
	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)DAC_DHR12RD_Address;//DMA�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&dma_data;//DMA�ڴ��ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//�ڴ���Ϊ���ݴ������Դ
	DMA_InitStructure.DMA_BufferSize= n ;//ָ��DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//�������ݿ��16  
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//�洢���ݿ��16
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;//������ѭ������ģʽ	 
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMAͨ��xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA2_Channel3,&DMA_InitStructure);	//dac��DMA2ͨ��3��   DAC1
	DMA_Cmd(DMA2_Channel3,ENABLE);//ʹ��DMA2
	//DMA_ITConfig(DMA2_Channel3, DMA_IT_TC, ENABLE); 
	
	
	DMA_DeInit(DMA2_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)DAC_DHR12LD_Address;//DMA�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&dma_data1;//DMA�ڴ��ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//�ڴ���Ϊ���ݴ������Դ
	DMA_InitStructure.DMA_BufferSize= n ;//ָ��DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//�������ݿ��16  
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//�洢���ݿ��16
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;//������ѭ������ģʽ	 
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMAͨ��xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA2_Channel4,&DMA_InitStructure);	//dac��DMA2ͨ��1��   DAC2
	DMA_Cmd(DMA2_Channel4,ENABLE);//ʹ��DMA2

}
//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}




















































