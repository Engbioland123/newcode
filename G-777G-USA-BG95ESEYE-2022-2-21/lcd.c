#include "HT45F67.h"
#include "Defineport.h"
#include "LCD.h"
#include "uart.h"
#include "string.h"

const uchar number_tabR[11]=
				{
					0b00000101,//0
					0b00000000,//1
					0b00000011,//2
					0b00000010,//3
					0b00000110,//4
					0b00000110,//5
					0b00000111,//6
					0b00000000,//7
					0b00000111,//8
					0b00000110,//9
					0b00000000,// 
				};
const uchar number_tabL[11]=
				{
					0b00001111,//0
					0b00000110,//1
					0b00001101,//2
					0b00001111,//3
					0b00000110,//4
					0b00001011,//5
					0b00001011,//6
					0b00001110,//7
					0b00001111,//8
					0b00001111,//9
					0b00000000,// 
				};
const uchar number_tabR2[11]=
				{
					0b00000110,//0
					0b00000000,//1
					0b00000010,//2
					0b00000000,//3
					0b00000100,//4
					0b00000100,//5
					0b00000110,//6
					0b00000000,//7
					0b00000110,//8
					0b00000100,//9
					0b00000000,// 
				};
const uchar number_tabM[11]=
				{
					0b00001000,//0
					0b00000000,//1
					0b00001010,//2
					0b00001010,//3
					0b00000010,//4
					0b00001010,//5
					0b00001010,//6
					0b00001000,//7
					0b00001010,//8
					0b00001110,//9
					0b00000000,// 
				};
const uchar number_tabL2[11]=
				{
					0b00000111,//0
					0b00000110,//1
					0b00000101,//2
					0b00000111,//3
					0b00000110,//4
					0b00000011,//5
					0b00000011,//6
					0b00000110,//7
					0b00000111,//8
					0b00000111,//9
					0b00000000,// 
				};
				
const small_number_tab[10]=
{
	0xFA,0x60,0xD6,0xF4,0x6C,0xBC,0xBE,0xE0,0xFE,0xFC
};
__attribute__((interrupt(0x20)))
void isr_timer_base0 (void)
{
//	_pb5=1;
	sys_time++;
	if(sys_time>3)
	{
		sys_time=0;
		uart_time++;
		if(SystemFlags.Datas.Flags.Bits.CHRC)
       	{
       		SystemFlags.Datas.Battery_Val++;
       		if(SystemFlags.Datas.Battery_Val>3)
       		{
       			SystemFlags.Datas.Battery_Val=0;	
       		}
       	}
		if(SystemFlags.Datas.Flags.Bits.flash_flag)
		{
			SystemFlags.Datas.Flags.Bits.flash_flag=0;	
		}
		else
		{
			SystemFlags.Datas.Flags.Bits.flash_flag=1;	
		}
		Second++;
		if(SystemFlags.Datas.Flags.Bits.Send_begin)
		{
			Gsm_timer++;	
		}
		sys_Second++;
	   	if(sys_Second>59)
		{
			sys_Second=0;
			sys_Minute++;
			if(sys_Minute>59)
			{
				sys_Minute=0;
				sys_Hour++;
			}
		}	
    }
//	_pb5=0;
}
void show_display()
{
	uchar i,a=0;
	for(i=0;i<16;i++)
	{
		LcdRam[a]=disp_buff[i]&0x0f;
		if(SystemFlags.Datas.Flags.Bits.flash_flag)
		{
			LcdRam[a]&=flash[i]|0xf0;
		}
		a+=1;
		LcdRam[a]=disp_buff[i]>>4;
		if(SystemFlags.Datas.Flags.Bits.flash_flag)
		{
			LcdRam[a]&=flash[i]>>4;
		}
		a+=1;
	}	
}
void show_battery()
{
	if(SystemFlags.Datas.Battery_Val>0)
	{
		disp_buff[15]|=0b00000001;//��ص�һ��
	}
	if(SystemFlags.Datas.Battery_Val>1)
	{
		disp_buff[13]|=0b00000001;//��صڶ���
	}
	if(SystemFlags.Datas.Battery_Val>2)
	{
		disp_buff[11]|=0b00010000;//��ص�����
	}
	disp_buff[3]|=0b10000000;//������	
}

void displey_YES()
{
	disp_buff[0]=0B01100000;
	disp_buff[1]=0B01110111;
	disp_buff[2]=0B01001001;
	disp_buff[3]=0B00111010;
	show_battery();
	show_display();	
}
void displey_test()
{
	disp_buff[0]=0B00110000;
	disp_buff[1]=0B01110000;
	disp_buff[2]=0B01001001;
	disp_buff[3]=0B10111110;
	show_battery();
	show_display();	
}
void displey_DEL()
{
	disp_buff[0]=0B00110000;
	disp_buff[1]=0B01110111;
	disp_buff[2]=0B01101001;
	disp_buff[3]=0B00010000;
	disp_buff[4]=0B00000000;
	disp_buff[5]=0B00001000;
	flash[5]	=0B11110111;
	show_battery();
	show_display();
}
void displey_EB()
{
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B00101001;
	disp_buff[2]=0B01100000;
	disp_buff[3]=0B00110010;	
	show_battery();
	show_display();
}
void displey_EU()
{
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B00101001;
	disp_buff[2]=0B01100000;
	disp_buff[3]=0B01110000;
	show_display();	
}

void Show_OFF()
{
	memset(disp_buff,0,16);
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B01111111;
	disp_buff[2]=0B01101000;
	disp_buff[3]=0B00001110;
	show_battery();
	show_display();	
}

void Show_VER()//�ϵ���ʾ�汾��
{ 		
	/*disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B01110110;
	disp_buff[3]=0B01111000; V1.0 
	
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B00010110;
	disp_buff[3]=0B01100000;  //V1.1
	
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B00110110;
	disp_buff[3]=0B01011010;  //V1.2
	
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B00010110;
	disp_buff[3]=0B01111010;  //V1.3
	
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B01010110;
	disp_buff[3]=0B01100010;  //V1.4
	
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B01010110;
	disp_buff[3]=0B00111010;  //V1.5
	
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B01110110;
	disp_buff[3]=0B00111010;  //V1.6

	disp_buff[0]=0B01010000;
	disp_buff[1]=0B00000111;
	disp_buff[2]=0B00010110;
	disp_buff[3]=0B01101000;  //V1.7
*/
//	disp_buff[0]=0B01010000;
//	disp_buff[1]=0B00000111;
//	disp_buff[2]=0B01110110;
//	disp_buff[3]=0B01111010;  //V1.8

// bumb 1--HOD14826D.dwg
// xFGE
// ABCD
LcdRam[1]=0b0101;//u 
LcdRam[2]=0b0111;//   
// bumb 2
// xFGE
// ABCD
LcdRam[3]=0b0000;//1
LcdRam[4]=0b0110;
//bumb 3
//xFEs 
//AxGx
//xBCD
LcdRam[5]=0b0110;//8
LcdRam[5]|=0b0001;//p1
LcdRam[6]|=0b1010;
LcdRam[7]|=0b0111;

//LcdRam[0]=0b1111;
//LcdRam[1]=0b1111;
//
//LcdRam[2]=0b1111;
//LcdRam[3]=0b1111;
//
//LcdRam[4]=0b1111;
//LcdRam[5]|=0b1111;
//LcdRam[6]|=0b1111;
//LcdRam[7]|=0b1111;

//	show_display();
}
void Show_Et()
{
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B00101001;
	disp_buff[2]=0b11100000;
	disp_buff[3]=0B00010111;
	show_display();
}
void Show_EF()
{
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B00101001;
	disp_buff[2]=0b01100000;
	disp_buff[3]=0B10001110;
	show_display();
}
void Show_EE()
{
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B00101001;
	disp_buff[2]=0b01100000;
	disp_buff[3]=0B00011010;
	show_display();
}
void Show_000()
{
	disp_buff[0]=0B00100000;
	disp_buff[1]=0B00100000;
	disp_buff[2]=0b00000000;
	disp_buff[3]=0B00000110;
	show_display();
}
void Show_CLOSE()//
{
	memset(disp_buff,0,16);
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B01011001;
	disp_buff[2]=0B11000001;
	disp_buff[3]=0B00111110;
	show_battery();
	show_display();
}
void Show_OPEN()//
{
	memset(disp_buff,0,16);
	disp_buff[0]=0B00110000;
	disp_buff[1]=0B01110011;
	disp_buff[2]=0B01101100;
	disp_buff[3]=0B01101000;
	show_battery();
	show_display();
}
void Show_END()
{
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B01011001;
	disp_buff[2]=0b00101110;
	disp_buff[3]=0B11110010;
	show_display();	
}
void Show_PC()//
{
	memset(disp_buff,0,16);
	disp_buff[0]=0B01110000;
	disp_buff[1]=0B01011100;
	disp_buff[2]=0B00001001;
	show_display();
}
void Show_usb()//
{
	memset(disp_buff,0,16);
	disp_buff[0]=0B01010000;
	disp_buff[1]=0B01100111;
	disp_buff[2]=0B01101011;
	disp_buff[3]=0B00110010;
	show_display();
}

void transformation()//��Ѫ��ֵ�²�����
{
	uint k;
	if(SystemFlags.Datas.CTL_mode==0)
	{
		k=Blood_glucose*100*Temperature_coefficient/10000;//���¶�ϵ������ѪҺϵ��
		Blood_glucose=k;	
	}
	if(SystemFlags.Datas.CTL_mode)
	{
		k=Blood_glucose*100*Temperature_CTL_coefficient/10000;//���¶�ϵ����ֵ��ϵ��
		Blood_glucose=k;	
	}
}

void Update_time()
{
	uchar i,i2,a,b,c,d;
	ushort k;

	i=sys_Month/10;
	if(i)
	{
		if(i==1)
		{
			disp_buff[5]|=0b01100000;	//�·�ʮλ
		}
		if(i==2)
		{
			disp_buff[5]|=0b11000000;	//�·�ʮλ
		}
	}
	else
	{
		disp_buff[5]&=0x1f;				//�·�ʮλ
	}
	i=sys_Month%10;	
	disp_buff[6]=small_number_tab[i];	//�·ݸ�λ
	i=sys_Day/10;
	disp_buff[10]=small_number_tab[i]<<4;	//����ʮλ
	disp_buff[10]|=0b00010000;//��������-��
	disp_buff[11]=small_number_tab[i]>>4;
			
	i=sys_Day%10;
	i2=disp_buff[11];
	disp_buff[11]=small_number_tab[i]<<4;	//���ڸ�λ
	disp_buff[11]|=i2;
	disp_buff[12]=small_number_tab[i]>>4;
	i=sys_Hour/10;
	if(i)
	{
		if(i==1)
		{
			disp_buff[12]|=0b01100000;	//ʱ��ʮλ
		}
		if(i==2)
		{
			disp_buff[12]|=0b11000000;	//ʱ��ʮλ
		}
	}
	else
	{
		disp_buff[12]&=0x0f;			//ʱ��ʮλ
	}
	i=sys_Hour%10;	
	disp_buff[13]=small_number_tab[i];	//ʱ�Ӹ�λ

	i=sys_Minute/10;
	disp_buff[14]=small_number_tab[i];	//����ʮλ
	disp_buff[14]|=1;	//����ʱ��:��

	i=sys_Minute%10;	
	disp_buff[15]=small_number_tab[i];	//���Ӹ�λ
}

//��flagΪ0ʱ����ʾP���ݣ�Ϊ1ʱ����ʾdat���ݣ�Ϊ2ʱ����ʾѪ��mgdl,Ϊ3ʱ����ʾѪ��mgdl

//��flagΪ0ʱ����ʾP���ݣ�  6λ���к�
//��flagΪ1ʱ����ʾdat���ݣ�3λ������
//��flagΪ2ʱ����ʾѪ��mgdl,
//��flagΪ3ʱ����ʾѪ��mmol,��ʾϵͳʱ��
//��flagΪ4ʱ����ʾѪ��mmol,��ʾ����ʱ��
void Show_Big_number(uchar *p,ushort dat,uchar flag)
{
	uchar i,i2,a,b,c,d;
	ushort k;
	if(flag==0)//
	{
		if(p[0]>10)
		{
			for(i=0;i<16;i++)
			{
				disp_buff[i]=0;
			}
			i=sys_Month/10;
			if(i)
			{
				if(i==1)
				{
					disp_buff[5]|=0b01100000;	//�·�ʮλ
				}
				if(i==2)
				{
					disp_buff[5]|=0b11000000;	//�·�ʮλ
				}
			}
			else
			{
				disp_buff[5]&=0x1f;				//�·�ʮλ
			}
			i=sys_Month%10;	
			disp_buff[6]=small_number_tab[i];	//�·ݸ�λ
			i=sys_Day/10;
			disp_buff[10]=small_number_tab[i]<<4;	//����ʮλ
			disp_buff[10]|=0b00010000;//��������-��
			disp_buff[11]=small_number_tab[i]>>4;
			
			i=sys_Day%10;
			i2=disp_buff[11];
			disp_buff[11]=small_number_tab[i]<<4;	//���ڸ�λ
			disp_buff[11]|=i2;
			disp_buff[12]=small_number_tab[i]>>4;
			i=sys_Hour/10;
			if(i)
			{
				if(i==1)
				{
					disp_buff[12]|=0b01100000;	//ʱ��ʮλ
				}
				if(i==2)
				{
					disp_buff[12]|=0b11000000;	//ʱ��ʮλ
				}
			}
			else
			{
				disp_buff[12]&=0x0f;			//ʱ��ʮλ
			}
			i=sys_Hour%10;	
			disp_buff[13]=small_number_tab[i];	//ʱ�Ӹ�λ
			
			i=sys_Minute/10;
			disp_buff[14]=small_number_tab[i];	//����ʮλ
			disp_buff[14]|=1;	//����ʱ��:��
			
			i=sys_Minute%10;	
			disp_buff[15]=small_number_tab[i];	//���Ӹ�λ
		}
		else
		{
			for(i=0;i<2;i++)//���ֵ�1��2��
			{
				b=number_tabL[p[i+3]];
				b<<=4;
				b|=number_tabR[p[i+3]];
				disp_buff[i]|=b<<4;
				disp_buff[i+1]|=b>>4;
			}
			b=number_tabM[p[5]];
			b<<=4;
			b|=number_tabR2[p[5]];
			disp_buff[2]|=b<<4;
			
			disp_buff[3]|=b>>4;
			b=number_tabL2[p[5]];
			b<<=4;
			disp_buff[3]|=b;//���ֵ�3��
			
			disp_buff[13]=small_number_tab[p[0]];//ʱ�Ӹ�λ
			disp_buff[14]=small_number_tab[p[1]];//����ʮλ
			disp_buff[15]=small_number_tab[p[2]];//���Ӹ�λ
		}
		if(SystemFlags.Datas.Flags.Bits.Test_paper)
		{
			flash[2]&=0b01111111;//��ֽ����
			disp_buff[2]|=0b10000000;//��ֽ��	
		}
		if(SystemFlags.Datas.Flags.Bits.Blood_drop)
		{
			disp_buff[1]|=0b10000000;//��Ѫ	
		}
//		disp_buff[4] |=0b00000100; //mmol
		disp_buff[4] |=0b00001000; //mg/dl��2020��9��28��13:58:17

	}
	else if(flag==1)//
	{
		disp_buff[0]=0;
		disp_buff[1]=0;
		disp_buff[2]=0;
		c=dat/100;
		if(c>0)
		{
			b=number_tabL[c];
			b<<=4;
			b|=number_tabR[c];
			disp_buff[0]|=b<<4;
			disp_buff[1]|=b>>4;	
		}
		c=dat%100/10;
		b=number_tabL[c];
		b<<=4;
		b|=number_tabR[c];
		disp_buff[1]|=b<<4;
		disp_buff[2]|=b>>4;	
		
		disp_buff[2]&=0x0f;
		disp_buff[3]=0;
		c=dat%10;	
		b=number_tabM[c];
		b<<=4;
		b|=number_tabR2[c];
		disp_buff[2]|=b<<4;
		
		disp_buff[3]|=b>>4;
		b=number_tabL2[c];
		b<<=4;
		disp_buff[3]|=b;
	}
	else if(flag>1)//
	{
		SystemFlags.Datas.Flags.Bits.point=0;//��ҪС����
		if((Blood_glucose>18)&&(Blood_glucose<601))
		{
		/*	if(flag==2)//
			{
				a=Blood_glucose%1000/100;
				b=Blood_glucose%1000%100/10;
				c=Blood_glucose%1000%100%10;
				SystemFlags.Datas.Flags.Bits.point=0;
			}*/
		//	if(flag==3)//
			{
				
//				k=Blood_glucose*100/18;
				k=Blood_glucose*100;//1 mmol/l = 18mg/dl;
				k = k/10;			  //��ҪС����
				c=k%1000%100%10;
				if(c>4)
				{
					k+=10;	
				}
				k/=10;
				a=k%1000/100;
				b=k%1000%100/10;
				c=k%1000%100%10;
			}
		#if 1
			if(a>0)	
			{
				disp_buff[0]=0;
				disp_buff[1]=0;
				disp_buff[2]=0;
				i=number_tabL[a];
				i<<=4;
				i|=number_tabR[a];
				disp_buff[0]|=i<<4;
				disp_buff[1]|=i>>4;
			}
			else
			{
				disp_buff[0]&=0x0f;
				disp_buff[1]=0;
				disp_buff[2]=0;
			}
			i=number_tabL[b];
			i<<=4;
			i|=number_tabR[b];
			disp_buff[1]|=i<<4;
			i>>=4;
			disp_buff[2]|=i;
			
			i=number_tabR2[c];
			i<<=4;
			i|=(disp_buff[2]&0x0f);
			disp_buff[2]=i;
			i=number_tabL2[c];
			i<<=4;
			i|=number_tabM[c];
			disp_buff[3]=i;
		#else
			
		#endif
		}
		
		if(Blood_glucose>600)
		{
			disp_buff[0]=0B01110000;
			disp_buff[1]=0B01010110;
			disp_buff[2]=0;
			disp_buff[3]=0;
		}
		if(Blood_glucose<19)
		{
			disp_buff[0]=0B01010000;
			disp_buff[1]=0B00110001;
			disp_buff[2]=0B00000011;
			disp_buff[3]=0;
		}
		if(Blood_glucose>240)
		{
			disp_buff[4]|=0b00000010;//ͪ�徯ʾ
		}
		if(SystemFlags.Datas.GSM_Signal>9)
		{
			disp_buff[4]|=0b10000000;//�źŵ�һ��	
		}
		if(SystemFlags.Datas.GSM_Signal>10)
		{
			disp_buff[5]|=0b00000001;//�źŵڶ���	
		}
		if(SystemFlags.Datas.GSM_Signal>15)
		{
			disp_buff[5]|=0b00000010;//�źŵ�����	
		}
		if(SystemFlags.Datas.GSM_Signal>25)
		{
			disp_buff[5]|=0b00000100;//�źŵ��ĸ�	
		}
		if(SystemFlags.Datas.Flags.Bits.Show_Memory)
		{
			disp_buff[5]|=0b00001000;//�鿴����
		}
		if(SystemFlags.Datas.Flags.Bits.point)
		{
			if((Blood_glucose>18)&&(Blood_glucose<601))
			{
				disp_buff[2]|=0b00010000;//��ʾС����
			}
			//disp_buff[4] |=0b00000100; //mmol	
			disp_buff[4] |=0b00001000; //mg/dl	
		}
		else
		{
			disp_buff[2]&=0b11101111;//ȥ��С����
//			disp_buff[4] |=0b00000100; //mmol
			disp_buff[4] |=0b00001000; //mg/dl
		}
		if(SystemFlags.Datas.Flags.Bits.GSM_Send_over)//���ǲ���ת�书��
		{
			disp_buff[0]|=0b10000000;//���߷�
			if(SystemFlags.Datas.Flags.Bits.Memory_Send)
			{
				disp_buff[4] |=0b00010000; //��������ʾ
				flash[4]    &=0b11101111;
			}
			else
			{
				disp_buff[4]&=0b11101111;
				if(SystemFlags.Datas.Flags.Bits.GSM_Send_OK)
				{
					disp_buff[4]|=0b00100000;//���ͳɹ�	
				}
				else
				{
					disp_buff[4]|=0b01000000;//����ʧ��	
				}	
			}	
		}
		if(flag!=4)
		{
			i=sys_Month/10;
		}
		else
		{
			i=test_buff[1]/10;	
		}
		if(i)
		{
			if(i==1)
			{
				disp_buff[5]|=0b01100000;	//�·�ʮλ
			}
			if(i==2)
			{
				disp_buff[5]|=0b11000000;	//�·�ʮλ
			}
		}
		else
		{
			disp_buff[5]&=0x1f;				//�·�ʮλ
		}
		if(flag!=4)
		{
			i=sys_Month%10;	
		}
		else
		{
			i=test_buff[1]%10;		
		}
		disp_buff[6]=small_number_tab[i];	//�·ݸ�λ
		if(flag!=4)
		{
			i=sys_Day/10;
		}
		else
		{
			i=test_buff[2]/10;	
		}
		disp_buff[10]=small_number_tab[i]<<4;	//����ʮλ
		disp_buff[10]|=0b00010000;//��������-��
		disp_buff[11]=small_number_tab[i]>>4;
		if(flag!=4)
		{
			i=sys_Day%10;
		}
		else
		{
			i=test_buff[2]%10;		
		}
		i2=disp_buff[11];
		disp_buff[11]=small_number_tab[i]<<4;	//���ڸ�λ
		disp_buff[11]|=i2;

		disp_buff[12]=small_number_tab[i]>>4;
		if(flag!=4)
		{
			i=sys_Hour/10;
		}
		else
		{
			i=test_buff[3]/10;		
		}
		if(i)
		{
			if(i==1)
			{
				disp_buff[12]|=0b01100000;	//ʱ��ʮλ
			}
			if(i==2)
			{
				disp_buff[12]|=0b11000000;	//ʱ��ʮλ
			}
		}
		else
		{
			disp_buff[12]&=0x0f;			//ʱ��ʮλ
		}
		if(flag!=4)
		{
			i=sys_Hour%10;	
		}
		else
		{
			i=test_buff[3]%10;	
		}
		disp_buff[13]=small_number_tab[i];	//ʱ�Ӹ�λ
		if(flag!=4)
		{
			i=sys_Minute/10;
		}
		else
		{
			i=test_buff[4]/10;	
		}
		disp_buff[14]=small_number_tab[i];	//����ʮλ
		disp_buff[14]|=1;	//����ʱ��:��
		if(flag!=4)
		{
			i=sys_Minute%10;
		}
		else
		{
			i=test_buff[4]%10;	
		}	
		disp_buff[15]=small_number_tab[i];	//���Ӹ�λ
	}

	if(flag != 1)
	{
		if(dat != 1)
		{
			if(SystemFlags.Datas.Flags.Bits.Before > 0)
			{
				disp_buff[4] |= 0b00000001; //��ǰ
				disp_buff[5] &= 0b11101111; //�ͺ�
			}
			else
			{
				disp_buff[4] &= 0b11111110; //��ǰ
				disp_buff[5] |= 0b00010000; //�ͺ�
			}
		}
		else
		{
			disp_buff[4] &= 0b11111110; //��ǰ
			disp_buff[5] &= 0b11101111; //�ͺ�
		}
	}
	
	show_battery();
}
