#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

void	KEYSCAN_INIT(void)
{
	gu8v_KeyDown.Val = 0;			
	gu8v_KeyOld = 0;
	gu8v_KeyNoChangedTime = 0;
	gu8v_KeyPress. Val= 0;
	gu8v_KeyUp.Val = 0;
	gu8v_KeyLast = 0;
	gu8v_Keypress_time = 0;
	gu8v_KeyCurrent.Val = 0;		
}
void	KEYSCAN(void)
{
	gu8v_wake_up_time ++;
	TIMERFLAG.bits.TB0_INT = 1;
	if(TIMERFLAG.bits.Display)
	{
		if(R_DISPLAYTIME)      //为SETTIME计时用
		{
			R_DISPLAYTIME--;
		}		
	}
	gu8v_KeyCurrent.Val = 0;   //当前有没有键下去

//	if(GPIO_MODEsub == 0 && GPIO_MODEadd == 0)
//	{
//		gu8v_KeyCurrent.bits.b5 = 1;
//	}
//	

//
//	
//	if(GPIO_MODEsub == 0)
//	{
//		gu8v_KeyCurrent.bits.b0 = 1;
//	}

	if(GPIO_STARTKEY == 0 && GPIO_RECALLKEY == 0)
	{
		gu8v_KeyCurrent.bits.b0 = 1;
	}
	
	if(GPIO_STARTKEY == 0 && GPIO_SETKEY == 0)
	{
		gu8v_KeyCurrent.bits.b4 = 1;
	}	

	if(GPIO_SETKEY == 0)		 //为组合区分							
	{
		gu8v_KeyCurrent.bits.b1 = 1;
	}
			
	if(GPIO_STARTKEY == 0)									
	{
		gu8v_KeyCurrent.bits.b2 = 1;
	}
	
	if(GPIO_RECALLKEY == 0)									
	{
		gu8v_KeyCurrent.bits.b3 = 1;
	}
	if(GPIO_RECALLKEY == 0 && GPIO_SETKEY == 0)
	{
		gu8v_KeyCurrent.bits.b6 = 1;
	}			

	if(gu8v_KeyCurrent.Val != gu8v_KeyOld)	 //防抖动设置		
	{
		gu8v_KeyNoChangedTime = 0;         
		gu8v_KeyOld = gu8v_KeyCurrent.Val;
		return;
	}
	else
	{	
		gu8v_KeyNoChangedTime++;	     				
		if(gu8v_KeyNoChangedTime >= LU8C_KEY_DEBOUNCE_TIME)	 //50 如果KEYSCAN是10MS一次那么就是50MS
		{
			gu8v_KeyNoChangedTime = LU8C_KEY_DEBOUNCE_TIME;	
			gu8v_KeyPress.Val = gu8v_KeyOld;      		//
		    gu8v_KeyDown.Val = gu8v_KeyPress.Val & (gu8v_KeyPress.Val ^ gu8v_KeyLast);// 
			gu8v_KeyUp.Val |= gu8v_KeyLast&(~gu8v_KeyPress.Val);     //	
		    gu8v_KeyLast = gu8v_KeyPress.Val;          // 
		}
	}


	if(gu8v_Keypress_time==600)
	{
		//如果按键1 长按时间超过2S 则认为是长按按键 1是10ms
		if(gu8v_KeyCurrent.bits.b0)
		{
			KEYFLAG.bits.STARTKEYRecallKeyHold = 1;
		}
		else if(gu8v_KeyPress.bits.b4) 
		{
			KEYFLAG.bits.STARTKEYSetKeyHold = 1;								
		}		
		else if(gu8v_KeyCurrent.bits.b6)
		{
			KEYFLAG.bits.RecallSetKeyHold = 1;
		}
		else if(gu8v_KeyPress.bits.b1) 		
		{
			KEYFLAG.bits.SetKeyHold = 1;						//					
		}
		else if(gu8v_KeyPress.bits.b2) 		
		{
			KEYFLAG.bits.STARTKEYHold = 1;						//					
		}		
		//如果按键2 长按时间超过2S 则认为是长按按键
		else if(gu8v_KeyPress.bits.b3) 
		{
			KEYFLAG.bits.RecallKeyHold = 1;								
		}
		else 
		{
		}
		gu8v_Keypress_time = 601;					
	}
	else if(gu8v_Keypress_time<600)
	{
		//如果按键1 按下时间小于2S 则认为是短按按键
		if(gu8v_KeyUp.bits.b1) 		
		{
			KEYFLAG.bits.SetKey = 1;	
		}
		//如果按键1 按下时间小于2S 则认为是短按按键	
		else if(gu8v_KeyUp.bits.b2) 
		{
			
			KEYFLAG.bits.StartKey = 1;	
							
		}
		else if(gu8v_KeyUp.bits.b3) 
		{
			
			KEYFLAG.bits.RecallKey = 1;	
							
		}	
		else
		{
			
		}
	}
	else
	{
		gu8v_Keypress_time = 601;				//Key time more than 3 s don't count,b.
												//because of judge gu8v_Keypress_time==5
	}
	
	//
//	if(gu8v_KeyUp.bits.b0)
//	{
//		KEYFLAG.bits.Modesub  = 1;
//	}
//	if(gu8v_KeyUp.bits.b4)
//	{
//		KEYFLAG.bits.Modeadd  = 1;
//	}	
//	if(gu8v_KeyUp.bits.b2)
//	{
//		KEYFLAG.bits.StartKey  = 1;
//	}
//	if(gu8v_KeyUp.bits.b3)
//	{
//		KEYFLAG.bits.RecallKey  = 1;
//	}	
	
	//判断是否有按键按下
	//有：清除睡眠计数，并长按计数
	if(gu8v_KeyPress.bits.b1 || gu8v_KeyPress.bits.b2 || gu8v_KeyPress.bits.b3)
	{
		gu8v_Keypress_time++;		
	}
	else
	{
		gu8v_Keypress_time = 0;
		
	}	
	gu8v_KeyUp.Val = 0;	
//	gu8v_KeyUp.Val = 0;
//	gu8v_KeyDown.Val = 0;

}
void	SBR_UPDATE_BTT(void)
{
	if(Up_dateBTT)
	{
	
		Up_dateBTT = 0;
		if(FUL_DET ==0)
          {//表示的是有插电源线在充电
	      	BTT_OFF=0;
	      	if(btt_cnt>2)
	      	{
	      		btt_cnt=0;     
	      	}
	      	btt_cnt++;
	        SBR_DISP_DOT_BTT(btt_cnt);	        	
	      }
	      else
	      {
	      	LOW_V =Samlpe_Adc1(2);
	      	if(LOW_V>400)
	      	{  //4.1
	      	 SBR_DISP_DOT_BTT(2);
	      	 BTT_OFF=0;
	      	}
	      	else if(LOW_V>385)
	      	{  //3.9 
	      	 SBR_DISP_DOT_BTT(2);
	      	 BTT_OFF=0;
	      	}
	      	else if(LOW_V>370)
	      	{  //3.8
	      	 SBR_DISP_DOT_BTT(2);
	      	 BTT_OFF=0;
	      	}
	      	else if(LOW_V>360)
	      	{  //3.7
	      	   SBR_DISP_DOT_BTT(1);
	      	 //  BTT_OFF=1;
	      	}
	      	else
	      	{
	      	 // BTT_OFF=1;
	      	   SBR_DISP_DOT_BTT(1);
	      	}
	      }	
	}
}
//void	SBR_UPDATE_BTT(void)
//{
//	if(Up_dateBTT)
//	{
//	    	Up_dateBTT = 0;
//	      	LOW_V =Samlpe_Adc1(2);
//	       if(LOW_V>500)
//	      	{  //4 5.5V
//	      	 SBR_DISP_DOT_BTT(4);
//	      	 BTT_OFF=0;
//	      	}
//	      	else if(LOW_V>460)
//	      	{  //3 5V 
//	      	 SBR_DISP_DOT_BTT(3);
//	      	 BTT_OFF=0;
//	      	}
//	      	else if(LOW_V>432)
//	      	{  //2 4.4V
//	      	 SBR_DISP_DOT_BTT(2);
//	      	 BTT_OFF=0;
//	      	}
//	      	else if(LOW_V>396)
//	      	{  //2 4.4V
//	      	 SBR_DISP_DOT_BTT(1);
//	      	 BTT_OFF=0;
//	      	}	      	
//	      	else
//	      	{
////	      	  BTT_OFF=0;
////	      	  SBR_DISP_DOT_BTT(1);
//	      	}
//	}
//}
//void	SBR_UPDATE_BTT(void)
//{
//	if(Up_dateBTT)
//	{
//	    	Up_dateBTT = 0;
//	      	LOW_V =Samlpe_Adc1(2);
//	       if(LOW_V>500)
//	      	{  //4 5.5V
//	      	 SBR_DISP_DOT_BTT(4);
//	      	 BTT_OFF=0;
//	      	}
//	      	else if(LOW_V>460)
//	      	{  //3 5V 
//	      	 SBR_DISP_DOT_BTT(3);
//	      	 BTT_OFF=0;
//	      	}
//	      	else if(LOW_V>432)
//	      	{  //2 4.4V
//	      	 SBR_DISP_DOT_BTT(2);
//	      	 BTT_OFF=0;
//	      	}
//	      	else if(LOW_V>396)
//	      	{  //2 4.4V
//	      	 SBR_DISP_DOT_BTT(1);
//	      	 BTT_OFF=0;
//	      	}	      	
//	      	else
//	      	{
////	      	  BTT_OFF=0;
////	      	  SBR_DISP_DOT_BTT(1);
//	      	}
//	}
//}

//
//void	SBR_UPDATE_BTT(void)                //20161014
//{
//   if(SEG[27].bits.b3)
//    {
//           LOW_V =Samlpe_Adc1(2);          //所采样的值是4分之一的VDD的电压值   
//		   if(LOW_V<432)		               //4.6v
//			 {
//			  LOW_V =Samlpe_Adc1(2);           //所采样的值是4分之一的VDD的电压值   
//
//		      if(LOW_V<432)		               //4.6v
//			  {
//			     SBR_DISP_DOT_LO_ON();	     //显示低电压//20161014
//			  }	
//			  else
//			  {
//			  	 SBR_DISP_DOT_LO_OFF();	
//			  }	
//			 }		   	
//    }    
//}
//

//;---------------------------------------------------------------------------
void	SBR_UPDATE_TIME(void)
{
	if(MODEFLAG.bits.Up_dateTime)
	{
		MODEFLAG.bits.Up_dateTime = 0;
		R_TEMPDATA.BYTE.BYTE_L = R_CLOCK_HOUR;
		SBR_DISP_HOUR_ON();		
		R_TEMPDATA.BYTE.BYTE_L = R_CLOCK_MINUTE;
		SBR_DISP_MINUTE_ON();		
		R_TEMPDATA.BYTE.BYTE_L = R_MONTH;
		SBR_DISP_MONTH_ON();
		R_TEMPDATA.BYTE.BYTE_L = R_DAY;
		SBR_DISP_DAY_ON();	
		SBR_DISP_DOT_COLD_ON();								
	
	}
}

//;---------------------------------------------------------------------------
//void	SBR_UPDATE_TIME(void)
//{
//	if(MODEFLAG.bits.Up_dateTime)
//	{
//		MODEFLAG.bits.Up_dateTime = 0;
//		
////		R_DISPLAY_COUNT++;
////		if(R_DISPLAY_COUNT<10)
////		{		
//			R_TEMPDATA.BYTE.BYTE_L = R_CLOCK_HOUR;
//			SBR_DISP_HOUR_ON();		
//			R_TEMPDATA.BYTE.BYTE_L = R_CLOCK_MINUTE;
//			SBR_DISP_MINUTE_ON();		
//////			SBR_DISP_DOT_COL_ON();
////			MODEFLAG.bits.b3 =1;	                  //时间秒点闪烁
////		}
////		else if(R_DISPLAY_COUNT<20)
////		{
//			R_TEMPDATA.BYTE.BYTE_L = R_MONTH;
//			SBR_DISP_MONTH_ON();
//			R_TEMPDATA.BYTE.BYTE_L = R_DAY;
//			SBR_DISP_DAY_ON();	
//////			MODEFLAG.bits.b3 =0;	                  //时间秒点闪烁			
//			SBR_DISP_DOT_COLD_ON();								
////		}
////		else
////		{
////			R_DISPLAY_COUNT = 0;
////		}
//		
//		
//		
//	}
//}

/*******************************************************************************************
** 函数名称: key_scan
** 函数描述: 扫描键
** 输入参数: 无
** 输出参数: 1,START 2, SET 3, MOMERY 4,MODE  5, SET长键 6，MOMERY长键
*******************************************************************************************/
uint8 key_scan(void)
{
//#define	SetKey		b0	//1=SET KEY DOWN
//#define	StartKey	b1	//1=START KEY DOWN
//#define	RecallKey	b2	//1=RECALL KEY DOWN
//#define	RecallSetKeyHold		b3	//1=MODE KEY DOWN
//#define	SetKeyHold	b4	//1=SET KEY HOLD 3s
//#define	RecallKeyHold	b5	//1=RECALL KEY HOLD 3s
//#define	SetKHing	b6	//扫描按键内部使用
//#define	ReacllKHing	b7	//扫描按键内部使用
// R_KEYSTATUS  按
	if(KEYFLAG.bits.StartKey)
 	{
		KEYFLAG.bits.StartKey=0;    				
		return(1);
	}
	if(KEYFLAG.bits.SetKey)
	{
		KEYFLAG.bits.SetKey=0;    				
		return(2);
	}
	if(KEYFLAG.bits.RecallKey)
	{
		KEYFLAG.bits.RecallKey=0;    				
		return(3);
	} 
	if(KEYFLAG.bits.RecallSetKeyHold)
	{
		KEYFLAG.bits.RecallSetKeyHold=0;    				
		return(4);
	}
	if(KEYFLAG.bits.SetKeyHold)
	{
		KEYFLAG.bits.SetKeyHold=0;    				
		return(5);
	}
	if(KEYFLAG.bits.RecallKeyHold)
	{
		KEYFLAG.bits.RecallKeyHold=0;    				
		return(6);
	} 
	if(KEYFLAG.bits.STARTKEYSetKeyHold)
	{
		KEYFLAG.bits.STARTKEYSetKeyHold=0;    				
		return(7);
	}
	if(KEYFLAG.bits.STARTKEYRecallKeyHold)
	{
		KEYFLAG.bits.STARTKEYSetKeyHold=0;    				
		return(8);		
	}
	if(KEYFLAG.bits.STARTKEYHold)
	{
		KEYFLAG.bits.STARTKEYHold=0;    				
		return(10);		
	}	
	if(FUL_DET==0)
	{	
	    return(9);
	}	
	return(0);
}
