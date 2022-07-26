#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

/******************************************************************************************* 
** ��������: TEST_CON
** ��������: �ܱղ����
** �������: �� 
** �������: ��  
*******************************************************************************************/
void TEST_CON(void)
{
     uint8 i;	 
     LCD_INIT_OFF();	                  //����
     MODEFLAG.bits.b0 =1;                      //��ʾʱ��ˢ��ʱ��;
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
	 disp_dia(0);			           //��Ҫ��ʾʲô��Ϣ������Ӿͺ���	  att
	 Delay_ms(18000);
	   
////////////////////////////////////////////////////////////////////////  ��0	   
 	 R_TEMPDATA.Val =0;
	 for(i=0;i<16;i++) 
	 {
	   R_TEMPDATA.Val +=P012_avg;//Samlpe_Adc1(4);       //an6��PGA1
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
       
	 LOW_V =Samlpe_Adc1(2);          //��������ֵ��4��֮һ��VDD�ĵ�ѹֵ   
	 if(LOW_V<360)		               //2.2
	 {
	   LOW_V =Samlpe_Adc1(2);           //��������ֵ��4��֮һ��VDD�ĵ�ѹֵ   
	   if(LOW_V<360)		               //2.2
		{
		  BPPLAY_ONE_INFOEND(BPF_LOWPOWER_MP3);
//		  SBR_DISP_DOT_LO_ON();	      //��ʾ�͵�ѹ
//	      R2FLAG.bits.b7 = 1;        //1:�͵�ѹ
	      REL1 = 0; 
	      BTT_OFF=1;
	      SBR_DISP_DOT_BTT(1);
	      Delay_ms(30000);
	      return;
		}
	 } 
     REL1 = 1;                       //����� ON 		  
     MODEFLAG.bits.b2 =0;
     FTM31 = 0;							   //��ʼ��ʱ180����Թ���
     COUNT1_JIA = 0;                      
     do
	  {
	    PUMPPRE=PUMPPRE+30;	           //��ѹ���ټ�ѹ
		if(PUMPPRE>=290)
		  {
		    PUMPPRE=290;
		  }
		if(PUMPPRE <=290 &&COUNT1_JIA <= 3)//�ټ�ѹ����ֵ���ܴ���283Ҳ���Ǽ�ѹ����ֻ����3������
		  {
		    ERFLAG.Val=0;                   //��������־
		    DEFLATION();			           //���ò���
		  }
		else
		  {
		    ERFLAG.bits.b0=0;              //�����Ҫ��ѹ��283���Ͼ���EE�޷�����
		    ERFLAG.bits.b2=1;		       //�˳���ʾ����EE
		  }
      }
	 while(ERFLAG.bits.b0==1);           //û����Ҫ�ټ�ѹ����,�ټ�ѹ����ҲҪ�˳�  
	 SBR_DISP_DOT_JIA_OFF();
     SBR_DISP_DOT_JIAN_OFF();
     REL1 = 0;                          //�ص����
     STP_PUMP_OFF();                    // �ڼ�ѹ�����˳���Ҫ�������PUMP���
     if(ERFLAG.Val==0)		            //�ж�û��û�з�������
	   { 
	   	
	
		PRE_SYS.Val=135;
		PRE_DIA.Val=120;
		PLSCNT=80;
		//	 SYSDAS_DE();	 
			 			
         //��ѹ��������ѹ��һ20���ѹС��25���ѹ���ڸ�ѹ��//Ӧ��С�ڼ�ѹ���20mmHg//��ѹҪ�����45//��ѹ���ڵ�ѹ    
		 if((PRE_SYS.Val-PRE_DIA.Val>150)||(PRE_DIA.Val<25)||(PRE_DIA.Val>PRE_SYS.Val)||(PLSCNT<38)||(PLSCNT>204))  
		   {
			   SBR_DISP_E4_ON();			        //
			   SBR_DISP_DOT_HEART_OFF();  
			   BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	              close_time =16550;      //�����жϺ������Ϲػ�  


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
                   	  //��������ʾ�ģ�IHB
                      SBR_DISP_DOT_HEART_ON();       //��ʾ���� 
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
			      test_data_int();       //�޸���ʱ����Ĭ�ϵ����ݡ� 
                  keyvalGSM =START_GSM();
///////////////////////////////////////////////////////////////////////////	      
			      if(GPIO_STARTKEY == 0 || KEYFLAG.bits.StartKey ==1)									
				   {
					 //��������Ļ�����˵�Ѿ�������ʱ�䣬����ʱ���¼ֵ�Ͳ���ʱ���˴�
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
                  if(keyvalGSM==0)        //���һ�β��ɹ��ٷ�һ��
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
				   	//��������ʾ������
				   	  GSM_OFF_ON =1;
				   	  GSM_OFF();           //��ģ��
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
/////		          BPPLAY_ONE_INFOEND(BPF_GPRS_ERR_MP3);   //����ǰ�������ź����������ѱ��棬�´β����ɹ����ϴ���
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
				   	     {  //�������ڴ�����ʱʧ��
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
				       GPRST =0;            //�����Ǹ��������ӷ�//ע��ɹ�	
				       //��������ʾ������
				       GSM_OFF_ON =1;
				       GSM_OFF();           //��ģ��
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
/////                  BPPLAY_ONE_INFOEND(BPF_GPRS_ERR_MP3);  //����ǰ�������ź����������ѱ��棬�´β����ɹ����ϴ���
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
                       GPRST =0;            //�����Ǹ��������ӷ�
                       SBR_DISP_DOT_GPRST_ON();
                       SBR_DISP_DOT_GPRSS_ON();						     	
//////			       BPPLAY_ONE_INFOEND(BPF_GPRS_SUC_MP3); 	//�����ϴ��ɹ�
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
//				    POWER_EN =0;         //��GPRS��Դ
//				    GSM_PWRKEY =0;    
////////////////////////////////////////////////////////////////////////////////////	   
			       close_time=0; 		           //�ػ�ʱ�������
			       keyval = key_scan(); 
				   if(keyval==1)	                             //�ÿ��ؼ��жϲ���
				   {
				 	 keyval=0;
					 close_time=15500;
				   }
		   	  } 
	   }
	  else
		{
//		  	close_time =14800;
		    switch(ERFLAG.Val)		                //������ʾ
	           {
	           	 case 2 :SBR_DISP_E1_ON();	 
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;            
                         break;                     //�����λԪ
		         case 4 :SBR_DISP_E2_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;   		         
 		                 break;	  
	             case 8 :SBR_DISP_E3_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;   	             	             
                         break;                     //�����λԪ
		         case 16 :SBR_DISP_E4_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;   		         
 		                 break;	                    //����ĵ�λԪ
                 case 32 :SBR_DISP_E5_ON();
	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;                    
	                     break;	                    //����ĵ�λԪ
                 case 64 :SBR_DISP_E6_ON(); 
 	           	         BPPLAY_ONE_INFOEND(BPF_TEST_ERR_MP3);
	           	         close_time =14500;                   
                         break;    //�����λԪ
		         case 128 :LCD_INIT_OFF();
		                  close_time =15500; 		         
		                  break;	//�����˳�����
                  default:            break;
	           }	             
	         ERFLAG.Val=0;                          //��������־ 
		}
}
