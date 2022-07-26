#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"


#define	C_Memory_Timeout	150//;s	

#define	C_Write_mod	    0b10000000	//; select write program rom mode
#define	C_pg_erase_mod	0b10010100	//; select page erase mode	
#define	C_read_mod	    0b10110000	//; select read program rom mode & set fden=1
#define	C_fwen_ctl_mod	0b01101000	//; select FWEN bit control mode & set FWPEN=1 
//;;****************************************************************
//EEPROM �ĵ�ַ
#define	C_EEPROM_Memory_120_0	    0x36
#define	C_EEPROM_Memory_120_1	    0x37
#define	C_EEPROM_Memory_addr_L_0	0x30
#define	C_EEPROM_Memory_addr_L_1	0x33
//;;...User Memory
#define	C_Memory_Start_addr_0	0x1B00
#define	C_Memory_Start_addr_1	0x1C40	
#define	C_Memory_Stop_addr		0x1D80
//#define	C_Memory_Num			50

//user0 user1�ĵ�ַ
#define	MemoryData0_addr	0x1B00
#define	MemoryData1_addr	0x1C40
//�_��IA���g
const  uint16	__attribute__((at(MemoryData0_addr))) MemoryData0[640]={};  //48  --- 64

void	L_MEN_DISPLAY();
void	L_MEN_DISPLAY_TIME();

//;****************************************************************
//; subroutine : SBR_SAVE_MEMORY
//; input  : none
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
//;---------------------------------------------------------
//iap �攵�� ���_ʼ����֮ǰһ��Ҫ���O��EEprom�е� IAP�x����ַ
void	SBR_SAVE_MEMORY(void)
{
	//���h�_ʼ�攵���r�P�]�Д�
	_emi = 0;
	//�xȡEEprom����
	SBR_READ_MEM_ADDR();
	//_PRE_SYS&_PRE_DIA�M�ϳ� 3 byte
	R_IAP_TEMP0.Val = PRE_SYS.BYTE.BYTE_L;
	R_IAP_TEMP2.Val = PRE_DIA.BYTE.BYTE_L;

	R_IAP_TEMP1.Val = PRE_SYS.BYTE.BYTE_H & 0x0f;
	R_IAP_TEMP1.Val |= (PRE_DIA.BYTE.BYTE_H & 0x0f)<<4;	
	//?��
	R_IAP_TEMP3.Val = PLSCNT;
	//��?
	R_IAP_TEMP4.Val = R_CLOCK_MINUTE & 0b00111111;
	//С�r
	R_IAP_TEMP5.Val = R_CLOCK_HOUR & 0x0f;
	//С�r
	if((R_CLOCK_HOUR & 0b00010000) !=0)
	{
		R_IAP_TEMP4.bits.b7 = 1;
	}
	//IHB
    if(IHB_COUNT>2)	                                 
    {
        R_IAP_TEMP4.bits.b6 = 1;	
    }
	R_IAP_TEMP6.Val = R_DAY & 0b00011111;
	
	R_IAP_TEMP6.bits.b7 = ASCVD; //�Ӹ�����Ӳ������    	
	//�씵
//	R_IAP_TEMP6.Val = R_DAY;
	//�·�
	R_IAP_TEMP5.Val |= (R_MONTH&0x0f)<<4;
	//���		
	R_IAP_TEMP7.Val = R_YEAR;
	
	//******************************************//
	//һ��IAP�Č�����
	SBR_WRITE_FLASH_ENABLE();
	//;;...._r_TempDataH/L(Address) 
	SBR_SELECT_WRITE_FLASH_MODE();
	SBR_WRITE_FLASH_BUFFER(8);
	SBR_WRITE_FLASH();
	//******************************************//
	
	//Next Record�������ꌑ�����󌢮�ǰָ�ָ����һ���յ�ַ
	SBR_NEXT_MEM_DAAR();
	
	//�������һ퓄t������һ�
	if((r_TempDataL&0b00111111)==0)
	{
		//******************************************//
		//һ��IAP�Ĳ�������		
		SBR_WRITE_FLASH_ENABLE();
		//;;...._r_TempDataH/L(Address) 
		SBR_SELECT_WRITE_FLASH_MODE();
		SBR_FLASH_PAGE_ERASE();	
		//******************************************//	
			
	}
	
	//ָ��ۼӼӵ�120ָ��1
	R_CURRENT_SN ++;
	if(R_CURRENT_SN>=C_Memory_Num+1)
	{
		R_CURRENT_SN = C_Memory_Num;
//��������˵��������120�飬�Ǿ���E�����ʾ����		
		if(MODEFLAG.bits.User)
	      {
		   R_EEPROM_DATA = C_EEPROM_Memory_120_1;
	      }
	      else
	      {
	    	R_EEPROM_DATA = C_EEPROM_Memory_120_0;		
	      }
		  EEPROM_WRITING(R_EEPROM_DATA,120);
       // r_TempDataL=SBR_EEPROM_READDATA(R_EEPROM_DATA);		
		
		
	}
	R_SEARCH_SN = R_CURRENT_SN;	
	
	//�õ�EEPROM�ĵ�ַ
	r_Temp0.Val = C_EEPROM_Memory_addr_L_0;
	if(MODEFLAG.bits.User)
	{
		r_Temp0.Val = C_EEPROM_Memory_addr_L_1;		
	}
	
	EEPROM_WRITING(r_Temp0.Val,r_TempDataL);
	r_Temp0.Val ++;
	EEPROM_WRITING(r_Temp0.Val,r_TempDataH);	
	r_Temp0.Val ++;
	EEPROM_WRITING(r_Temp0.Val,R_CURRENT_SN);	
	//�˳��r���_���Д�	
	_emi = 1;		
}

void UPDATA_MEMORY(uint8 GSM_DATA_CNT)
{
//	uint8 i;
	SBR_READ_MEM_ADDR();
	R_SEARCH_SN = R_CURRENT_SN;
    do
    {
		R_SEARCH_SN -- ;
		if(R_SEARCH_SN==0)
		{
		 R_SEARCH_SN = C_Memory_Num;
		}
		GSM_DATA_CNT --;
    }
	while(GSM_DATA_CNT);
	//�O�ò�ԃָ�
	SBR_SEARCH_MEM_ADDR();
	SBR_READ_MEN_DATA();	
////////////////////////////////////////////////////////////////////////////////////////////
//#define	R_MINUTE_SEARCH	R_IAP_TEMP[5]	
//#define	R_IAP_TEMP6	R_IAP_TEMP[6]
//#define	R_HOUR_SEARCH	R_IAP_TEMP[6]	
//#define	R_IAP_TEMP7	R_IAP_TEMP[7]
//#define	R_DAY_SEARCH	R_IAP_TEMP[7]	
//#define	R_IAP_TEMP8	R_IAP_TEMP[8]
//#define	R_MONTH_SEARCH	R_IAP_TEMP[8]	
//#define	R_IAP_TEMP9	R_IAP_TEMP[9]
//#define	R_YEAR_SEARCH	R_IAP_TEMP[9]			   
    R_TEMPDATA.Val=R_YEAR_SEARCH.Val;
	SBR_BIN_TO_BCD();
	up_data.year[2]=HEX_TO_Char(r_Temp1.Val);
	up_data.year[3]=HEX_TO_Char(r_Temp0.Val);
    R_TEMPDATA.Val=R_MONTH_SEARCH.Val;
	SBR_BIN_TO_BCD();
	up_data.month[0]=HEX_TO_Char(r_Temp1.Val);
	up_data.month[1]=HEX_TO_Char(r_Temp0.Val);
    R_TEMPDATA.Val=R_DAY_SEARCH.Val;
	SBR_BIN_TO_BCD();
	up_data.day[0]=HEX_TO_Char(r_Temp1.Val);
	up_data.day[1]=HEX_TO_Char(r_Temp0.Val);
    R_TEMPDATA.Val=R_HOUR_SEARCH.Val;
	SBR_BIN_TO_BCD();
	up_data.our[0]=HEX_TO_Char(r_Temp1.Val);
	up_data.our[1]=HEX_TO_Char(r_Temp0.Val);
    R_TEMPDATA.Val=R_MINUTE_SEARCH.Val;
	SBR_BIN_TO_BCD();
	up_data.mini[0]=HEX_TO_Char(r_Temp1.Val);
	up_data.mini[1]=HEX_TO_Char(r_Temp0.Val);   
////////////////////////////////////////
    if(MODEFLAG.bits.b5==0)
	  { 
		 up_data.USER_BUF='1';
	  }
	else
      {
         up_data.USER_BUF='2' ;
      }	
    PRE_SYS.BYTE.BYTE_L = R_IAP_TEMP0.Val;
	PRE_SYS.BYTE.BYTE_H = R_IAP_TEMP1.Val;
	PRE_DIA.BYTE.BYTE_L = R_IAP_TEMP2.Val;
	PRE_DIA.BYTE.BYTE_H = R_IAP_TEMP3.Val;
	PLSCNT = R_IAP_TEMP4.Val;
					  	  				
////////////////////////////////////////
    R_TEMPDATA.Val=PRE_SYS.Val;
	SBR_BIN_TO_BCD();
	up_data.SYS[0]=HEX_TO_Char(r_Temp2.Val);
	up_data.SYS[1]=HEX_TO_Char(r_Temp1.Val);
	up_data.SYS[2]=HEX_TO_Char(r_Temp0.Val);

    R_TEMPDATA.Val=PRE_DIA.Val;
	SBR_BIN_TO_BCD();
	up_data.DIA[0]=HEX_TO_Char(r_Temp2.Val);
	up_data.DIA[1]=HEX_TO_Char(r_Temp1.Val);
	up_data.DIA[2]=HEX_TO_Char(r_Temp0.Val);
								
    R_TEMPDATA.Val=PLSCNT;
	SBR_BIN_TO_BCD();
	up_data.PUL[0]=HEX_TO_Char(r_Temp2.Val);
	up_data.PUL[1]=HEX_TO_Char(r_Temp1.Val);
	up_data.PUL[2]=HEX_TO_Char(r_Temp0.Val);     
					  
//�������Ǿ���д��ȥ��ID�ţ�Ҫ��EEPROM��������
    r_Temp0.Val = SBR_EEPROM_READDATA(0x08);                 
	                 							  
    up_data.Serialnumber[1]=HEX_TO_Char((r_Temp0.Val>>4)&0x0F);   //'1';		//��
    up_data.Serialnumber[2]=HEX_TO_Char(r_Temp0.Val&0x0F);        //'7';
							  
    r_Temp0.Val = SBR_EEPROM_READDATA(0x09);
    switch(r_Temp0.Val)
       	  {
       	  	case 1:up_data.Serialnumber[3]='A';				 //	�� 
       	  	break;
       	  	case 2:up_data.Serialnumber[3]='B';				 //	�� 
       	  	break;
       	  	case 3:up_data.Serialnumber[3]='C';				 //	�� 
       	  	break;
       	  	case 4:up_data.Serialnumber[3]='D';				 //	�� 
       	  	break;
       	  	case 5:up_data.Serialnumber[3]='E';				 //	�� 
       	  	break;
       	  	case 6:up_data.Serialnumber[3]='F';				 //	�� 
       	  	break;
       	  	case 7:up_data.Serialnumber[3]='G';				 //	�� 
       	  	break;
       	  	case 8:up_data.Serialnumber[3]='H';				 //	�� 
       	  	break;
       	  	case 9:up_data.Serialnumber[3]='I';				 //	�� 
       	  	break;
       	  	case 0X0A:up_data.Serialnumber[3]='J';				 //	�� 
       	  	break;
       	  	case 0X0B:up_data.Serialnumber[3]='K';				 //	�� 
       	  	break;
       	  	case 0X0C:up_data.Serialnumber[3]='L';				 //	�� 
       	  	break;					       	  						       	  						       	  						       	  						       	  	
	       	  	default:
	        break;
       	  }						  

	      r_Temp0.Val = SBR_EEPROM_READDATA(0x0C);
		  up_data.Serialnumber[4]=HEX_TO_Char((r_Temp0.Val>>4)&0x0F);//'1';		 
		  up_data.Serialnumber[5]=HEX_TO_Char(r_Temp0.Val&0x0F);    //'2';
						
	      r_Temp0.Val = SBR_EEPROM_READDATA(0x0B);
		  up_data.Serialnumber[6]=HEX_TO_Char((r_Temp0.Val>>4)&0x0F);//'3';
		  up_data.Serialnumber[7]=HEX_TO_Char(r_Temp0.Val&0x0F);     //'4';
						
		  r_Temp0.Val = SBR_EEPROM_READDATA(0x0A);				
		  up_data.Serialnumber[8]=HEX_TO_Char((r_Temp0.Val>>4)&0x0F);//'5';							  
		  up_data.Serialnumber[9]=HEX_TO_Char(r_Temp0.Val&0x0F);     //'6';	
}


//;****************************************************************
//; subroutine : SBR_READ_MEMORY
//; input  : none 
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
void	SBR_READ_MEMORY()
{
	//��ʼ������r�g
	uint8 gu8v_long_press_times =0;	
//	uint8 gu8v_long_press_times1 =0;	
	R_TIMEOUT_SECOND = 0;
//	F_ModeKeyDown = 0;
	r_Temp0.Val = 0;
	r_Temp1.Val = 0;
	r_Temp2.Val = 0;
	r_Temp3.Val = 0;	
	r_Temp4.Val = 0;
	r_Temp5.Val = 0;
	R_SEARCH_SN = 0;	      //����Ϊ0�ʹ�
	
//	KEYFLAG.bits.RecallKey =1;
//	
	//ȡ��һ�P����
	SBR_READ_MEM_ADDR();      //����ǰ�ĵ�ַ�����Ƿ���EEPROM���ROM��������
	SBR_Previous_Mem_Addr();
	SBR_READ_MEN_DATA();
	//�Д��Л]��data
	if(R_EEPROM_DATA)
	{
		SBR_ADD_MEM();
	}
	//ȡ�ڶ��P����	
	SBR_Previous_Mem_Addr();
	SBR_READ_MEN_DATA();
	//�Д��Л]��data	
	if(R_EEPROM_DATA)
	{
		SBR_ADD_MEM();
	}
	//ȡ�����P����	
	SBR_Previous_Mem_Addr();
	SBR_READ_MEN_DATA();
	//�Д��Л]��data	
	if(R_EEPROM_DATA)
	{
		SBR_ADD_MEM();
	}
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
	
// 	if(R_SEARCH_SN==0)       //���Ǹ�ʾǰ��ȡ���˼�������ƽ�������һ������û��ȡ���Ļ�������û������
//	{
//		R_IAP_TEMP0.Val = 0;
//		R_IAP_TEMP1.Val = 0;
//		R_IAP_TEMP2.Val = 0;
//		R_IAP_TEMP3.Val = 0;
//		R_IAP_TEMP4.Val = 0;
//		R_IAP_TEMP5.Val = 0;
//		R_IAP_TEMP6.Val = 0;
//		R_IAP_TEMP7.Val = 0;
//		R_IAP_TEMP8.Val = 0;
//		R_IAP_TEMP9.Val	= 0;	
//	}
//	else
//	{
//		UINT16_VAL	DIVIDE_buff;
//		//ǰ������ƽ��	����С춵������
//		DIVIDE_buff.BYTE.BYTE_L = r_Temp0.Val;
//		DIVIDE_buff.BYTE.BYTE_H = r_Temp1.Val;	
//		DIVIDE_buff.Val /= R_SEARCH_SN;	
//		R_IAP_TEMP0.Val = DIVIDE_buff.BYTE.BYTE_L;
//		R_IAP_TEMP1.Val = DIVIDE_buff.BYTE.BYTE_H;		
//
//		DIVIDE_buff.BYTE.BYTE_L = r_Temp2.Val;
//		DIVIDE_buff.BYTE.BYTE_H = r_Temp3.Val;	
//		DIVIDE_buff.Val /= R_SEARCH_SN;	
//		R_IAP_TEMP2.Val = DIVIDE_buff.BYTE.BYTE_L;
//		R_IAP_TEMP3.Val = DIVIDE_buff.BYTE.BYTE_H;		
//
//
//		DIVIDE_buff.BYTE.BYTE_L = r_Temp4.Val;
//		DIVIDE_buff.BYTE.BYTE_H = r_Temp5.Val;	
//		DIVIDE_buff.Val /= R_SEARCH_SN;	
//		R_IAP_TEMP4.Val = DIVIDE_buff.BYTE.BYTE_L;
//	}
	if(R_SEARCH_SN>=1)              
	{
//			//�@ʾǰ���P��ƽ��ֵ
//			LCD_INIT_OFF();
//			if(MODEFLAG.bits.b5==0)
//		       { 
//		       	SBR_DISP_DOT_U2_OFF();     
//		        SBR_DISP_DOT_U1_ON();
//		        
//		       }
//		       else
//		       {
//		        SBR_DISP_DOT_U1_OFF();
//		        SBR_DISP_DOT_U2_ON();
//		       }			
//			r_TempDataL = R_IAP_TEMP0.Val;
//			r_TempDataH = R_IAP_TEMP1.Val;
//			disp_sys(R_TEMPDATA.Val);
//			r_TempDataL = R_IAP_TEMP2.Val;
//			r_TempDataH = R_IAP_TEMP3.Val;
//			disp_dia(R_TEMPDATA.Val);
//			r_TempDataL = R_IAP_TEMP4.Val;
//			r_TempDataH = 0;
//			SBR_DISP_PLUSE_ON();
//			SBR_DISP_DOT_MEMORY_ON();
//			PRE_SYS.BYTE.BYTE_L = R_IAP_TEMP0.Val;
//			PRE_SYS.BYTE.BYTE_H = R_IAP_TEMP1.Val;
//			PRE_DIA.BYTE.BYTE_L = R_IAP_TEMP2.Val;
//			PRE_DIA.BYTE.BYTE_H = R_IAP_TEMP3.Val;
//			PLSCNT = R_IAP_TEMP4.Val;		
//			DISPLAYWHO();
//			SBR_DISP_ANO_T_ON();
//			//����Ҫ����100��ʱ���ֵ 
//		if(MODEFLAG.bits.User)
//	      {
//		   R_EEPROM_DATA = C_EEPROM_Memory_120_1;
//	      }
//	      else
//	      {
//	    	R_EEPROM_DATA = C_EEPROM_Memory_120_0;		
//	      }
//		//  EEPROM_WRITING(R_EEPROM_DATA,120);
//         r_TempDataL=SBR_EEPROM_READDATA(R_EEPROM_DATA);
//         if(r_TempDataL==120)
//         {
//         	r_TempDataL = R_CURRENT_SN;
//         }
//         else
//         {
//         	r_TempDataL = R_CURRENT_SN-1;
//         }			
//			r_TempDataH = 0;	
//			SBR_DISP_ANO_NUM_ON();
	}
	else
	{
			MODEFLAG.bits.b3 =1;             //ʱ�������˸
		    MODEFLAG.bits.b0 =1;             //ˢ��ʱ��;
		    SBR_UPDATE_TIME();
		    SBR_UPDATE_BTT();	  
		    SBR_DISP_NOMON_ON();
		    SBR_DISP_DOT_MEMORY_ON();
		    Delay_ms(30000);
			MODEFLAG.bits.b3 =0;             //ʱ�������˸
		    MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;		    
		    return;		    
	}
	//�����������ƽ�����ܾ��������
	//�ʂ��@ʾ
	SBR_READ_MEM_ADDR();        //���¶�EEP���ݿ�ʼ����鹦��
	R_SEARCH_SN = R_CURRENT_SN; //�ѵ�ǰ��λ�ø���R_SEARCH_SN	
	TIMERFLAG.bits.SearchOver = 0;
///////////////////////////////////////////////////////////////////////////////	
	if(MODEFLAG.bits.User)
	  {
		   R_EEPROM_DATA = C_EEPROM_Memory_120_1;
	  }
	else
	  {
	       R_EEPROM_DATA = C_EEPROM_Memory_120_0;		
	  }
//  EEPROM_WRITING(R_EEPROM_DATA,120);
    r_TempDataL=SBR_EEPROM_READDATA(R_EEPROM_DATA);
    if(r_TempDataL==120)       //���120�Ǵ���������һ��
      {
           R_CURRENT_SN_DISP = C_Memory_Num;      //50
           OVERMEMORY =1;                         //�����ڷ����ʱ�������һ���Ǹ߱ʺͺ����	
      }
    else 
      {
           R_CURRENT_SN_DISP = R_CURRENT_SN;	  //
           OVERMEMORY =0;                        //����
      }	
    R_SEARCH_SN_DISP =0;
         
    KEYFLAG.bits.RecallKey = 1;    
///////////////////////////////////////////////////////////////////////////////	
	while(1)
	{
		if(R_TIMEOUT_SECOND >= C_Memory_Timeout)   //��ʱ�˳�
		{
			break;
		}	
//		//��ԃģʽ�����IAP
//		if(KEYFLAG.bits.RecallSetKeyHold)             //����M�������
//		{
//			KEYFLAG.bits.RecallKeyHold = 0;
//			MODEFLAG.bits.User =0;
//			SBR_CLEAR_MEMORY();	
//			MODEFLAG.bits.User =1;
//			SBR_CLEAR_MEMORY();	
//			break;					
//		}
//		if(KEYFLAG.bits.SetKeyHold)             //����M�������
//		{
//			KEYFLAG.bits.SetKeyHold = 0;
//			SBR_CLEAR_MEMORY();	
//			break;					
//		}		

		if(KEYFLAG.bits.SetKey)                    //SET�������˳�
		{
//			KEYFLAG.bits.SetKey = 0;
			LCD_INIT_OFF();
			break;							
		}

		if(KEYFLAG.bits.StartKey)                  //���ؼ��˳�
		{
			KEYFLAG.bits.StartKey = 0;
			LCD_INIT_OFF();
			break;							
		}
		
	    if(gu8v_KeyPress.bits.b3 == 1)
		{
			if(gbv_tb0_flag)
			{
				gbv_tb0_flag = 0;
				gu8v_long_press_times++;
				if(gu8v_long_press_times>230)
				{
					KEYFLAG.bits.RecallKey = 1;
					gu8v_long_press_times = 200;
				}						
			}
		}
		else
		{
			gu8v_long_press_times = 0;
		}

//					
//		if(gu8v_KeyPress.bits.b1 == 1)
//		{
//			if(gbv_tb0_flag)
//			{
//				gbv_tb0_flag = 0;
//				gu8v_long_press_times1++;
//				if(gu8v_long_press_times1>230)
//				{
//					KEYFLAG.bits.SetKey = 1;
//					gu8v_long_press_times1 = 200;
//				}						
//			}
//		}
//		else
//		{
//			gu8v_long_press_times1 = 0;
//		}										
//			
//		if(KEYFLAG.bits.SetKey)                  //������
//		{
//			KEYFLAG.bits.SetKey = 0;			
//
////			SBR_DISP_DOT_AVG_OFF();
//
//			R_TIMEOUT_SECOND = 0;
//			while(1)
//			{//����򵽵�������飬����Ҫ�Ե�ǰʱ��ֵR_SEARCH_SN_DISP
//			if(TIMERFLAG.bits.SearchOver == 0)
//			 {
//			    if(R_SEARCH_SN_DISP!=0)
//			    {
//			        R_SEARCH_SN_DISP--;
//			    }
//			    if(R_SEARCH_SN_DISP ==0)
//				{
//					R_SEARCH_SN_DISP = R_CURRENT_SN_DISP-1;
//					if(R_CURRENT_SN_DISP == C_Memory_Num)   //��ʹ���49
//					{
//					  if(OVERMEMORY ==0)
//					  {	
//					    R_SEARCH_SN_DISP = C_Memory_Num -1;	
//					  }
//					  else
//					  {
//					  	R_SEARCH_SN_DISP = C_Memory_Num;
//					  }
//					}
//				   
//				}
//			 }	
//				R_SEARCH_SN++;
//				if(R_SEARCH_SN > C_Memory_Num)
//				{
//					R_SEARCH_SN = 1;
//				}
//				//�O�ò�ԃָ�
//				SBR_SEARCH_MEM_ADDR();
//				SBR_READ_MEN_DATA();
//				if(R_EEPROM_DATA)
//				{
//					L_MEN_DISPLAY_TIME();
//					vodisplay = 1;
////					L_MEN_DISPLAY();
//					break;
//				}
//				if(TIMERFLAG.bits.SearchOver)
//				{
////					L_MEN_DISPLAY();
//					break;						
//				}	
//				else
//				{
//					TIMERFLAG.bits.SearchOver = 1;
//					R_SEARCH_SN = 0;			
//				}
//			}
//		}

		if(R_TIMEOUT_SECOND > 1 && vodisplay == 1 )	
		{
			L_MEN_DISPLAY();
			vodisplay =0;
		}		

		if(KEYFLAG.bits.RecallKey)
		{
			KEYFLAG.bits.RecallKey = 0;			
//			SBR_DISP_DOT_AVG_OFF();

			R_TIMEOUT_SECOND = 0;
			while(1)
			{
				//�����˵��
			    if(TIMERFLAG.bits.SearchOver == 0)
				{
				    R_SEARCH_SN_DISP++;
				    if(R_SEARCH_SN_DISP == C_Memory_Num && OVERMEMORY ==0)   //��ʹ���49
					{
					    R_SEARCH_SN_DISP =1;	
					}
					if(R_SEARCH_SN_DISP == C_Memory_Num)
					{
					}
					else if(R_SEARCH_SN_DISP >= R_CURRENT_SN_DISP)
					{					
						R_SEARCH_SN_DISP = 1;
					}				
				}
				R_SEARCH_SN -- ;
				if(R_SEARCH_SN==0)
				{
					R_SEARCH_SN = C_Memory_Num;
				}				
				//�O�ò�ԃָ�
				SBR_SEARCH_MEM_ADDR();
				SBR_READ_MEN_DATA();
				if(R_EEPROM_DATA)
				{
					L_MEN_DISPLAY_TIME();
					vodisplay = 1;
//					L_MEN_DISPLAY();
					break;
				}
				if(TIMERFLAG.bits.SearchOver)
				{
				//	L_MEN_DISPLAY();
					break;						
				}	
				else
				{
					TIMERFLAG.bits.SearchOver = 1;
					R_SEARCH_SN = R_CURRENT_SN;			
				}			
			}
		}			
	}
}

//;****************************************************************
//; subroutine : _SBR_Write_Flash_Enable
//; input  : none
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
void	SBR_WRITE_FLASH_ENABLE()
{
	SFR_FC0 = C_fwen_ctl_mod;
	_fd1l = 0;
	_fd1h = 4;
	_fd2l = 0x0d;
	_fd2h = 0x09;
	_fd3l = 0xc3;
	_fd3h = 0x40;
	while(SFR_FC0&0b00001000)
	{
		GCC_NOP();
	}
}

//;****************************************************************
//; subroutine : _SBR_Select_Write_Flash_Mode
//; input  : _r_TempDataH/L(Address) 
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
void	SBR_SELECT_WRITE_FLASH_MODE()
{	
	SFR_FC0 = C_Write_mod;
	_fc0 = 0b10000000;
	_farh = r_TempDataH;
	_farl = r_TempDataL;
	SFR_FC2 |= 0x01;//Clear	Write Buffer
}
//;****************************************************************
//; subroutine : _SBR_Write_Flash_Buffer
//; input  : ACC,_R_IAP_TEMP0~_R_IAP_TEMP7 
//; output : none
//; effect:  _R_EEPROM_DATA,MP0
//; Descriptor : 
//;****************************************************************
void	SBR_WRITE_FLASH_BUFFER(uchar Data_Length)
{  
	uint8	i;
	R_EEPROM_DATA = Data_Length;
	for(i=0;i<R_EEPROM_DATA;i++)
	{
		_fd0l = R_IAP_TEMP[i].Val;
		i++;
		_fd0h = R_IAP_TEMP[i].Val;
	}
	
}
//;****************************************************************
//; subroutine : _SBR_Write_Flash
//; input  : none 
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
void	SBR_WRITE_FLASH()
{
	SFR_FC0 |= 0x04;
	while(SFR_FC0&0x04)
	{
	}
	SFR_FC0 &= 0x7f;	//;Disable Write Flash Function	
}
//;****************************************************************
//; subroutine : _SBR_Flash_Page_Erase
//; input  : none 
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
void	SBR_FLASH_PAGE_ERASE()
{
	SFR_FC0 = C_pg_erase_mod;
	while(_fc0 & 0x02)
	{
		
	}
	SFR_FC0 &= 0x7f;	//;Disable Write Flash Function	
}

//;****************************************************************
//; subroutine : SBR_NEXT_MEM_DAAR
//; input  : none 
//; output : none
//; effect:  mp1
//; Descriptor : 
//;****************************************************************
void	SBR_NEXT_MEM_DAAR()
{
	UINT16_VAL	table_addr;
	//
	if(MODEFLAG.bits.User)
	{
		table_addr.Val = MemoryData1_addr+320;	
	}
	else
	{
		table_addr.Val = MemoryData0_addr+320;	
	}
	//r_TempDataL��r_TempDataH
	R_TEMPDATA.Val += 4;
	
	if(R_TEMPDATA.Val>=table_addr.Val)
	{
		if(MODEFLAG.bits.User)
		{
			R_TEMPDATA.Val = MemoryData1_addr;			
		}
		else
		{
			R_TEMPDATA.Val = MemoryData0_addr;	
		}		
	}
}

	
void	L_MEN_DISPLAY_TIME()
{
	TIMERFLAG.bits.SearchOver = 0;	
	LCD_INIT_OFF();
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
	r_TempDataL = R_IAP_TEMP8.Val;
	SBR_DISP_MONTH_ON();
	r_TempDataL = R_IAP_TEMP7.Val;
	SBR_DISP_DAY_ON();
	r_TempDataL = R_IAP_TEMP6.Val;
	SBR_DISP_HOUR_ON();
	r_TempDataL = R_IAP_TEMP5.Val;
	SBR_DISP_MINUTE_ON();
	SBR_DISP_DOT_COLD_ON();
	SBR_DISP_DOT_COL_ON();
	SBR_DISP_DOT_MEMORY_ON();
	//��0�M���@ʾλ����һ�M
	r_TempDataL = R_SEARCH_SN_DISP;	
	if(R_SEARCH_SN == 0)
	{
		r_TempDataL = C_Memory_Num;			
	}
	r_TempDataH = 0;
	SBR_DISP_DIA_ON();
	if(r_TempDataL<10)
      {
		  _mp1h = 4;
		  _mp1l = 20;
		  SFR_iar1.bits.b0 = 1;		
		  SFR_iar1.bits.b1 = 1;		
		  _mp1l--;				
		  SFR_iar1.bits.b0 = 1;		
		  SFR_iar1.bits.b2 = 1;		
		  _mp1l--;	
		  SFR_iar1.bits.b0 = 1;		
		  SFR_iar1.bits.b1 = 1;		  
      }	
	
}

void	L_MEN_DISPLAY()
{
//    if(R_IAP_TEMP4.Val !=0)
//      {
			r_TempDataL = R_IAP_TEMP0.Val;
			r_TempDataH = R_IAP_TEMP1.Val;
		//	SBR_DISP_SYS_ON();
			disp_sys(R_TEMPDATA.Val);
			r_TempDataL = R_IAP_TEMP2.Val;
			r_TempDataH = R_IAP_TEMP3.Val;
		//	SBR_DISP_DIA_ON();
		    disp_dia(R_TEMPDATA.Val);	
			r_TempDataL = R_IAP_TEMP4.Val;
			r_TempDataH = 0;
			SBR_DISP_PLUSE_ON();
		//	SBR_DISP_DOT_MEMORY_ON();
		//	if(MODEFLAG.bits.b5==0)
		//       { 
		//       	SBR_DISP_DOT_U2_OFF();     
		//        SBR_DISP_DOT_U1_ON();
		//        
		//       }
		//       else
		//       {
		//        SBR_DISP_DOT_U1_OFF();
		//        SBR_DISP_DOT_U2_ON();
		//       }
		
		    //��������ʾ�ģ�IHB
			SBR_DISP_DOT_HEART_OFF(); 
			SBR_DISP_DOT_HEART2_OFF();	
			if(IHB_COUNT == 0XAA)
			{
				IHB_COUNT =0;
		        SBR_DISP_DOT_HEART_ON();       //��ʾ���� 
		        SBR_DISP_DOT_HEART2_ON();		
			}
			if(ASCVD)
		    {
		       	SBR_DISP_DOT_ASCVD_ON();              
		    } 
		    else
		    {
		       	SBR_DISP_DOT_ASCVD_OFF(); 
		  	}
		//	;;..........Voice	
			PRE_SYS.BYTE.BYTE_L = R_IAP_TEMP0.Val;
			PRE_SYS.BYTE.BYTE_H = R_IAP_TEMP1.Val;
			PRE_DIA.BYTE.BYTE_L = R_IAP_TEMP2.Val;
			PRE_DIA.BYTE.BYTE_H = R_IAP_TEMP3.Val;
			PLSCNT = R_IAP_TEMP4.Val;
			//20150824 ming �@�z�����������Ӱ푵����I�Ĉ����ٶ�
			DISPLAYWHO();
		    BPPLAY_ONE_INFOEND(BPF_NXTE_MP3); //��һ�� 
			BPPLAYINFOEND();
//      }  
//	  else
//	  {
//			MODEFLAG.bits.b3 =1;             //ʱ�������˸
//		    MODEFLAG.bits.b0 =1;             //ˢ��ʱ��;
//		    SBR_UPDATE_TIME();
//		    SBR_UPDATE_BTT();	  
//		    SBR_DISP_NOMON_ON();
//		    SBR_DISP_DOT_MEMORY_ON();
//		    Delay_ms(30000);
//			MODEFLAG.bits.b3 =0;             //ʱ�������˸
//		    MODEFLAG.bits.b0 =0;             //ˢ��ʱ��;
//		    R_TIMEOUT_SECOND =160;		
//      }	
	
}


//;****************************************************************
//; subroutine : SBR_READ_MEMORY
//; input  : none 
//; output : none
//; effect:  mp1
//; Descriptor : ��ȡ��ǰ�洢��ַ���洢λ��Ϊ�գ�
//;****************************************************************
void SBR_READ_MEM_ADDR()
{
	if(MODEFLAG.bits.User)
	{
		R_EEPROM_DATA = C_EEPROM_Memory_addr_L_1;
	}
	else
	{
		R_EEPROM_DATA = C_EEPROM_Memory_addr_L_0;		
	}
	
	
	r_TempDataL=SBR_EEPROM_READDATA(R_EEPROM_DATA);
	R_EEPROM_DATA ++;
	r_TempDataH=SBR_EEPROM_READDATA(R_EEPROM_DATA);	
	R_EEPROM_DATA ++;
	R_CURRENT_SN=SBR_EEPROM_READDATA(R_EEPROM_DATA);
		
}


void	SBR_READ_MEM_ADDR1()
{
	if(MODEFLAG.bits.User)
	{
		R_EEPROM_DATA = C_EEPROM_Memory_addr_L_1;
	}
	else
	{
		R_EEPROM_DATA = C_EEPROM_Memory_addr_L_0;		
	}
	
	
	r_TempDataL=SBR_EEPROM_READDATA(R_EEPROM_DATA);
	R_EEPROM_DATA ++;
	r_TempDataH=SBR_EEPROM_READDATA(R_EEPROM_DATA);	
	R_EEPROM_DATA ++;
	R_CURRENT_SN=SBR_EEPROM_READDATA(R_EEPROM_DATA);
		
}


//;****************************************************************
//; subroutine : SBR_READ_MEMORY
//; input  : none 
//; output : none
//; effect:  mp1
//; Descriptor : ��ȡ��ǰ�洢��ַ���洢λ��Ϊ�գ�
//;****************************************************************
void	SBR_Previous_Mem_Addr()
{
	UINT16_VAL	table_addr;
	//
	if(MODEFLAG.bits.User)
	{
		table_addr.Val = MemoryData1_addr;	
	}
	else
	{
//		table_addr = C_Memory_Start_addr_1/256;	
		table_addr.Val = MemoryData0_addr;	
	}
	
	//r_TempDataL��r_TempDataH
	R_TEMPDATA.Val -= 4;
	
	if(R_TEMPDATA.Val<table_addr.Val)
	{
		if(MODEFLAG.bits.User)
		{
			R_TEMPDATA.Val = MemoryData1_addr+316;			
		}
		else
		{
			R_TEMPDATA.Val = MemoryData0_addr+316;	
		}		
	}	
	
}

//;****************************************************************
//;IAP format(4 words)
//;sys_L	--����ѹ
//;dia_H & sys_H(bit7~0)	
//;dia_L	--����ѹ
//;pulse
//;min;;bit7=0 am/bit7=1 pm OR hour.4
//;bit7--bit4 month/bit3--bit0 hour
//;day
//;year
//;****************************************************************
void	SBR_READ_MEN_DATA()
{
	volatile	UINT16_VAL TABLE_BUFF;
	TABLE_BUFF.Val = MemoryData0[R_TEMPDATA.Val - C_Memory_Start_addr_0];
	R_IAP_TEMP0.Val = TABLE_BUFF.BYTE.BYTE_L;
	R_IAP_TEMP1.Val = TABLE_BUFF.BYTE.BYTE_H&0x0f;
	R_IAP_TEMP3.Val = (TABLE_BUFF.BYTE.BYTE_H>>4)&0x0f;
	
	
	R_TEMPDATA.Val++;
	TABLE_BUFF.Val = MemoryData0[R_TEMPDATA.Val - C_Memory_Start_addr_0];
	R_IAP_TEMP2.Val = TABLE_BUFF.BYTE.BYTE_L;
	R_IAP_TEMP4.Val = TABLE_BUFF.BYTE.BYTE_H;	
	
	R_TEMPDATA.Val++;
	TABLE_BUFF.Val = MemoryData0[R_TEMPDATA.Val - C_Memory_Start_addr_0];
	R_IAP_TEMP5.Val = TABLE_BUFF.BYTE.BYTE_L;	
	R_IAP_TEMP6.Val = TABLE_BUFF.BYTE.BYTE_H&0x0f;
	if(R_IAP_TEMP5.bits.b7)
	{
		R_IAP_TEMP6.bits.b4 = 1; 	
		R_IAP_TEMP5.bits.b7 = 0;	
	}
	if(R_IAP_TEMP5.bits.b6)
	{
	    IHB_COUNT = 0XAA;
		R_IAP_TEMP5.bits.b6 = 0;	
	}	

	R_IAP_TEMP8.Val = (TABLE_BUFF.BYTE.BYTE_H>>4)&0x0f;//;month
	R_TEMPDATA.Val++;
	TABLE_BUFF.Val = MemoryData0[R_TEMPDATA.Val - C_Memory_Start_addr_0];	
	R_IAP_TEMP7.Val = TABLE_BUFF.BYTE.BYTE_L;
	R_IAP_TEMP9.Val = TABLE_BUFF.BYTE.BYTE_H;
	
	ASCVD = R_IAP_TEMP7.bits.b7;
	R_IAP_TEMP7.bits.b7 =0;	

	R_TEMPDATA.Val -= 3;	
	R_EEPROM_DATA = 0;
	
	if(R_IAP_TEMP0.Val==0 && R_IAP_TEMP1.Val==0)
	{
		return;	
	}
	if(R_IAP_TEMP2.Val==0 && R_IAP_TEMP3.Val==0)
	{
		return;	
	}	
	if(R_IAP_TEMP4.Val)
	{
		R_EEPROM_DATA = 0xff;
	}
	
}

void	SBR_ADD_MEM()
{
	volatile	UINT16_VAL ADD_MEM_BUFF1,ADD_MEM_BUFF2;	
	
	ADD_MEM_BUFF1.BYTE.BYTE_L = R_IAP_TEMP0.Val;
	ADD_MEM_BUFF1.BYTE.BYTE_H = R_IAP_TEMP1.Val;	

	ADD_MEM_BUFF2.BYTE.BYTE_L = r_Temp0.Val;
	ADD_MEM_BUFF2.BYTE.BYTE_H = r_Temp1.Val;	

	ADD_MEM_BUFF2.Val += ADD_MEM_BUFF1.Val;
	r_Temp0.Val = ADD_MEM_BUFF2.BYTE.BYTE_L;
	r_Temp1.Val = ADD_MEM_BUFF2.BYTE.BYTE_H;

	ADD_MEM_BUFF1.BYTE.BYTE_L = R_IAP_TEMP2.Val;
	ADD_MEM_BUFF1.BYTE.BYTE_H = R_IAP_TEMP3.Val;	

	ADD_MEM_BUFF2.BYTE.BYTE_L = r_Temp2.Val;
	ADD_MEM_BUFF2.BYTE.BYTE_H = r_Temp3.Val;	

	ADD_MEM_BUFF2.Val += ADD_MEM_BUFF1.Val;
	r_Temp2.Val = ADD_MEM_BUFF2.BYTE.BYTE_L;
	r_Temp3.Val = ADD_MEM_BUFF2.BYTE.BYTE_H;		

	ADD_MEM_BUFF1.BYTE.BYTE_L = R_IAP_TEMP4.Val;
	ADD_MEM_BUFF1.BYTE.BYTE_H = 0;	

	ADD_MEM_BUFF2.BYTE.BYTE_L = r_Temp4.Val;
	ADD_MEM_BUFF2.BYTE.BYTE_H = r_Temp5.Val;	

	ADD_MEM_BUFF2.Val += ADD_MEM_BUFF1.Val;
	r_Temp4.Val = ADD_MEM_BUFF2.BYTE.BYTE_L;
	r_Temp5.Val = ADD_MEM_BUFF2.BYTE.BYTE_H;

	R_SEARCH_SN ++;

}



//;****************************************************************
//;; 1......_R_CURRENT_SN-------_R_SEARCH_SN.....99
//;****************************************************************
void	SBR_SEARCH_MEM_ADDR()
{
	volatile	UINT16_VAL	SEARCH_MEM_BUFF1;
	//��ԃ��ָᘴ�춵�춮�ǰ��ָ�
	if(R_SEARCH_SN>=R_CURRENT_SN)
	{
		r_Temp1.Val = R_CURRENT_SN + C_Memory_Num - R_SEARCH_SN;
	}
	else
	{
		r_Temp1.Val = R_CURRENT_SN  - R_SEARCH_SN;		
	}
	SEARCH_MEM_BUFF1.BYTE.BYTE_L = r_Temp1.Val;
	SEARCH_MEM_BUFF1.BYTE.BYTE_H = 0;	
	SEARCH_MEM_BUFF1.Val *= 4;

	SBR_READ_MEM_ADDR();
	
	R_TEMPDATA.Val -= SEARCH_MEM_BUFF1.Val;
	
	UINT16_VAL	table_addr;
	//
	if(MODEFLAG.bits.User)
	{
		table_addr.Val = MemoryData1_addr;	
	}
	else
	{

		table_addr.Val = MemoryData0_addr;	
	}	

	if(R_TEMPDATA.Val<table_addr.Val)
	{
		R_TEMPDATA.Val += 320;
	}
	
	if(R_TEMPDATA.Val>=table_addr.Val+320)
	{
		R_TEMPDATA.Val += table_addr.Val;
	}	

}

void	SBR_CLEAR_MEMORY()
{
	uint16	table_addr_end;
	LCD_INIT_OFF();
	if(MODEFLAG.bits.User)
	{
		R_TEMPDATA.Val = MemoryData1_addr;	
		table_addr_end = MemoryData1_addr+316;
	}
	else
	{
		R_TEMPDATA.Val = MemoryData0_addr;	
		table_addr_end = MemoryData0_addr+316;		
	}

	r_Temp0.Val = 16;
	while(1)
	{
		SBR_WRITE_FLASH_ENABLE();
		//;;...._r_TempDataH/L(Address) 
		SBR_SELECT_WRITE_FLASH_MODE();
		SBR_FLASH_PAGE_ERASE();
		R_TEMPDATA.Val += 64; 
		if(table_addr_end>R_TEMPDATA.Val)
		{
			
		}
		else
		{
		
			if(MODEFLAG.bits.User)
			{
				r_Temp0.Val = C_EEPROM_Memory_addr_L_1;		
				EEPROM_WRITING(r_Temp0.Val,MemoryData1_addr%256);	
				r_Temp0.Val++;
				EEPROM_WRITING(r_Temp0.Val,MemoryData1_addr/256);	
				r_Temp0.Val++;
				EEPROM_WRITING(r_Temp0.Val,1);	
				R_TEMPDATA.Val = C_Memory_Start_addr_1;	
				EEPROM_WRITING(0x3B,0);					
			}
			else
			{
				r_Temp0.Val = C_EEPROM_Memory_addr_L_0;		
				EEPROM_WRITING(r_Temp0.Val,MemoryData0_addr%256);	
				r_Temp0.Val++;
				EEPROM_WRITING(r_Temp0.Val,MemoryData0_addr/256);	
				r_Temp0.Val++;
				EEPROM_WRITING(r_Temp0.Val,1);	
				R_TEMPDATA.Val = C_Memory_Start_addr_0;	
				EEPROM_WRITING(0x3A,0);							
			}
			if(MODEFLAG.bits.User)
		    {
			    R_EEPROM_DATA = C_EEPROM_Memory_120_1;
		    }
		    else
		    {
		    	R_EEPROM_DATA = C_EEPROM_Memory_120_0;		
		    }
			EEPROM_WRITING(R_EEPROM_DATA,1);
			OLD_PRE_SYS = 0; 
			OLD_PRE_DIA = 0;
			OLD_PLSCNT = 0;
		    Delay_ms(10000);			
			break;
		}

	}
	
		
}

void	SBR_NEXT_MEM_DAAR1()
{
	UINT16_VAL	table_addr;
	//
	if(MODEFLAG.bits.User)
	{
		table_addr.Val = MemoryData1_addr+320;	
	}
	else
	{
//		table_addr = C_Memory_Start_addr_1/256;	
		table_addr.Val = MemoryData0_addr+320;	
	}
	//r_TempDataL��r_TempDataH
	R_TEMPDATA.Val += 4;
	
	if(R_TEMPDATA.Val>=table_addr.Val)
	{
		if(MODEFLAG.bits.User)
		{
			R_TEMPDATA.Val = MemoryData1_addr;			
		}
		else
		{
			R_TEMPDATA.Val = MemoryData0_addr;	
		}		
	}
}

