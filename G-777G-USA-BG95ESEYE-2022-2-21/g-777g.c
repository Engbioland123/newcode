#include "HT45F67.h"
#include "Defineport.h"
#include "LCD.h"
#include "DELAY.h"
#include "string.h"
#include "uart.h"
#include "runTask.h"
#include "ad.h"
#include "iap.h"



uint iSec;
void Sys_RESET()
{
	_smod0 = 1;
//	_wdtc=0b01010010;
	_wdtc=0b01010100;
	_lcdc = 0b10000000;
}

void init_timer_base0()
{
	_emi=0;
	_tbc   = 0b10000101;//250ms中断一次//使能，8192/f(TB)时基F(TBC)
	//_tbc   = 0b10000100;//125ms中断一次
	_tb0f=0;//时基0中断请求标志位无请求(没有中断标志？)
	_tb0e=1;//时基0中断控制位使能
	_emi=1;//开总中断
}

void PORT_init()
{	
	_pa    = 0b00111111;
	_pac   = 0b00111111;
	_pawu  = 0b00001000;
	_papu  = 0b00111110;

	_pb   = 0b01000000;
	_pbc  = 0b00000000;
	//_pbpu = 0b00000000;
	
	_pcfs = 0;
	_pc   = 0b00011001;
	_pcc  = 0b00011001;
	//_pcpu = 0b00000000;
	
	_pbfs1=1;//OP1N
	_pbfs3=1;//AN1
	_pbfs4=1;//AN1
	
	_pdfs = 0b11111110;
	_pdc  = 0b11111110;
	_pd   = 0b00000000;

	_pefs = 0b00111111;
	_pffs = 0b11100000;
	_pgfs = 0b00111111;
	

	_phfs =0;
	_phc  =0xfe;
	_ph   =0xfe;
	_phpu =0xfe;
	
	_sfs0 = 1;
	_sfs1 = 0;
	
}

uchar key_scan()
{
	uchar i=0;
	uchar i2=0;
	uchar i3=0;
	i=_pa;
	i&=0b00001100;
	i>>=2;
	i2=i;//开机键为1，记忆键为2
	while(i!=3)
	{
		me_delay_ms(10);
		i=_pa;
		i&=0b00001100;
		i>>=2;
		i3++;
		SystemFlags.Datas.Flags.Bits.TestKeyboad=0;
		if(i3>60)
		{
			if(i==1)
			{
				i2=0xf0;//记忆键长按	
			}
			if(i==2)
			{
				i2=0xff;//开机键长按
			}
			if(i==0)
			{
				i2=0;//两个同时按下	
			}
			break;	
		}
	}
	return i2;
}

void entry_Blood_drop(void)
{
	SystemFlags.Datas.Flags.Bits.Blood_drop=1;
	memset(disp_buff,0,16);
	show_display();
	AD_set();
	AD_value=0;
	_acs2=1;
	_acs1=0;
	_acs0=0;
	_tsc=1;
	_pbc1=1;
	_pb1=1;
	_pbpu1=0;
	WDR();
	me_delay_ms(800);
	WDR();
	SystemFlags.Datas.Flags.Bits.uart_reicev_flag=0;
	SystemFlags.Datas.uart_reicev_count=0;
	flash[1]    &=0b01111111;//滴血符闪
	flash[14]=0b11111110;//号时钟:号闪烁
	Show_Big_number(" ",0,0);
}

void exit(void)
{
	SystemFlags.Datas.Flags.Bits.GSM_Send_over=0;
	SystemFlags.Datas.Flags.Bits.May_reicev_uart=0;
	SystemFlags.Datas.Flags.Bits.Memory_Send=0;
	SystemFlags.Datas.Flags.Bits.Bluetooth=0;
	SystemFlags.Datas.Flags.Bits.TestKeyboad=0;
	SystemFlags.Datas.Flags.Bits.Win_task=0;
	SystemFlags.Datas.CTL_mode=0;
	SystemFlags.Datas.Class=0;
	SystemFlags.Datas.Flags.Bits.CHRC=0;
	SystemFlags.Datas.Flags.Bits.power_on=0;	
	SystemFlags.Datas.Flags.Bits.Test_paper=0;
	SystemFlags.Datas.Flags.Bits.Blood_drop=0;
	SystemFlags.Datas.Flags.Bits.point=0;
	SystemFlags.Datas.Flags.Bits.Battery_LO=0;
	SystemFlags.Datas.GSM_Signal=0;
	SystemFlags.Datas.Error_Loop_Count=0;
}

void show_sequence(void)
{
	test_buff[0]=Project_Sequence/100000%10;//查看序列号
	test_buff[1]=Project_Sequence/10000%10;
	test_buff[2]=Project_Sequence/1000%10;
	test_buff[3]=Project_Sequence/100%10;
	test_buff[4]=Project_Sequence/10%10;
	test_buff[5]=Project_Sequence%10;
	Show_Big_number(test_buff,0,0);
	show_display();
}

void main()
{
	uint i=0;
	uint iUrl = 0;
	uint a,b=0;
	uchar uSecond = 0;
	
	PORT_init();
	if(_to)//看门狗溢出
    {
    	if(SystemFlags.Datas.Flags.Bits.Send_begin)
		{ 
			Gsm_timer++;
		}
		run_time();
	}
	else//上电
	{
		Sys_RESET();
		memset(flash,0xff,16);
		Sleep_time=180;
		//Sleep_time=300;
		memset(LcdRam,0x00,32);
	  	Show_VER();//版本号
		_lcdc = 0b10000001;
		init_timer_base0();
		WDR();
		me_delay_ms(800);
		WDR();
		me_delay_ms(800);
		WDR();
//		while(1)WDR();;
//------------------------------
#if testmode


					memset(BLOOD_Package.bytes,0,128);

					BLOOD_Package.bytes[0]=0x25;//版本号
					BLOOD_Package.bytes[1]=0x01;//客户码
					BLOOD_Package.bytes[2]=0x02;//机种码
					BLOOD_Package.bytes[3]=0x02;//机型号
					BLOOD_Package.bytes[4]=0x00;//用户号
					BLOOD_Package.bytes[5]=0x01;//生产月份
					BLOOD_Package.bytes[6]=0x19;//生产年份
					
					Project_Sequence=111111;
												
					BLOOD_Package.bytes[7]=Project_Sequence&0xff; //机身序列号1 低位
					BLOOD_Package.bytes[8]=(Project_Sequence>>8)&0xff; //机身序列号2
					BLOOD_Package.bytes[9]=(Project_Sequence>>16)&0xff; //机身序列号3
					BLOOD_Package.bytes[10]=(Project_Sequence>>24)&0xff;//机身序列号4 高位
					
					BLOOD_Package.bytes[11]=165;//2V电压值 //_pvref
					
					BLOOD_Package.bytes[12]=0x00;//_dal					
					BLOOD_Package.bytes[13]=0x66;//400mV电压值 _dah

					BLOOD_Package.bytes[14]=0;
					BLOOD_Package.bytes[15]=0;
					BLOOD_Package.bytes[16]=0;	
					BLOOD_Package.bytes[17]=0;//血糖测试次数序列号
					
					BLOOD_Package.bytes[18]=0x71;//_opc1;					
					
					BLOOD_Package.bytes[19]=0;	
					BLOOD_Package.bytes[20]=0;	
					BLOOD_Package.bytes[71]=1000%256;//Pub_temp;
					BLOOD_Package.bytes[72]=1000/256;//Pub_temp>>8;
					BLOOD_Package.bytes[74]=BLOOD_Package.bytes[11]^BLOOD_Package.bytes[12]^BLOOD_Package.bytes[13]^BLOOD_Package.bytes[18]^BLOOD_Package.bytes[71]^BLOOD_Package.bytes[72];
					BLOOD_Package.bytes[75]=18;		//年
					BLOOD_Package.bytes[76]=10;		//月
					BLOOD_Package.bytes[77]=1;		//月
					BLOOD_Package.bytes[78]=9;		//时
					BLOOD_Package.bytes[79]=45;		//分
			
					if(fun_enable_fwen())
					{
						me_delay_100us();
						fun_erase_page(Mem_adjust_address);	
						me_delay_100us();
						fun_write_cpage(Mem_adjust_address,128,0);
					}
					
//							_dal  =0;
//							_dah  =0x66;
//							_opc1 =0x71;
//							_pvref=165;
//							Pub_temp=1000;
//							Project_Sequence=111111;					
					
#endif				

//------------------------------		
		
		
		if((sys_Year>2013)&&(sys_Year<2099)&&(sys_Month>0)&&(sys_Month<13))
		{
			memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
			fun_read_page(Mem_back_address);
			me_delay_ms(5);
			BLOOD_Package.bytes[75]=sys_Year-2000;	//年
			BLOOD_Package.bytes[76]=sys_Month;		//月
			BLOOD_Package.bytes[77]=sys_Day;		//日
			BLOOD_Package.bytes[78]=sys_Hour;		//时
			BLOOD_Package.bytes[79]=sys_Minute;		//分
			BLOOD_Package.bytes[80]=sys_Second;		//秒
			if(fun_enable_fwen())
			{
				me_delay_100us();
				fun_erase_page(Mem_back_address);	
				me_delay_100us();
				fun_write_cpage(Mem_back_address,128, 0);//写到永久存储
				me_delay_100us();
			}
		}
		me_delay_ms(5);
		memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
		fun_read_page(Mem_back_address);
		me_delay_ms(5);
		WDR();
		if((BLOOD_Package.bytes[75]>13)&&(BLOOD_Package.bytes[75]<99))
		{
			sys_Year=2000+BLOOD_Package.bytes[75];
			sys_Month=BLOOD_Package.bytes[76];
			sys_Day=BLOOD_Package.bytes[77];
			sys_Hour=BLOOD_Package.bytes[78];
			sys_Minute=BLOOD_Package.bytes[79];
			sys_Second=BLOOD_Package.bytes[80];
		}
		else
		{
			sys_Year=2018;
			sys_Month=10;
			sys_Day=1;
			sys_Hour=9;
			sys_Minute=45;
			sys_Second=15;
		}
		Mem_sequence=BLOOD_Package.bytes[20];
		Mem_sequence<<=8;//存入记忆组数
		Mem_sequence|=BLOOD_Package.bytes[19];
		
		SystemFlags.Datas.Flags.Bits.Mem_sequence_falg=BLOOD_Package.bytes[73];
		memset(BLOOD_Package.bytes,0,10);
		memset(SystemFlags.bytes,0,14);
		memset(disp_buff,0,16);
		SystemFlags.Datas.Flags.Bits.point=1;
		SystemFlags.Datas.Flags.Bits.Send_flag=1;
//		SystemFlags.Datas.Flags.Bits.Mmol_falg=1;//mmol/L
		SystemFlags.Datas.Flags.Bits.Mmol_falg=0;//mg/dl
		SystemFlags.Datas.Flags.Bits.GSM_Open=0;
		SystemFlags.Datas.Flags.Bits.Before=1;
		show_display();

		if(_pa3==0)//开机，进入标定模式
		{
			_dac=1;//DAC电源开
	   		_adoff=0;//AD电源开
			uart_init(0);
			_bgc = 0B00010000; //Bandgap使能为2.0V
			_pvref=120;
			_opc1= 0b00111111;//使能运算放大器模式
			SystemFlags.Datas.Flags.Bits.test_falg=1;
			Blood_Sequence=25663;//这是预设400mV电压值，
			SystemFlags.Datas.uart_reicev_count_set=6;
			Show_PC();
			_pac2=0;//设为串口输出
			_pa2=1;
		}
		else
		{
			SystemFlags.Datas.Flags.Bits.test_falg=0;
			uart_init(1);
			_pac1=1;
			_pa1=1;
		}
		SystemFlags.Datas.Flags.Bits.NO_Temperature=0;
		WDR();
		Buzzer();
		//_pb6=1;
//		SystemFlags.Datas.Flags.Bits.ready=0;
	}
	Gsm_timer=0;
    SystemFlags.Datas.Flags.Bits.Send_begin=0;
	while(1)
	{
		WDR();
		i=0;
		while(SystemFlags.Datas.Flags.Bits.test_falg)//进入标定模式
		{
			WDR();
			reivce_data();
		}
		if(SystemFlags.Datas.Flags.Bits.test_falg==0)//非标定模式
		{
			Get_Charge();
			Key_value=key_scan();
#if Gsm_start_on
			if(SystemFlags.Datas.Flags.Bits.Send_flag == 1)
			{
				if((SystemFlags.Datas.Flags.Bits.GSM_On==1) && (iSec < 1000))
				{
				//	iSec++;
					if(uSecond != sys_Second)
					{
						iSec++;
						uSecond = sys_Second;
					}
				}
			}
#endif
			
			if(SystemFlags.Datas.Flags.Bits.TestKeyboad==0)//如果没有按键按下
			{
				if(Key_value==0xff)//长按 开/关机
				{
					Key_value=0;
					if(SystemFlags.Datas.Flags.Bits.CHRC == 0)
					{
						Power_ON_OFF();
						iSec = 0;
						uart_init(1);
					}
				}
				else 
				{
					if((Key_value==0xf0)&&(SystemFlags.Datas.Flags.Bits.power_on==0))
					{
						Key_value=0;
						Power_ON_OFF();
						SystemFlags.Datas.Flags.Bits.Test_paper=0;
						SystemFlags.Datas.Flags.Bits.Before=1;
						SystemFlags.Datas.Class=5;
						Mem_sequence_count=0;
	                    Show_Big_number(" ",0,0);//显示血糖值mmol
						show_battery();
						show_display();
					}
					else if(Key_value==1)
					{
						if((SystemFlags.Datas.Flags.Bits.power_on)&&(SystemFlags.Datas.Class==6))
						{
							Second=0;
							if(SystemFlags.Datas.CTL_mode==0)
							{
								SystemFlags.Datas.CTL_mode=1;//值控	
								disp_buff[0]|=0b01010000;
								disp_buff[1]|=0b01011001;
								disp_buff[2]|=0b01101000;	
								disp_buff[3]|=0b00010000;	
							}
							else
							{
								SystemFlags.Datas.CTL_mode=0;
								disp_buff[0]&=0b10101111;
								disp_buff[1]&=0b10100110;
								disp_buff[2]&=0b10010111;	
								disp_buff[3]&=0b11101111;		
							}
						}
					}
					else if(Key_value==2)
					{
						if((SystemFlags.Datas.Flags.Bits.power_on)&&(SystemFlags.Datas.Class==6))
						{
							if(SystemFlags.Datas.Flags.Bits.Before)
								SystemFlags.Datas.Flags.Bits.Before = 0;
							else
								SystemFlags.Datas.Flags.Bits.Before = 1;
							
							Show_Big_number(" ", 0, 0);
						}
					}
					else if(Key_value==4)
					{
						Key_value=0;
						Old_Second=10;
						Power_ON_OFF();
					}
				}
			}
			if((_pa4==0)&&(SystemFlags.Datas.Class!=10))
			{
				if(SystemFlags.Datas.Flags.Bits.trigger==0)
				{
					me_delay_ms(50);
					if(_pa4==0)
					{
						if(SystemFlags.Datas.Flags.Bits.Win_task==0)
						{
							SystemFlags.Datas.Flags.Bits.trigger=1;//试纸插入
							SystemFlags.Datas.Flags.Bits.Win_task=1;
							SystemFlags.Datas.Flags.Bits.Show_Memory=0;
							_dac=1;//DAC电源开
   							_adoff=0;//AD电源开
   							_ph0=1;//背光打开
   							OP_set();
   							Buzzer();
   							//GSM_turn_ON();
   							Get_Battery();
   							uart_init(1);//改2020年9月27日09:05:55

   							memset(BLOOD_Package.bytes,0,128);
   							fun_read_page(Mem_back_address);
							_dal  =BLOOD_Package.bytes[12];
							_dah  =BLOOD_Package.bytes[13];
							_pvref=BLOOD_Package.bytes[11];
							_opc1 =BLOOD_Package.bytes[18];	
							
							Project_Sequence =BLOOD_Package.bytes[10];
							Project_Sequence<<=8;
							Project_Sequence|=BLOOD_Package.bytes[9];
							Project_Sequence<<=8;
							Project_Sequence|=BLOOD_Package.bytes[8];
							Project_Sequence<<=8;
							Project_Sequence|=BLOOD_Package.bytes[7];

							productMonth = BLOOD_Package.bytes[5];
							productYear = BLOOD_Package.bytes[6];
							
							Mem_sequence =BLOOD_Package.bytes[20];
							Mem_sequence<<=8;
							Mem_sequence|=BLOOD_Package.bytes[19];
							
							Pub_temp=BLOOD_Package.bytes[72];
							
							Pub_temp<<=8;
							Pub_temp|=BLOOD_Package.bytes[71];
							_lcdc = 0b10000001;
							

							i=0;
							i=BLOOD_Package.bytes[11]^BLOOD_Package.bytes[12]^BLOOD_Package.bytes[13]^BLOOD_Package.bytes[18]^BLOOD_Package.bytes[71]^BLOOD_Package.bytes[72];
							if((i!=BLOOD_Package.bytes[74])||(0==BLOOD_Package.bytes[74]))
							{
								memset(disp_buff,0,16);
								Show_EE();
								WDR();
								me_delay_ms(800);
								WDR();
								goto all_end;	
							}	



							get_lowPwd(3,1);
							if(SystemFlags.Datas.Flags.Bits.power_on==0)
							{
								memset(disp_buff,0xff,16);
								memset(flash,0xff,16);
								show_display();
								WDR();
								me_delay_ms(800);
								WDR();
								memset(disp_buff,0,16);
								show_display();
								Get_Battery();
								
								if(SystemFlags.Datas.Battery_Val==0)//实际情况是低于3.7V关机
								{
									displey_EB();
									me_delay_ms(800);
									WDR();
									Show_OFF();
									me_delay_ms(800);
									WDR();
									goto all_end;		
								}
								
								SystemFlags.Datas.Flags.Bits.uart_reicev_flag=0;
								SystemFlags.Datas.uart_reicev_count=0;
								SystemFlags.Datas.Flags.Bits.Bluetooth=1;
								SystemFlags.Datas.Flags.Bits.Before=1;
								Second=0;
								memset(BLOOD_Package.bytes,0,30);
								
								get_lowPwd(3,1);
								if(AD_value>1010)
								{
									SystemFlags.Datas.Class=8;
								}
							}
							else
							{
								memset(disp_buff,0,16);
								Second=0;
								//Blood_glucose=10;
								get_lowPwd(3,1);
								if(AD_value>1010)
								{
									SystemFlags.Datas.Class=8;
								}
							}
							SystemFlags.Datas.Flags.Bits.power_on=1;

							SystemFlags.Datas.Flags.Bits.Test_paper=0;
							if(AD_value<1010)
							{
								/*while(1)
								{
									staic_Temperature=Get_Temperature();
									Show_Big_number(" ",staic_Temperature,1);
									show_display();
									
									if(_pa4)
									{
										Show_OFF();
										SystemFlags.Datas.Class=0;
										WDR();
										me_delay_ms(800);
										WDR();
										goto all_end;	
									}
									BLOOD_Package.bytes[0]=AD_value/1000%10+0x30;
								 	BLOOD_Package.bytes[1]=AD_value/100%10+0x30;
								 	BLOOD_Package.bytes[2]=AD_value/10%10+0x30;
								 	BLOOD_Package.bytes[3]=AD_value%10+0x30;
								 	BLOOD_Package.bytes[4]=0x0d;
								 	Uart_Send(BLOOD_Package.bytes,5);
								 	WDR();
									me_delay_ms(500);
									WDR();
								}*/
								staic_Temperature=Get_Temperature();//改2020年9月27日12:04:12//陈斌
								//staic_Temperature=35;//改2020年9月27日12:04:12//陈斌
								//Send_data(AD_value>>8);
								//Send_data(AD_value);
								if((staic_Temperature > 40) || (staic_Temperature < 1))
								{
									Show_Et();
									WDR();
									me_delay_ms(800);
									WDR();
									SystemFlags.Datas.Flags.Bits.power_on=0;
									goto all_end;	
								}
								Show_Big_number(" ",staic_Temperature,1);
								show_display();
								WDR();
								
								me_delay_ms(800);
								WDR();
		
								me_delay_ms(800);
								WDR();
#if Gsm_start_on
								SetIoLo(GSM_Power2);
								SetIoLo(GSM_Power1);
								wait_return(1);
								GSM_turn_ON();
								iSec = 0;
								uSecond = sys_Second;

								if(SystemFlags.Datas.Flags.Bits.Send_flag == 1)
									SystemFlags.Datas.Class = 16;
								else
								{
									entry_Blood_drop();
									SystemFlags.Datas.Class=6;
								}
#else
								entry_Blood_drop();
								SystemFlags.Datas.Class=6;
#endif								
							}
						}
					}
				}	
			}
			else
			{
				SystemFlags.Datas.Flags.Bits.trigger=0;//试纸拔出
				memset(disp_buff,0,16);
			}

			if(SystemFlags.Datas.Flags.Bits.power_on)
			{
				switch(SystemFlags.Datas.Class)
				{
					case 1 :
							show_sequence();
							
							if(Key_value==2)//右键
							{
								SystemFlags.Datas.Class=2;	
							//	if(SystemFlags.Datas.Flags.Bits.Send_flag==0)
								{
									Show_OPEN();//激活GSM
									Key_value = 100;
								}
							}
							if(Second>Sleep_time)
							{
								SystemFlags.Datas.Class=0;
								goto all_end;
							}	
							break;
					case 2:
							if(Key_value==1)
							{
								if(SystemFlags.Datas.Flags.Bits.Send_flag == 1)
									SystemFlags.Datas.Flags.Bits.Send_flag = 0;
								else
									SystemFlags.Datas.Flags.Bits.Send_flag = 1;
								displey_YES();
								WDR();
								me_delay_ms(800);
								WDR();
								Key_value=2;
							}
							if(Key_value==2)//右键
							{
								SystemFlags.Datas.Class=3;	
								Key_value = 100;
							}
							if(Second>Sleep_time)
							{
								SystemFlags.Datas.Class=0;
								goto all_end;
							}	
							break;
							
					case 3:
							displey_test();
							if(Key_value==1)
							{
								SystemFlags.Datas.Flags.Bits.NO_Temperature=1;
								displey_YES();
								WDR();
								me_delay_ms(800);
								WDR();
								Key_value=2;
							}
							if(Key_value==2)//右键
							{
								SystemFlags.Datas.Class=4;	
								Key_value = 100;
							}
							if(Second>Sleep_time)
							{
								SystemFlags.Datas.Class=0;
								goto all_end;
							}	
							break;
					case 4:	
					
							displey_DEL();//清空记忆
							if(Key_value==1)
							{
								displey_YES();
								memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
								fun_read_page(Mem_back_address);
								me_delay_ms(5);
								Mem_sequence=0;		//记忆组数清0
								BLOOD_Package.bytes[19]=0;	//存入记忆组数
								BLOOD_Package.bytes[20]=0;//存入记忆组数
								BLOOD_Package.bytes[73]=0;
								if(fun_enable_fwen())
								{
									me_delay_100us();
									fun_erase_page(Mem_back_address);	
									me_delay_100us();
									fun_write_cpage(Mem_back_address,128, 0);//写到永久存储
									me_delay_100us();
								}
								Mem_sequence_falg=0;//重来标记清0
								WDR();
								me_delay_ms(800);
								WDR();
								Key_value=2;
							}
							if(Key_value==2)//右键
							{
								Show_OFF();
								SystemFlags.Datas.Class=0;
								Key_value = 100;
								WDR();
								me_delay_ms(800);
								WDR();
								goto all_end;	
							}
							if(Second>Sleep_time)
							{
								SystemFlags.Datas.Class=0;
								goto all_end;
							}	
							break;
							
					case 5 :
							if(Key_value==1)
							{
								Key_value=0;
								if(Mem_sequence > 0)
								{
									if(Mem_sequence < Max_Mem_sequence)
										b = Mem_sequence;
									else
										b = Max_Mem_sequence;
										
	Mem_sequence_count_loop:		if(Mem_sequence_count < b)
									{
										SystemFlags.Datas.Flags.Bits.Show_Memory=0;
										i=Mem_sequence_count+1;
										Show_Big_number(" ",i,1);
										for(a=0;a<130;a++)
										{
											show_display();
											me_delay_ms(1);
											WDR();
											if(_pa3==0)
											{
												if(a>60)
												{
													break;
												}	
											}	
										}	
										i=Mem_sequence-Mem_sequence_count-1;
										Mem_sequence_count++;
										Pub_temp=Mem_sequence_count;

										if(_pa3==0)
										{
											goto Mem_sequence_count_loop;	
										}
										SystemFlags.Datas.Flags.Bits.Show_Memory=1;
										Blood_glucose=Get_Memroy(i);
										Show_Big_number(" ",0,4);
										show_battery();
										show_display();
									}
									else//如果不考虑衔接问题，则这程序足已,不需要if
									{
										Show_END();
										WDR();
										me_delay_ms(800);
										WDR();
										Show_OFF();
										WDR();
										me_delay_ms(800);
										WDR();
										Mem_sequence_count=0;
										SystemFlags.Datas.Class=0;
										SystemFlags.Datas.Flags.Bits.power_on=0;
									}
								}
								else
								{
									Show_000();
									WDR();
									me_delay_ms(800);
									WDR();
									Mem_sequence_count=0;
									SystemFlags.Datas.Class=0;
									SystemFlags.Datas.Flags.Bits.power_on=0;
								}
							}
							if(Second>Sleep_time)
							{
								SystemFlags.Datas.Class=0;
								goto all_end;
							}	
							break;
					case 6 :
							if(strstr(&BLOOD_Package.bytes,"APP RDY"))
							{
								SystemFlags.Datas.Flags.Bits.Call_Ready=1;
								
								disp_buff[0]|=0b10000000;//天线符
								disp_buff[4]|=0b00000000;//信号第一格
								disp_buff[5]|=0b00000000;//信号第二、三、四格
								//SystemFlags.Datas.GSM_Signal=31;
							}
							else
							{
								SystemFlags.Datas.Flags.Bits.Call_Ready=0;	
							}

							Update_time();
							show_battery();
							show_display();
							SystemFlags.Datas.Flags.Bits.Test_paper=0;
							SystemFlags.Datas.Flags.Bits.Blood_drop=1;
							
							if(Second>Sleep_time)
							{
								Gsm_power_off(0);
								SystemFlags.Datas.Class=0;
								goto all_end;
							}
							if(_pa4)
							{
								SystemFlags.Datas.Flags.Bits.trigger=0;//试纸拔出
								SystemFlags.Datas.Flags.Bits.Send_flag = 1;
								Show_OFF();
								WDR();
								me_delay_ms(800);
								WDR();
								#if Gsm_start_on
									Gsm_power_off(0);
								#endif
								goto all_end;
							}
							else
							{
								get_lowPwd(3,1);
								if(AD_value>1010)
								{
									AD_value=0;
									me_delay_ms(10);

									get_lowPwd(3,1);
									if(AD_value>1010)//大于1uA启动
									{
										SystemFlags.Datas.Flags.Bits.May_reicev_uart=1;
										_adcr1 = 0B00000100;
										SystemFlags.Datas.Flags.Bits.Blood_drop=0;
										Buzzer();
										i=0;
										Old_Second=0;
										Second=0;
										sys_time=0;
										while(1)
										{
											a=5-Old_Second;
											memset(disp_buff,0,16);
											Show_Big_number(" ",a,1);
											wait_return(1);
											WDR();
											i++;
											if(i==5)
											{
												i=0;
												Old_Second++;
											}
											if(Old_Second==5)
											{
												SystemFlags.Datas.Flags.Bits.ready=1;
												flash[14]=0b11111110;//号时钟:号闪烁
												Show_Big_number(" ",0,1);
												show_display();
												WDR();
												me_delay_ms(803);
												WDR();
												get_lowPwd(3,1);//读血糖//采样时间变成了200mS,不对
												//_pb6=~_pb6;
												if(SystemFlags.Datas.Flags.Bits.NO_Temperature==0)
												{
													transformation();//是温补及值控处理
												}
												Show_Big_number(" ",0,3);//显示血糖值mmol	
												show_display();
												//if((SystemFlags.Datas.CTL_mode==0)&&(SystemFlags.Datas.Flags.Bits.Send_flag==1)&&(SystemFlags.Datas.Flags.Bits.NO_Temperature==0))
												if((SystemFlags.Datas.CTL_mode==0)&&(SystemFlags.Datas.Flags.Bits.Send_flag==1))
												{
													Show_Big_number(" ",0,3);//显示血糖值mmol	
												#if Gsm_start_on
												#else
													SetIoLo(GSM_Power2);
													SetIoLo(GSM_Power1);
													wait_return(1);
													GSM_turn_ON();
													WDR();
													me_delay_ms(800);
													WDR();
												#endif
													
													SystemFlags.Datas.Class=7;
													SystemFlags.Datas.Flags.Bits.NO_Temperature=0;
													SystemFlags.Datas.Flags.Bits.Memory_Send=1;
													SystemFlags.Datas.Flags.Bits.GSM_Send_over=1;//传送结束
												}
												else
												{
													SystemFlags.Datas.Class=9;
													SystemFlags.Datas.Flags.Bits.NO_Temperature=0;
												}
												break;
											}
											if(_pa4)
											{
												Show_EF();
												WDR();
												me_delay_ms(800);
												WDR();
												Show_OFF();
												WDR();
												me_delay_ms(800);
												WDR();
												SystemFlags.Datas.Flags.Bits.trigger=0;//试纸拔出
												SystemFlags.Datas.Flags.Bits.Send_flag = 1;
												#if Gsm_start_on
													Gsm_power_off(0);
												#endif
												goto all_end;
											}
										}	
									}
								}
							}
							break;
					case 7 :
							memset(BLOOD_Package.bytes,0,128);
							SystemFlags.Datas.GSM_Signal = 10;//强行给个初值改2020年9月29日08:40:10
							Show_Big_number(" ",0,3);
							show_display();
							//Get_Memroy(Mem_sequence);//先把整页存储读到缓冲区
							
							if(SystemFlags.Datas.CTL_mode==0)
							{
								Mem_sequence++;//记忆组数增加1组
								if(Mem_sequence>Max_Mem_sequence)//如果已经存满最大记忆组数
								{
									//Mem_sequence=1;	//则重新第1组开始存
									SystemFlags.Datas.Flags.Bits.Mem_sequence_falg=1;
								}
								
								if(Mem_sequence > Max_sequence)//如果所有数据被覆盖
								{
									Mem_sequence = Max_Mem_sequence + 1;	//存满状况下，从头开始覆盖存
								}
								Put_Memroy(Mem_sequence-1);//然后把当次血糖测量值以及日期时间储存到flash.
								WDR();
								me_delay_ms(800);
								WDR();
								me_delay_ms(800);
								WDR();
								me_delay_ms(800);
								WDR();
								me_delay_ms(800);
								WDR();
								me_delay_ms(800);
								//因为NB模块的原因最后会发个0D,0A这两个数据可能会在读取Mem_back_address后发来，
								//会重置BLOOD_Package.bytes[0]=0x0D,BLOOD_Package.bytes[1]=0x0A;
								//会造成读取错误，最后导致存储错误，所以，这里要延长一些时间，或者重新读取数据覆盖一次。
								memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));		
								fun_read_page(Mem_back_address);
								BLOOD_Package.bytes[19]=Mem_sequence;	
								BLOOD_Package.bytes[20]=Mem_sequence>>8;
								BLOOD_Package.bytes[73]=SystemFlags.Datas.Flags.Bits.Mem_sequence_falg;
								BLOOD_Package.bytes[75]=sys_Year-2000;	//年
								BLOOD_Package.bytes[76]=sys_Month;		//月
								BLOOD_Package.bytes[77]=sys_Day;		//日
								BLOOD_Package.bytes[78]=sys_Hour;		//时
								BLOOD_Package.bytes[79]=sys_Minute;		//分
								if(fun_enable_fwen())
								{
									me_delay_100us();
									fun_erase_page(Mem_back_address);	
									me_delay_100us();
									fun_write_cpage(Mem_back_address,128, 0);//写到永久存储
									me_delay_100us();
								}
								WDR();
								me_delay_ms(800);
								WDR();
								fun_read_page(Mem_back_address);
							}
							SystemFlags.Datas.Flags.Bits.May_reicev_uart=0;
							SystemFlags.Datas.Flags.Bits.uart_reicev_flag=0;
							SystemFlags.Datas.uart_reicev_count=0;
							if((SystemFlags.Datas.CTL_mode==0)&&(SystemFlags.Datas.Flags.Bits.Send_flag==1))
							{
								Gsm_timer=0;
								SystemFlags.Datas.Flags.Bits.Send_begin=1;
	//							if(SystemFlags.Datas.Flags.Bits.ready)
								{
									i=Send_GSM2(0,0);//发送当次
	//								SystemFlags.Datas.Flags.Bits.ready   = 0;
								}
								
								if(i)
								{
									SystemFlags.Datas.Flags.Bits.GSM_Send_OK=0;//传送失败						
									Store_Failure_buff();
								}
								else
								{
									SystemFlags.Datas.Flags.Bits.GSM_Send_OK=1;//传送成功
								}
							}
							

						
							
							
							SystemFlags.Datas.Flags.Bits.Memory_Send=0;
							Show_Big_number(" ",0,3);//显示血糖值mmol
							show_display();;//显示血糖值mmol
							
							if(SystemFlags.Datas.Flags.Bits.GSM_Send_OK)
							{
								Send_Failure_buff();
							}

							
							
				uart_tx_string("AT+QIDEACT=1\r\n");
				wait_return(2); 
			//	if(strstr(BLOOD_Package.bytes,"OK"))
				{
					uart_tx_string("AT+QPOWD\r\n");
					WDR();
					me_delay_ms(4000);
					WDR();
					
				}							
							
				Gsm_power_off(0);							
							
							SystemFlags.Datas.Class=9;
							Show_Big_number(" ",0,3);//显示血糖值mmol
							show_display();
							Gsm_timer=56;
							break;
					case 8 :
							displey_EU();//试纸过期
							WDR();
							me_delay_ms(800);
							WDR();
							Show_OFF();
							WDR();
							me_delay_ms(800);
							WDR();
							SystemFlags.Datas.Flags.Bits.power_on=0;
							goto all_end;
							break;
					case 9 :
							Show_Big_number(" ",0,3);//显示血糖值mmol	
							show_display();
							WDR();
							me_delay_ms(500);
							WDR();
							me_delay_ms(500);
							WDR();
							me_delay_ms(500);
							WDR();
							me_delay_ms(500);//网络通信成功或失败，这里加一个延时方便看清。
							if(_pa4)
							{
								SystemFlags.Datas.Flags.Bits.trigger=0;//试纸拔出
								SystemFlags.Datas.Flags.Bits.Send_flag = 1;
								Show_OFF();
								WDR();
								me_delay_ms(800);
								WDR();
							//	Gsm_power_off(0);
								goto all_end;
							}
							if(Second>Sleep_time)
							{
								Gsm_power_off(0);
								SystemFlags.Datas.Class=0;
								goto all_end;
							}
							break;
					case 10 :
							{
								_lcdc = 0b10000001;
								show_battery();	
								show_display();
								if(SystemFlags.Datas.Flags.Bits.CHRC==0)
								{
									Show_OFF();
									WDR();
									me_delay_ms(800);
									WDR();
									memset(disp_buff,0,16);
									goto all_end;
								}
								if(Second>Sleep_time)
								{
									Show_OFF();
									WDR();
									me_delay_ms(800);
									WDR();
									memset(disp_buff,0,16);
									SystemFlags.Datas.Class=0;
									goto all_end;
								}
							}
							break;
					default:break;	
				} 
				me_delay_ms(10);
			}
			else
			{
				if(SystemFlags.Datas.Class==8)
				{
					if(SystemFlags.Datas.Flags.Bits.CHRC==0)
					{
						SystemFlags.Datas.Class=0;	
					}
				}
				else
				{
all_end:			Second=0;
					exit();
					_ph0=0;//背光关掉
					SysSleep();
				}
			}
		}
	}
}
