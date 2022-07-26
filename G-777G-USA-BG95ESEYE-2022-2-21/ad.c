#include "HT45F67.h"
#include "AD.h"
#include "DELAY.h"
#include "Defineport.h"
#include "UART.h"


void AD_Delay()
{
	uchar i=84;
	while(i!=0)
	{
		i--;	
	}	
}
void OP_set()
{
	_bgc = 0B00010000; //Bandgap使能为2.0V
	_opc1|= 0b01100000;//使能运算放大器模式
}
void AD_set()
{
	// AD寄存器设置
	_adcr1 = 0B00000100;    //  设置ADC时钟源为系统时钟16分频
	_adcr2 = 0b00001000;	//正相参考电压为bandgap 反相参考电压为GND	
}
void test_OP()
{
	uchar i;
	uint a=0;
	for ( i = 0; i < 64; i++ )
	{
	//	_pb2=~_pb2;
		_start=0;//启动AD
		_start=1;//重置
		_start=0;//启动AD
		while(_eocb)
		{
			WDR();	
		}
		// 取值		
		AD_value=_adrh;
		AD_value<<=8;
		AD_value|=_adrl;
		AD_value>>=4;
		a+=AD_value;
	}
	AD_value=a/64;		
}

void get_lowPwd(uchar Channel,uchar flag)
{	
	 uchar i;
	 uint a=0,b=0;
	 ulong c=0;
	 AD_value=0;

	switch(Channel)
	{
		case 1:	
				{
					AD_set();//  设Pb3为AD输入
					_pbc2=0;//PB2设置为输出
					_pb2=1;//输出1
					_pbc3=1;//PB3设置为输入
					_pb3=1;//
					_pbpu3=0;//不加上拉
					_acs2=0;
					_acs1=0;
					_acs0=1;//AN1通道
					me_delay_ms(10);
					for ( i = 0; i < 128; i++ )
					{
						_start=0;//启动AD
						_start=1;//重置
						_start=0;// 启动AD
						while(_eocb)
						{
							WDR();	
						}
						// 取值		
						AD_value=_adrh;
						AD_value<<=8;
						AD_value|=_adrl;
						AD_value>>=4;

						if(i>3)
							a+=AD_value;
						AD_Delay();
					}
					_pb2=0;
					AD_value=a/124;
				}
				break;
		case 2:	
				{
					AD_set();//  设Pb4为AD输入
					_acs2=0;
					_acs1=1;
					_acs0=0;//设置AN2通道
					_pbc4=1;//PB4输入
					_pb4=0;//这个不管，不要也可以
					_pbpu4=0;//不加上拉
					me_delay_ms(10);
					for ( i = 0; i < 20; i++ )
					{
						
						_start=0;//启动AD
						_start=1;//重置
						_start=0;// 启动AD
						while(_eocb)
						{
							WDR();	
						}
					}
					for ( i = 0; i < 50; i++ )
					{
						
						_start=0;//启动AD
						_start=1;//重置
						_start=0;// 启动AD
						while(_eocb)
						{
							WDR();	
						}
						// 取值		
						AD_value=_adrh;
						AD_value<<=8;
						AD_value|=_adrl;
						AD_value>>=4;
						a+=AD_value;
						AD_Delay();
					}
					AD_value=a/50;
					AD_value-=10;//得出电压值mv
				}
				break;
		case 3:	
				{
					AD_set();
					_acs2=1;
					_acs1=0;
					_acs0=0;
					_tsc=1;
					_pbc1=1;
					_pb1=1;
					_pbpu1=0;//设PB1为OP1反相输入		
					// 取AD值
					//_pd5=1;
					a=0;
					for ( i = 0; i < 128; i++ )
					{
						_start=0;//启动AD
						_start=1;//重置
						_start=0;//启动AD
						while(_eocb)
						{
							WDR();	
						}
						// 取值
						AD_value=_adrh;
						AD_value<<=8;
						AD_value|=_adrl;
						AD_value>>=4;
						if(i>3)
						{
							a+=AD_value;
						}
						AD_Delay();	
					}
					AD_value = a/124;
//					AD_value = AD_value * 18;//改2020年9月28日14:00:59 这里是mmol/l和mg/dl之间的转换
					if(flag)
					{
						c=AD_value*Pub_temp;
						c/=1000;
						AD_value=c;	
					}
					
					Blood_glucose=0;
					if(AD_value>3941)//等于25K,对应值为0X0F70 
					{
						Blood_glucose=601;//HI
						break;
					}
					if(AD_value<1017)//大于1M
					{
						Blood_glucose=18;//LO
						break;
					}
					if(SystemFlags.Datas.CTL_mode==1)
					{
						Blood_glucose =Calculate_contrul(AD_value,Blood_glucose);
					}
					else
					{
						
						Blood_glucose = Calculate_blood(AD_value,Blood_glucose);

					}
				}
				break;
		default:break;
	}	
}
