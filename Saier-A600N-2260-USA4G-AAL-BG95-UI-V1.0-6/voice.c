#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

/*****************************************************************/
//����:����ָ�����е������ļ�
//����:��������
//����: ��
//�޸ļ�¼:
/*****************************************************************/
//void SK080G_PlaySoundIndex(uint16 da)
//{   
//	uchar cnt=0;
//	uchar da_cnt;
//	SK080G_ResetTG33= 1;     //����
//	SK080G_CountTG11= 1;     //����
//	Delay_ms(6); 
//	SK080G_CountTG11= 0;     //���
//	SK080G_CountTG1 = 0;
//	while(SK080G_ResetTG3==1&&cnt<200)
//	{
//	 cnt++;
//	 Delay_ms(1);
//	}
//	Delay_ms(6);
//    SK080G_ResetTG33= 1;     //����
//	SK080G_CountTG11= 1;     //����
//	Delay_ms(6); 
//	for(da_cnt=0;da_cnt<32;da_cnt++)
//	{
//	  if(da&0x01)
//        {
//         SK080G_ResetTG33= 0;     //���
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
// 	      SK080G_CountTG11= 0;     //���
//	      SK080G_CountTG1 = 0;
//	      cnt=0;
//         while(SK080G_ResetTG3==1&&cnt<200)
//	      {
//	       Delay_ms(1);
//	       cnt++;
//	       }   
//         }
//      Delay_ms(6);   
//      SK080G_ResetTG33= 1;     //����
//	  SK080G_CountTG11= 1;     //����
//	  Delay_ms(6); 
//	  da=da>>1;   
//	}
//	cnt=0;
//   while(SK080G_CountTG11==1&&cnt<200)
//    {
//      Delay_ms(1);	
//      cnt++;
//    }   
//	SK080G_ResetTG33= 0;     //���
//	SK080G_ResetTG3 = 0;
//	Delay_ms(6);             //��Լ100us
//    SK080G_ResetTG33= 1;     //����
//	SK080G_CountTG11= 1;     //����	
//}
/*****************************************************************/
//����:����ָ�����е������ļ�
//����:��������
//����: ��
//�޸ļ�¼:
/*****************************************************************/
void SK080G_PlaySoundIndex(uint8 index)
{
	if(index == 0) return;
	SK080G_ResetTG33= 0;     //���
	SK080G_ResetTG3 = 0;
	Delay_ms(2);		     //��Լ100us
	SK080G_ResetTG33= 1;     //���� 
	Delay_ms(2);		     //��Լ100us
	SK080G_ResetTG33= 0;     //���
	SK080G_ResetTG3 = 0;
    SK080G_CountTG11= 0;     //���
	SK080G_CountTG1 = 0;
	Delay_ms(2);		     //��Լ100us
	while(index --)			 //�������м�������
	{
	 SK080G_CountTG11= 1;     //����		
	 Delay_ms(2);		     //��Լ100us
	 SK080G_CountTG11= 0;         //���
	 SK080G_CountTG1 = 0;
	 Delay_ms(2);		     //��Լ100us
	}
	Delay_ms(7);
}
/*********************************************************************/
//����:�ж��Ƿ����ڲ�������
//����:��
//����: 0 û�в���; 1 ���ڲ���
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
   	SK080G_ResetTG33= 0;         //���
	SK080G_ResetTG3 = 0;
	Delay_ms(2);		         //��Լ100us
	SK080G_ResetTG33= 1;         //����
	Delay_ms(2);		         //��Լ100us
	SK080G_ResetTG33= 0; 
	SK080G_ResetTG3 = 0;
	Delay_ms(2);		         //��Լ100us
	SK080G_CountTG11= 0;         //���
	SK080G_CountTG1 = 0;
}
/*********************************************************************/
//����:�ж��Ƿ����ڲ�������
//����:��
//����: 0 û�в���; 1 ���ڲ���
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
 * Description : ��ʼ����buf �е���Ƶ�ļ�������ָ����ļ���
 * Arguments   : buf �� ��Ƶ�ļ�������
 *               len �� �ļ������ų��� 
 *********************************************************************************/
void playSDFile(uint8 len)
{ 	
//  uint8 i=0;
//  while(i < len)    //i�ӵ�һ��ϵ�п�ʼ���곤��Ϊֹ
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
//	  while(SPEAKBUSYFLAG == 1);  //0 û�в���; 1 ���ڲ���
//	}
}
/******************************************************************************
 *  SpeakNum(uint16 numb)
 *  Description : ������ֵֻ������ 
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
 * Description : ���Ų������
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
// 	PLS_SOT[WAVE_count++] = idnumb;   //	���Ѫѹ�� ����ѹ
// 	playSDFile(WAVE_count);
 }
/********************************************************************************
 * Description : ���Ų������
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
// 	PLS_SOT[WAVE_count++] = BPF_SHOUSUOYA_MP3;   //	���Ѫѹ�� ����ѹ
// 	if(mmHg_Kpa==0)
//     {				   
//    	ISD_SpeakNum(PRE_SYS.Val);
// 	    PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	���׹���
// 	    PLS_SOT[WAVE_count++] = BPF_SHUZHANGYA_MP3;  //	��ѹ
//     	ISD_SpeakNum(PRE_DIA.Val);
//    	PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	���׹���
//     }
//     else
//       {
//       	
//        i = mmhg_chance_kpa(PRE_SYS.Val);
//       	ISD_SpeakNum(i/10);
//       	PLS_SOT[WAVE_count++] = BPF_DIAN_MP3;   //	��
//       	ISD_SpeakNum(i%10);
// 	//    PLS_SOT[WAVE_count++] = BPF_KP_MP3;        //	kap
// 	    PLS_SOT[WAVE_count++] = BPF_SHUZHANGYA_MP3;  //	��ѹ
// 	    i = mmhg_chance_kpa(PRE_DIA.Val);
//     	ISD_SpeakNum(i/10);
//     	PLS_SOT[WAVE_count++] = BPF_DIAN_MP3;   //	��
//     	ISD_SpeakNum(i%10);
//    //	PLS_SOT[WAVE_count++] = BPF_KP_MP3;        //	kap
//       } 
//
// 	PLS_SOT[WAVE_count++] = BPF_MAIBO_MP3;       //	����ÿ����
// 	ISD_SpeakNum(PLSCNT);
// 	PLS_SOT[WAVE_count++] = BPF_CHI_MP3;         //	��
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
//	 	PLS_SOT[WAVE_count++] = BPF_SHOUSUOYA_MP3;   //	���Ѫѹ�� ����ѹ
//	 	ISD_SpeakNum(PRE_SYS.Val);
//	 	PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	���׹���
//	 	PLS_SOT[WAVE_count++] = BPF_SHUZHANGYA_MP3;  //	��ѹ
//	 	ISD_SpeakNum(PRE_DIA.Val);
//	 	PLS_SOT[WAVE_count++] = BPF_MMHG_MP3;        //	���׹���
//	 	PLS_SOT[WAVE_count++] = BPF_MAIBO_MP3;       //	����ÿ����
//	 	ISD_SpeakNum(PLSCNT);
//	 	PLS_SOT[WAVE_count++] = BPF_CHI_MP3;         //	��
//	 	playSDFile(WAVE_count);
	 }

void BPPLAYWHO(void)	        //����WHO
{
//	 if((PRE_SYS.Val>=90)&&(PRE_DIA.Val>=60)) 
//	 {
//	   BPPLAY_ONE_INFOEND(BPF_WHO_MP3);     //	��������������֯��׼,����Ѫѹ.
//	   if((PRE_SYS.Val>=140)||(PRE_DIA.Val>=90)) 
//	     {//ƫ��
//	     	 BPPLAY_ONE_INFOEND(BPF_HIGH_MP3);
//	     } 
//	      else
//	       {//����
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
//	else if(PRE_SYS.Val<140&&PRE_DIA.Val<90)    //С��4.7V
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