#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

//����ʽ
void main()
{	
	uint16 i=0;
	Ram_Init();
	INT_SYSTEM();
	INT_POWER(); 
	INT_IO(); 
	Uart_Init();
	INT_LCD();
	INT_OP1();
	INT_OP();  
	INT_AD();
	INT_TMR();
	INT_INTP();
	Init_val();
	FUN_INT1_2_INIT();
	SBR_INI_TIMEBASE();
	INT_DATE_TIME();       //ʱ�����ڳ�ʼ��
////start 
    LEDR =1; 
	LCD_INIT_ON(); 
	close_time1=0;             //��ʼ����3���ʱ 
	while(close_time1<65500)
	{ 
		close_time1++;
		if(KEYFLAG.bits.StartKey == 1)
		{
			KEYFLAG.bits.StartKey = 0;
			close_time1=0;
			i++;						
		}
	}                   
	switch(i) 
	{
//		case 3 :   
//		case 4 ://GAUGE();      break;	           //3��������3��������������Ϊ����ѹ���ȶ�ģ���� 	           
		case 5 :
		case 6 :
		case 7 :
		case 8 :STUDY_PRE();
				STUDY_PRE1();
				STUDY_PRE2();
				STUDY_PRE3(); 
				while(1);     break;               //3��������6��������������Ϊ��������ģ����	 
  		default:              break;
	}
	MODEFLAG.bits.b0 =1;                      //��ʾʱ��ˢ��ʱ��;
	MODEFLAG.bits.b1 =0;                      //����������û�в�����
	MODEFLAG.bits.b5 =0;                      //���Ե���,0-1��,1Ϊ2��
	MODEFLAG.bits.b3 =1;	                  //ʱ�������˸
	MODEFLAG.bits.b4 =0;					  //������ʼΪ����״̬
	OLD_PRE_SYS = 0; 
	OLD_PRE_DIA = 0;
	Delay_ms(20000);
    close_time=0;
    LCD_INIT_OFF();
    CHARGE=0;
	while(1)
	{
		//����
	    if(close_time>16500&&CHARGE==0)	         //û�м�����͹��ĵ�ʱ��ֶ�150��
	    {
	        MODEFLAG.bits.b3 =0;	
	       
	        CHARGE =1;
	        LCD_INIT_OFF();
	        close_time=16490;	 	
	    }
		else
	    {
	        if(close_time<16490)
	        {
                MODEFLAG.bits.b3 =1;	      	
		        SBR_UPDATE_TIME();                   //��ʾʱ��ˢ��ʱ��;
	        }
	        else if(FUL_DET==0&&CHARGE==1)
	        {
	      	    LEDR =0;
	      	    MODEFLAG.bits.b3 =0;	
	      	    close_time=16490;
	        }
	    }
		if(BTT_OFF==0 && close_time < 16499)
		{
		    SBR_UPDATE_BTT(); 
		} 
	    if(FUL_DET==0)
		{
		   _int0e =0;
		   KEYFLAG.Val =0;	
		   continue;	
		}
 	    keyval=key_scan();
		if(close_time>16500)	                         //û�м�����͹��ĵ�ʱ��ֶ�150��
		{
//			close_time=0;
//			LCD_INIT_OFF();	                         //��������͹���ģʽ
//				   if(MODEFLAG.bits.b5==0)
//                     {  
//                     	SBR_DISP_DOT_U2_OFF();    
//                        SBR_DISP_DOT_U1_ON();
//                      
//                     }
//                    else
//                     {
//                      SBR_DISP_DOT_U1_OFF();
//                      SBR_DISP_DOT_U2_ON();
//                     }
//          MODEFLAG.bits.Up_dateTime=1;             //����ˢʱ��         
//			SBR_UPDATE_TIME();
            MODEFLAG.bits.b3 =1;                     //ʱ�������˸
			MODEFLAG.bits.b1 =0;                     //�´ο�����û�в����� //20130629
//			if(FUL_DET==0)
//			{
//				close_time=17000;
//	//			LCD_INIT_OFF();	                         //��������͹���ģʽ
//	//            Up_dateBTT = 1;	
//	            BTT_OFF=0;
//				if(BTT_OFF==0)
//				{
//				  SBR_UPDATE_BTT(); 
//				} 
//			}
//			else
//			{ 
			if(FUL_DET==1)
			{
			    _pe7 =0;         //��GPRS��Դ
//				_pe6 =0;   
				LCD_INIT_OFF();	
//		        GSM_PWRKEY =1; 
//		        Delay_ms(12000);
//		        GSM_PWRKEY =0; 				
	            MODEFLAG.bits.b3 =1;                     //ʱ�������˸
				MODEFLAG.bits.b1 =0;                     //�´ο�����û�в����� //20130629	
/*				Delay_ms(32000);*/					
				SBR_ENTER_HALTMODE();                    //����͹���ģʽ
				
				//�а������Ѿʹ����￪ʼִ��
				INT_SYSTEM();
				INT_POWER(); 
				INT_IO();
				Uart_Init(); 
				INT_LCD();
				INT_OP1();
				INT_OP();  
				INT_AD();
				INT_TMR(); 
				INT_INTP();  
				Init_val();
				FUN_INT1_2_INIT();
				SBR_INI_TIMEBASE();
				BTT_OFF=0;
				LEDR =1; 
				close_time=15500;                  //�����ȴ���ʼ��ʱ
				MODEFLAG.bits.b1 =0;               //����������û�в�����
				MODEFLAG.bits.b3 =0;	           //ʱ�������˸ 
				LCD_INIT_OFF();
				CHARGE=0;
//                MEMEKEYshift =0;                          //�����ʶ��û�в��������������A���Ǿ��ǲ���	
                MEMO_INT_SPEAK =0;				
			}
	
		} 

		   switch(keyval)
		  // �������: 1,START 2, SET 3, MOMERY 4,MODE  5, SET���� 6��MOMERY����
	        {
		    case 1:	
		           keyval=0; 
		           if(MODEFLAG.bits.b1 ==0)
			         {
			         	TIME_TEEP_flag =1;
     	          	    LCD_INIT_ON();
	/////////////////////////////////////////////////////////////////////////////////////			          
//						_pe7 =1;               //
//						Delay_ms(5000);				   
//						_pe6 =1;  
	/////////////////////////////////////////////////////////////////////////////////////                      
				        Delay_ms(30000);
//				        	 LEDR =0;	
		                PUMPPRE=185; 					   //��û������ʱ��ѹ��210
		                
						LEDR =0; 
						PUMPPRE=185;         //��û������ʱ��ѹ��210
						GSM_OFF_ON =1;
						TEST_CON();
						if(GSM_OFF_ON==0)
						{
							GSM_OFF();           //��ģ��
						}
				        
	                    MODEFLAG.bits.b1 =1;             //����ͱ�ʾû����һ��
			            MODEFLAG.bits.b0 =1;                      //ˢ��ʱ��;
         	         }
		           else
		             {
			           MODEFLAG.bits.b3 =0;             //ʱ�������˸
					   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	         
				   	   LCD_INIT_OFF();	
				       SBR_DISP_OFF_T_ON();
				       close_time=17000; 
				       Delay_ms(10000);	     	
		           	
		             }
				   KEYFLAG.Val = 0;
				   CHARGE=0;
				   break;  
		    case 2:	
		           keyval=0;
		           TIME_TEEP_flag =1;
                   MODEFLAG.bits.b3 =1;                          //ʱ�������˸
				   MODEFLAG.bits.b0 =1;                          //ˢ��ʱ��;		           
		           if(MEMO_INT_SPEAK ==0)                        //�ӿ���������Ǵ� 
		           {	
	                   if(MODEFLAG.bits.b1 !=0)                  //20161014
	                     {	        
					        MODEFLAG.bits.b5 = ~MODEFLAG.bits.b5;	 //���Ե���,0-1��,1Ϊ2��
	                     }
	                   else
	                     {
	                   	    MODEFLAG.bits.b1=1;
	                     }
					   if(MODEFLAG.bits.b5==0)
	                     {      
	                        SBR_DISP_DOT_U1_ON();
	                        SBR_DISP_DOT_U2_OFF();
	                     }
	                    else
	                     {
	                        SBR_DISP_DOT_U1_OFF();
	                        SBR_DISP_DOT_U2_ON();
	                     }
					    close_time=0;  
		           }
		           else
		           {
		           	   KEYFLAG.bits.RecallKey =1;
		           }           
			break;			   
				                                    
	        case 3:
	               TIME_TEEP_flag =1;               //S2���δ���
		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	 
				   MEMO_INT_SPEAK =1;        
		           SBR_READ_MEMORY();               //���������� 
		           if(KEYFLAG.bits.SetKey) 
		           {
		           	   KEYFLAG.Val =0;
		           	   close_time =0; 
		           	   MODEFLAG.bits.b5 = ~MODEFLAG.bits.b5;	 //���Ե���,0-1��,1Ϊ2��
		           	   KEYFLAG.bits.RecallKey =1;	          	  
		           }
		           else
		           {
				   	   LCD_INIT_OFF();
				       SBR_DISP_OFF_T_ON();
				       close_time=17000; 
				       Delay_ms(10000);	
				       MEMO_INT_SPEAK =0;				       		   	   		   	   
				   	   KEYFLAG.Val = 0;
		           }
		    break;
		    case 4:                                     //S4���δ���
		           keyval=0;
		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	 		           
		           GAUGE();
		           Delay_ms(1000);
		           SBR_DISP_OFF_T_ON();
			       close_time=17000; 
			       Delay_ms(10000);
				   KEYFLAG.Val = 0;
				   CHARGE=0;
		    break;                     
//	        case 5:		                                    //S3��������
//		         //  keyval=0;	
//		           MODEFLAG.bits.b5 =0;
//		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
//				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	         
//		          // SBR_READ_MEMORY();                       //���������� 
//		           SBR_TIME_SETTING();
//			   	   LCD_INIT_OFF();	
//			       SBR_DISP_OFF_T_ON();
//			       close_time=17000; 
//			       Delay_ms(10000);			   	   		   	   
////			   	   MODEFLAG.bits.b0 =1;                      //ˢ��ʱ��;
////			   	   MODEFLAG.bits.b3 =1;             //ʱ�������˸
////			   	   close_time=17000; 
//			   	   KEYFLAG.Val = 0; 
//			   	   CHARGE=0;
//     	    break;
//	        case 6:		                                    //S3��������
//		         //  keyval=0;	
//		           MODEFLAG.bits.b5 =1;
//		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
//				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	         
//		           SBR_READ_MEMORY();                       //���������� 
//			   	   LCD_INIT_OFF();	
//			       SBR_DISP_OFF_T_ON();
//			       close_time=17000; 
//			       Delay_ms(10000);			   	   		   	   
////			   	   MODEFLAG.bits.b0 =1;                      //ˢ��ʱ��;
////			   	   MODEFLAG.bits.b3 =1;             //ʱ�������˸
////			   	   close_time=17000; 
//			   	   KEYFLAG.Val = 0; 
//			   	   CHARGE=0; 
//     	    break;     	    
	        case 7:		                                    //S3��������
		           keyval=0;
		           LCD_INIT_OFF();
		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
		           while(GPIO_STARTKEY==0); 
		           close_time =0;
		           disp_sys(100);	
		           while(GPIO_SETKEY==0 && close_time < 600)
		             {
	
		             }
		           if(close_time>=590)
		           {
			           MODEFLAG.bits.b5 =0;
					   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	         
	                   STUDY_PRE();
					   STUDY_PRE1();
				 	   STUDY_PRE2();
					   STUDY_PRE3(); 
				       Delay_ms(10000);	
				   	   KEYFLAG.Val = 0; 
				   	   CHARGE=0; 
		           }
			       LCD_INIT_OFF();
			       close_time=17000; 
     	    break; 
     	    case 8:
		           keyval=0;
		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	      		           
		           DISP_SN();
		           Delay_ms(1000);
		           SBR_DISP_OFF_T_ON();
			       close_time=17000; 
			       Delay_ms(10000);
				   KEYFLAG.Val = 0;
				   CHARGE=0;
     	    break;     	    
    	    case 10:	                
		           keyval=0;
				   LCD_INIT_OFF();
		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	 				   
				   mmHg_Kpa = ~mmHg_Kpa;
				    if(mmHg_Kpa)
			        {
//					   SBR_DISP_DP1_KPA_ON();
//	                   SBR_DISP_DOT_P1_ON();
//	                   SBR_DISP_DOT_P2_ON();
//				       R_TEMPDATA.Val=0;
//		               SBR_DISP_DIA_ON();
//		               SBR_DISP_SYS_ON();
                       disp_dia(0);
				    }
				    else
				    {
//				       R_TEMPDATA.Val=0;
//		               SBR_DISP_DIA_ON();
//		               SBR_DISP_SYS_ON();	
//					   SBR_DISP_DOT_DIA_ON();
                       disp_dia(0);
				    }  		           
		           Delay_ms(30000);
		           SBR_DISP_OFF_T_ON();
			       close_time=17000; 
			       Delay_ms(10000);
				   KEYFLAG.Val = 0;
				   CHARGE=0;	                
     	    break; 
//    	    case 10:
//		           keyval=0;
//				   LCD_INIT_OFF();
//		           MODEFLAG.bits.b3 =0;             //ʱ�������˸
//				   MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;	 				   
//				   MODEFLAG.bits.b4 = ~MODEFLAG.bits.b4;
//				   if(MODEFLAG.bits.b4==0)
//                    {
//                     SBR_DISP_SP_OFF();
//				    }
//                    else
//                     {
// 			    	  SBR_DISP_SP_ON();
//                     }		           
//		           Delay_ms(30000);
//		           SBR_DISP_OFF_T_ON();
//			       close_time=17000; 
//			       Delay_ms(10000);
//				   KEYFLAG.Val = 0;
//				   CHARGE=0;
//     	    break;       	     
		    default:
		 		    keyval=0;
		    break;
	        }		
	}
}