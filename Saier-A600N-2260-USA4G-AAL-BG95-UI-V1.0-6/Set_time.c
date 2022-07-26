#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"


/************************ ****************/
#define	C_TimerSetting_Timeout	150
//;---------------------------------------------------------
volatile	uint8	lu8v_halt_mode;
//年月日時分的最小值
const	uint8	T_TIME_MIN[5]= {0,1,1,0,0};
//年月日時分的最大值
const	uint8	T_TIME_MAX[5]= {86,12,31,23,59};
//每個月的天數判斷，當處於2月時程序中會再次判斷是否是閏年
const	uint8	T_DAY_MAX[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

void	SBR_FLASHING_DISABLE();
void	SBR_FLASHING_ENABLE();
void	SBR_TIME_ADD();
void	SBR_MONTH_ON();
void	SBR_DAY_ON();
void	SBR_HOUR_ON();
void	SBR_MINUTE_ON();


void	INT_DATE_TIME(void)
{
//	R_YEAR = 17;
//	R_MONTH = 1;	
//	R_DAY= 1;	
//	R_CLOCK_HOUR = 12;
//	R_CLOCK_MINUTE = 0;
    R_YEAR = SBR_EEPROM_READDATA(0x0D);
    R_MONTH = SBR_EEPROM_READDATA(0x0E);
    R_DAY = SBR_EEPROM_READDATA(0x3D);
    R_CLOCK_HOUR = SBR_EEPROM_READDATA(0x3E);
    R_CLOCK_MINUTE = SBR_EEPROM_READDATA(0x3F);                
	R_CLOCK_SECOND = 100;
}

/*******************************************************************************************
** 函数名称: SBR_TIME_SETTING
** 函数描述: 設置時間日期
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_TIME_SETTING(void)
{
	uint8 gu8v_loop_flag;
	uint8 gu8v_long_press_times=0;	
	//關閉LCD
	LCD_INIT_OFF();
	//開啟顯示
	SBR_FLASHING_ENABLE();
	//清除溢出時間設置	
	R_TIMEOUT_SECOND = 0;
	//
	KEYFLAG.Val &= 0B11000000;
	CLRMON =1;
	//循環標誌位設置，如果要跳出循環清除標準位即可
	gu8v_loop_flag = 1;
	while(gu8v_loop_flag)
	{
		//判斷時間是否有溢出
		if(R_TIMEOUT_SECOND < C_TimerSetting_Timeout)
		{
			if(KEYFLAG.bits.SetKey)
			{
				//如果有set按鍵按下將設置的數據移動至下一位，依次是年月日時分
				KEYFLAG.bits.SetKey = 0;
				//清屏
				LCD_INIT_OFF();
				R_DISPLAYCOUNTER++;
				R_DISPLAYCOUNTER++;
				//CLR	_R_DISPLAYCOUNTER.0	
				R_DISPLAYCOUNTER &= 0B11111110;	
				R_DISPLAYTIME = 0;
				if(R_DISPLAYCOUNTER>=14)
				{
					//如果設置完畢顯示月份&時間
//					r_TempDataL = R_MONTH;
//					SBR_DISP_MONTH_ON();
//					r_TempDataL = R_DAY;
//					SBR_DISP_DAY_ON();
//					r_TempDataL = R_CLOCK_HOUR;
//					SBR_DISP_HOUR_ON();
//					r_TempDataL = R_CLOCK_MINUTE;
//					SBR_DISP_MINUTE_ON();
                    
					//退出循環
					if(CLRMON)
		              {
		              	LCD_INIT_OFF();
		              }
		              else
		              {
		              	Delay_ms(30000);
		              	MODEFLAG.bits.b5=0;
 	                    SBR_CLEAR_MEMORY();
 	 					MODEFLAG.bits.b5=1;	
	 					SBR_CLEAR_MEMORY();		                
		                LCD_INIT_OFF();
		              }
					gu8v_loop_flag = 0;
				}

			}
			if(KEYFLAG.bits.StartKey)
			{
//如果有set按鍵按下將設置的數據移動至下一位，依次是年月日時分
				KEYFLAG.bits.StartKey = 0;
				LCD_INIT_OFF();
				//如果設置完畢顯示月份&時間
//				r_TempDataL = R_MONTH;
//				SBR_DISP_MONTH_ON();
//				r_TempDataL = R_DAY;
//				SBR_DISP_DAY_ON();
//				r_TempDataL = R_CLOCK_HOUR;
//				SBR_DISP_HOUR_ON();
//				r_TempDataL = R_CLOCK_MINUTE;
//				SBR_DISP_MINUTE_ON();				
				//退出循環
				gu8v_loop_flag = 0;
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
			
			if(KEYFLAG.bits.RecallKey)
			{
				KEYFLAG.bits.RecallKey = 0;
				R_TIMEOUT_SECOND = 0;
				R_DISPLAYTIME = 0;
//				R_DISPLAYCOUNTER.0 = 0;
				R_DISPLAYCOUNTER &= 0B11111110;	
				if((R_DISPLAYCOUNTER<10))
				{
				 SBR_TIME_ADD();	
				}
				else
				{   //这里面就设置年月日时分外的其他的了
				  switch(R_DISPLAYCOUNTER)
			            {   //在这里面改标志参数
//			               case 10:
//			               case 11: MODEFLAG.bits.b4 = ~MODEFLAG.bits.b4; break;   //语音0关1开
			               case 10:
			               case 11:	mmHg_Kpa = ~mmHg_Kpa;   break;	               //单位选择			            
			               case 12:
			               case 13:  CLRMON = ~CLRMON;   break;             //单位选择
			            }
				} 			
			}
			SBR_FLASHING_TIME();
		}
		else
		{
			//關閉顯示
			SBR_FLASHING_DISABLE();
			//退出設置跳出死循環
			gu8v_loop_flag = 0;
			
		}
	}
}	

/*******************************************************************************************
** 函数名称: SBR_TIME_ADD
** 函数描述: 相應的位累加
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_TIME_ADD()
{
	//年||月||日||時||分進行累加
	R_TIME[R_DISPLAYCOUNTER/2]++;
	//通過查表得到當前設置參數的最大值與最小值，以便判斷是否有溢出
	//最小值
	r_Temp0.Val =T_TIME_MIN[R_DISPLAYCOUNTER/2];
	//最大值	
	r_Temp1.Val=T_TIME_MAX[R_DISPLAYCOUNTER/2];
	//是否是設置日期，如果設置日期需要考慮31天30天以及2月份的特殊情況
	if(R_DISPLAYCOUNTER/2 == 2)
	{
		//如果設置日期的話將最小值設為1
		r_Temp0.Val = 1;
		r_Temp1.Val = T_DAY_MAX[R_MONTH];
		if(R_MONTH == 2)
		{
			//閏年判斷，當前判斷方式僅適用於2014-2099
			if((R_YEAR & 0b00000011) == 0)
			{
				//閏年為29天
				r_Temp1.Val++;
			}
		}		
	}
	//用於進位判斷
	r_Temp2.Val = 0;
	if(R_TIME[R_DISPLAYCOUNTER/2]<r_Temp0.Val)
	{
		R_TIME[R_DISPLAYCOUNTER/2] = r_Temp0.Val;
	}
	if(R_TIME[R_DISPLAYCOUNTER/2]>r_Temp1.Val)
	{
		R_TIME[R_DISPLAYCOUNTER/2] = r_Temp0.Val;	
		//產生進位
		r_Temp2.Val = 1;	
	}	
}


/*******************************************************************************************
** 函数名称: SBR_FLASHING_ENABLE
** 函数描述: LCD ENABLE
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_FLASHING_ENABLE()
{
	TIMERFLAG.bits.Display = 1;
	R_DISPLAYCOUNTER = 0;
	R_DISPLAYTIME =0 ;
}


/*******************************************************************************************
** 函数名称: SBR_FLASHING_DISABLE
** 函数描述: LCD disable
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_FLASHING_DISABLE()
{
	TIMERFLAG.bits.Display = 0;
	R_DISPLAYCOUNTER = 0;
	R_DISPLAYTIME =0 ;
}

/*******************************************************************************************
** 函数名称: SBR_FLASHING_TIME
** 函数描述: 設置模式時LCD的顯示效果
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_FLASHING_TIME()
{
	if(TIMERFLAG.bits.Display && R_DISPLAYTIME==0)
	{
		if(R_DISPLAYCOUNTER < 14)
		{
			switch(R_DISPLAYCOUNTER)
			{
				//0 1 為年份閃爍
				case	0:
				//_L_FLASHING_YEAR_ON:
				LCD_INIT_OFF();
				r_TempDataL = 20;
				SBR_DISP_MONTH_ON();
				r_TempDataL = R_YEAR;
				SBR_DISP_DAY_ON();				
				R_DISPLAYTIME = 500/8;
				R_DISPLAYCOUNTER++;		
				break;
				case	1:
				//_L_FLASHING_YEAR_OFF:
				SBR_DISP_MONTH_OFF();
				SBR_DISP_DAY_OFF();			
			//	R_DISPLAYCOUNTER--;
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;
			//	R_DISPLAYCOUNTER++;								
				break;	
				//2 3 為月份閃爍
				case	2:
				//_L_FLASHING_MONTH_ON:
				SBR_MONTH_ON();
				SBR_DAY_ON();
//				SBR_HOUR_ON();
//				SBR_MINUTE_ON();
				SBR_DISP_DOT_COLD_ON();
//				SBR_DISP_DOT_COL_ON();			
				R_DISPLAYTIME = 500/8;	
				R_DISPLAYCOUNTER++;					
				break;	
				case	3:
				//_L_FLASHING_MONTH_OFF:
				SBR_DISP_MONTH_OFF();
/*				SBR_DAY_ON();*/
//				SBR_HOUR_ON();
//				SBR_MINUTE_ON();
				SBR_DISP_DOT_COLD_ON();
			//	SBR_DISP_DOT_COL_ON();		
			//	R_DISPLAYCOUNTER--;
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;
			//	R_DISPLAYCOUNTER++;				
				break;					
				
				//4 5  為天數份閃爍
				case	4:
				//_L_FLASHING_DAY_ON:
				SBR_MONTH_ON();
				SBR_DAY_ON();
//				SBR_HOUR_ON();
//				SBR_MINUTE_ON();
				SBR_DISP_DOT_COLD_ON();
//				SBR_DISP_DOT_COL_ON();
				R_DISPLAYTIME = 500/8;	
				R_DISPLAYCOUNTER++;					
				break;	
				case	5:
				//_L_FLASHING_DAY_OFF:
/*				SBR_MONTH_ON();*/
				SBR_DISP_DAY_OFF();
//				SBR_HOUR_ON();
//				SBR_MINUTE_ON();
				SBR_DISP_DOT_COLD_ON();
//				SBR_DISP_DOT_COL_ON();
			//	R_DISPLAYCOUNTER--;
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;
			//	R_DISPLAYCOUNTER++;				
				break;	
				//6 7 為小時閃爍				
				case	6:
				//_L_FLASHING_HOUR_ON:
				SBR_MONTH_ON();
				SBR_DAY_ON();
				SBR_HOUR_ON();
				SBR_MINUTE_ON();
				SBR_DISP_DOT_COLD_ON();
				SBR_DISP_DOT_COL_ON();
				R_DISPLAYTIME = 500/8;	
				R_DISPLAYCOUNTER++;					
				break;	
				case	7:
				//_L_FLASHING_HOUR_OFF:
//				SBR_MONTH_ON();
//				SBR_DAY_ON();
				SBR_DISP_HOUR_OFF();
/*				SBR_MINUTE_ON();*/
				SBR_DISP_DOT_COLD_ON();
				SBR_DISP_DOT_COL_ON();
			//	R_DISPLAYCOUNTER--;
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;
			//	R_DISPLAYCOUNTER++;				
				break;					
				
				//8 9 為分鐘閃爍
				case	8:
				//_L_FLASHING_MINUTE_ON:
				SBR_MONTH_ON();
				SBR_DAY_ON();
				SBR_HOUR_ON();
				SBR_MINUTE_ON();
				SBR_DISP_DOT_COLD_ON();
				SBR_DISP_DOT_COL_ON();
				R_DISPLAYTIME = 500/8;	
				R_DISPLAYCOUNTER++;					
				break;	
				case	9:
				//_L_FLASHING_MINUTE_OFF:
//				SBR_MONTH_ON();
//				SBR_DAY_ON();
//				SBR_HOUR_ON();
				SBR_DISP_MINUTE_OFF();
				SBR_DISP_DOT_COLD_ON();
				SBR_DISP_DOT_COL_ON();
			//	R_DISPLAYCOUNTER--;
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;	
			//	R_DISPLAYCOUNTER++;								
				break;          
//			    case 10:
//				LCD_INIT_OFF();
////				SBR_DISP_SPE_ON();
//				   if(MODEFLAG.bits.b4==0)
//                    {
//                     SBR_DISP_SP_OFF();
//				    }
//                    else
//                     {
// 			    	  SBR_DISP_SP_ON();
//                     }
//			    R_DISPLAYTIME = 500/8;
//				R_DISPLAYCOUNTER++;
//				break;
//			    case 11: 		        
//			    SBR_DISP_DIA_OFF();           
//				R_DISPLAYCOUNTER--;	
//				R_DISPLAYTIME = 500/8;						
//				break;
			    case     10://设置单位
			    LCD_INIT_OFF();
			    if(mmHg_Kpa)
		        {
//				   SBR_DISP_DP1_KPA_ON();
//                   SBR_DISP_DOT_P1_ON();
//                   SBR_DISP_DOT_P2_ON();
//			       R_TEMPDATA.Val=0;
//	               SBR_DISP_DIA_ON();
//	               SBR_DISP_SYS_ON();
			    }
			    else
			    {
//			       R_TEMPDATA.Val=0;
//	               SBR_DISP_DIA_ON();
//	               SBR_DISP_SYS_ON();	
				   SBR_DISP_DOT_DIA_ON();
			    }
			    R_DISPLAYTIME = 500/8;
				R_DISPLAYCOUNTER++;
				break;
			    case     11:
//                SBR_DISP_DP1_KPA_OFF();
                SBR_DISP_DOT_DIA_OFF();
//                SBR_DISP_DOT_P1_OFF();
//                SBR_DISP_DOT_P2_OFF();                
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;	
			//	R_DISPLAYCOUNTER++;								
				break; 									
				
			    case     12://设置单位
			    LCD_INIT_OFF();
			    SBR_DISP_CLL_ALL_T_ON();
			    SBR_DISP_DOT_MEMORY_ON();
			    if(CLRMON)
		        {
				   SBR_Disp_NO_ON();
			    }
			    else
			    {
				   SBR_Disp_YS_ON();
			    }
			    R_DISPLAYTIME = 500/8;
				R_DISPLAYCOUNTER++;
				break;
			    case     13:
			    SBR_DISP_SYS_OFF();
				R_DISPLAYCOUNTER--;	
				R_DISPLAYTIME = 500/8;	
			//	R_DISPLAYCOUNTER++;								
				break;															
			}
		}
		else
		{
			//
			SBR_FLASHING_DISABLE();
		}
		
	}	
}




/*******************************************************************************************
** 函数名称: SBR_MONTH_ON
** 函数描述: 
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_MONTH_ON()
{
	r_TempDataL = R_MONTH;
	SBR_DISP_MONTH_ON();	
}

/*******************************************************************************************
** 函数名称: SBR_DAY_ON
** 函数描述:
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_DAY_ON()
{
	r_TempDataL = R_DAY;
	SBR_DISP_DAY_ON();	
}

/*******************************************************************************************
** 函数名称: SBR_HOUR_ON
** 函数描述: 
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_HOUR_ON()
{
	r_TempDataL = R_CLOCK_HOUR;
	SBR_DISP_HOUR_ON();	
}

/*******************************************************************************************
** 函数名称: SBR_MINUTE_ON
** 函数描述: 
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_MINUTE_ON()
{
	r_TempDataL = R_CLOCK_MINUTE;
	SBR_DISP_MINUTE_ON();	
}

/*******************************************************************************************
** 函数名称: SBR_ENTER_HALTMODE
** 函数描述: 
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void	SBR_ENTER_HALTMODE()
{


	lu8v_halt_mode = 1;	
	while(lu8v_halt_mode)
	{
		_tb0e = 0;					
		GCC_CLRWDT();	
		GCC_CLRWDT1();
		GCC_CLRWDT2();	
	//	INT_IO();
		_pcs1 = 0;      //set tx PC5 rx   PC4	
		
		_pac =  0b00111010;
		_pa =   0b00000000;
		_papu = 0b00111010;
		_pawu = 0b00111010;
		
		_pbc =  0;
		_pb =   0;
		_pbpu = 0b11111111;	
		
		_pcc =  0b00010000;
		_pc =   0B00010000;
		_pcpu = 0b11101111;
		
		_pdc = 0;
		_pd =  0;
		_pdpu = 0b11111111;
			
		_pec = 0;
		_pe =  0;
		_pepu = 0b11111111;	
		
		_batden = 0;
		_adcen = 0;
		_regc =  0x01;   //内部稳压IC开关  enable =3.3v
		_pgac0 = 0;
		_pgac1 = 0;
		_pgac2 = 0;
		_pgac3 = 0;	
		_scfc0 = 0;
		_scfc1 = 0;
		_scfckd = 0;
		_ccvrefc = 0;
		_lcden = 0;
	
		_ptm1c0 = 0;
		_ptm1c1 = 0;
		_ptm2c0 = 0;
		_ptm2c1 = 0;
		_stm0c0 = 0;
		_stm0c1 = 0;
		
	    //睡眠模式循環
		_fsiden = 1;	//		;IDLE0
		_fhiden = 0;
		TIMERFLAG.bits.TB1_INT = 0;	
		_pt1on = 0;
		_pt2on = 0;	
		TIMERFLAG.bits.TB1_INT_625 = 0;		
		GCC_HALT();
//		al_scan();
		GCC_CLRWDT1();
		GCC_CLRWDT2();
//		SBR_UPDATE_TIME();	
		if(TIMERFLAG.bits.TB1_INT)
			{
				TIMERFLAG.bits.TB1_INT = 0;
				if(TIMERFLAG.bits.NewDay)
				{
					TIMERFLAG.bits.NewDay = 0;
					R_DISPLAYCOUNTER = 4;
					SBR_TIME_ADD();
					if(r_Temp2.Val)
					{
						R_DISPLAYCOUNTER = 2;
						SBR_TIME_ADD();	
						if(r_Temp2.Val)
						{
							R_DISPLAYCOUNTER = 0;
							SBR_TIME_ADD();						
						}
					}
				}
		    }
		else
		{
						//这里还要检讨一下，待机时按键太快会有不能唤醒的状况
			if(GPIO_STARTKEY==0||FUL_DET==0||GPIO_RECALLKEY==0||GPIO_SETKEY==0)
			{
				_tb0e = 1;
//				_mf3e = 1;
				gu8v_wake_up_time = 0;
				KEYSCAN_INIT();
				while(gu8v_wake_up_time<10)
				{
					GCC_NOP();
					if(gu8v_KeyDown.Val ==0)
					{

					}	
					else
					{
						lu8v_halt_mode = 0;						
					}
					if(FUL_DET==0)
					{
						TIME_TEEP_flag =1;	
				        _int0e =1;
					    lu8v_halt_mode = 0;		
					}						
				}
			}
		
		}
	}	
}

