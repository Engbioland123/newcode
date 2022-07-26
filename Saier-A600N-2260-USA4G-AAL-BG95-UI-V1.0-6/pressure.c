#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

/******************************************************************************************* 
** 函数名称: TEST_CON
** 函数描述: 密闭测度试
** 输入参数: 无 
** 输出参数: 无  
*******************************************************************************************/
void TEST_CON(void)
{
     uint8 i;	 
     LCD_INIT_OFF();	                  //清屏
     MODEFLAG.bits.b0 =1;                      //显示时间刷新时间;
     MODEFLAG.bits.b3 =1;

     SBR_UPDATE_TIME();
     SBR_UPDATE_BTT();
     SBR_DISP_DOT_COL_ON();
	 if(MODEFLAG.bits.b5==0)
      { 
       	SBR_DISP_DOT_U2_OFF();     
        SBR_DISP_DOT_U1_ON();
        
      }
     else
      {
        SBR_DISP_DOT_U1_OFF();
        SBR_DISP_DOT_U2_ON();
      }
	 disp_dia(0);			           //还要显示什么信息在这里加就好了	  att
	 Delay_ms(18000);
	   
////////////////////////////////////////////////////////////////////////  归0	   
 	 R_TEMPDATA.Val =0;
	 for(i=0;i<16;i++) 
	 {
	   R_TEMPDATA.Val +=P012_avg;//Samlpe_Adc1(4);       //an6是PGA1
	   Delay_ms(35);
	 }
	 R_TEMPDATA.Val = R_TEMPDATA.Val/16;
	 if(pres_ad_0 > R_TEMPDATA.Val)
	 {
	 	if(pres_ad_0 - R_TEMPDATA.Val < 50)
	 	{
	 	  i = pres_ad_0 - R_TEMPDATA.Val;
	 	  pres_ad_0 = pres_ad_0 - i;
	 	  pres_ad_100 = pres_ad_100 - i;
	 	  pres_ad_200 = pres_ad_200 - i;
	 	  pres_ad_300 = pres_ad_300 - i;  
	 	}	 	
	 }
	 else
	 {
	    if(R_TEMPDATA.Val - pres_ad_0 < 50)
	 	{
	 	  i = R_TEMPDATA.Val - pres_ad_0;
	 	  pres_ad_0 = pres_ad_0 + i;
	 	  pres_ad_100 = pres_ad_100 + i;
	 	  pres_ad_200 = pres_ad_200 + i;
	 	  pres_ad_300 = pres_ad_300 + i;
	 	}	 	
	 }
////////////////////////////////////////////////////////////////////////	   
       
	 LOW_V =Samlpe_Adc1(2);          //所采样的值是4分之一的VDD的电压值   
	 if(LOW_V<360)		               //2.2
	 {
	   LOW_V =Samlpe_Adc1(2);           //所采样的值是4分之一的VDD的电压值   
	   if(LOW_V<360)		               //2.2
		{
		  BPPLAY_ONE_INFOEND(BPF_LOWPOWER_MP3);
//		  SBR_DISP_DOT_LO_ON();	      //显示低电压
//	      R2FLAG.bits.b7 = 1;        //1:低电压
	      REL1 = 0; 
	      BTT_OFF=1;
	      SBR_DISP_DOT_BTT(1);
	      Delay_ms(30000);
	      return;
		}
	 } 
     REL1 = 1;                       //电减阀 ON 		  
     MODEFLAG.bits.b2 =0;
     FTM31 = 0;							   //开始计时180秒测试过程
     COUNT1_JIA = 0;                      
     do
	  {
	    PUMPPRE=PUMPPRE+30;	           //加压和再加压
		if(PUMPPRE>=290)
		  {
		    PUMPPRE=290;
		  }
		if(PUMPPRE <=290 &&COUNT1_JIA <= 3)//再加压的数值不能大于283也就是加压次数只能是3次以下
		  {
		    ERFLAG.Val=0;                   //清除错误标志
		    DEFLATION();			           //调用测试
		  }
		else
		  {
		    ERFLAG.bits.b0=0;              //如果需要加压到283以上就显EE无法量测
		    ERFLAG.bits.b2=1;		       //退出显示错误EE
		  }
      }
	 while(ERFLAG.bits.b0==1);           //没有需要再加压往下,再加压三次也要退出  
	 SBR_DISP_DOT_JIA_OFF();
     SBR_DISP_DOT_JIAN_OFF();
     REL1 = 0;                          //关电减阀
     STP_PUMP_OFF();                    // 在加压过程退出就要在这里关PUMP马达
     if(ERFLAG.Val==0)		            //判断没有没有发生错误
	   { 
	   	
	
		PRE_SYS.Val=135;
		PRE_DIA.Val=120;
		PLSCNT=80;
		//	 SYSDAS_DE();	 
			 			
         //高压大于所加压力一20或低压小于25或低压大于高压或//应该小于加压点的20mmHg//低压要求大于45//高压在于低压    
		 if((PRE_SYS.Val-PRE_DIA.Val>150)||(PRE_DIA.Val<25)||(PRE_DIA.Val>PRE_SYS.Val)||(PLSCNT<38)||(PLSCNT>204))  
		   {
			   SBR_DISP_E4_ON();			        //
			   SBR_DISP_DOT_HEART_OFF();  
			   BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	              close_time =16550;      //按键中断后能马上关机  


		   }
		   else
		      { 
				  OLD_PRE_SYS = PRE_SYS.Val; 
				  OLD_PRE_DIA = PRE_DIA.Val;
				  OLD_PLSCNT = PLSCNT;  	
		          disp_sys(PRE_SYS.Val);		   
                  disp_dia(PRE_DIA.Val);
                  disp_pu(PLSCNT);
                  SBR_DISP_DOT_ASCVD_OFF();
                  if((PRE_SYS.Val-PRE_DIA.Val)>=60)
                   {
                   	  SBR_DISP_DOT_ASCVD_ON(); 
                   	  ASCVD =1;                   
                   } 
                  else
                   {
                   	  SBR_DISP_DOT_ASCVD_OFF(); 
                   	  ASCVD =0; 
                   }                 
                  SBR_DISP_DOT_HEART_OFF();
                  if(IHB_COUNT>2)
                    {
                   	  //在这里显示心，IHB
                      SBR_DISP_DOT_HEART_ON();       //显示心跳 
                      SBR_DISP_DOT_HEART2_ON();                 
                    }
                  DISPLAYWHO();  
                   _pe7 =1;
	              GSM_PWRKEY =0;               //
			      BPPLAYINFOEND();
			      BPPLAYWHO();	             
		          Delay_ms(5000);				   
		          GSM_PWRKEY =1; 
		          Delay_ms(12000);
		          GSM_PWRKEY =0;                  
                  GSM_OFF_ON =0;
//////////////////////////////////////////////////////////////////////////	
                  SBR_DISP_DOT_GPRST_ON();
                  SBR_DISP_DOT_GPRSS_ON();				   
			      test_data_int();       //无更新时，用默认的数据。 
                  keyvalGSM =START_GSM();
///////////////////////////////////////////////////////////////////////////	      
			      if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				   {
					 //到了这里的话，就说已经更新了时间，在这时存记录值就不会时间了错
				     if(MODEFLAG.bits.b5==0)
					  { 
						 GSM_DATA_CNT = SBR_EEPROM_READDATA(0x3A);
					   	 GSM_DATA_CNT++;
					   	 if(GSM_DATA_CNT>=C_Memory_Num)
					   	 {
						 	GSM_DATA_CNT =C_Memory_Num;
						 }
						 EEPROM_WRITING(0x3A,GSM_DATA_CNT);
					  }
					 else
					  {
					     GSM_DATA_CNT = SBR_EEPROM_READDATA(0x3B);
				         GSM_DATA_CNT++;
				         if(GSM_DATA_CNT>=C_Memory_Num)
				       	 {
				       	 	GSM_DATA_CNT =C_Memory_Num;
				       	 }
				         EEPROM_WRITING(0x3B,GSM_DATA_CNT);
				      }			       	
			       	 SBR_SAVE_MEMORY(); 
				     close_time =15500; 
//				     KEYFLAG.Val = 0;
				     return;
			       }     
//////////////////////////////////////////////////////////////////////////	                 
///////////////////////////////////////////////////////////////////////////	
                  if(keyvalGSM==0)        //如果一次不成功再发一次
				   {
 			         Delay_ms(15000);				   
			    	 keyvalGSM =START_GSM();
				   }			      
			      if(MODEFLAG.bits.b5==0)
				   { 
					 GSM_DATA_CNT = SBR_EEPROM_READDATA(0x3A);
				   	 GSM_DATA_CNT++;
				   	 if(GSM_DATA_CNT>=C_Memory_Num)
				   	 {
				 	   GSM_DATA_CNT =C_Memory_Num;
					 }
					 EEPROM_WRITING(0x3A,GSM_DATA_CNT);
				   }
				  else
				   {
				     GSM_DATA_CNT = SBR_EEPROM_READDATA(0x3B);
				     GSM_DATA_CNT++;
				     if(GSM_DATA_CNT>=C_Memory_Num)
				   	 {
				       GSM_DATA_CNT =C_Memory_Num;
				     }
				     EEPROM_WRITING(0x3B,GSM_DATA_CNT);
				   }			       	
			      SBR_SAVE_MEMORY(); 
//////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////	      
			      if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				   {
					  close_time =15500; 
					  return;
				   }     
////////////////////////////////////////////////////////////////////////////	
    
					   
				  if(keyvalGSM==0)
				   {
				   	  GPRST =0; 
				   	//在这里显示错误码
				   	  GSM_OFF_ON =1;
				   	  GSM_OFF();           //关模组
				      if(step <= 26)
				       {
				          step =7;	
				       }
				      else
				       {
				          step =8;	
				       }
				      SBR_DISP_E_NO(step);
                      SBR_DISP_DOT_GPRST_OFF();
                      SBR_DISP_DOT_GPRSS_OFF();					   	 
				   	  Delay_ms(40000);
/////		          BPPLAY_ONE_INFOEND(BPF_GPRS_ERR_MP3);   //您当前的网络信号弱，数据已保存，下次测量成功后上传；
///////////////////////////////////////////////////////////////////////////	      
			      	  if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				       {
					      close_time =15500; 
	//				      KEYFLAG.Val = 0;
					      return;
				       }     
//////////////////////////////////////////////////////////////////////////			                     
//                     Delay_ms(20000); 
//                     disp_sys(PRE_SYS.Val);		   
//                     disp_dia(PRE_DIA.Val);
//                     disp_pu(PLSCNT);
                       disp_sys(OLD_PRE_SYS);		   
                       disp_dia(OLD_PRE_DIA);
	                   disp_pu(OLD_PLSCNT);
///////////////////////////////////////////////////////////////////////////	      
			      	  if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				       {
					      close_time =15500; 
	//				      KEYFLAG.Val = 0;
					      return;
				       }     
//////////////////////////////////////////////////////////////////////////	                                 
				   }
				   else
				   {
				     do
				     {
				       UPDATA_MEMORY(GSM_DATA_CNT);
				   	   keyvalGSM=GSM_STNT_DATA();  	   				   	   
				   	   if(keyvalGSM==0)
				   	     {  //这里是在传数据时失败
				   	        break;
				   	     //	return;
				   	     }
				   	     else
				   	     {
				   	      GSM_DATA_CNT--;	
				   	      if(MODEFLAG.bits.b5==0)
					       { 
					         EEPROM_WRITING(0x3A,GSM_DATA_CNT);
					       }
					       else
					       {
					         EEPROM_WRITING(0x3B,GSM_DATA_CNT);
					       }
				   	     } 							   	     
				     }
				   	 while(GSM_DATA_CNT);
				   	 if(keyvalGSM==0)
				     {
				       GPRST =0;            //不闪那个天线柱子符//注册成功	
				       //在这里显示错误码
				       GSM_OFF_ON =1;
				       GSM_OFF();           //关模组
					   if(step <= 26)
					    {
				           step =7;	
					    }
					    else
					    {
					       step =8;	
					    }
					   SBR_DISP_E_NO(step);
                       SBR_DISP_DOT_GPRST_OFF();
                       SBR_DISP_DOT_GPRSS_OFF();
				       Delay_ms(40000);  
/////                  BPPLAY_ONE_INFOEND(BPF_GPRS_ERR_MP3);  //您当前的网络信号弱，数据已保存，下次测量成功后上传；
///////////////////////////////////////////////////////////////////////////	      
				       if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				       {
					    close_time =15500; 
	//				    KEYFLAG.Val = 0;
					    return;
				       }     
//////////////////////////////////////////////////////////////////////////				                       
                       Delay_ms(10000); 
//                       disp_sys(PRE_SYS.Val);		   
//                       disp_dia(PRE_DIA.Val);
//                       disp_pu(PLSCNT);
                       disp_sys(OLD_PRE_SYS);		   
                       disp_dia(OLD_PRE_DIA);
	                   disp_pu(OLD_PLSCNT);                       
///////////////////////////////////////////////////////////////////////////	      
				       if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				       {
					    close_time =15500; 
	//				    KEYFLAG.Val = 0;
					    return;
				       }     
////////////////////////////////////////////////////////////////////////	                                   
				     }
				     else
				     {
                       GPRST =0;            //不闪那个天线柱子符
                       SBR_DISP_DOT_GPRST_ON();
                       SBR_DISP_DOT_GPRSS_ON();						     	
//////			       BPPLAY_ONE_INFOEND(BPF_GPRS_SUC_MP3); 	//数据上传成功
///////////////////////////////////////////////////////////////////////////	      
				       if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				       {
					    close_time =15500;
	//				    KEYFLAG.Val = 0; 
					    return;
				       }     
//////////////////////////////////////////////////////////////////////////								       
				     }
	               }
//	               GSM_OFF();
//					print_with_Enter((const unsigned char*)"AT+QPOWD=1");	//
//			    	delay_ms(500);
//				    POWER_EN =0;         //关GPRS电源
//				    GSM_PWRKEY =0;    
////////////////////////////////////////////////////////////////////////////////////	   
			       close_time=0; 		           //关机时间计数器
			       keyval = key_scan(); 
				   if(keyval==1)	                             //用开关键中断测量
				   {
				 	 keyval=0;
					 close_time=15500;
				   }
		   	  } 
	   }
	  else
		{
//		  	close_time =14800;
		    switch(ERFLAG.Val)		                //错误显示
	           {
	           	 case 2 :SBR_DISP_E1_ON();	 
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;            
                         break;                     //编码高位元
		         case 4 :SBR_DISP_E2_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;   		         
 		                 break;	  
	             case 8 :SBR_DISP_E3_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;   	             	             
                         break;                     //编码高位元
		         case 16 :SBR_DISP_E4_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;   		         
 		                 break;	                    //编码的低位元
                 case 32 :SBR_DISP_E5_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;                    
	                     break;	                    //编码的低位元
                 case 64 :SBR_DISP_E6_ON(); 
 	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;                   
                         break;    //编码高位元
		         case 128 :LCD_INIT_OFF();
		                  close_time =15500; 		         
		                  break;	//按键退出清屏
                  default:            break;
	           }	             
	         ERFLAG.Val=0;                          //清除错误标志 
		}
}
