#include "DMA_Waveoutput.h"
#include "delay.h"

//extern float volt_verf,um;
void SineWave_Data( u16 cycle ,u16 *D,float um)
{
	u16 i;
		um=um-0.4;
	for( i=0;i<cycle;i++)
	{
		D[i]=((um*sin(( 1.0*i/(cycle-1))*2*PI)+um)*4095/3.3);//(u16)256 * sin(1.0 * i / (cycle - 1) * 2 * PI) + 2048;//((Um*sin(( 1.0*i/(cycle-1))*2*PI)+Um)*4095/3.3);
	}
}
void SineWave_Data1( u16 cycle ,u16 *D1,float um1)
{
	u16 i;

	for( i=0;i<cycle;i++)
	{
		D1[i]=((um1*sin(( 1.0*i/(cycle-1))*2*PI)+um1)*4095/3.3);//(u16)256 * sin(1.0 * i / (cycle - 1) * 2 * PI) + 2048;//((Um*sin(( 1.0*i/(cycle-1))*2*PI)+Um)*4095/3.3);
	}
}
/********���ɾ�ݲ��������***********/
void SawTooth_Data( u16 cycle ,u16 *D)
{
	u16 i;
	for( i=0;i<cycle;i++)
	{
		D[i]= (u16)(1.0*i/255*4095);
	}
}

/******************���Ҳ��α�***********************/
#ifdef  Sine_WaveOutput_Enable 	
     u16 SineWave_Value[256] = { 0x7FF,0x831,0x863,0x896,0x8C8,0x8FA,0x92B,0x95D,0x98E,0x9C0,0x9F1,0xA21,0xA51,0xA81,0xAB1,0xAE0
,0xB0F,0xB3D,0xB6A,0xB98,0xBC4,0xBF0,0xC1C,0xC46,0xC71,0xC9A,0xCC3,0xCEB,0xD12,0xD38,0xD5E,0xD83
,0xDA7,0xDCA,0xDEC,0xE0D,0xE2E,0xE4D,0xE6C,0xE89,0xEA5,0xEC1,0xEDB,0xEF5,0xF0D,0xF24,0xF3A,0xF4F
,0xF63,0xF75,0xF87,0xF97,0xFA6,0xFB4,0xFC1,0xFCD,0xFD7,0xFE0,0xFE8,0xFEF,0xFF5,0xFF9,0xFFC,0xFFE
,0xFFE,0xFFE,0xFFC,0xFF9,0xFF5,0xFEF,0xFE8,0xFE0,0xFD7,0xFCD,0xFC1,0xFB4,0xFA6,0xF97,0xF87,0xF75
,0xF63,0xF4F,0xF3A,0xF24,0xF0D,0xEF5,0xEDB,0xEC1,0xEA5,0xE89,0xE6C,0xE4D,0xE2E,0xE0D,0xDEC,0xDCA
,0xDA7,0xD83,0xD5E,0xD38,0xD12,0xCEB,0xCC3,0xC9A,0xC71,0xC46,0xC1C,0xBF0,0xBC4,0xB98,0xB6A,0xB3D
,0xB0F,0xAE0,0xAB1,0xA81,0xA51,0xA21,0x9F1,0x9C0,0x98E,0x95D,0x92B,0x8FA,0x8C8,0x896,0x863,0x831
,0x7FF,0x7CD,0x79B,0x768,0x736,0x704,0x6D3,0x6A1,0x670,0x63E,0x60D,0x5DD,0x5AD,0x57D,0x54D,0x51E
,0x4EF,0x4C1,0x494,0x466,0x43A,0x40E,0x3E2,0x3B8,0x38D,0x364,0x33B,0x313,0x2EC,0x2C6,0x2A0,0x27B
,0x257,0x234,0x212,0x1F1,0x1D0,0x1B1,0x192,0x175,0x159,0x13D,0x123,0x109,0x0F1,0x0DA,0x0C4,0x0AF
,0x09B,0x089,0x077,0x067,0x058,0x04A,0x03D,0x031,0x027,0x01E,0x016,0x00F,0x009,0x005,0x002,0x000
,0x000,0x000,0x002,0x005,0x009,0x00F,0x016,0x01E,0x027,0x031,0x03D,0x04A,0x058,0x067,0x077,0x089
,0x09B,0x0AF,0x0C4,0x0DA,0x0F1,0x10A,0x123,0x13D,0x159,0x175,0x192,0x1B1,0x1D0,0x1F1,0x212,0x234
,0x257,0x27B,0x2A0,0x2C6,0x2EC,0x313,0x33B,0x364,0x38D,0x3B8,0x3E2,0x40E,0x43A,0x466,0x494,0x4C1
,0x4EF,0x51E,0x54D,0x57D,0x5AD,0x5DD,0x60E,0x63E,0x670,0x6A1,0x6D3,0x704,0x736,0x768,0x79B,0x7CD};
		      u16 SineWave_Value1[256] = { 0x7FF,0x831,0x863,0x896,0x8C8,0x8FA,0x92B,0x95D,0x98E,0x9C0,0x9F1,0xA21,0xA51,0xA81,0xAB1,0xAE0
,0xB0F,0xB3D,0xB6A,0xB98,0xBC4,0xBF0,0xC1C,0xC46,0xC71,0xC9A,0xCC3,0xCEB,0xD12,0xD38,0xD5E,0xD83
,0xDA7,0xDCA,0xDEC,0xE0D,0xE2E,0xE4D,0xE6C,0xE89,0xEA5,0xEC1,0xEDB,0xEF5,0xF0D,0xF24,0xF3A,0xF4F
,0xF63,0xF75,0xF87,0xF97,0xFA6,0xFB4,0xFC1,0xFCD,0xFD7,0xFE0,0xFE8,0xFEF,0xFF5,0xFF9,0xFFC,0xFFE
,0xFFE,0xFFE,0xFFC,0xFF9,0xFF5,0xFEF,0xFE8,0xFE0,0xFD7,0xFCD,0xFC1,0xFB4,0xFA6,0xF97,0xF87,0xF75
,0xF63,0xF4F,0xF3A,0xF24,0xF0D,0xEF5,0xEDB,0xEC1,0xEA5,0xE89,0xE6C,0xE4D,0xE2E,0xE0D,0xDEC,0xDCA
,0xDA7,0xD83,0xD5E,0xD38,0xD12,0xCEB,0xCC3,0xC9A,0xC71,0xC46,0xC1C,0xBF0,0xBC4,0xB98,0xB6A,0xB3D
,0xB0F,0xAE0,0xAB1,0xA81,0xA51,0xA21,0x9F1,0x9C0,0x98E,0x95D,0x92B,0x8FA,0x8C8,0x896,0x863,0x831
,0x7FF,0x7CD,0x79B,0x768,0x736,0x704,0x6D3,0x6A1,0x670,0x63E,0x60D,0x5DD,0x5AD,0x57D,0x54D,0x51E
,0x4EF,0x4C1,0x494,0x466,0x43A,0x40E,0x3E2,0x3B8,0x38D,0x364,0x33B,0x313,0x2EC,0x2C6,0x2A0,0x27B
,0x257,0x234,0x212,0x1F1,0x1D0,0x1B1,0x192,0x175,0x159,0x13D,0x123,0x109,0x0F1,0x0DA,0x0C4,0x0AF
,0x09B,0x089,0x077,0x067,0x058,0x04A,0x03D,0x031,0x027,0x01E,0x016,0x00F,0x009,0x005,0x002,0x000
,0x000,0x000,0x002,0x005,0x009,0x00F,0x016,0x01E,0x027,0x031,0x03D,0x04A,0x058,0x067,0x077,0x089
,0x09B,0x0AF,0x0C4,0x0DA,0x0F1,0x10A,0x123,0x13D,0x159,0x175,0x192,0x1B1,0x1D0,0x1F1,0x212,0x234
,0x257,0x27B,0x2A0,0x2C6,0x2EC,0x313,0x33B,0x364,0x38D,0x3B8,0x3E2,0x40E,0x43A,0x466,0x494,0x4C1
,0x4EF,0x51E,0x54D,0x57D,0x5AD,0x5DD,0x60E,0x63E,0x670,0x6A1,0x6D3,0x704,0x736,0x768,0x79B,0x7CD};
#endif	
/******************��ݲ��α�***********************/
#ifdef  SawTooth_WaveOutput_Enable
     u16 SawToothWave_Value[256] = {0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256,273,289,305,321,337,353,369,385,401,417,433,449,465,481,497,513,529,546,562,578,594,610,626,642,658,674,690,706,722,738,754,770,786,802,819,835,851,867,883,899,915,931,947,963,979,995,1011,1027,1043,1059,1075,1092,1108,1124,1140,1156,1172,1188,1204,1220,1236,1252,1268,1284,1300,1316,1332,1348,1365,1381,1397,1413,1429,1445,1461,1477,1493,1509,1525,1541,1557,1573,1589,1605,1621,1638,1654,1670,1686,1702,1718,1734,1750,1766,1782,1798,1814,1830,1846,1862,1878,1894,1911,1927,1943,1959,1975,1991,2007,2023,2039,2055,2071,2087,2103,2119,2135,2151,2167,2184,2200,2216,2232,2248,2264,2280,2296,2312,2328,2344,2360,2376,2392,2408,2424,2440,2457,2473,2489,2505,2521,2537,2553,2569,2585,2601,2617,2633,2649,2665,2681,2697,2713,2730,2746,2762,2778,2794,2810,2826,2842,2858,2874,2890,2906,2922,2938,2954,2970,2986,3003,3019,3035,3051,3067,3083,3099,3115,3131,3147,3163,3179,3195,3211,3227,3243,3259,3276,3292,3308,3324,3340,3356,3372,3388,3404,3420,3436,3452,3468,3484,3500,3516,3532,3549,3565,3581,3597,3613,3629,3645,3661,3677,3693,3709,3725,3741,3757,3773,3789,3805,3822,3838,3854,3870,3886,3902,3918,3934,3950,3966,3982,3998,4014,4030,4046,4062,4078,4095};  //���ú�������
#endif	
	
/******DAC�Ĵ�����ַ����*******/	
#define DAC_DHR12R1    (u32)&(DAC->DHR12R1)   //DACͨ��1����Ĵ�����ַ
#define DAC_DHR12R2    (u32)&(DAC->DHR12R2)   //DACͨ��2����Ĵ�����ַ


/****************���ų�ʼ��******************/
void SineWave_GPIO_Config( u8 NewState1 ,u8 NewState2)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  if( NewState1!=DISABLE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ʱ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //�������ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//�������	
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ; //ѡ������
		GPIO_SetBits(GPIOA,GPIO_Pin_4)	;	//�������
	}
	if( NewState1==DISABLE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ʱ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       //����
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ; //ѡ������
	}
	if( NewState2!=DISABLE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ʱ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //�������ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//�������	
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ; //ѡ������
		GPIO_SetBits(GPIOA,GPIO_Pin_5)	;	//�������
	}
	if( NewState2==DISABLE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ʱ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       //����
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ; //ѡ������
	}
	GPIO_Init(GPIOA, &GPIO_InitStructure);		//��ʼ��
}

/******************DAC��ʼ��*************************/
void SineWave_DAC_Config( u8 NewState1 ,u8 NewState2)
{
	DAC_InitTypeDef            DAC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��DACʱ��
	
  /**************DAC�ṹ��ʼ��������Ҫ�������޲���*******************/
	DAC_StructInit(&DAC_InitStructure);		
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//����������
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; //��ʹ���������
	if( NewState1!=DISABLE)
	{
		DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//ѡ��DAC����ԴΪTIM2
	  DAC_Init(DAC_Channel_1, &DAC_InitStructure);//��ʼ��
	  DAC_Cmd(DAC_Channel_1, ENABLE);	   //ʹ��DACͨ��1
	  DAC_DMACmd(DAC_Channel_1, ENABLE); //ʹ��DACͨ��1��DMA
	}
	if( NewState2!=DISABLE)
	{
		DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;//ѡ��DAC����ԴΪTIM6
		DAC_Init(DAC_Channel_2, &DAC_InitStructure);//��ʼ��
		DAC_Cmd(DAC_Channel_2, ENABLE);	   //ʹ��DACͨ��2
		DAC_DMACmd(DAC_Channel_2, ENABLE); //ʹ��DACͨ��2��DMA
	}	
	if( NewState1==DISABLE)
	{
		DAC_Cmd(DAC_Channel_1, DISABLE);	   //ʹ��DACͨ��1
	  DAC_DMACmd(DAC_Channel_1, DISABLE); //ʹ��DACͨ��1��DMA
	}
	if( NewState2==DISABLE)
	{
		DAC_Cmd(DAC_Channel_2, DISABLE);	   //ʹ��DACͨ��1
	  DAC_DMACmd(DAC_Channel_2, DISABLE); //ʹ��DACͨ��1��DMA
	}
}
		 
/*********��ʱ������************/
void SineWave_TIM_Config( u32 Wave1_Fre ,u8 NewState1 ,u32 Wave2_Fre ,u8 NewState2)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	if( NewState1!=DISABLE)	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��ʱ��
	if( NewState2!=DISABLE)	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);//��ʱ��
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
 	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;     //��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //����Ƶ	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
  if( NewState1!=DISABLE)
	{
			TIM_TimeBaseStructure.TIM_Period = Wave1_Fre;    
	    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//����TIM2�������Ϊ����ģʽ
	}
	if( NewState2!=DISABLE)
	{
			TIM_TimeBaseStructure.TIM_Period = Wave2_Fre;     //�������Ƶ��       
	    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  //��ʼ��
	    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
	}
	if(NewState1==DISABLE)//�ָ�Ĭ��
		TIM_DeInit(TIM2);
	if(NewState2==DISABLE)
		TIM_DeInit(TIM6);
}

/*********DMA����***********/
void SineWave_DMA_Config( u16 *Wave1_Mem ,u8 NewState1 ,u16 *Wave2_Mem ,u8 NewState2)
{					
	DMA_InitTypeDef            DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//��DMA2��ʱ��
	
	DMA_StructInit( &DMA_InitStructure);		//DMA�ṹ��ʼ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//�Ӵ洢��������
	DMA_InitStructure.DMA_BufferSize = N;//�����С��һ��Ϊ256��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���Ϊ����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���Ϊ����
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ����ǳ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�ر��ڴ浽�ڴ�ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ������ģʽ 
	if( NewState1!=DISABLE)
	{
			DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//�����ַΪDACͨ��1���ݼĴ���
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Wave1_Mem;//�ڴ��ַΪ���������������
			DMA_Init(DMA2_Channel3, &DMA_InitStructure);//��ʼ��
			DMA_Cmd(DMA2_Channel3, ENABLE);  //ʹ��DMAͨ��3       
	}
	if( NewState2!=DISABLE)
	{
			DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2;//���������ַΪDACͨ��1���ݼĴ���
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Wave2_Mem;//�ڴ��ַΪ���������������
			DMA_Init(DMA2_Channel4, &DMA_InitStructure);//��ʼ��
			DMA_Cmd(DMA2_Channel4, ENABLE);	 //ʹ��DMAͨ��4
	}  
	if( NewState1==DISABLE)
	{
		DMA_Cmd(DMA2_Channel3, DISABLE);  //ʹ��DMAͨ��3  
	}	
	if( NewState2==DISABLE)
	{
		DMA_Cmd(DMA2_Channel4, DISABLE);  //ʹ��DMAͨ��3  
	}		
}

/***********���Ҳ���ʼ��***************/
void SineWave_Init(u8 Wave1,u16 Wave1_Fre,float um,u8 NewState1,u8 Wave2,u16 Wave2_Fre,float um1,u8 NewState2)
{
  u16 *add1,*add2;
	u16 f1=(u16)(72000000/sizeof(SineWave_Value)*2/Wave1_Fre);
	u16 f2=(u16)(72000000/sizeof(SineWave_Value)*2/Wave2_Fre);
  SineWave_Data( N ,SineWave_Value,um);		//���ɲ��α�1
	SineWave_Data1( N ,SineWave_Value1,um1);		//���ɲ��α�1
	SawTooth_Data( N ,SawToothWave_Value);//���ɲ��α�2
	if( NewState1!=DISABLE)
	{
	    if( Wave1==0)  //sine_ware 
		    add1=SineWave_Value;
	    else				
		    add1=SawToothWave_Value;
	}
  if( NewState2!=DISABLE)
	{
	    if( Wave2==0)   //sine_ware
		    add2=SineWave_Value1;
	    else			
		    add2=SawToothWave_Value;
	}
	SineWave_GPIO_Config( NewState1 ,NewState2);			  //��ʼ������ 
	SineWave_TIM_Config( f1 , NewState1 ,f2 ,NewState2);			  //��ʼ����ʱ�� 
	SineWave_DAC_Config(NewState1 ,NewState2);			  //��ʼ��DAC
	SineWave_DMA_Config( add1 ,NewState1 ,add2 ,NewState2);			  //��ʼ��DMA
//  if( NewState1!=DISABLE)	
//		TIM_Cmd(TIM2, ENABLE);			 //ʹ��TIM2,��ʼ�������� 
//  if( NewState2!=DISABLE)   
//		TIM_Cmd(TIM6, ENABLE);			 //ʹ��TIM6,��ʼ��������  
}

void Set_WaveFre( u8 Wave_Channel ,u16 fre)
{
	TIM_TypeDef* TIMX;
	u16 reload;
	
	if( Wave_Channel==0)		TIMX = TIM2;
	else if(Wave_Channel==1)		TIMX = TIM6;
		
	reload=(u16)(72000000/256/fre);
	TIM_SetAutoreload( TIMX ,reload);
}

