#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

//;---------------------------------------------------------------------------
void	INT_SYSTEM(void)
{
	//
	_scc = 0b00000100;		//hirc	bit3=0 lirc	bit2=0
	_hircc = 0b00000101;	//hirc = 8mhz 	enable hirc
	_hxtc = 0b00000000;
	_pas0 = 0b00110011;
	_lxtc = 0b00000001;	
	
//				_scc = 0b00000000;		//hirc	bit3=0 lirc	bit2=0
//			_pas0 = 0b00000000;
//			_lxtc = 0b00000000;	
	//内部时钟，没理解错的话两个都是内部时钟8Ｍ　外部32Ｋ
	GCC_DELAY(255);
	//256次延时
	_wdtc = 0B10101111;  
}

/********************************************************************
Function:	Reset_Init
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Ram_Init() 
{
	_mp1h = 0;
	_mp1l = 0x80;
	while(_mp1h <5)
	{
		for(_tblp = 0x00;_tblp < 128;_tblp++)
		{
			 _iar1 = 0;
			  _mp1l++;
		}
		_mp1l = 0x80;		
		_mp1h++;
	}		
}

void	INT_IO(void)
{
	_pac =  0b00111010;
	_pa =   0b00000000;
	_papu = 0b00111010;
	_pawu = 0b00111000;
	
	_pbc =  0b00000001;
	_pb =   0;
	_pbpu = 0b11111111;	
	
	_pcc =  0b00000001;
	_pc =   0;
	_pcpu = 0b11111111;
	
	_pdc = 0;
	_pd =  0;
	_pdpu = 0b11111111;
		
	_pec = 0;
	_pe =  0;
	_pepu = 0b11111111;		
}

void	INT_POWER(void)
{
	_regc = 0x03;   //内部稳压IC开关  enable =3.3v
	_ccvrefc = 0x01;//设置静态电流电路
	_ccvrefen = 1;  //恒流源电路开关        enable
	_batden = 1;    //电池电压侦测电路开关  enable	
}

// ;-----------------------------------------------------------------------------
// ;设置TIMER0为定时器，每1MS中断一次
// ;设置TIMER1为定时器，每2.25MS中断一次
// ;设置TIMER2为PWM输出，输出设为TP2_0,TP2_1可切换，脉冲频率设2KHZ，分辨率11位以上
// ;-----------------------------------------------------------------------------

void	INT_TMR(void)
{
	_pscr = 0b00000011;	   //time base = fsub 
	_tb0c = 0b00000000;    //4ms 
	_tb1c = 0b00000110;    //625ms

	_ptm1c0 = 0b00100000;  //FH/16
	_ptm1c1 = 0b11000001;  //A match	
	_ptm1al = 0x35;        //0.104US
	_ptm1ah = 0x00;	

	_ptm2c0 = 0b00110000;  //FH/64      64*0X119/8M
	_ptm2c1 = 0b11000001;  //A match	   2.25
	_ptm2al = 0x19;        //
	_ptm2ah = 0x01;	
	
	_stm0c0 = 0b00010000;  //时钟有系统时钟
	_stm0c1 = 0b10101000;
	_stm0al = 0xff;        //占空比
	_stm0ah = 0x02;
	_stm0rp = 0x04;        //4*256 周期	

}

void	INT_LCD(void)
{
//	while(_lxtf==0)
//         {
//          GCC_CLRWDT1();
//	      GCC_CLRWDT2();
//         }
	
	_lcdc0 = 0b10000111;	//form vc 1.08v R type enlcd   //
	_lcdcp = 0b00001000;
	_lcdc2 = 0b11100010;	//1/6duty 1/3 bais

    _pas0 = 0b00110011; //
    _pas1 = 0b00000000; //    
    	
	_pbs0 = 0b01000000; //pb0-3 SEG
	
    _pcs0 = 0b00000011; //
//    _pcs1 = 0b00000000;      //set tx  PC5 rx    PC4
    	
	_pds0 = 0b10101111;	//pd0-1 com pd2-7 seg
	_pds1 = 0b11111111;		
	
	_pes0 = 0b00111111;	//pe0-2 seg
	_pes1 = 0b00000000;	//v2 c1 c2	
	
}
/********************************************************************
Function:	FUN_PINTB_INIT
INPUT	:	
OUTPUT	:	
NOTE	:	设置为双边沿触发中断，测试时采用pa0作为输入现象时；led0翻转
********************************************************************/
void	FUN_INT1_2_INIT()
{	
	_integ = 0b00000010	;					//int1 int2 设置为双边触发
	_int0e = 1;
	_int1e = 0;
//	_pafs |= 0b11000000;					//choose PA6&PA7 INT&OP2N&VG PIN
//	_sfs1 |= 0b11000000;					//choose PA6&PA7 INT PIN
//	_emi  = 1;

}	

/********************************************************************
Function:	Uart_Init
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/

void Uart_Init(void)
{
	_pcs1 = 0b00001010;      //set tx PC5 rx   PC4
	_rxps = 1;
    _ucr1 = UCR1_8_N_1;      //enable UART function,8bits-Data  NONE-Parity 1bit-Stop Format
    _ucr2 = UCR2Data1;       //enable TXEN,RXEN,Hige Speed Baud Rate, Receiver interrupt enable 
	_rie = 1;
	#ifndef	Debug
   		_brg = BRGData;         //9600 Baud Rate	
	#else
   		_brg = 51;              //9600 Baud Rate  //收时间	
	#endif
	_ure = 1;      			    //UART interrupt enable	
}

void	INT_OP(void)
{
	_scfc0 = 0b00001010;///???????56+4*10 = 96 ,低通9HZ  
	_scfc1 = 0b01011100;//00011000b、1024	;;auto convert 512//充许AD采SCF 
	_scfckd = 0x15;     //SCF 电路clock分频选择  自动采样周期的微调
	_pgac3 = 0b11001110;//scf offset voltage,低5位有效VOREG/2  1.65 pgaen ,pga2*1	
}

//void	INT_OP(void)
//{
//	_scfc0 = 0b00011000;///???????56+4*24 = 152 ,低通9HZ  
//	_scfc1 = 0b01011100;//00011000b、1024	;;auto convert 512//充许AD采SCF 
//	_scfckd = 0x15;     //SCF 电路clock分频选择  自动采样周期的微调
//	_pgac3 = 0b11001011;//scf offset voltage,低5位有效VOREG/2  1.65 pgaen ,pga2*1	
//}

// ;-----------------------------------------------------------------------------
// ;内部的AN 4 -7都设为AD，不要中断采样，要调用一函数等待采样完成
// ;-----------------------------------------------------------------------------
void	INT_AD(void)
{
	_sadc0 = 0b00111111;	//an 0 -3通道浮空 en adc
	_sadc1 = 0b11101011;	//設置為voreg供電，採樣率為1us

}
void	INT_INTP(void)
{
	_mf1e = 1;
	_ptm1ae = 1;
	_ptm2ae = 1;
//	_pt1on = 1;
	_pt2on = 1;	
	_mf1e = 1;
	
//	_mfic0 = 0x03;//定时器0
//	_mfic1 = 0x03;//定时器1
//	_tbon = 1;
//	_t0ae = 1;//TM0 COMPARATOR A MATCH INTERRUPT CONTROL  ENABLE
//	_t0on = 1;//TM0 ON	
//	_t1ae = 1;
//	_t1on = 1;

}


void SBR_INI_TIMEBASE(void)		 //TBC
{
	_tb0e=1;
	_tb1e=1;
	_tb0on = 1;
	_tb1on = 1;	
//	_tbc=0b10100001;	//0b10100001
//	_mf3e=1;
//	_mf4e=1;
	_tb0f = 0;
	_tb1f = 0;	
	GCC_NOP();
	_emi = 1;//GLOBAL INTERRUPT CONTROL  ENABLE 总中断允许
}


void INT_OP1(void)
{   
	uchar i;
	for(i=0;i<8;i++)
	{
		P1_ad[i]=SBR_EEPROM_READDATA(i);
	}
	_pgac0 = (uchar)P1_ad[0];
	_pgaen = 1; //PGAEN
	_pgac1 = (uchar)P1_ad[1];
	_pgac2 = (uchar)P1_ad[2];
	pres_ad_300 = P1_ad[3] << 8;
	pres_ad_300 = pres_ad_300 + P1_ad[4] + 3;//这里这个3是陈工说有点线性差才改的
	pres_ad_0 = P1_ad[5] <<8;
	pres_ad_0 = pres_ad_0 + P1_ad[6];
	BAS_L1 = (uchar)P1_ad[7];
	pres_ad_200 = (pres_ad_300 - pres_ad_0) / 3;
	pres_ad_100 = pres_ad_0 + pres_ad_200;
	pres_ad_200 = pres_ad_200 + pres_ad_100;
}
/******************************************************************************************* 
** 函数名称: Init_val
** 函数描述: 初始化相关变量 
** 输入参数: 无 
** 输出参数: 无  
*******************************************************************************************/
void Init_val(void)
{  
	ERFLAG.Val=0;
	COUNT1_XIA=0;
    po1=0;	        //标志寄存器
    max616=0;	    //标志寄存器
    max816=0;	    //标志寄存器
 	Over300=0;
	WAVE_count=0;
	PLSFTM=0;
    PLSCNT=0;
	PLSFTM0=0; 	
	DASP1=0;
	R2FLAG.Val=0;
	M1_PH=0;
	M1_PL=0;
	M1_PRE=0;
	MAX_WAVE=0;
	OLD_M1_PH=0;
	OLD_M1_PL=0;
	OLD_PRE=0;
	MAXIHB	=0;   
    MINIHB =255;
    IHB_COUNT=0;
    counter2ms = 0;
    GPRST =0; 
//    wudongzuo =0;
}
/*******************************************************************************************
** 函数名称: Delay_ms   0.05
** 函数描述: 延时cnt毫秒
** 输入参数: cnt:延时毫秒数
** 输出参数: 无 
*******************************************************************************************/
 void delay_ms(uint16 cnt)
{
	volatile  uint16 i;
	volatile  uint8 j;
	for(i=cnt;i>0;i--)
	{
		GCC_CLRWDT1();
		GCC_CLRWDT2();	
		for(j=0;j<140;j++)
		{
		 GCC_NOP();	
		}	
	}
}
/*******************************************************************************************
** 函数名称: Delay_ms   0.05
** 函数描述: 延时cnt毫秒
** 输入参数: cnt:延时毫秒数
** 输出参数: 无 
*******************************************************************************************/
 void Delay_ms(uint16 cnt)
{
	volatile  uint16 i;
	volatile  uint8 j;
	for(i=cnt;i>0;i--)
	{
		GCC_CLRWDT1();
		GCC_CLRWDT2();	
		for(j=0;j<14;j++)
		{ }	
	}
}
 