#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "DMA_Waveoutput.h"
#include "key4_4.h"
#include "stdio.h"
#include "string.h"
 

int CHX=0,flag1=0;
u8 line_a=0,line_b=64;
u8 line_a_level=0,line_b_level=0;
int CHA_state=0,CHB_state=0;
u8 CHA_Waveform=0,CHB_Waveform=0;
int frequency_a=1000,frequency_b=1000;
float volt_a=3.3,volt_b=3.3;
u8 fraseflag=0;
int frase=0;
long temp_frase,last_frase;
float volt_verf=1.65;
u8 double_channel=0;
char receive_catch0[4]={0},receive_catch1[5]={0},receive_catch2[10]={0},receive_catch5[10]={0};
int receive_catch3;
float receive_catch4;
char receive_catch6[4]={0},receive_catch7[4]={0};
int receive_catch9,receive_catch8;
float receive_catch10;
u8 USART_DOUBEL_FLAG=0;
void LCD_Clear_line(u16 Color,u8 line)
{
		u16 i;  	
		LCD_Address_Set(0,line,127,LCD_H-1);
    for(i=0;i<127;i++)
	  {
					LCD_WR_DATA(Color);
	  }
}
void LCD_Init_Show()
{
	u8 x,i;
	LCD_ShowString(0,0,(const u8 *)"CHA:",RED);
	LCD_ShowString(32,0,(const u8 *)"ON ",RED);
	LCD_ShowString(64,0,(const u8 *)"select",GREEN);
	for(x=0,i=0;x<=80;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,16,i,16,RED);   //���Σ����Ҳ�
	}
	for(x=0,i=9;x<=32;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,32,i,16,RED);   //Ƶ��:
	}
	LCD_ShowNum(48,32,frequency_a,4,RED);//1000
	LCD_ShowString(96,32,(const u8 *)"Hz",RED);
	for(x=0,i=12;x<=32;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,48,i,16,RED);   //��ֵ:
	}
	LCD_ShowNum1(48,48,volt_a,3,RED);//3.3
	LCD_ShowString(96,48,(const u8 *)"V",RED);
//	LCD_DrawLine(0,64,127,64,BLACK);
	LCD_ShowString(0,65,(const u8 *)"CHB:",BLUE);
	LCD_ShowString(32,65,(const u8 *)"ON ",BLUE);
	for(x=0,i=0;x<=80;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,81,i,16,BLUE);   //���Σ����Ҳ�
	}
	for(x=0,i=9;x<=32;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,97,i,16,BLUE);   //Ƶ�ʣ�
	}
	LCD_ShowNum(48,97,frequency_b,4,BLUE);//1000
	LCD_ShowString(96,97,(const u8 *)"Hz",BLUE);
	for(x=0,i=12;x<=32;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,113,i,16,BLUE);   //��ֵ;
	}
	LCD_ShowNum1(48,113,volt_b,3,BLUE);//3.3
	LCD_ShowString(96,113,(const u8 *)"V",BLUE);
	for(x=0,i=15;x<=32;x=x+16,i=i+1)
	{
		LCD_ShowChinese(x,129,i,16,BLUE);   //��λ��
	}
	LCD_ShowNum(48,129,0,3,BLUE);//1000
//	LCD_ShowString(80,129,(const u8 *)"W:",BLACK);//��λ
}


void usart_set_form()
{
			u16 i=0;	
			char *p;
			char *p1=(char*)USART_RX_BUF;
			if(p=strstr((const char*)USART_RX_BUF,"CHA"),(p!=NULL))//ͨ��1   CHA ON SAW 5000 3
				{
					sscanf((const char*)USART_RX_BUF,"%s%s%s%d%f",receive_catch0,receive_catch1,receive_catch2,&receive_catch3,&receive_catch4);
					printf("%s\r\n%s\r\n%s\r\n%d\r\n%f\r\n",receive_catch0,receive_catch1,receive_catch2,receive_catch3,receive_catch4);
					CHB_state=1;
					if(receive_catch1[1]=='N')//��
					{
						CHA_state=0;						
						frequency_a=receive_catch3;
						volt_a=receive_catch4;	
						LCD_ShowString(48, 32, "      ", WHITE);
						LCD_ShowNum(48,32,frequency_a,4,RED);//1000
						LCD_ShowString(48, 48, "      ", WHITE);
						LCD_ShowNum1(48,48,volt_a,3,RED);//3.3
						if(receive_catch2[0]=='S'&&receive_catch2[1]=='I'&&receive_catch2[2]=='N')
								CHA_Waveform=0;
						else if(receive_catch2[0]=='S'&&receive_catch2[1]=='A'&&receive_catch2[2]=='W')
								CHA_Waveform=1;
					}
					else if(receive_catch1[1]=='F'&&receive_catch1[2]=='F')//��
					{
						CHA_state=1;
					}
					if(CHA_state==0&&CHB_state!=0)
					{
								LCD_ShowString(32,0,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,0,(const u8 *)"ON",RED);
								LCD_ShowString(32,65,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,65,(const u8 *)"OFF",BLUE);
					}
					else	if(CHA_state!=0&&CHB_state!=0)
					{
								LCD_ShowString(32,0,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,0,(const u8 *)"OFF",RED);
								LCD_ShowString(32,65,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,65,(const u8 *)"OFF",BLUE);
					}
				
				}
				else if(p=strstr((const char*)USART_RX_BUF,"CHB"),(p!=NULL))//ͨ��2   
				{
					sscanf((const char*)USART_RX_BUF,"%s%s%s%d%f",receive_catch0,receive_catch1,receive_catch2,&receive_catch3,&receive_catch4);
					printf("%s\r\n%s\r\n%s\r\n%d\r\n%f\r\n",receive_catch0,receive_catch1,receive_catch2,receive_catch3,receive_catch4);
					CHA_state=1;
					if(receive_catch1[1]=='N')//��
					{
						CHB_state=0;
						frequency_b=receive_catch3;
						volt_b=receive_catch4;	
						LCD_ShowString(48, 97, "      ", WHITE);
						LCD_ShowNum(48,97,frequency_b,4,BLUE);//1000
						LCD_ShowString(48, 113, "      ", WHITE);
						LCD_ShowNum1(48,113,volt_b,3,BLUE);//3.3
						if(receive_catch2[0]=='S'&&receive_catch2[1]=='I'&&receive_catch2[2]=='N')
								CHB_Waveform=0;
						else if(receive_catch2[0]=='S'&&receive_catch2[1]=='A'&&receive_catch2[2]=='W')
								CHB_Waveform=1;
					}
					else if(receive_catch1[1]=='F'&&receive_catch1[2]=='F')//��
					{
						CHB_state=1;
					}
					if(CHB_state==0&&CHA_state!=0)
					{
								LCD_ShowString(32,0,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,0,(const u8 *)"OFF",RED);
								LCD_ShowString(32,65,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,65,(const u8 *)"ON",BLUE);
					}
					else	if(CHB_state!=0&&CHA_state!=0)
					{
								LCD_ShowString(32,0,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,0,(const u8 *)"OFF",RED);
								LCD_ShowString(32,65,(const u8 *)"   ",WHITE);
								LCD_ShowString(32,65,(const u8 *)"OFF",BLUE);
					}				
				}
				else if(p=strstr((const char*)USART_RX_BUF,"double"),(p!=NULL))//˫ͨ��
				{
					sscanf((const char*)USART_RX_BUF,"%s%s%s%s%d%f%s%s%d%f%d",receive_catch5,receive_catch0,receive_catch1,receive_catch2,&receive_catch3,&receive_catch4,receive_catch6,receive_catch7,&receive_catch9,&receive_catch10,&receive_catch8);
					printf("%s  %s  %s  %d  %f  ",receive_catch0,receive_catch1,receive_catch2,receive_catch3,receive_catch4);
					printf("%s  %s  %d  %f  %d  ",receive_catch6,receive_catch7,receive_catch9,receive_catch10,receive_catch8);
					if(receive_catch0[1]=='N')
					{
						USART_DOUBEL_FLAG=1;
						CHA_state=0;
						CHB_state=0;
						frequency_a=receive_catch3;
						volt_a=receive_catch4;	
						frequency_b=receive_catch9;
						volt_b=receive_catch10;	
						frase=receive_catch8;
						LCD_ShowString(48, 32, "      ", WHITE);
						LCD_ShowNum(48,32,frequency_a,4,RED);//a
						LCD_ShowString(48, 48, "      ", WHITE);
						LCD_ShowNum1(48,48,volt_a,3,RED);//a
						LCD_ShowString(48, 97, "      ", WHITE);
						LCD_ShowNum(48,97,frequency_b,4,BLUE);//b
						LCD_ShowString(48, 113, "      ", WHITE);
						LCD_ShowNum1(48,113,volt_b,3,BLUE);//b
						LCD_ShowString(48, 129, "    ", WHITE);
						LCD_ShowNum(48,129,frase,3,BLUE);//frase
						if(receive_catch2[0]=='S'&&receive_catch2[1]=='I'&&receive_catch2[2]=='N')
								CHA_Waveform=0;
						else if(receive_catch2[0]=='S'&&receive_catch2[1]=='A'&&receive_catch2[2]=='W')
								CHA_Waveform=1;
						if(receive_catch7[0]=='S'&&receive_catch7[1]=='I'&&receive_catch7[2]=='N')
								CHB_Waveform=0;
						else if(receive_catch7[0]=='S'&&receive_catch7[1]=='A'&&receive_catch7[2]=='W')
								CHB_Waveform=1;
						LCD_ShowString(32,0,(const u8 *)"   ",WHITE);
						LCD_ShowString(32,0,(const u8 *)"ON",RED);
						LCD_ShowString(32,65,(const u8 *)"   ",WHITE);
						LCD_ShowString(32,65,(const u8 *)"ON",BLUE);
					}
					else if(receive_catch0[1]=='F'&&receive_catch0[2]=='F')//��
					{
						USART_DOUBEL_FLAG=0;
						LCD_ShowString(32,0,(const u8 *)"   ",WHITE);
						LCD_ShowString(32,0,(const u8 *)"OFF",RED);
						LCD_ShowString(32,65,(const u8 *)"   ",WHITE);
						LCD_ShowString(32,65,(const u8 *)"OFF",BLUE);
					}
				}
					p1=0;
					while(USART_RX_BUF[i]!=NULL)
					{
						USART_RX_BUF[i]=NULL;
						i++;
					}
					USART_RX_STA=0;
				

			 
}
//δ��������ֹ����������ѧϰ�ο�-------------------------------By   EMB_HH  2020/9/11
int main(void)
 {	 

	int key;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
//	 
	KEY_Init44();			  //��ʼ����������
	 
// 	LED_Init();			     //LED�˿ڳ�ʼ��
		Lcd_Init();
	 	LCD_Clear(WHITE);
	  BACK_COLOR=WHITE;
	  GPIO_SetBits(GPIOB,GPIO_Pin_1);//BLK
		SineWave_Init(CHA_Waveform,frequency_a,volt_verf,DISABLE,CHA_Waveform,frequency_b,volt_verf,DISABLE);//��ʼ��
	 	TIM_Cmd(TIM2, DISABLE);			 //��ʹ��TIM2,���������� 
		TIM_Cmd(TIM6, DISABLE);			 //��ʹ��TIM6,����������  
 	  LCD_ShowPicture(0,0,127,159)    ;
		delay_ms(2000);
		LCD_Clear(WHITE);
		LCD_Init_Show();
		printf("���������²�����\r\n");
		printf("��ͨ����\r\n");
		printf("CHA sate waveform frequency volt\r\n");//CHA ON SIN 1000 3
		printf("CHB sate waveform frequency volt\r\n");//CHB ON SIN 1000 3
		printf("��ͨ����\r\n");
		printf("double state cha waveform frequency volt chb waveform frequency volt frase\r\n");//double ON cha SIN 1000 3.3 chb SIN 1000 3.3 
	while(1)
	{
			usart_set_form();
//			delay_ms(300);
			if(CHA_state==0&&CHB_state!=0)//��ͨ��A
			{

					SineWave_Init(CHA_Waveform,frequency_a,volt_a/2,ENABLE,CHB_Waveform,frequency_b,volt_b/2,DISABLE);//��ʼ��
					TIM_Cmd(TIM6, DISABLE);
					TIM_Cmd(TIM2, ENABLE);
				Set_WaveFre( 0 ,frequency_a);
//					Set_WaveFre( 1 ,72000000/256/fre);
			}
			if(CHA_state!=0&&CHB_state!=0)//ȫ��
			{
					TIM_Cmd(TIM2, DISABLE);
					TIM_Cmd(TIM6, DISABLE);
			}
			if(CHA_state!=0&&CHB_state==0)//��ͨ��B
			{

					SineWave_Init(CHA_Waveform,frequency_a,volt_a/2,DISABLE,CHB_Waveform,frequency_b,volt_b/2,ENABLE);//��ʼ��	
					TIM_Cmd(TIM2, DISABLE);
					TIM_Cmd(TIM6, ENABLE);
					Set_WaveFre( 1 ,frequency_b);
			}
			
			if(CHA_state==0&&CHB_state==0)//˫ͨ������5000k  ��λ����
			{		
				last_frase=temp_frase;
				temp_frase=(frase*1000000/(frequency_a*360));	
				if(USART_DOUBEL_FLAG==1)
				{
								SineWave_Init(CHA_Waveform,frequency_a,volt_a/2,ENABLE,CHB_Waveform,frequency_b,volt_b/2,ENABLE);//��ʼ��
						
								TIM_Cmd(TIM2, ENABLE);
								if(last_frase<=temp_frase)
								{
									if((temp_frase-last_frase)>0)
										delay_us((u32)(temp_frase-last_frase));//
									else if((temp_frase-last_frase)>=0)
										delay_us((u32)(temp_frase));
								}
								TIM_Cmd(TIM6, ENABLE);
								
								Set_WaveFre( 0 ,frequency_a);

								Set_WaveFre( 1 ,frequency_b);
				}
				else if(USART_DOUBEL_FLAG==0)
				{
					SineWave_Init(CHA_Waveform,frequency_a,volt_a/2,DISABLE,CHB_Waveform,frequency_b,volt_b/2,DISABLE);//��ʼ��
					TIM_Cmd(TIM2, DISABLE);
					TIM_Cmd(TIM6, DISABLE);
				}
			}
			

	
	}
}
 


