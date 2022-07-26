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
	_bgc = 0B00010000; //Bandgapʹ��Ϊ2.0V
	_opc1|= 0b01100000;//ʹ������Ŵ���ģʽ
}
void AD_set()
{
	// AD�Ĵ�������
	_adcr1 = 0B00000100;    //  ����ADCʱ��ԴΪϵͳʱ��16��Ƶ
	_adcr2 = 0b00001000;	//����ο���ѹΪbandgap ����ο���ѹΪGND	
}
void test_OP()
{
	uchar i;
	uint a=0;
	for ( i = 0; i < 64; i++ )
	{
	//	_pb2=~_pb2;
		_start=0;//����AD
		_start=1;//����
		_start=0;//����AD
		while(_eocb)
		{
			WDR();	
		}
		// ȡֵ		
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
					AD_set();//  ��Pb3ΪAD����
					_pbc2=0;//PB2����Ϊ���
					_pb2=1;//���1
					_pbc3=1;//PB3����Ϊ����
					_pb3=1;//
					_pbpu3=0;//��������
					_acs2=0;
					_acs1=0;
					_acs0=1;//AN1ͨ��
					me_delay_ms(10);
					for ( i = 0; i < 128; i++ )
					{
						_start=0;//����AD
						_start=1;//����
						_start=0;// ����AD
						while(_eocb)
						{
							WDR();	
						}
						// ȡֵ		
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
					AD_set();//  ��Pb4ΪAD����
					_acs2=0;
					_acs1=1;
					_acs0=0;//����AN2ͨ��
					_pbc4=1;//PB4����
					_pb4=0;//������ܣ���ҪҲ����
					_pbpu4=0;//��������
					me_delay_ms(10);
					for ( i = 0; i < 20; i++ )
					{
						
						_start=0;//����AD
						_start=1;//����
						_start=0;// ����AD
						while(_eocb)
						{
							WDR();	
						}
					}
					for ( i = 0; i < 50; i++ )
					{
						
						_start=0;//����AD
						_start=1;//����
						_start=0;// ����AD
						while(_eocb)
						{
							WDR();	
						}
						// ȡֵ		
						AD_value=_adrh;
						AD_value<<=8;
						AD_value|=_adrl;
						AD_value>>=4;
						a+=AD_value;
						AD_Delay();
					}
					AD_value=a/50;
					AD_value-=10;//�ó���ѹֵmv
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
					_pbpu1=0;//��PB1ΪOP1��������		
					// ȡADֵ
					//_pd5=1;
					a=0;
					for ( i = 0; i < 128; i++ )
					{
						_start=0;//����AD
						_start=1;//����
						_start=0;//����AD
						while(_eocb)
						{
							WDR();	
						}
						// ȡֵ
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
//					AD_value = AD_value * 18;//��2020��9��28��14:00:59 ������mmol/l��mg/dl֮���ת��
					if(flag)
					{
						c=AD_value*Pub_temp;
						c/=1000;
						AD_value=c;	
					}
					
					Blood_glucose=0;
					if(AD_value>3941)//����25K,��ӦֵΪ0X0F70 
					{
						Blood_glucose=601;//HI
						break;
					}
					if(AD_value<1017)//����1M
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
