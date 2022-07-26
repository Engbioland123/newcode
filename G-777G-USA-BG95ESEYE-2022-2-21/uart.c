#include "HT45F67.h"
#include "Uart.h"
#include "Defineport.h"
#include "iap.h"
#include "DELAY.h"
#include "string.h"
#include "LCD.h"
#include "runTask.h"
#include <string.h>
#include <stdlib.h>

#define adjust_demo


const uchar Get_time[12]={0x55,0xaa,0x00,0x90,0,0,0,0,0,12,0x5d,1};
const char urlHead[] = "POST /bioland HTTP/1.1\r\nHost: api.tellihealth.com\r\nContent-Length: 176\r\n\r\n";

const char imei[] = "{\r\n\t\"IMEI\":";
const char sn[] = "\r\n\t\"SN\":";
const char checkTime[] = "\r\n\t\"Check Time\":";
const char checkData[] = "\r\n\t\"Check Data\":\r\n\t{";
const char bloodSugarVal[] = "\r\n\t\t\"Blood sugar value\":";
const char b_O_AfterMeal[] = "\r\n\t\t\"Before or after meals\":";
const char dakuohao[] = "}";
const char huanhangkong[] = "\r\n\t";
const char huanhang[] = "\r\n";

const unsigned char crc8_table[128]=
{
	0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,
	0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,
	0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,
	0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,
	0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,
	0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,
	0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,
	//0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,
	//0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,
	//0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,
	//0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,
	//0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,
	//0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,
	//0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,
	//0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,
	//0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3
};
uchar calculate_crc8(uchar *data,uchar start_address,ushort cnt)
{
	uchar crc8 = 0;
	uchar i;
	for(i=start_address;i<(start_address+cnt);i++)
	//while(cnt--)
	{  
		crc8=crc8_table[crc8^data[i]];
	}
	return crc8;
}
__attribute__((interrupt(0x14))) 
void ISR_UART()
{
	if(SystemFlags.Datas.Flags.Bits.uart_reicev_flag==0)
	{
		BLOOD_Package.bytes[SystemFlags.Datas.uart_reicev_count]=_txrrxr;
		SystemFlags.Datas.uart_reicev_count++;
		if(SystemFlags.Datas.uart_reicev_count>127)
		{
			SystemFlags.Datas.uart_reicev_count=0;	
		}
	}
	_urf=0;
}
//////////////////////////////////////////////
void Uart_delay(volatile uchar k)
{
	while(k!=0)
	{
		k--;	
	}	
}
//这是9600波特率接收
unsigned char Receice_one_byte()
{
	uchar i=0;
	uchar DATA=0;
	while(_pa4)
	{
		WDR();

	}
	Uart_delay(23);
	for(i=0;i<8;i++)
	{
		DATA>>=1;
		if(_pa4)
		{
			DATA|=0x80;	
		}
		Uart_delay(22);
	}
	return (DATA);	
}

void Uart_Receice_9600(unsigned char *Pdat,unsigned char len)
{
	unsigned char i=0;
	while(i<len)
	{
		Pdat[i] = Receice_one_byte();
		i++;
	}
}

//这是9600波特率发送
void Send_data_9600(uchar ch)
{
	unsigned char i;
	//_ph0=0;
	_pa2=0;
	Uart_delay(22);
	for(i=0;i<8;i++)
	{
		if(ch&0x01)
		{
			//_ph0=1;
			_pa2=1;
		}
		else
		{
			//_ph0=0;
			_pa2=0;
		}
		ch>>=1;
		Uart_delay(21);
	}
	//_ph0=1;
	_pa2=1;
	Uart_delay(22);	
}

void Uart_Send_9600(unsigned char *data,unsigned char len)
{
	unsigned char i;
	
	for(i=0;i<len;i++)
	{
	   Send_data_9600(data[i]);
	}	
}

void uart_init(int type)//为0的时候波特率9600，为1的时候波特率19200。
{
	uchar i;
	_emi=0;
	i=_usr;
	
	_pcc0=0;
	_pc0=0;
	_pcc0=1;
	_pac1=0;
	_bno=0;
	_prt=0;
	_pren=0;
	_stops=0;
	_brg=25;//波特率9600
//	_brg=12;//波特率19200
	_rxen=1;
	_ucr1=0x80;	
	_ucr2=0xe4;	
	_integ=0;//外部中断除能
	_mfi0=0b00001100;//
	_mfi1=0b00001000;//UART使能
	_mfi2=0b00000001;
	_intc1=0b00000010;
	_intc0=0b00000001;
	_emi=1;
	me_delay_100us();
	i=_txrrxr;
#if 0 
	uchar i;
	_emi=0;
	i=_usr;
	
	if(type==0)
	{
		_pec  = 0b00111111;
		_pfc  = 0b11100000;
		_pgc  = 0b00111111;
	}
	_pc0=1;//_pc0=0;
	_pcc0=1;
	
	_pac1=1;
	if(type==0)
	{
		_bno=0;
		_prt=0;
		_pren=0;
		_stops=0;
		_brg=25;//波特率9600
	}
	else
	{
		_brg=12;//波特率19200
	}	
	_brg=12;//波特率19200

	if(type==0)
		_rxen=1;
	
	_ucr1=0x80;	
	if(type==0)
		_ucr2=0xe4;		//发送使能，接收使能，高波特率，接收中断使能
	else	
		_ucr2=0xec;		//发送使能，接收使能，高波特率，RX带唤醒功能，接收中断使能
	_integ=0;//外部中断除能
	_mfi0=0b00001100;//
	_mfi1=0b00001000;//UART使能
	_mfi2=0b00000001;
	_intc1=0b00000010;
	_intc0=0b00000001;
	_emi=1;
	me_delay_100us();
	i=_txrrxr;
#endif
}

void uart_close()
{
	_ure=0;
	_mfi1=0;
	_txen=0;
	_rxen=0;
	_pcc0=1;
	_pc0=1;
	_pac1=1;
	_pa1=1;
	_dac=0;//DAC电源关
	_adoff=1;//AD电源关
	_bgc=0;
	_op1en=0;
}
void Send_data(uchar dat)
{
	while(_tidle==0)
	{
		_clrwdt();
	}
	_txrrxr=dat;
}
void Uart_Send(unsigned char *data,unsigned char len)
{
	unsigned char i;	
	for(i=0;i<len;i++)
	{
		Send_data(data[i]);
	}
}

void wait_return(ushort i)
{
	while(i)
	{
		WDR();
		nbIotSignal();
		show_display();
		me_delay_ms(200);
		i--;
//		if(Gsm_timer>120)
		if(Gsm_timer>270)
		{
			break;	
		}
	}
}

void wait_100MS(ushort i)
{
	while (i)
	{
		show_battery();
		//show_display();
		me_delay_ms(100);
		i--;
		if (Gsm_timer > GSM_max_time)
		{
			return 0;
		}
	}
}

void uart_tx_string(uchar *p)
{
    uchar len;  
	len=strlen((uchar*)p);//计数‘ ’（空字符 值为0 或 ‘ ’）之前的字符个数
	Uart_Send((uchar *)p,len);
}

uchar get_len_string(uchar *p)
{
    uchar len;  

	len=strlen((uchar*)p);//计数‘ ’（空字符 值为0 或 ‘ ’）之前的字符个数
	
	return len;
}


extern const uchar data_time2[];
//+QLTS: "2022/07/20,03:40:55+32,0"
//
//OK

//+QNTP: 0,"2022/06/20,21:32:20-16"


uchar getModuleTime(char *str)
{
	char *PA = str;
	char *PB;
	uchar ret = 0;
	uint yearTemp = 0;
	_emi=0;
	if(strstr(PA,":"))//防止是空的跑进来
	{
		PB = strchr(PA,'\"');
		yearTemp = atoi(&PB[1]);
		if(yearTemp < 2042)//防止基站错误出现80/01/06跑进来
		{
			sys_Year = yearTemp;
			PA = PB;
			PB = strchr(PA, '/');
			sys_Month = atoi(&PB[1]);
			PA = &PB[1];
			PB = strstr(PA, "/");
			sys_Day = atoi(&PB[1]);
			PA = PB;
			PB = strchr(PA, ',');
			sys_Hour = atoi(&PB[1]);
			PA = PB;
			PB = strchr(PA, ':');
			sys_Minute = atoi(&PB[1]);
			PA = &PB[1];
			PB = strchr(PA, ':');
			sys_Second = atoi(&PB[1]);
			
				 if(sys_Hour>3)// 减4小时
				 {
						sys_Hour-=4;
				 }
				 else
				 {
					sys_Hour=(sys_Hour+24-4)%24;
					sys_Day--;
					if(sys_Day==0)
					{						
					   sys_Month--;		    	   
					   if(sys_Month==0)
						 {
							sys_Month=12;
							sys_Year--;
						 }		    	    
					   sys_Day=data_time2[sys_Month];		    	   		    	   
					   if(sys_Year%4==0 && sys_Month==2)//如果是闰年
						  sys_Day=29;
					}			  				 			 	
				 }			
			
			
			Update_time();
			ret = 1;
		}		
	}
	_emi=1;
	return ret;
	
	
	
}



void nbIotSignal(void)
{
	if(SystemFlags.Datas.GSM_Signal>9)
	{
		disp_buff[4]|=0b10000000;//信号第一格	
	}
	else if(SystemFlags.Datas.GSM_Signal>10)
	{
		disp_buff[5]|=0b00000001;//信号第二格	
	}
	else if(SystemFlags.Datas.GSM_Signal>15)
	{
		disp_buff[5]|=0b00000010;//信号第三格	
	}
	else if(SystemFlags.Datas.GSM_Signal>25)
	{
		disp_buff[5]|=0b00000100;//信号第四格	
	}
	else if(SystemFlags.Datas.GSM_Signal>31)
	{
		disp_buff[5]|=0b00000000;//信号第四格
	}
}

uchar getBloodSuger(uint sugarVal,uchar *pdata)
{
	ushort k = 0;
	uchar a,b,c;
	if(sugarVal>600)
	sugarVal=601;
	k=sugarVal*100;
	k = k/10;			  //不要小数点
	c=k%1000%100%10;
	if(c>4)
	{
		k+=10;	
	}
	k/=10;
	a=k%1000/100;
	b=k%1000%100/10;
	c=k%1000%100%10;
	pdata[0] = '\"';
	if(a > 0)
		pdata[1] = a + 0x30;
	else
		pdata[1] = 0x20;
	pdata[2] = b + 0x30;
	pdata[3] = c + 0x30;
	memcpy(&pdata[4],"mg/dl\"",sizeof("mg/dl\""));

}

//这里合泰的编译器不支持空指针？？？
uchar getServerCallback(uchar *str,uchar len)
{
	uchar ret = 0;
	char *PA = str;

	if(strstr(PA,"20"))
		ret = 0;
	else if(strstr(PA,"40"))//40时候的错误
		ret = 1;
	else if(strstr(PA,"ERROR"))//70出现错误
		ret = 2;
	else 
		ret = 6;
	return ret;
}

uchar getRssi(uchar *str,uchar len)
{
	uchar i = 0,j=0,k=0;
	uchar flag = 0;
	uchar ret = 0xFF;
	uchar rssiArray[2] = {0x00,0x00};
	for (i = 0; i < len; i++)
	{
		if ((str[i] >= '0') && ((str[i] <= '9')))
		{
			if (j == (i - 1))
				rssiArray[k] = rssiArray[k] * 10 + (str[i] - 0x30);
			else
				rssiArray[k] = str[i] - 0x30;
			j = i;
			flag = 1;
		}
		else
		{
			if (flag == 1)
			{
				flag = 0;
				k++;
			}
		}
	}

	if((rssiArray[0] >= 1)&&(rssiArray[0] <= 31))
	{
		if(rssiArray[1] == 99)
		{
			ret = 0;
		}
	}
	else 
	{
		ret = 1;
	}
	SystemFlags.Datas.GSM_Signal = rssiArray[0];
	nbIotSignal();
	return ret;
}

uchar getIMEI(uchar *str,uchar len)
{
	uchar ret = 0;
	uchar hlen = 0;
	char *PA = str;
	if(PA != 0)
	{
		memset(httptemp,0,sizeof(httptemp));
		httptemp[0] = '\"';
		memcpy(&httptemp[1],&PA[2],15);//15是IMEI号长度
		httptemp[16] = '\"';
		ret = 1;
	}
	else
		ret = 0;
	
	return ret;
}
void clnUartBuf(void)
{
	SystemFlags.Datas.uart_reicev_count=0;
	memset(BLOOD_Package.bytes,0,128);
}

uchar hexToAscii(int data)
{
	if ((data >= 0) && (data <= 9))
		data += '0';
	else if ((data >= 10) && (data <= 15))
		data += 'A';
	return data;
}

//用creg,cereg,cgreg查询网络状态
uchar Check_NetReg(char *pdatain)
{
	char *PA;
	char ret = 0;
	uchar i = 0;
	uchar temp[3] = {0,};

//	PA = strchr(pdatain, ',');
//	temp[0] = atoi(++PA);
//	if((temp[0] == 1)||(temp[0] == 5))
//	{
//		ret = 1;
//	}

	PA = strchr(pdatain, ',');
	temp[0] = atoi(++PA);
	PA = strchr(PA, ',');
	temp[1] = atoi(++PA);
	PA = strchr(PA, ',');
	temp[2] = atoi(++PA);
	for (i = 0; i < 3; i++)
	{
		if ((temp[i] == 1) || (temp[i] == 5))
		{
			ret = 1;
			break;
		}
	}
	return ret;
}

void stopGSMTask(void)
{
	comEnterCount = 0;
	comEnterStep = e_nb_END;
	comRestartCount = 0;
}

void Send_phase(uchar step)
{
	comEnterCount = 0;
	comRestartCount = 0;
	comEnterStep = step;
}
uchar Send_GSM2(ushort index,uchar flag)//发送成功返回a=0，失败返回a=1,如果b==0,则为当次发送，b==1,为失败缓冲发送
{
	uchar i = 0;
	uchar ret = 0xFF;
	uchar result = 0xFF;
	comEnterCount = 0;
	if(flag == 0)//发送当前
	{
		Send_phase(e_nb_ATE0);
		//Send_phase(e_nb_CPIN);
		while(comEnterStep != e_nb_END)
		{
		
			comEnterCount++;

			if(Gsm_timer > 360)
			{
				result = 22;
				break;
			}		
			result = GSM_task(comEnterStep,11);
			if(result != 0)
				break;
		}
	}
	else if(flag == 1)
	{
		Send_phase(e_nb_GSN);
		while(comEnterStep != e_nb_END)
		{
			comEnterCount++;

			if(Gsm_timer > 240)
			{
				result = 22;
				break;
			}
			
			result = GSM_task(comEnterStep,index);
			if(result != 0)
				break;
		}
	}
	
	memset(BLOOD_Package.bytes,0,sizeof(BLOOD_Package));
	ret = (result != 0)?1:0;
	return ret;
}
//这里分4种情况
//1.发送1次，200ms内一定有返回。
//2.发送N次，200ms内一定又返回。
//3.发送1次，等很久才有返回。(for循环直接等)
//4.发送1次，等有返回后再发另一次。(拆开成两步执行)

//需要修改的参数，参数长度， 参数数值，输出
uchar GSM_task(uchar step,ushort buff)
{
	uchar b = 0;
	ushort i = 0;
	uchar result = 0;//成功标志位
	uchar ret = 0;
	uint bloodVal = 0;
	uchar restart=0;
	static uchar errCount = 0;//出错需要返回，这里计算返回次数，成功后清零。
	
	WDR();
	if(step < e_nb_QHTTPREAD)//发送之后，不要清除了，等待返回
		clnUartBuf();
	
	switch(comEnterStep)
	{
//---------------------------------------------------------------------------------			
		case e_nb_ATE0: 
		{					

			if(comEnterCount < 6)
			{
				uart_tx_string("ATE0\r\n");
				wait_return(1);				
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
				//	result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QGMR;
				}
			}
			else
			{
				result = 1;
				stopGSMTask();
			}
		}
		break;
//---------------------------------------------------------------------------------			
		case e_nb_QGMR: // ATI Display Product Identification Information
		{					

			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QGMR\r\n");
				wait_return(1);				
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
				//	result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_CPIN;
				}
			}
			else
			{
					comEnterCount = 0;
					comEnterStep = e_nb_CPIN;
			}
		}
		break;		
//---------------------------------------------------------------------------------	
		case e_nb_CPIN:
		{

			if(comEnterCount < 6)
			{
				uart_tx_string("AT+CPIN?\r\n");
				wait_return(5);	
				if(strstr(BLOOD_Package.bytes,"+CPIN: READY"))
				{
					wait_return(1);
					comEnterCount = 0;
					//comEnterStep = e_nb_CIMI;
					comEnterStep = e_nb_CIMI;
				}
			}
			else
			{
				result = 2;
				stopGSMTask();
			}
		};break;
		
//---------------------------------------------------------------------------------			
		
		case e_nb_CIMI:
		{
				uart_tx_string("AT+CIMI\r\n");
				wait_return(1);
				comEnterCount = 0;				
				comEnterStep = e_nb_autosel;			

		};break;
//---------------------------------------------------------------------------------		
		case e_nb_autosel:
		{
				uart_tx_string("AT+QMBNCFG=\"autosel\"\r\n");
				wait_return(1);
				if(!strstr(BLOOD_Package.bytes,",0"))//
				{
					uart_tx_string("AT+QMBNCFG=\"autosel\",0\r\n");
					wait_return(1);
					uart_tx_string("AT+CFUN=1,1\r\n");
					wait_return(1);
					comEnterCount = 0;
					comEnterStep = e_nb_ATE0;
				
				}
				else
				{
					comEnterCount = 0;
					comEnterStep = e_nb_BAND;
				}				
				
		

		};break;
//---------------------------------------------------------------------------------					

		case e_nb_BAND:
		{

			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QCFG=\"band\"\r\n");
				wait_return(1);	
				//if(!strstr(BLOOD_Package.bytes,"0xf,0x180a,0x180a"))
				if(!strstr(BLOOD_Package.bytes,"0xf,0x100002000000000f0e189f,0x10004200000000090e189f"))
				{
					//uart_tx_string("AT+QCFG=\"band\",0xF,0x180A,0x180A,1\r");
					uart_tx_string("AT+QCFG=\"band\",0xf,0x100002000000000f0e189f,0x10004200000000090e189f,1\r");
					wait_return(1);
					comEnterCount = 0;
					restart=1;
	
				}
				else
				{
					comEnterCount = 0;
					comEnterStep =e_nb_IOTOP;//e_nb_COPS;
				}
			}
			else
			{
				result = 4;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_IOTOP:
		{

			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QCFG=\"iotopmode\"\r\n");
				wait_return(1); 
				if(!strstr(BLOOD_Package.bytes,"0"))//0 emtc 1 nb-iot 2emtc nbiot 只要EMTC
				{
					uart_tx_string("AT+QCFG=\"iotopmode\",0,1\r\n");
					wait_return(1);
					comEnterCount = 0;
					restart=1;
				}
				else
				{
					comEnterCount = 0;
					comEnterStep = e_nb_SCANSEQ ;
				}
			}
			else
			{
				result = 6;
				stopGSMTask();
			}

		};break;		
//---------------------------------------------------------------------------------	
		
		case e_nb_SCANSEQ:
		{

			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QCFG=\"nwscanseq\"\r\n");//扫描顺序
				wait_return(1);	
				//if(!strstr(BLOOD_Package.bytes,"020301"))//01  gsm  02emtc  03nb-iot
				if(!strstr(BLOOD_Package.bytes,"020103"))//01  gsm  02emtc  03nb-iot
				{
					//uart_tx_string("AT+QCFG=\"nwscanseq\",020301,1\r\n");
					uart_tx_string("AT+QCFG=\"nwscanseq\",020103,1\r\n");
					wait_return(1);
					comEnterCount = 0;
					restart=1;
					
				}
				else
				{
					comEnterCount = 0;
					comEnterStep = e_nb_NWSCAN;
				}
				
			}
			else
			{
				result = 7;
				stopGSMTask();
			}
		}break;
//---------------------------------------------------------------------------------	
		case e_nb_NWSCAN:
		{

			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QCFG =\"nwscanmode\"\r\n");
				wait_return(1);	
				if(!strstr(BLOOD_Package.bytes,"0"))//0 automatic 1gsm   3lte
				//if(!strstr(BLOOD_Package.bytes,"3"))//0 automatic 1gsm   3lte只要LTE
				{
					uart_tx_string("AT+QCFG=\"nwscanmode\",0,1\r\n");
					//uart_tx_string("AT+QCFG=\"nwscanmode\",3,1\r");
					wait_return(1);
					comEnterCount = 0;
					restart=1;
				
				}
				else
				{
					comEnterCount = 0;
					//comEnterStep = e_nb_CGDCONT;
					comEnterStep = e_nb_restart;
				}
			}
			else
			{
				result = 5;
				stopGSMTask();
			}
		}break;
//---------------------------------------------------------------------------------	
		case e_nb_restart:
		{  
			if(restart)
			{
				uart_tx_string("AT+CFUN=0\r\n");
				wait_return(5);
				uart_tx_string("AT+CFUN=1\r\n");
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
				}
				else
				 wait_return(5);				
				comEnterCount = 0;
				comEnterStep = e_nb_CIMI;				
								
			}
			else
			{
				comEnterStep = e_nb_CGDCONT;				
				
			}


		}break;		
//---------------------------------------------------------------------------------	
		
		case e_nb_CGDCONT:
		{
			
			if(comEnterCount < 6)
			{
				//uart_tx_string("AT+CGDCONT=1,\"IP\",\"\","",""\r");
				//uart_tx_string("AT+CGDCONT=1,\"IP\",\"ESEYE1\","",""\r");
			//	uart_tx_string("AT+CGDCONT=2;+CGDCONT=3;+CGDCONT=4;+QICSGP=1,1,\"ESEYE.COM\",\"\",\"\",0\r");
			//	uart_tx_string("AT+CGDCONT=2;+CGDCONT=3;+CGDCONT=4;+QICSGP=1,1,\"Eseye1\",\"\",\"\",0\r\n");
				uart_tx_string("AT+CGDCONT=2,\"IPV4V6\",\"vzwadmin\";+CGDCONT=3;+CGDCONT=4;+QICSGP=1,1,\"Eseye1\",\"\",\"\",0\r\n");
				wait_return(5);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QSSLCFG1;
				}
			}
			else
			{		
				comRestartCount = 0;
				result = 8;
				stopGSMTask();	
			}	
		}break;
//---------------------------------------------------------------------------------			
		case e_nb_QSSLCFG1:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QSSLCFG=\"seclevel\",1,0\r\n");
				wait_return(1);		
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QSSLCFG2;
				}
			}
			else
			{
				result = 9;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_QSSLCFG2:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QSSLCFG=\"sni\",1,1\r\n");
				wait_return(1);		
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QSSLCFG3;
				}
			}
			else
			{
				result = 10;
				stopGSMTask();
			}
		}break;
//---------------------------------------------------------------------------------			
		case e_nb_QSSLCFG3:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QSSLCFG=\"sslversion\",1,4\r\n");
				wait_return(1);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QSSLCFG4;
				}
			}
			else
			{
				result = 11;
				stopGSMTask();
			}
		}break;
//---------------------------------------------------------------------------------			
		case e_nb_QSSLCFG4:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QSSLCFG=\"ciphersuite\",1,0XFFFF\r\n");
				wait_return(1);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QHTTPCFG1;
				}
			}
			else
			{
				result = 12;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_QHTTPCFG1:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QHTTPCFG=\"contextid\",1\r\n");
				wait_return(1);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QHTTPCFG2;
				}
			}
			else
			{
				result = 13;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_QHTTPCFG2:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QHTTPCFG=\"sslctxid\",1\r\n");
				wait_return(1);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QHTTPCFG3;
				}
			}
			else
			{
				result = 14;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_QHTTPCFG3:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QHTTPCFG=\"requestheader\",1\r\n");
				wait_return(1);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QICSGP;
				}
			}
			else
			{
				result = 15;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------			

//		case e_nb_AUTOSEL:
//		{
//			
//			//if(comEnterCount < 6)
//			{
//				uart_tx_string("AT+QHTTPCFG=\"autosel\"\r\n");------------
//				wait_return(1);
//				if(!strstr(BLOOD_Package.bytes,",0"))
//				{
//				   uart_tx_string("AT+CFUN=1\r\n");
//				   wait_return(1);
//
//				}
//				result = 0;//成功
//				comEnterCount = 0;
//				comEnterStep = e_nb_QICSGP;				
//			}
////			else
////			{
////				result = 16;
////				stopGSMTask();
////			}
//		};break;

//---------------------------------------------------------------------------------		
		
		case e_nb_QICSGP:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+QICSGP=1,1,\"Eseye1\",\"\",\"\",1\r\n");//apn
				wait_return(1);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QIACT;
				}
			}
			else
			{
				result = 17;
				stopGSMTask();
			}
		}break;	
//---------------------------------------------------------------------------------			
		case e_nb_QIACT:
		{
			

				uart_tx_string("AT+QIACT?\r\n");
				wait_return(5);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_COPS1;
					break;	
				}

				result = 0;//成功
				comEnterCount = 0;
				comEnterStep = e_nb_QIACT2;
			
		}break;			
//---------------------------------------------------------------------------------	
		case e_nb_QIACT2:
		{
			result = 18;
			stopGSMTask();
			uart_time=0;			
			while(uart_time < 60)
			{
				uart_tx_string("AT+QIACT=1\r\n");
				wait_return(5);
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_COPS1;
					break;
				}
				if(strstr(BLOOD_Package.bytes,"ERROR"))
				{
					
					result = 0;//收到错误也往下执行。
					comEnterCount = 0;
					comEnterStep = e_nb_COPS1;
					break;
					
				}
				
				
			}

		}break;			
//---------------------------------------------------------------------------------	
		
		
		case e_nb_COPS1:
		{
			
			if(comEnterCount < 150)// about 3min
			{
				uart_tx_string("AT+COPS?\r\n");
				wait_return(10);//2 S
				if(strstr(BLOOD_Package.bytes,","))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_CXREG;
				}
			}
			else
			{
				result = 19;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------					
		case e_nb_CXREG:
		{
			
			if(comEnterCount < 91)
			{
				uart_tx_string("AT+CREG?;+CEREG?;+CGREG?\r\n");
//				uart_tx_string("AT+CEREG?\r");
				//uart_tx_string("AT+CGREG?\r");
				wait_return(10);//2秒扫一次				
				ret = Check_NetReg(BLOOD_Package.bytes);
				if(ret == 1)//1,5 已经注册上了
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_CSQ;
				}
			}
			else
			{
				result = 20;
				stopGSMTask();
			}
		}break;
//---------------------------------------------------------------------------------			
		case e_nb_CSQ:
		{
			
			if(comEnterCount < 60)
			{
				uart_tx_string("AT+CSQ\r\n");
				wait_return(5);	
				if(!getRssi(BLOOD_Package.bytes,128))//获得信号值
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_INFO;
				}
			}
			else
			{
				result = 21;
				stopGSMTask();
			}
		}break;
//---------------------------------------------------------------------------------			
		case e_nb_INFO:
		{
			
			if(comEnterCount < 60)
			{
				uart_tx_string("AT+QNWINFO\r\n");
				wait_return(5);	
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					result = 0;//成功
					comEnterCount = 0;
					comEnterStep = e_nb_QLTS;
				}
			}
			else
			{
				result = 21;
				stopGSMTask();
			}
		}break;	
//---------------------------------------------------------------------------------					
		case e_nb_QLTS:
		{

				uart_tx_string("AT+QLTS\r\n");
				wait_return(5); 
				if(strstr(BLOOD_Package.bytes,"OK"))
				{
					ret = getModuleTime(BLOOD_Package.bytes);
					if(ret || comEnterCount>2)
					{
						result = 0;//成功
						comEnterCount = 0;
						comEnterStep = e_nb_GSN;
					}
				}
				else
				{
						result = 0;
						comEnterCount = 0;
						comEnterStep = e_nb_CCLK;					
				}

		}break;
//---------------------------------------------------------------------------------				
		case e_nb_CCLK:
		{
			
		//	if(comEnterCount < 6)
			{
				uart_tx_string("AT+QNTP=1,\"192.168.111.2\",123,1\r\n");
				wait_return(5);
				ret = getModuleTime(BLOOD_Package.bytes);
				comEnterStep = e_nb_GSN;
			}

		}break;

//---------------------------------------------------------------------------------			
		case e_nb_GSN:
		{
			
			if(comEnterCount < 6)
			{
				uart_tx_string("AT+CGSN\r\n");
				wait_return(1);
				ret = getIMEI(BLOOD_Package.bytes,sizeof(BLOOD_Package));
				if(ret == 1)//获取成功
				{
					result = 0;
					comEnterCount = 0;
					
					comEnterStep = e_nb_QHTTPURL;

				}

			}
			else
			{
				result = 23;
				stopGSMTask();
			}
		}break;

//---------------------------------------------------------------------------------	
		case e_nb_QHTTPURL:
		{
			uart_tx_string("AT+QHTTPURL=35,80\r\n");
			for(i = 0;i < 10; i++)//10 * 1000 = 10S
			{	
				WDR();
				wait_return(5);		
				if(strstr(&BLOOD_Package.bytes,"CONNECT"))
				{
					result = 0;//成功
					comEnterCount = 0;
					
					comEnterStep = e_nb_QHTTPURL1;
					break;
				}
				else if(strstr(BLOOD_Package.bytes,"ERROR"))
				{
					errCount ++;
					if(errCount <= 3)
					{
						result = 0;
						comEnterStep = e_nb_QHTTPURL;
						break;
					}
					else if(errCount > 3)
					{					
						result = 24;
						stopGSMTask();
					}
					break;
				}
				clnUartBuf();
			}
			if(i == 10)
			{
				result = 25;
				stopGSMTask();
			}
		};break;
//---------------------------------------------------------------------------------				
		case e_nb_QHTTPURL1:
		{
				result = 19;
				stopGSMTask();
				uart_time=0;
				uart_tx_string("https://api.tellihealth.com/bioland\r\n");
				while(uart_time<15)
					{
						wait_return(1);		
						if(strstr(&BLOOD_Package.bytes,"OK"))
						{
							result = 0;//成功
							comEnterCount = 0;
							comEnterStep = e_nb_QHTTPPOST;
							clnUartBuf();
							
							break;
						}
						
					}


			
		};break;
//---------------------------------------------------------------------------------	
		case e_nb_QHTTPPOST:
		{
				result = 20;
				stopGSMTask();
				uart_time=0;
			//uart_tx_string("AT+QHTTPPOST=278,30,30\r");
			uart_tx_string("AT+QHTTPPOST=250,30,30\r\n");
			while(uart_time<30)
			{
				WDR();
				wait_return(1);		
				if(strstr(BLOOD_Package.bytes,"CONNECT"))//30秒的时间从接收到CONNECT开始计算
				{
					errCount = 0;
					result = 0;//成功
					comEnterCount = 0;
					clnUartBuf();
					comEnterStep = e_nb_QHTTPPOST1;
					break;
				}
				else if(strstr(BLOOD_Package.bytes,"ERROR"))
				{
					result = 0;
					comEnterCount = 0;
					comEnterStep = e_nb_QHTTPURL;
					clnUartBuf();
					errCount ++;
					if(errCount > 3)
					{
						errCount = 0;
						result = 26;
						stopGSMTask();
					}
					break;
				}
				else if(strstr(BLOOD_Package.bytes,"+QIURC:"))
				{
					result = 0;
					comEnterCount = 0;
					comEnterStep = e_nb_QHTTPURL;
					clnUartBuf();
					errCount ++;
					if(errCount > 3)
					{
						errCount = 0;
						result = 27;
						stopGSMTask();
					}
					break;
				}
				
			}


			
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_QHTTPPOST1:
		{
			uart_tx_string((uchar *)urlHead);
			
			uart_tx_string((uchar *)imei);
			uart_tx_string((uchar *)httptemp);
			
			uart_tx_string((uchar *)sn);					
			memset(httptemp,0,sizeof(httptemp));

			httptemp[0] = '\"';
			httptemp[1] = hexToAscii(productYear / 16);//年
			httptemp[2] = hexToAscii(productYear % 16);//年
			httptemp[3] = (productMonth - 1) + 'A';
			httptemp[4] = Project_Sequence / 100000 + '0';
			httptemp[5] = Project_Sequence / 10000 % 10 + '0';
			httptemp[6] = Project_Sequence / 1000 % 10 + '0';
			httptemp[7] = Project_Sequence / 100 % 10 + '0';
			httptemp[8] = Project_Sequence /10 % 10 + '0';
			httptemp[9] = Project_Sequence % 10 + '0';
			httptemp[10] = '\"';//年
			uart_tx_string((uchar *)httptemp);	

			uart_tx_string((uchar *)checkTime);
			memset(httptemp,0,sizeof(httptemp));		
			if(buff==11)
			{
				httptemp[0] = '\"';
				httptemp[1] = sys_Year/1000 + 0x30;
				httptemp[2] = sys_Year%1000/100 + 0x30;
				httptemp[3] = sys_Year%100/10 + 0x30;
				httptemp[4] = sys_Year%10 + 0x30;
				httptemp[5] = sys_Month/10 + 0x30;
				httptemp[6] = sys_Month%10 + 0x30;
				httptemp[7] = sys_Day/10 + 0x30;
				httptemp[8] = sys_Day%10 + 0x30;
				httptemp[9] = sys_Hour/10 + 0x30;
				httptemp[10] = sys_Hour%10 + 0x30;
				httptemp[11] = sys_Minute/10 + 0x30;
				httptemp[12] = sys_Minute%10 + 0x30;
				httptemp[13] = sys_Second/10 + 0x30;
				httptemp[14] = sys_Second%10 + 0x30;
				httptemp[15] = '\"';
			}
			else
			{
				buff -= 1;
				bloodVal = Get_Memroy(buff);
				httptemp[0] = '\"';
				httptemp[1] = (2016 + test_buff[0])/1000 + '0';
				httptemp[2] = (2016 + test_buff[0])%1000/100 + '0';
				httptemp[3] = (2016 + test_buff[0])%100/10 + '0';
				httptemp[4] = (2016 + test_buff[0])%10 + '0';//年
				httptemp[5] = test_buff[1]/10 + '0';
				httptemp[6] = test_buff[1]%10 + '0';//月
				httptemp[7] = test_buff[2]/10 + '0';
				httptemp[8] = test_buff[2]%10 + '0';//日
				httptemp[9] = test_buff[3]/10 + '0';
				httptemp[10] = test_buff[3]%10 + '0';//时
				httptemp[11] = test_buff[4]/10 + '0';
				httptemp[12] = test_buff[4]%10 + '0';//分
				httptemp[13] = test_buff[5]/10 + '0';
				httptemp[14] = test_buff[5]%10 + '0';//秒
				httptemp[15] = '\"';
				//bloodVal = (test_buff[6]<<8)|test_buff[7];
			}
			uart_tx_string((uchar *)httptemp);

			uart_tx_string((uchar *)checkData);
			uart_tx_string((uchar *)bloodSugarVal); 
			memset(httptemp, 0, sizeof(httptemp));
			if(buff == 11)
				getBloodSuger(Blood_glucose,httptemp);	//现在的 
			else
				getBloodSuger(bloodVal,httptemp);			//历史记录
			uart_tx_string((uchar *)httptemp);

			uart_tx_string((uchar *)b_O_AfterMeal); 		
			memset(httptemp, 0, sizeof(httptemp));
			if(SystemFlags.Datas.Flags.Bits.Before == 0)	//餐后
				memcpy(httptemp, "\" after\"", sizeof("\" after\""));
			else											//餐前
				memcpy(httptemp, "\"before\"", sizeof("\"before\""));
			uart_tx_string((uchar *)httptemp);
			
			uart_tx_string((uchar *)huanhangkong);
			uart_tx_string((uchar *)dakuohao);
			uart_tx_string((uchar *)huanhang);
			uart_tx_string((uchar *)dakuohao);
			uart_tx_string((uchar *)huanhang);

			result = 0;
			comEnterCount = 0;
			comEnterStep = e_nb_QHTTPREAD;
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_QHTTPREAD:
		{	
			for(i = 0;i < 150; i++)//150*200 = 30S
			{
				WDR();
				wait_return(1);	
				ret = getServerCallback(BLOOD_Package.bytes,sizeof(BLOOD_Package));				
				if(ret == 0)
				{
					result = 0;
					comEnterCount = 0;
					comEnterStep = e_nb_END;
					clnUartBuf();
					break;
				}
				else if(ret != 6)//收到错误的时候
				{
					if(comRestartCount<3)
					{
						comRestartCount ++;
						result = 0;
						comEnterCount = 0;
						comEnterStep = e_nb_QHTTPURL;//重发
						clnUartBuf();
						break;
					}
					else
					{
						result = 28;
						comRestartCount = 0;
						comEnterCount = 0;
						comEnterStep = e_nb_END;
						clnUartBuf();
						break;
					}
				}
			}
			if(i == 150)//超时没收到的情况
			{
				result = 24;
				stopGSMTask();	
			}
		};break;
//---------------------------------------------------------------------------------			
		case e_nb_END:
		{
			if(result != 0)
				result = 29;
			comEnterStep = e_nb_END;
			comEnterCount = 0;
			clnUartBuf();
		};break;
//---------------------------------------------------------------------------------			
	}
	return result;
}


