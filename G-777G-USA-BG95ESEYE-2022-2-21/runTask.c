#include "HT45F67.h"
#include "Defineport.h"
#include "DELAY.h"
#include "UART.h"
#include "iap.h"
#include "runTask.h"
#include "AD.h"
#include "string.h"
#include "LCD.h"
#include "uart.h"

typedef struct tagSoundGroup
{	
	ushort count;			//读取到的温度AD值	
	uchar  Temperature;	    //温示温度值
	uchar  Indexs[2];		//Indexs[0]为血糖温度补偿系数；Indexs[1]为质控温度补偿系数  
}TSoundGroup;
const TSoundGroup SoundGroups[] =
{
	//这是3.0V LDO
	{ 2308,50, {121, 124} },  //负1度
	{ 2210, 0, {120, 123} },  //
	{ 2128, 1, {119, 122} },  //
	{ 2073, 2, {118, 121} },  // 
	{ 2013, 3, {117, 120} },  // 
	{ 1956, 4, {116, 119} },  //
	{ 1910, 5, {115, 118} },  //
	{ 1846, 6, {114, 117} },  // 
	{ 1792, 7, {113, 116} },  // 
	{ 1739, 8, {112, 115} },  //
	{ 1691, 9, {112, 115} },  //
	{ 1648,10, {111, 114} },  // 
	{ 1598,11, {110, 114} },  // 
	{ 1547,12, {108, 113} },  //
	{ 1497,13, {107, 112} },  //
	{ 1451,14, {106, 110} },  // 
	{ 1410,15, {106, 109} },  // 
	{ 1371,16, {105, 108} },  //
	{ 1332,17, {105, 105} },  //
	{ 1294,18, {104, 102} },  // 
	{ 1249,19, {103, 101} },  // 
	{ 1210,20, {103, 100} },  //
	{ 1169,21, {102, 100} },  //
	{ 1138,22, {102, 100} },  //
	{ 1108,23, {101, 100} },  // 
	{ 1074,24, {100, 100} },  // 
	{ 1040,25, {100, 100} },  // 
	{ 1003,26, {100,  98} },  //
	{ 974,27, {100,  97} },  //
	{ 948,28, {100,  95} },  //
	{ 918,29, {100,  94} },  //
	{ 890,30, {100,  92} },  // 
	{  863,31, {100,  90} },  //
	{  837,32, {100,  89} },  //
	{  813,33, {100,  87} },  // 
	{  787,34, {100,  86} },  // 
	{  763,35, {100,  84} },  //
	{  738,36, {100,  83} },  // 
	{  717,37, {100,  82} },  //
	{  698,38, {100,  81} },  //
	{  676,39, {100,  79} },  // 
	{  652,40, {100,  78} },  // 
	{  632,41, {100,  77} },  //
	/*{ 2545,50, {121, 124} },  //负1度
	{ 2477, 0, {120, 123} },  //
	{ 2410, 1, {119, 122} },  //
	{ 2344, 2, {118, 121} },  // 
	{ 2279, 3, {117, 120} },  // 
	{ 2216, 4, {116, 119} },  //
	{ 2154, 5, {115, 118} },  //
	{ 2093, 6, {114, 117} },  // 
	{ 2034, 7, {113, 116} },  // 
	{ 1976, 8, {112, 115} },  //
	{ 1919, 9, {112, 115} },  //
	{ 1863,10, {111, 114} },  // 
	{ 1809,11, {110, 114} },  // 
	{ 1756,12, {108, 113} },  //
	{ 1704,13, {107, 112} },  //
	{ 1654,14, {106, 110} },  // 
	{ 1604,15, {106, 109} },  // 
	{ 1546,16, {105, 108} },  //
	{ 1510,17, {105, 105} },  //
	{ 1464,18, {104, 102} },  // 
	{ 1425,19, {103, 101} },  // 
	{ 1377,20, {103, 100} },  //
	{ 1336,21, {102, 100} },  //
	{ 1295,22, {102, 100} },  //
	{ 1256,23, {101, 100} },  // 
	{ 1217,24, {100, 100} },  // 
	{ 1180,25, {100, 100} },  // 
	{ 1144,26, {100,  98} },  //
	{ 1109,27, {100,  97} },  //
	{ 1075,28, {100,  95} },  //
	{ 1042,29, {100,  94} },  //
	{ 1010,30, {100,  92} },  // 
	{  979,31, {100,  90} },  //
	{  949,32, {100,  89} },  //
	{  920,33, {100,  87} },  // 
	{  892,34, {100,  86} },  // 
	{  864,35, {100,  84} },  //
	{  838,36, {100,  83} },  // 
	{  812,37, {100,  82} },  //
	{  797,38, {100,  81} },  //
	{  763,39, {100,  79} },  // 
	{  740,40, {100,  78} },  // 
	{  718,41, {100,  77} },  //*/
};
const uchar data_time1[]={31,31,29,31,30,31,30,31,31,30,31,30,31};
const uchar data_time2[]={31,31,28,31,30,31,30,31,31,30,31,30,31};

uchar Get_Temperature()
{
	uchar i;
	get_lowPwd(1,0);

	for(i=0;i<43;i++)
	{
		if(AD_value>SoundGroups[i].count)
		{
			Temperature_coefficient    =SoundGroups[i].Indexs[0];
			Temperature_CTL_coefficient=SoundGroups[i].Indexs[1];
			return 	SoundGroups[i].Temperature;
		}
	}
	return 0xff;
}

void Get_Battery()
{
	get_lowPwd(2,0);
	if(AD_value<3750)//低于3.8V，显E-B
	{
		SystemFlags.Datas.Battery_Val=0;
		SystemFlags.Datas.Flags.Bits.Battery_LO=0;	
	}
	if(AD_value>3751)//大于3.8V，1格
	{
		SystemFlags.Datas.Battery_Val=1;
		SystemFlags.Datas.Flags.Bits.Battery_LO=1;	
	}
	if(AD_value>3850)//大于3.9V，2格
	{
		SystemFlags.Datas.Battery_Val=2;
	}
	if(AD_value>4050)////大于4.0V，电池满格
	{
		SystemFlags.Datas.Battery_Val=3;
	}
}
void Get_Charge()//充电
{
	if((_ph1==0)||(_ph6==0))
	{
		if(_ph1==0)
		{
			SystemFlags.Datas.Flags.Bits.CHRC=1;
			SystemFlags.Datas.Flags.Bits.Battery_LO=0;	
			if(SystemFlags.Datas.Class==0)
			{
				SystemFlags.Datas.Flags.Bits.power_on=1;
				SystemFlags.Datas.Class=10;
			}
		}
		if(_ph6==0)
		{
			SystemFlags.Datas.Flags.Bits.CHRC=0;
			SystemFlags.Datas.Flags.Bits.Battery_LO=0;
		}
	}
	else
	{
		SystemFlags.Datas.Flags.Bits.CHRC=0;
	}	
}
void Buzzer()
{
	ushort i;
	for(i=0;i<200;i++)
	{
		_pb6=~_pb6;	
		me_delay_100us();
		me_delay_100us();
	}
	_pb6=1;	
}
void GSM_turn_ON()
{
	/*	SetIoHi(GSM_Power1);
	wait_return(5);
	SetIoHi(GSM_Power2);
	wait_return(5);
	SetIoLo(GSM_Power2);
	wait_return(20);
	uart_init();
	*/
	int i;
	SetIoHi(GSM_Power1);
	me_delay_ms(150);
	
	SetIoLo(GSM_Power2);
	me_delay_ms(10);
	SetIoHi(GSM_Power2);//SetIoHi(GSM_Power2);
	me_delay_ms(600);
	SetIoLo(GSM_Power2);
	me_delay_ms(10);

	uart_init(1);//切换成19200和NB-IOT通信

	WDR();
	me_delay_ms(100);
}

void Put_Memroy(ushort adr)
{
	ushort i;//求出当前记忆笔数位于flash第几页
	ushort i2;//求出当页里第几组
#if 0	
	i=adr*8/128;
	i2=(adr*8)-(i*128);
	fun_read_page(i*Mem_address_page+Mem_start_address);
	//me_delay_100us();
	me_delay_ms(1);
	BLOOD_Package.bytes[i2]  =sys_Year-2000;
	BLOOD_Package.bytes[i2+1]=sys_Month;
	BLOOD_Package.bytes[i2+2]=sys_Day;
	BLOOD_Package.bytes[i2+3]=sys_Hour;
	BLOOD_Package.bytes[i2+4]=sys_Minute;
	BLOOD_Package.bytes[i2+5]=sys_Second;
	BLOOD_Package.bytes[i2+6]=Blood_glucose>>8;
	BLOOD_Package.bytes[i2+7]=Blood_glucose;
#else
	uchar iOne, iTwo, iTemp, iPosNum, iPosition;
	ushort ipos;
	
	ipos = adr % Max_Mem_sequence;
	
	i = ipos / Mem_page_num;
	iTemp = ipos % Mem_page_num;
	iPosNum = iTemp / 8;
	iPosition = iTemp % 8;
	i2 = iTemp * Mem_log_length;
	
	fun_read_page(i * Mem_address_page + Mem_start_address);
	me_delay_ms(1);
	
	if(SystemFlags.Datas.Flags.Bits.Before > 0)
	{
		BLOOD_Package.bytes[125 + iPosNum] |= 0b00000001 << (8 - iPosition - 1);
	}
	else
	{
		if(iPosition == 0)
			BLOOD_Package.bytes[125 + iPosNum] &= 0b01111111;
		else 
			BLOOD_Package.bytes[125 + iPosNum] &= (char)0b10111111 >> (iPosition - 1);
	}
		
	if(sys_Year < 2016)
		iTwo = 0;
	else if(sys_Year > 2031)
		iTwo = 15;
	else
		iTwo = sys_Year - 2016;
	BLOOD_Package.bytes[i2] = iTwo << 4;
	
	if(sys_Month > 12)
		iOne = 12;
	else if(sys_Month < 1)
		iOne = 1;
	else
		iOne = sys_Month;
	BLOOD_Package.bytes[i2] = 	BLOOD_Package.bytes[i2] + iOne;
		
	if(sys_Day < 1)
		iTwo = 1;
	else if(sys_Day > 31)
		iTwo = 31;
	else
		iTwo = sys_Day;
	BLOOD_Package.bytes[i2 + 1] = iTwo << 3;
	
	if(sys_Hour > 23)
		iOne = 23;
	else if(sys_Hour < 0)
		iOne = 0;
	else
		iOne = sys_Hour;
	iTemp = iOne << 3;
	iTemp = iTemp >> 5;
	BLOOD_Package.bytes[i2 + 1] = BLOOD_Package.bytes[i2 + 1] + iTemp;
	
	iTemp = iOne << 6;
	BLOOD_Package.bytes[i2 + 2] = iTemp;
	if(sys_Minute < 0)
		iTwo = 0;
	else if(sys_Minute > 59)
		iTwo = 59;
	else
		iTwo = sys_Minute;
	BLOOD_Package.bytes[i2 + 2] = BLOOD_Package.bytes[i2 + 2] + iTwo;
	
	if(sys_Second < 0)
		iOne = 0;
	else if(sys_Second > 59)
		iOne = 59;
	else
		iOne = sys_Second;
	iTemp = iOne << 2;
	BLOOD_Package.bytes[i2 + 3] = iTemp;
	
	iOne = Blood_glucose>>8;
	iTwo = Blood_glucose;
	iTemp = iOne << 6;
	iTemp = iTemp >> 6;
	BLOOD_Package.bytes[i2 + 3] = BLOOD_Package.bytes[i2 + 3] + iTemp;
	BLOOD_Package.bytes[i2 + 4] = iTwo;
	
#endif	
	
	if(fun_enable_fwen())
	{
		me_delay_100us();
		fun_erase_page(i*Mem_address_page+Mem_start_address);	
		me_delay_100us();
		fun_write_cpage(i*Mem_address_page+Mem_start_address,128,0);
		me_delay_100us();
	}
}
ushort Get_Memroy(ushort adr)
{
#if 0
	ushort i;//求出当前记忆笔数位于flash第几页
	ushort i2;//求出当页里第几组
	uchar a;
	i=adr*8/128;
	i2=(adr*8)-(i*128);
	memset(BLOOD_Package.bytes,0,128);
	fun_read_page(i*Mem_address_page+Mem_start_address);
	i=BLOOD_Package.bytes[i2+6];
	i<<=8;	
	i|=BLOOD_Package.bytes[i2+7];
	for(a=0;a<8;a++)
	{
		test_buff[a]=BLOOD_Package.bytes[i2+a];
	}
	return i;
#else
	ushort i;//求出当前记忆笔数位于flash第几页
	ushort i2;//求出当页里第几组
	uchar iOne, iTwo, iTemp, iPosNum, iPosition, iBef;
	ushort ipos;
	
	ipos = adr % Max_Mem_sequence;
	
	i = ipos / Mem_page_num;
	iTemp = ipos % Mem_page_num;
	i2 = iTemp * Mem_log_length;

	iPosNum = iTemp / 8;
	iPosition = iTemp % 8;

	memset(BLOOD_Package.bytes, 0, 128);
	fun_read_page(i * Mem_address_page + Mem_start_address);
	if(iPosition == 0)
		iBef = BLOOD_Package.bytes[125 + iPosNum] & 0b10000000;
	else
		iBef = BLOOD_Package.bytes[125 + iPosNum] & ((char)0b01000000 >> (iPosition - 1));

	if(iBef > 0)
		SystemFlags.Datas.Flags.Bits.Before = 1;
	else
		SystemFlags.Datas.Flags.Bits.Before = 0;
	
	iOne = BLOOD_Package.bytes[i2 + 0];
	iTemp = iOne >> 4;
	test_buff[0] = iTemp;//年
	iTemp = iOne << 4;
	iTemp = iTemp >> 4;
	test_buff[1] = iTemp;//月

	iOne = BLOOD_Package.bytes[i2 + 1];
	iTwo = BLOOD_Package.bytes[i2 + 2];
	iTemp = iOne >> 3;
	test_buff[2] = iTemp;//日

	iTemp = iOne << 5;
	iTemp = iTemp >> 3;
	test_buff[3] = iTemp;//时 前3位
	iTemp = iTwo >> 6;
	test_buff[3] = test_buff[3] + iTemp;//时

	iTemp = iTwo << 2;
	iTemp = iTemp >> 2;
	test_buff[4] = iTemp;//分
	
	iOne = BLOOD_Package.bytes[i2 + 3];
	iTwo = BLOOD_Package.bytes[i2 + 4];
	iTemp = iOne >> 2;
	test_buff[5] = iTemp;//秒
	
	iTemp = iOne << 6;
	iTemp = iTemp >> 6;
	test_buff[6] = iTemp;//测量值百位
	test_buff[7] = iTwo;//测量值个位十位

	//计算测量值
	i = test_buff[6];
	i <<= 8;	
	i |= test_buff[7];

	return i;
#endif
}

uchar Gsm_power_off(uchar type)
{
	uchar uAtReturn = 0;
#if 0	
//	if((SystemFlags.Datas.Flags.Bits.GSM_Open == 1) || (SystemFlags.Datas.Flags.Bits.GSM_On == 1))
	{
		memset(&BLOOD_Package.bytes,0,128);
//		if(TTS_task(E_COMMAND_AT) == 0)
		{
			me_delay_ms(5);
//			if(TTS_task(E_COMMAND_AT_CPAS) == 0)
			{
//				me_delay_ms(5);
				if(type == 1)
				{
					if(TTS_task(E_COMMAND_AT_QPOWD_1) == 0)
						uAtReturn = 0;
				}
				else
				{
					if(TTS_task(E_COMMAND_AT_QPOWD_0) == 0)
						uAtReturn = 0;
				}
			}
		}
	}
#endif	
	SetIoLo(GSM_Power2);
	SetIoLo(GSM_Power1);

	return uAtReturn;
}


void Gsm_power_reset(void)
{
	uchar i;
	WDR();
	wait_return(3);
	WDR();

	SetIoLo(GSM_Power2);
	SetIoLo(GSM_Power1);
	wait_return(1);
	GSM_turn_ON();
	
	for(i = 0; i < 13; i++)
	{
		wait_return(2);
		WDR();
	}
	uart_init(1);
}

#if 0
uchar Check_GSM_ready()
{
	uchar i=2;
	SystemFlags.Datas.Error_Loop_Count=0;
	
	return 0;
kl1:
	while(SystemFlags.Datas.Error_Loop_Count<5)
	{
		if(GSM_task(6,11)==0)
		{
			SystemFlags.Datas.Error_Loop_Count=0;
			goto kl2;
		}
		SystemFlags.Datas.Error_Loop_Count++;
		goto kl1;
kl2:	if(GSM_task(12,11)==0)
		{
			SystemFlags.Datas.Error_Loop_Count=0;
			return 0;
		}
		SystemFlags.Datas.Error_Loop_Count++;
	}
	return 1;	
}
#endif

void Store_Failure_buff()
{
	uchar i;
	ushort Failure_buff[10];
	ushort Failure_temp = 0;
	
	memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
	fun_read_page(Mem_back_address);

	for(i=0;i<10;i++)
	{
		Failure_buff[i]=BLOOD_Package.bytes[Failure_buff_start_address+i*2+1];//先把失败的数据位置高位找出	
		Failure_buff[i]<<=8;
		Failure_buff[i]|=BLOOD_Package.bytes[Failure_buff_start_address+i*2];//先把失败的数据位置低位找出
	}
	for(i=0;i<10;i++)//然后从高到低，逐笔查看哪里有空位
	{
		if(Failure_buff[i]==0)//找到了空位
		{
			break;
		}
	}
	BLOOD_Package.bytes[Failure_buff_start_address+i*2]=Mem_sequence;	//存入记忆组数
	BLOOD_Package.bytes[Failure_buff_start_address+i*2+1]=Mem_sequence>>8;//存入记忆组数

	if(fun_enable_fwen())
	{
		me_delay_100us();
		fun_erase_page(Mem_back_address);	
		me_delay_100us();
		fun_write_cpage(Mem_back_address,128,0);//写到永久存储
		me_delay_100us();
	}	
}
void Send_Failure_buff()
{
	uchar i, iNum;
	ushort Failure_buff[10];
	memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
	fun_read_page(Mem_back_address);
	for(i=0;i<10;i++)
	{
		Failure_buff[i]=BLOOD_Package.bytes[Failure_buff_start_address+i*2+1];//先把失败的数据位置高位找出	
		Failure_buff[i]<<=8;
		Failure_buff[i]|=BLOOD_Package.bytes[Failure_buff_start_address+i*2];//先把失败的数据位置低位找出
	}
	iNum = 0;
	for(i=10;i>0;i--)//然后逐笔查看哪些没发送
	{
		if(Failure_buff[i-1] > 0)//找到没发送的笔数
		{
			if(iNum < 3)
			{
				if(Send_GSM2(Failure_buff[i-1],1)==0)//如果本次发送成功了
				{
					Failure_buff[i-1]=0;	//则把所在的位置清掉	
				}
				iNum++;
			}
		}
	}
	WDR();
	me_delay_ms(800);
	WDR();
	memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
	fun_read_page(Mem_back_address);
	for(i=0;i<10;i++)
	{
		if(Failure_buff[i] == 0)
		{
			BLOOD_Package.bytes[Failure_buff_start_address+i*2+1]=0;
			BLOOD_Package.bytes[Failure_buff_start_address+i*2]=0;
		}
	}
	me_delay_ms(5);
	if(fun_enable_fwen())
	{
		me_delay_100us();
		fun_erase_page(Mem_back_address);	
		me_delay_100us();
		fun_write_cpage(Mem_back_address,128,0);//写到永久存储
		me_delay_100us();
	}
}
void SysSleep()
{
	_lcdc = 0;
	uart_close();
	_opc1=0;
	_halt();
}

void reivce_data()
{
	uchar i;
	float a,b,c;
	Uart_Receice_9600(BLOOD_Package.bytes,SystemFlags.Datas.uart_reicev_count_set);
	if(BLOOD_Package.bytes[2])//当收到治具发来的命令且校验正确
	{
		switch(BLOOD_Package.bytes[2])
		{
			case 1: 
				Pub_temp=BLOOD_Package.bytes[4]*255+BLOOD_Package.bytes[5];//调校2V电压
				if(Pub_temp>0)
				{
					if(BLOOD_Package.bytes[3]==0x02)
					{
						if(_pvref>1)
						{
							_pvref-=1;//值越大，电压越低
						}
					}
					else if(BLOOD_Package.bytes[3]==0x01)
					{
						if(_pvref<250)
						{
							_pvref+=1;//值越大，电压越低
						}
					}
					break;	
				}
				else//调校2V电压完成
				{
					BLOOD_Package.bytes[0]=0x55;
					BLOOD_Package.bytes[1]=0x05;
					BLOOD_Package.bytes[2]=0x01;
					BLOOD_Package.bytes[3]=0x4f;//O
					BLOOD_Package.bytes[4]=0x4b;//K
					Uart_Send_9600(BLOOD_Package.bytes,5);
					Uart_Send_9600(BLOOD_Package.bytes,5);
				}
				break;
			case 2:	
				Pub_temp=BLOOD_Package.bytes[4]*255+BLOOD_Package.bytes[5];//调校0.4V电压
				if(Pub_temp>0)
				{
					if(BLOOD_Package.bytes[3]==0x02)
					{
						if(Blood_Sequence<65471)
						{
							Blood_Sequence+=64;
							_dal=Blood_Sequence;
							_dah=Blood_Sequence>>8;//值越大，电压越高
						}
					}
					else if(BLOOD_Package.bytes[3]==0x01)
					{
						if(Blood_Sequence>64)
						{
							Blood_Sequence-=64;
							_dal=Blood_Sequence;
							_dah=Blood_Sequence>>8;//值越大，电压越高
						}
					}
				}
				else//调校0.4V电压完成
				{
					Blood_Sequence+=64;
					_dal=Blood_Sequence;
					_dah=Blood_Sequence>>8;//值越大，电压越高
					Blood_Sequence=0;//血糖序列号清零
					BLOOD_Package.bytes[0]=0x55;
					BLOOD_Package.bytes[1]=0x05;
					BLOOD_Package.bytes[2]=0x02;
					BLOOD_Package.bytes[3]=0x4f;//O
					BLOOD_Package.bytes[4]=0x4b;//K
					Uart_Send_9600(BLOOD_Package.bytes,5);
					Uart_Send_9600(BLOOD_Package.bytes,5);
					SystemFlags.Datas.uart_reicev_count_set=3;
					memset(BLOOD_Package.bytes,0,20);
					AD_set();
					_acs2=1;
					_acs1=0;
					_acs0=0;
					_tsc=1;
					_pbc1=1;
					_pb1=1;
					_pbpu1=0;
					me_delay_ms(10);
					AD_value=0;
				}
				break;
			case 3:
				test_OP();
				if(AD_value>820)
				{
					if(_opc1<0b00111111)
					{
						_opc1+=1;	
					}
				}                                                                                      
				if(AD_value<820)
				{
					if(_opc1>0b00100000)
					{
						_opc1-=1;	
					}
				}
				test_OP();
				BLOOD_Package.bytes[0]=0x55;
				BLOOD_Package.bytes[1]=0x07;
				BLOOD_Package.bytes[2]=0x03;
				BLOOD_Package.bytes[4]=AD_value;
				BLOOD_Package.bytes[3]=AD_value>>8;
				//BLOOD_Package.bytes[4]=0x34;
				//BLOOD_Package.bytes[3]=3;
				BLOOD_Package.bytes[5]=0x4f;//O
				BLOOD_Package.bytes[6]=0x4b;//K    
				Uart_Send_9600(BLOOD_Package.bytes,7);
				Uart_Send_9600(BLOOD_Package.bytes,7);
				SystemFlags.Datas.uart_reicev_count_set=3;
				break;
			case 4:
				get_lowPwd(3,0);
				get_lowPwd(3,0);
				a=1832;
				b=AD_value;
				if(a!=b)
				{
					c=a/b;	
				}
				else
				{
					c=1;	
				}
				c*=10000;
				Pub_temp=c;
				i=Pub_temp%10;
				if(i>4)
				{
					Pub_temp+=10;	
				}
				Pub_temp/=10;
				get_lowPwd(3,1);
				get_lowPwd(3,1);
				BLOOD_Package.bytes[0]=0x55;
				BLOOD_Package.bytes[1]=0x07;
				BLOOD_Package.bytes[2]=0x04;
				BLOOD_Package.bytes[4]=AD_value;
				BLOOD_Package.bytes[3]=AD_value>>8;
				BLOOD_Package.bytes[5]=0x4f;//O
				BLOOD_Package.bytes[6]=0x4b;//K	
				Uart_Send_9600(BLOOD_Package.bytes,7);
				if((AD_value>1829)&&(AD_value<1839))
				{
					SystemFlags.Datas.uart_reicev_count_set=3;
					uart_init(1);
					SetIoHi(GSM_Power1);
					SetIoHi(GSM_Power2);
					WDR();
					me_delay_ms(800);
					WDR();
					me_delay_ms(800);
					WDR();
					me_delay_ms(400);
					WDR();
				}
				break;	
			case 5:	
				//i=GSM_task(8,0);
				//if(i==0)
				{
					//i=GSM_task(8,0);
				//	if(i==0)
					{
						BLOOD_Package.bytes[0]=0x55;
						BLOOD_Package.bytes[1]=0x06;
						BLOOD_Package.bytes[2]=0x05;
						BLOOD_Package.bytes[3]=15;//SystemFlags.Datas.GSM_Signal;//O
						BLOOD_Package.bytes[4]=0x4f;//O
						BLOOD_Package.bytes[5]=0x4b;//K
						Uart_Send_9600(BLOOD_Package.bytes,6);
						me_delay_ms(100);
						Uart_Send_9600(BLOOD_Package.bytes,6);
						SystemFlags.Datas.uart_reicev_count_set=22;//这是告诉程序，下次要接收的数据长度为19
					}
				}
				break;			
			case 6:	
				test_buff[0]=0;
				for(i=0;i<21;i++)
				{
					test_buff[0]+=BLOOD_Package.bytes[i];
				}
				if(BLOOD_Package.bytes[21]==test_buff[0])
				{
					test_buff[0]=BLOOD_Package.bytes[3];//版本号
					test_buff[1]=BLOOD_Package.bytes[4];//客户码
					test_buff[2]=BLOOD_Package.bytes[5];//机种码
					test_buff[3]=BLOOD_Package.bytes[6];//机型号
					test_buff[4]=BLOOD_Package.bytes[7];//用户号
					test_buff[5]=BLOOD_Package.bytes[19];//生产月份
					test_buff[6]=BLOOD_Package.bytes[20];//生产年份
												
					test_buff[7]=BLOOD_Package.bytes[15]; //机身序列号1 低位
					test_buff[8]=BLOOD_Package.bytes[16]; //机身序列号2
					test_buff[9]=BLOOD_Package.bytes[17]; //机身序列号3
					test_buff[10]=BLOOD_Package.bytes[18];//机身序列号4 高位
					test_buff[11]=_pvref;//2V电压值
					test_buff[13]=_dah;//400mV电压值
					test_buff[12]=_dal;
					test_buff[14]=0;
					test_buff[15]=0;
					test_buff[16]=0;	
					test_buff[17]=0;//血糖测试次数序列号
					test_buff[18]=_opc1;

					memset(BLOOD_Package.bytes,0,128);
					for(i=0;i<19;i++)
					{
						BLOOD_Package.bytes[i]=test_buff[i];
					}
					BLOOD_Package.bytes[19]=0;	
					BLOOD_Package.bytes[20]=0;	
					BLOOD_Package.bytes[71]=Pub_temp;
					BLOOD_Package.bytes[72]=Pub_temp>>8;
					BLOOD_Package.bytes[74]=test_buff[11]^test_buff[12]^test_buff[13]^test_buff[18]^BLOOD_Package.bytes[71]^BLOOD_Package.bytes[72];
					BLOOD_Package.bytes[75]=18;		//年
					BLOOD_Package.bytes[76]=10;		//月
					BLOOD_Package.bytes[77]=1;		//月
					BLOOD_Package.bytes[78]=9;		//时
					BLOOD_Package.bytes[79]=45;		//分
					for(i=21;i<41;i++)
					{
						BLOOD_Package.bytes[i]=0;
					}			
					if(fun_enable_fwen())
					{
						me_delay_100us();
						fun_erase_page(Mem_adjust_address);	
						me_delay_100us();
						fun_write_cpage(Mem_adjust_address,128,0);
					}
					BLOOD_Package.bytes[0]=0x55;
					BLOOD_Package.bytes[1]=0x0a;
					BLOOD_Package.bytes[2]=0x06;
					
					BLOOD_Package.bytes[3]=_pvref;//2V电压值
					BLOOD_Package.bytes[4]=_dah;//400mV电压值
					BLOOD_Package.bytes[5]=_dal;
					BLOOD_Package.bytes[6]=_opc1;
					BLOOD_Package.bytes[7]=Pub_temp;
					BLOOD_Package.bytes[8]=Pub_temp>>8;
					BLOOD_Package.bytes[9]=0;
					for(i=0;i<9;i++)
					{
						BLOOD_Package.bytes[9]+=BLOOD_Package.bytes[i];
					}
					
					SystemFlags.Datas.uart_reicev_count_set=57;
					Uart_Send_9600(BLOOD_Package.bytes,10);	
					memset(BLOOD_Package.bytes,0,128);
					SystemFlags.Datas.uart_reicev_count=0;
					me_delay_ms(100);
				}
				break;
			case 7:
				SystemFlags.Datas.Flags.Bits.ready=1;
				BLOOD_Package.bytes[0]=0x55;
				BLOOD_Package.bytes[1]=0x05;
				BLOOD_Package.bytes[2]=0x07;
				BLOOD_Package.bytes[3]=0x4f;//O
				BLOOD_Package.bytes[4]=0x4b;//K
				Uart_Send_9600(BLOOD_Package.bytes,5);
				me_delay_ms(100);
				break;
			case 8:
				SystemFlags.Datas.Flags.Bits.test_falg=0;
				BLOOD_Package.bytes[0]=0x55;
				BLOOD_Package.bytes[1]=0x05;
				BLOOD_Package.bytes[2]=0x08;
				BLOOD_Package.bytes[3]=0x4f;//O
				BLOOD_Package.bytes[4]=0x4b;//K
				Uart_Send_9600(BLOOD_Package.bytes,5);
				me_delay_ms(100);
				Uart_Send_9600(BLOOD_Package.bytes,5);
				break;
		}
		memset(BLOOD_Package.bytes,0,10);
	}	
}


uchar Power_ON_OFF()
{
	SystemFlags.Datas.Flags.Bits.TestKeyboad=1;
	if(SystemFlags.Datas.Flags.Bits.power_on==0)
	{
		_dac=1;//DAC电源开
		_adoff=0;//AD电源开
		_ph0=1;//背光打开
		uart_init(1);
		OP_set();
		memset(BLOOD_Package.bytes,0,30);
		SystemFlags.Datas.Flags.Bits.uart_reicev_flag=0;
		SystemFlags.Datas.uart_reicev_count=0;
		memset(disp_buff,0xff,16);
		memset(flash,0xff,16);
		show_display();
		_lcdc = 0b10000001;
		memset(BLOOD_Package.bytes,0,128);
		fun_read_page(Mem_back_address);
		_pvref=BLOOD_Package.bytes[11];
		_dal  =BLOOD_Package.bytes[12];
		_dah  =BLOOD_Package.bytes[13];
		_opc1 =BLOOD_Package.bytes[18];	
		
		Project_Sequence =BLOOD_Package.bytes[10];
		Project_Sequence<<=8;
		Project_Sequence|=BLOOD_Package.bytes[9];
		Project_Sequence<<=8;
		Project_Sequence|=BLOOD_Package.bytes[8];
		Project_Sequence<<=8;
		Project_Sequence|=BLOOD_Package.bytes[7];
		
		Pub_temp=BLOOD_Package.bytes[72];
		Pub_temp<<=8;
		Pub_temp|=BLOOD_Package.bytes[71];
		SystemFlags.Datas.Flags.Bits.Mem_sequence_falg=BLOOD_Package.bytes[73];
		WDR();
		me_delay_ms(500);
		WDR();
		me_delay_ms(500);
		WDR();
		/*
		_dal  =0;
		_dah  =0x67;
		_opc1 =0x71;
		_pvref=200;
		Pub_temp=1000;
		*/
		memset(disp_buff,0,16);
		show_display();
		Get_Battery();
		if(SystemFlags.Datas.Battery_Val==0)//实际情况是低于3.6V关机
		{
			uart_close();
			displey_EB();
			WDR();
			me_delay_ms(500);
			WDR();
			me_delay_ms(500);
			WDR();
			Show_OFF();
			WDR();
			me_delay_ms(500);
			WDR();
			me_delay_ms(500);
			WDR();
			return 0;
		}
		while(_pa2==0)//开机后等待按键松开
		{
			WDR();	
		}
		memset(BLOOD_Package.bytes,0,128);
		fun_read_page(Mem_back_address);	
		Mem_sequence =BLOOD_Package.bytes[20];
		Mem_sequence<<=8;
		Mem_sequence|=BLOOD_Package.bytes[19];
		SystemFlags.Datas.Class=1;
			
		SystemFlags.Datas.Flags.Bits.Bluetooth=1;
		SystemFlags.Datas.Flags.Bits.Test_paper=1;
		SystemFlags.Datas.CTL_mode=0;
		SystemFlags.Datas.Flags.Bits.Blood_drop=0;
		SystemFlags.Datas.Flags.Bits.power_on=1;//GSM_turn_ON();//SystemFlags.Datas.Flags.Bits.power_on=1;
		staic_Temperature=Get_Temperature();
		SystemFlags.Datas.Flags.Bits.TestKeyboad=0;
		Second=0;
	}
	else
	{
		if(_pa4)//如果试纸已拔出，才可正常按键关机
		{
			#if Gsm_start_on
				Gsm_power_off(0);
			#endif
			Second=0;
			Show_OFF();
			show_display();
			WDR();
			me_delay_ms(500);
			WDR();
			me_delay_ms(500);
			WDR();
			SystemFlags.Datas.Flags.Bits.power_on=0;
			Mem_sequence_count=0;//查看的记忆数组位置回到零
			memset(flash,0xff,16);
			memset(disp_buff,0,16);
		}
	}	
}
uchar check_sys_Year()
{
	float i,a;
	uint b;
	a=sys_Year;
	i=a/400;	
	a=i;
	b=(int)i;
	if(((a-b)*100)==0)
	{
		return 1;	
	}
	
	a=sys_Year;
	i=a/100;
	a=i;
	b=(int)i;
	if(((a-b)*100)!=0)
	{
		a=sys_Year;
		i=a/4;
		a=i;
		b=(int)i;
		if(((a-b)*100)==0)
		{
			return 1;	
		}
	}
	return 0;
}
void run_time()
{
	sys_Second++;
   	if(sys_Second>59)
	{
		sys_Second=0;
		sys_Minute++;
		if(sys_Minute>59)
		{
			sys_Minute=0;
			sys_Hour++;
			if(sys_Hour>23)
			{
				sys_Hour=0;
				sys_Day++;
				if(check_sys_Year())//如果是闰年
				{
					if(sys_Day>data_time1[sys_Month])
					{
						sys_Day=1;
	    				sys_Month++;
	    				if(sys_Month>12)
	    				{
	    					sys_Month=1;
	    					sys_Year++;
	    				}		
					}
				}
				else
				{
					if(sys_Day>data_time2[sys_Month])
					{
						sys_Day=1;
	    				sys_Month++;
	    				if(sys_Month>12)
	    				{
	    					sys_Month=1;
	    					sys_Year++;
	    				}		
					}	
				}
			}
		}
	}	
}

#if 0
uchar check_sum_count(uchar uStart, uchar uEnd, uchar uCheck)
{
	uchar a, b, c;
	
	memset(IP_address, 0, 15);
	a = b = c = 0;
	
	for(a=uStart;a<uEnd;a++)//http模式
	{
		if(BLOOD_Package.bytes[a]>0x39)
		{
			IP_address[b]=BLOOD_Package.bytes[a];
			IP_address[b]-=0x37;
		}
		else
		{
			IP_address[b]=BLOOD_Package.bytes[a];
			IP_address[b]-=0x30;
		}
		IP_address[b]<<=4;
		if(BLOOD_Package.bytes[a+1]>0x39)
		{
			c=BLOOD_Package.bytes[a+1];
			c-=0x37;
		}
		else
		{
			c=BLOOD_Package.bytes[a+1];
			c-=0x30;
		}
		IP_address[b]|=c;
		a++;
		b++;
	}
	c=0;	
	for(a=0;a<uCheck;a++)
	{
		c^=IP_address[a];	
	}
	
	if (c == IP_address[uCheck])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


uchar check_sum()
{
	uchar a, b;
/*	memset(IP_address, 0, 15);
	b = 0;

	for(a=3;a<17;a++)//http模式
	{
		if(BLOOD_Package.bytes[a]>0x39)
		{
			IP_address[b]=BLOOD_Package.bytes[a];
			IP_address[b]-=0x37;
		}
		else
		{
			IP_address[b]=BLOOD_Package.bytes[a];
			IP_address[b]-=0x30;
		}
		IP_address[b]<<=4;
		if(BLOOD_Package.bytes[a+1]>0x39)
		{
			c=BLOOD_Package.bytes[a+1];
			c-=0x37;
		}
		else
		{
			c=BLOOD_Package.bytes[a+1];
			c-=0x30;
		}
		IP_address[b]|=c;
		a++;
		b++;
	}
	c=0;	
	for(a=0;a<6;a++)
	{
		c^=IP_address[a];	
	}
	if(c!=IP_address[6])
	{
		return 0;	
	}

	memset(IP_address, 0, 15);
	b = 0;

	for (a = 17; a < 30; a++)
	{
		if (BLOOD_Package.bytes[a] > 0x39)
		{
			IP_address[b] = BLOOD_Package.bytes[a];
			IP_address[b] -= 0x37;
		}
		else
		{
			IP_address[b] = BLOOD_Package.bytes[a];
			IP_address[b] -= 0x30;
		}
		IP_address[b] <<= 4;
		if (BLOOD_Package.bytes[a + 1] > 0x39)
		{
			c = BLOOD_Package.bytes[a + 1];
			c -= 0x37;
		}
		else
		{
			c = BLOOD_Package.bytes[a + 1];
			c -= 0x30;
		}
		IP_address[b] |= c;
		a++;
		b++;
	}
	
	c = 0;
	for (a = 0; a < 5; a++)
	{
		c ^= IP_address[a];
	}
	if (c == IP_address[5])
	{
		return 1;
	}
	else
	{
		return 0;
	}
	*/
	a = check_sum_count(3, 17, 6);
	b = check_sum_count(17, 29, 5);
	
	return a&b;
}


uchar get_value_status(void)
{
	uchar bRank;
	
	if((Blood_glucose <= 71) || (Blood_glucose >= 300))
		bRank = 3;
	else
	{
		if(Blood_glucose < 79)
			bRank = 2;
		else
		{
			if(Blood_glucose <= 126)
				bRank = 0;
			else
				bRank = 1;
		}
	}
	
	return bRank;
}
#endif
