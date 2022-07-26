#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

/*****************************************************************/
//功能:播放指定序列的语音文件
//参数:语音序列
//返回: 无
//修改记录:
/*****************************************************************/
//void SK080G_PlaySoundIndex(uint16 da)
//{   
//	uchar cnt=0;
//	uchar da_cnt;
//	SK080G_ResetTG33= 1;     //输入
//	SK080G_CountTG11= 1;     //输入
//	Delay_ms(6); 
//	SK080G_CountTG11= 0;     //输出
//	SK080G_CountTG1 = 0;
//	while(SK080G_ResetTG3==1&&cnt<200)
//	{
//	 cnt++;
//	 Delay_ms(1);
//	}
//	Delay_ms(6);
//    SK080G_ResetTG33= 1;     //输入
//	SK080G_CountTG11= 1;     //输入
//	Delay_ms(6); 
//	for(da_cnt=0;da_cnt<32;da_cnt++)
//	{
//	  if(da&0x01)
//        {
//         SK080G_ResetTG33= 0;     //输出
//	     SK080G_ResetTG3 = 0;
//	     cnt=0;	
//        while(SK080G_CountTG11==1&&cnt<200)
//	      {
//	       Delay_ms(1);	
//	       cnt++;
//	       } 	
//        }
//         else
//         {
// 	      SK080G_CountTG11= 0;     //输出
//	      SK080G_CountTG1 = 0;
//	      cnt=0;
//         while(SK080G_ResetTG3==1&&cnt<200)
//	      {
//	       Delay_ms(1);
//	       cnt++;
//	       }   
//         }
//      Delay_ms(6);   
//      SK080G_ResetTG33= 1;     //输入
//	  SK080G_CountTG11= 1;     //输入
//	  Delay_ms(6); 
//	  da=da>>1;   
//	}
//	cnt=0;
//   while(SK080G_CountTG11==1&&cnt<200)
//    {
//      Delay_ms(1);	
//      cnt++;
//    }   
//	SK080G_ResetTG33= 0;     //输出
//	SK080G_ResetTG3 = 0;
//	Delay_ms(6);             //大约100us
//    SK080G_ResetTG33= 1;     //输入
//	SK080G_CountTG11= 1;     //输入	
//}
/*****************************************************************/
//功能:播放指定序列的语音文件
//参数:语音序列
//返回: 无
//修改记录:
/*****************************************************************/
void SK080G_PlaySoundIndex(uint8 index)
{
	if(index == 0) return;
	SK080G_ResetTG33= 0;     //输出
	SK080G_ResetTG3 = 0;
	Delay_ms(2);		     //大约100us
	SK080G_ResetTG33= 1;     //输入 
	Delay_ms(2);		     //大约100us
	SK080G_ResetTG33= 0;     //输出
	SK080G_ResetTG3 = 0;
    SK080G_CountTG11= 0;     //输出
	SK080G_CountTG1 = 0;
	Delay_ms(2);		     //大约100us
	while(index --)			 //语音序列计数脉冲
	{
	 SK080G_CountTG11= 1;     //输入		
	 Delay_ms(2);		     //大约100us
	 SK080G_CountTG11= 0;         //输出
	 SK080G_CountTG1 = 0;
	 Delay_ms(2);		     //大约100us
	}
	Delay_ms(7);
}
/*********************************************************************/
//功能:判断是否正在播放语音
//参数:无
//返回: 0 没有播放; 1 正在播放
/*********************************************************************/
void AKW_IsPlaySound(void)
{
	static uint8  cnt = 0;
	if(SK080G_BusyTG4)
	{
		cnt = 0;
		SPEAKBUSYFLAG = 1;
	}	
	else
	{
		if(cnt>0)
		{
		 SPEAKBUSYFLAG = 0;
		}
		cnt++;	
	}
}
void AKW_StopPlayVoice(void)
{
   	SK080G_ResetTG33= 0;         //输出
	SK080G_ResetTG3 = 0;
	Delay_ms(2);		         //大约100us
	SK080G_ResetTG33= 1;         //输入
	Delay_ms(2);		         //大约100us
	SK080G_ResetTG33= 0; 
	SK080G_ResetTG3 = 0;
	Delay_ms(2);		         //大约100us
	SK080G_CountTG11= 0;         //输出
	SK080G_CountTG1 = 0;
}
/*********************************************************************/
//功能:判断是否正在播放语音
//参数:无
//返回: 0 没有播放; 1 正在播放
/*********************************************************************/
//void AKW_IsPlaySound(void)
//{
//	static uint8  cnt = 0;
//	if(SK080G_BusyTG4==0)
//	{
//		cnt = 0;
//		SPEAKBUSYFLAG = 1;
//	}	
//	else
//	{
//		if(cnt>0)
//		{
//		 SPEAKBUSYFLAG = 0;
//		}
//		cnt++;	
//	}
//}
/* ********************************************************************************
 * void playSDFile(uint8 len)
 * Description : 开始播放buf 中的音频文件索引号指向的文件。
 * Arguments   : buf ： 音频文件索引号
 *               len ： 文件索引号长度 
 *********************************************************************************/
void playSDFile(uint8 len)
{ 	
//  uint8 i=0;
//  while(i < len)    //i从第一个系列开始播完长度为止
//	{
//	  SK080G_PlaySoundIndex(PLS_SOT[i]);
//	  i++; 
//	 do	
//	  {
//	   AKW_IsPlaySound();
//	   if(KEYFLAG.Val != 0)
//	   {
//	   	AKW_StopPlayVoice();
//	    return;
//	   }	   	
//	  }
//	  while(SPEAKBUSYFLAG == 1);  //0 没有播放; 1 正在播放
//	}
}
/******************************************************************************
 *  SpeakNum(uint16 numb)
 *  Description : 播报数值只做编码 
 *  Returns     :  
*******************************************************************************/
void ISD_SpeakNum(uint16 val)
{
//    uint8 bai,shi, ge;
//
//	R_TEMPDATA.Val =val;	
//	SBR_BIN_TO_BCD();

//	ge = r_Temp0.Val;
//	shi = r_Temp1.Val;
//	bai = r_Temp2.Val;
//   if(val<20)
//	{
//     PLS_SOT[WAVE_count++] = BPF_0_MP3 + val;	
//	}
//	else if((bai==0)&&(shi!=0)&&(ge==0))   //00X0
//	{
//      PLS_SOT[WAVE_count++] = BPF_20_MP3 + shi - 2;
//	}
//	else if((bai==0)&&(shi!=0)&&(ge!=0))   //00XX
//	{
//      PLS_SOT[WAVE_count++] = BPF_20_MP3 + shi - 2;
//	  PLS_SOT[WAVE_count++] = BPF_0_MP3 + ge;	
//	}
//	else if((bai!=0)&&(shi==0)&&(ge==0))   //0X00
//	{
//       PLS_SOT[WAVE_count++] = BPF_0_MP3 + bai;
//       PLS_SOT[WAVE_count++] = BPF_100_MP3;
//	}
//	else if((bai!=0)&&(shi==0)&&(ge!=0))   //0X0X
//	{
//		
//       PLS_SOT[WAVE_count++] = BPF_0_MP3 + bai;
//       PLS_SOT[WAVE_count++] = BPF_100_MP3;		
//  	   PLS_SOT[WAVE_count++] = BPF_0_MP3;
//	   PLS_SOT[WAVE_count++] = BPF_0_MP3 + ge;
//	}
//	else if((bai!=0)&&(shi==1)/*&&(ge!=0)*/)   //0X1X
//	{
//       PLS_SOT[WAVE_count++] = BPF_0_MP3 + bai;
//       PLS_SOT[WAVE_count++] = BPF_100_MP3;		
//	   PLS_SOT[WAVE_count++] = BPF_10_MP3 + ge;
//	}
//	else if((bai!=0)&&(shi!=0)&&(ge==0))   //0XX0
//	{
//       PLS_SOT[WAVE_count++] = BPF_0_MP3 + bai;
//       PLS_SOT[WAVE_count++] = BPF_100_MP3;	
//	   PLS_SOT[WAVE_count++] = BPF_20_MP3 + shi - 2;
//	}
//	else //0XXX
//	{
//       PLS_SOT[WAVE_count++] = BPF_0_MP3 + bai;
//       PLS_SOT[WAVE_count++] = BPF_100_MP3;	
//	   PLS_SOT[WAVE_count++] = BPF_20_MP3 + shi - 2;
//	   PLS_SOT[WAVE_count++] = BPF_0_MP3 + ge;
//  }
}
/********************************************************************************
 * Description : 播放测量结果
 *
 * Arguments   : 
 *
 * Returns     :  
 *
 * Notes       : 
 *
 *********************************************************************************/

 void BPPLAY_ONE_INFOEND(uint16 idnumb)
 {
// 	if(MODEFLAG.bits.b4 ==0)
// 	{
// 	 return;
// 	}	
// 	WAVE_count =0;
// 	PLS_SOT[WAVE_count++] = idnumb;   //	你的血压是 ，高压
// 	playSDFile(WAVE_count);
 }
/********************************************************************************
 * Description : 播放测量结果
 *
 * Arguments   : 
 *
 * Returns     :  
 *
 * Notes       : 
 *
 *********************************************************************************/
// void BPPLAYINFOEND(void)
// {   
// 	int16 i;
// 	if(MODEFLAG.bits.b4 ==0)
// 	{
// 	 return;
// 	}	
// 	WAVE_count =0;
// 	PLS_SOT[WAVE_count++] = BPF_SHOUSUOYA_MP3;   //	你的血压是 ，高压
// 	if(mmHg_Kpa==0)
//     {				   
//    	ISD_SpeakNum(PRE_SYS.Val);
// 	    PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	毫米汞柱
// 	    PLS_SOT[WAVE_count++] = BPF_SHUZHANGYA_MP3;  //	低压
//     	ISD_SpeakNum(PRE_DIA.Val);
//    	PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	毫米汞柱
//     }
//     else
//       {
//       	
//        i = mmhg_chance_kpa(PRE_SYS.Val);
//       	ISD_SpeakNum(i/10);
//       	PLS_SOT[WAVE_count++] = BPF_DIAN_MP3;   //	点
//       	ISD_SpeakNum(i%10);
// 	//    PLS_SOT[WAVE_count++] = BPF_KP_MP3;        //	kap
// 	    PLS_SOT[WAVE_count++] = BPF_SHUZHANGYA_MP3;  //	低压
// 	    i = mmhg_chance_kpa(PRE_DIA.Val);
//     	ISD_SpeakNum(i/10);
//     	PLS_SOT[WAVE_count++] = BPF_DIAN_MP3;   //	点
//     	ISD_SpeakNum(i%10);
//    //	PLS_SOT[WAVE_count++] = BPF_KP_MP3;        //	kap
//       } 
//
// 	PLS_SOT[WAVE_count++] = BPF_MAIBO_MP3;       //	心率每分钟
// 	ISD_SpeakNum(PLSCNT);
// 	PLS_SOT[WAVE_count++] = BPF_CHI_MP3;         //	次
// 	playSDFile(WAVE_count);
//// 	AKW_StopPlayVoice(); 	
// }
	 void BPPLAYINFOEND(void)
	 {
//	 	if(MODEFLAG.bits.b4 ==0)
//	 	{
//	 	 return;
//	 	}	
//	 	WAVE_count =0;
//	 	PLS_SOT[WAVE_count++] = BPF_SHOUSUOYA_MP3;   //	你的血压是 ，高压
//	 	ISD_SpeakNum(PRE_SYS.Val);
//	 	PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	毫米汞柱
//	 	PLS_SOT[WAVE_count++] = BPF_SHUZHANGYA_MP3;  //	低压
//	 	ISD_SpeakNum(PRE_DIA.Val);
//	 	PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	毫米汞柱
//	 	PLS_SOT[WAVE_count++] = BPF_MAIBO_MP3;       //	心率每分钟
//	 	ISD_SpeakNum(PLSCNT);
//	 	PLS_SOT[WAVE_count++] = BPF_CHI_MP3;         //	次
//	 	playSDFile(WAVE_count);
	 }

void BPPLAYWHO(void)	        //波报WHO
{
//	 if((PRE_SYS.Val>=90)&&(PRE_DIA.Val>=60)) 
//	 {
//	   BPPLAY_ONE_INFOEND(BPF_WHO_MP3);     //	根据世界卫生组织标准,您的血压.
//	   if((PRE_SYS.Val>=140)||(PRE_DIA.Val>=90)) 
//	     {//偏高
//	     	 BPPLAY_ONE_INFOEND(BPF_HIGH_MP3);
//	     } 
//	      else
//	       {//正常
//	       	  BPPLAY_ONE_INFOEND(BPF_AB_NORMAL_MP3);
//	       }
//	 }  	
} 
void DISPLAYWHO(void)
{
// 	SBR_DISP_DOT_SWX_ON();
    if(PRE_SYS.Val<60)
    {
//     i =1;
     SBR_DISP_DOT_WX(1);	
    }
    else if(PRE_SYS.Val<90)
    {
//     i = 2;	
     SBR_DISP_DOT_WX(2);
    }
    else if(PRE_SYS.Val<107)
    {
//     i = 3;
     SBR_DISP_DOT_WX(3);	
    }
    else if(PRE_SYS.Val<124)
    {
//     i = 4;	
     SBR_DISP_DOT_WX(4);
    }
    else if(PRE_SYS.Val<140)
    {
//     i = 5;	
     SBR_DISP_DOT_WX(5);
    }
    else if(PRE_SYS.Val<150)
    {
//     i = 6;	
     SBR_DISP_DOT_WX(6);
    }            
    else if(PRE_SYS.Val<160)
    {
//     i = 7;	
     SBR_DISP_DOT_WX(7);
    }    
    else 
    {
//     i = 8;
     SBR_DISP_DOT_WX(8);	
    } 
    if(PRE_DIA.Val>=160)
    {
//     i =1;
     SBR_DISP_DOT_WX_DIA(7);	
    }
    else if(PRE_DIA.Val>=150)
    {
//     i = 2;	
     SBR_DISP_DOT_WX_DIA(6);
    }
    else if(PRE_DIA.Val>=140)
    {
//     i = 3;
     SBR_DISP_DOT_WX_DIA(5);	
    }
    else if(PRE_DIA.Val>=124)
    {
//     i = 4;	
     SBR_DISP_DOT_WX_DIA(4);
    }
    else if(PRE_DIA.Val>=107)
    {
//     i = 5;	
     SBR_DISP_DOT_WX_DIA(3);
    }
    else if(PRE_DIA.Val>=90)
    {
//     i = 6;	
     SBR_DISP_DOT_WX_DIA(2);
    }            
    else if(PRE_DIA.Val>=60)
    {
//     i = 7;	
     SBR_DISP_DOT_WX_DIA(1);
    }    
    else 
    {

    }   
	
}



// void DISPLAYWHO(void)
// {
// 	if(PRE_SYS.Val<=99&&PRE_DIA.Val<=60)
//	 {
//		SBR_DISP_DOT_WX(1);
//	 }
//	else if(PRE_SYS.Val<140&&PRE_DIA.Val<90)    //小于4.7V
//		  {
//             SBR_DISP_DOT_WX(2);
//		  }
//	else if(PRE_SYS.Val<160&&PRE_DIA.Val<100)
//		  {
//    		 SBR_DISP_DOT_WX(3);
//		  }	
//		  else
//		  {
//			SBR_DISP_DOT_WX(4);
//		  }
// }