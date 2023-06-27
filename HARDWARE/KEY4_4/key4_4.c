#include "key4_4.h"
#include "delay.h"
#include "sys.h"

unsigned char Y1,Y2,Y3,Y4;
void KEY_Init44(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(X1_RCC|X2_RCC|X3_RCC|X4_RCC|Y1_RCC|Y2_RCC|Y3_RCC|Y4_RCC|RCC_APB2Periph_AFIO, ENABLE);
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
/*****************************4行输出*********************************************/
   GPIO_InitStructure.GPIO_Pin =  X1_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X1_GPIO_PORT, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin =  X2_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X2_GPIO_PORT, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin =  X3_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X3_GPIO_PORT, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Pin = X4_GPIO_PIN ;
   GPIO_Init(X4_GPIO_PORT, &GPIO_InitStructure);

/**************************************4列输入*************************************/
   GPIO_InitStructure.GPIO_Pin =  Y1_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y1_GPIO_PORT, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin =  Y2_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y2_GPIO_PORT, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin =  Y3_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y3_GPIO_PORT, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Pin = Y4_GPIO_PIN;
   GPIO_Init(Y4_GPIO_PORT, &GPIO_InitStructure);
}

int KEY_Scan44(void)
{
   u8 KeyVal = -1;
   GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);  //先让X1输出高
   GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);  //先让X2输出高
   GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);  //先让X3输出高
   GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN);  //先让X4输出高

	if((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)|GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN)|GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN)|GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))==0x0000)
        return -1; //如果X1到X4全为零则没有按键按下
	 else
	 {	
	    delay_ms(5);    //延时5ms去抖动
         if((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)|GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN)|GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN)|GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))==0x0000)
	    return -1;
	 }
	
     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN);

    Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
    Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=13;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=0;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=15;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=14;

     while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
    //等待按键释放
     GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);

    Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
    Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=1;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=2;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=3;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=10;

      while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
		

     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);

     Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
     Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=4;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=5;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=6;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=11;

      while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
		
     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);

     Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
     Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=7;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=8;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=9;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=12;

       while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
	
		return KeyVal;
}

/************************************
按键表盘为：	1  2  3  A
							4  5  6  B
							7  8  9  C
							*  0  #  D
************************************/
//void Key_Test(void)
//{
//    int num;
//	  num = Key_Scan();
//	  switch(num)
//	  {
//        case 0: printf("0\n"); break;					  				
//				case 1: printf("1\n"); break;					  				
//				case 2: printf("2\n"); break;					  				
//				case 3: printf("3\n"); break;					  				
//				case 4: printf("4\n"); break;				 	
//				case 5: printf("5\n"); break;					  				
//				case 6: printf("6\n"); break;					  				
//				case 7: printf("7\n"); break;					 			
//				case 8: printf("8\n"); break;								 		
//				case 9: printf("9\n"); break;							 				     	
//        case 'A': printf("A\n"); break;						 				      		
//				case 'B': printf("B\n"); break;					 				
//				case 'C': printf("C\n"); break;							 				      	
//        case 'D': printf("D\n"); break;							 				       	
//				case '#': printf("#\n"); break;					 				
//				case '*': printf("*\n"); break;					 			
//      }
//}
