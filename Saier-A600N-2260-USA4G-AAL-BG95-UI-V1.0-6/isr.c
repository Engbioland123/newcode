#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"
//***************************TIMER0中断服务子程序****************************************
//	
//
//
//***************************************************************************************
void __attribute((interrupt(0x14))) ISR_TM0(void)
{   
	uchar i;
//	uint32	lu32v_filter_buff;
	if(_ptm1af)
	{
		_ptm1af = 0;			
	}
	if(_ptm2af)
	{
		_ptm2af = 0;

	 //   _pa5 =1;//~_pc0;
//*********************这里面加中断要处理的代码********************
//*****************************************************************     
     switch(counter2ms)
      {
	  case 0: for(i=0;i<7;i++)
	          {
	           P0_ad[i]=P0_ad[i+1];
	          }
			  P0_ad[7]=Samlpe_Adc(4);       //an6是PGA1
			  counter2ms+=1;
			  break;
	  case 1: P012_avg =0;
              for(i=0;i<8;i++)
              {
               P012_avg = P012_avg + P0_ad[i]; 
              }
              P012_avg = P012_avg >> 3;
 //             pres_avl=pres(P012_avg);           //测试参7电源电压进行采样看是否稳定
 //////////////////////////////////////////////////////////////////////////////////////
              pres_avl.Val = 0;
              if(P012_avg<=(pres_ad_0))
                {
	             pres_avl.Val=0;
	            } 
	          else if( P012_avg<=pres_ad_100 )
	           {
	            pres_avl.Val = P012_avg - pres_ad_0;
	            pres_avl.Val = pres_avl.Val * 100;
	            pres_avl.Val = pres_avl.Val /(pres_ad_100-pres_ad_0);
	           }
	          else if( P012_avg<=pres_ad_200 )
	           { 
	            pres_avl.Val = P012_avg - pres_ad_100;
	            pres_avl.Val = pres_avl.Val * 100;
	            pres_avl.Val = pres_avl.Val /(pres_ad_200-pres_ad_100);
	            pres_avl.Val = pres_avl.Val + 100;
	           }
	          else if( P012_avg<=pres_ad_300 )
	           {
	            pres_avl.Val = P012_avg - pres_ad_200;
	            pres_avl.Val = pres_avl.Val * 100;
	            pres_avl.Val = pres_avl.Val /(pres_ad_300-pres_ad_200);
	            pres_avl.Val = pres_avl.Val + 200;
	            if(pres_avl.Val>295)
	            {
	              Over300++;	
	            }
	           }
	          else 		                  
               {
	             pres_avl.Val=299;
	             Over300++;
               }
              if(Over300>3)
               {
	            MODEFLAG.bits.b2 =1;                  //压力过300
	           }
		      counter2ms +=1;
                   break;	           
	  case 2: for(i=0;i<7;i++)
	          {
	           P1_ad[i]=P1_ad[i+1];  
	          }
			  P1_ad[7]=Samlpe_Adc(5)>>2;       //an5是VSCF  
		  
			  counter2ms+=1;
			  break;
	  case 3: //P0_avg=0;
              for(i=1;i<8;i++)
              {
               P1_ad[0]=P1_ad[0]+P1_ad[i]; 
              }	
              P1_ad[0] = P1_ad[0] >> 3; 
	          P1VAL_B = (uchar)(P1_ad[0]);       
	          dowm_time+=1;		                 //灭心形符时间定时；
			  counter2ms=0;		                 //counter2ms只能是0到3
			  close_time+=1;
			  counter9ms+=1;                     //4次中断包括中断内处理的时间为9.06MS
			  PLSFTM+=1;                         //记录波和波之间的时间 
			  PLSFTM1+=1;                        //记录波峰到确认波之间的时间 
	          FTM31+=1;  
	          S_PCNT+=1;
	          P_PWMCNT+=1;
////////////////////////////////////////////////////////////////////	           
	          if(MS10JSQ)
	          MS10JSQ--;
              Timer_Flag_t10ms_Count++;
			  if(Timer_Flag_t10ms_Count >= 50)       // 500ms 时间到
			    {	
		          if(timegsm)timegsm--;
                  Timer_Flag_t10ms_Count = 0;
                }	          
////////////////////////////////////////////////////////////////////
              s_pres_avl15+=1;      
              if(FTM31==0x4CD8)                  //测量时间超过180秒
              {                  
               MODEFLAG.bits.b2 =1;              //e2flag=0x0f;                    
			  }  

//	         if(s_pres_avl15>660)                    
//			  {	
//			  	S_PCNT2	= old_pres_avl;   	
//			  }
//			  
//	         if(S_PCNT15>7)                    
//			  {			  
//		   	   s_pres_avl15-=1;
//		   	   S_PCNT15=0; 
//		   	   if(old_pres_avl-s_pres_avl15>15)     
//			     {
//			         s_pres_avl15=old_pres_avl-10;	
//			     }
//			  }			  
			  
	         if(S_PCNT>7)                    
			  {
			   s_pres_avl+=1;
			  if(s_pres_avl>280)
			   {
			  	 s_pres_avl=280;
			   }
			   S_PCNT=0;	
			  }
			  if(P_PWMCNT>1)
			  {
			   if(pres_avl.Val<20) 
			     {
			      pwm_val1+=1;
			     } 
			  	P_PWMCNT=0;
 		       if(pres_avl.Val<=s_pres_avl) 
			    {
			  	   pwm_val1+=1;
			      if(s_pres_avl-pres_avl.Val>20)     
			        {
			         s_pres_avl-=25;	
			        }
			      if(pres_avl.Val>150) 
			        {
			         pwm_val1+=1;
			        }	  
			    }
			  }                                               
			  break;
		default :   break;
	  }	
	 // _pa5 =0;
	}	
//*****************************************************************  

}

/********************************************************************
Function:	UART_ISR
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
//@------------uart--------------@

/********************************************************************
Function:	UART_ISR
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
//@------------uart--------------@

void __attribute((interrupt(UART_VECTOR)))  UART_ISR()
{	
	uint8	lu8v_isr_temp0;
	//clear urf flag
   	if(_perr || _nf || _ferr || _oerr)		// error found?
   	{
   	   lu8v_isr_temp0 = _usr;				//read USR to clear error flag 
   	   lu8v_isr_temp0 =  _txr_rxr;				//read USR to clear error flag 	   	       
   	}
   	else									// no error found
   	{
//	   #define TI			            gu8v_uart_flag.bits.b6
//     #define RI		   	   	  	   	   
   	   if(_rxif)							//RXR	data register has available	data
  	   {
          RI=1;
          _rxif=0;
  	   	  //receive data from PC
    	  GCC_NOP();
   	   }
   	   if(_txif)							//TXR	data register is empty
   	   {
   	   	  TI=1;
	 	  _txif=0;
	   }
	}	
}


//***************************TIMER1中断服务子程序****************************************
//
//
//
//***************************************************************************************
void __attribute((interrupt(0x0c))) ISR_TM1(void)
{
 											      
}

//***************************************************************************************
void __attribute((interrupt(0x20))) ISR_TB0(void)
{	
	_tb0f=0;
	gbv_tb0_flag = 1;
	R_10ms_COUNT++;
	if(R_10ms_COUNT>=60)
	{
		R_10ms_COUNT =0;
//		B_500ms = ~B_500ms;			
	}
	KEYSCAN();		
	if(Uart_overtine1==1)
	{
	  Uart_overtine	=1;
	}
	Uart_overtine1 =1;
    GCC_NOP();
}
//***************************************************************************************
void __attribute((interrupt(0x24))) ISR_TB1(void)
{	
    TIMERFLAG.bits.TB1_INT_625 = 1;	
	GCC_CLRWDT1();
	GCC_CLRWDT2();				
	TIMERFLAG.bits.TB1_INT = 1;						
//................................................
	R_CLOCK_SECOND+=1;
	if(R_CLOCK_SECOND&0x01)
	{
		//计算溢出时间
		R_TIMEOUT_SECOND ++;
		if(R_TIMEOUT_SECOND == 0)
		{
			R_TIMEOUT_SECOND = 0xff;	
		}					
	}
	if(MODEFLAG.bits.DisplayTime)
	{
		//COL显示 05s闪烁一次
		if(SEG[10].bits.b3)
		{
			SEG[10].bits.b3 = 0;
		}
		else
		{
			SEG[10].bits.b3 = 1;				
		}
	}
		
	if(BTT_OFF)
	{
	    if(R_CLOCK_SECOND%2)
		{
            SEG[22].bits.b4 = 1;
		}
		else
		{
			SEG[22].bits.b4 = 0;
		}
	}
//	GPRST =1;
	if(GPRST)
	{
	    if(R_CLOCK_SECOND%2)
		{
            SEG[22].bits.b3 = 1;
		}
		else
		{
			SEG[22].bits.b3 = 0;
		}
	}

    Up_dateBTT = 1;		
	MODEFLAG.bits.Up_dateTime = 1;			
	if(R_CLOCK_SECOND==120)
	{
   
		R_CLOCK_SECOND=0;
		R_CLOCK_MINUTE++;

		if(R_CLOCK_MINUTE==60)
		{
			R_CLOCK_MINUTE=0;
			R_CLOCK_HOUR++;
			if(R_CLOCK_HOUR==24)
			{
				R_CLOCK_HOUR=0;
				TIMERFLAG.bits.NewDay=1;
			}
		}
	}
	GCC_NOP();
}
/********************************************************************
Function:	fun_int0_isr
INPUT	:	
OUTPUT	:	
NOTE	:   场い耞0 
*******************************************************************/
void __attribute((interrupt(0x04)))  func_int0_isr()
{
	_int0f = 0;	
	if(FUL_DET==0)
	{
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();				
		if(FUL_DET==0)
		{		
			if(TIME_TEEP_flag)
			{
			    EEPROM_WRITING_INT(0x0D,R_YEAR);
			    EEPROM_WRITING_INT(0x0E,R_MONTH);	
				EEPROM_WRITING_INT(0x3D,R_DAY);
			    EEPROM_WRITING_INT(0x3E,R_CLOCK_HOUR);
			    EEPROM_WRITING_INT(0x3F,R_CLOCK_MINUTE);
				TIME_TEEP_flag =0; 
			}   	
			_wdtc = 0B11111111;	    //如果这时去了电池就RST
		}
	}
}




/********************************************************************
Function:	fun_int1_isr
INPUT	:	
OUTPUT	:	
NOTE	:   场い耞1
*******************************************************************/
void __attribute((interrupt(0x08)))  func_int1_isr()
{
	_int1f = 0;
}
