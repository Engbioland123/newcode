#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

                 	//;	-CBEDGFA
#define	Display_0	0b01111011	//;0
#define	Display_1	0b01100000	//;1
#define	Display_2	0b00111101	//;2
#define	Display_3	0b01101101	//;3
#define	Display_4	0b01100110	//;4
#define	Display_5	0b01001111	//;5
#define	Display_6	0b01011111	//;6
#define	Display_7	0b01100001	//;7
#define	Display_8	0b01111111	//;8
#define	Display_9	0b01101111	//;9
#define	Display_a	0b01110111	//;A
#define	Display_b	0b01011110	//;B
#define	Display_c	0b00011011	//;C
#define	Display_d	0b01111100	//;D
#define	Display_e	0b00011111	//;E
#define	Display_f	0b00010111	//;F
//			;	-CBEDGFA
#define	Display_all_off	0b00000000	//;10h	;not display
#define	Display_P	0b00110111	//;11h	;P
#define	Display_L	0b00011010	//;12h	;L
#define	Display__	0b00000100	//;13h	;-
#define	Display_r	0b00010100	//;14h	;r
#define	Display_o	0b01011100	//;15h	;o  
#define	Display_H	0b00011110	//;16h	;H  
#define	Display_J	0b00000100	//;17h 	;J   
#define	Display_U	0b01111010 	//;18h	;U 
#define	Display_n	0b01010100	//;19h 	;n
#define	Display_uu	0b01011000	//;1Ah	;u
#define	Display_y	0b01101110	//;1Bh	;y
#define	Display_t	0b00000100	//;1Ch 	;n	
	
	
	
const	uint8	display_num[29]= {Display_0,Display_1,Display_2,Display_3,Display_4,Display_5,
Display_6,Display_7,Display_8,Display_9,Display_a,Display_b,Display_c,Display_d,Display_e,
Display_f,Display_all_off,Display_P,Display_L,Display__,Display_r,Display_o,Display_H,
Display_J,Display_U,Display_n,Display_uu,Display_y,Display_t};

uint16 mmhg_chance_kpa(uint16 pre)	   //单位转换
{
 uint16 i=0;
 i=pre*100/75;
 return(i);
}                              

void disp_pu(uint16 da)	      //DIA位置显示数值,da是16进制数0-199
{
	 R_TEMPDATA.Val=da;
	 SBR_DISP_PLUSE_ON();  //   disp_pu(88);	
}
void disp_dia(uint16 da)	   //DIA竚?ボ?,da琌16??0-399
{ 	 
	if(mmHg_Kpa==0)
     {				   
        SBR_DISP_DP2_OFF();
	    SBR_DISP_DOT_DIA_ON();
	    SBR_DISP_DOT_KPA_OFF();		   
        R_TEMPDATA.Val=da;
	    SBR_DISP_DIA_ON();
     }
     else
       {
	     R_TEMPDATA.Val=mmhg_chance_kpa(da);	              //?琌???KPA10
         SBR_DISP_DP2_ON();
	     SBR_DISP_DOT_DIA_OFF();
	     SBR_DISP_DOT_KPA_ON();	
         SBR_DISP_DIA_ON();
         if(R_TEMPDATA.Val<10)
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
}

void disp_sys(uint16 da)	    //SYS竚?ボ?,da琌16??0-399
{
	 if(mmHg_Kpa==0)
     {
       R_TEMPDATA.Val=da;
       SBR_DISP_DP1_OFF();
	   SBR_DISP_SYS_ON();
     }
     else
       {
	      R_TEMPDATA.Val=mmhg_chance_kpa(da);	              //?琌???KPA10
	      SBR_DISP_DP1_ON();
          SBR_DISP_SYS_ON();
         if(R_TEMPDATA.Val<10)
           {
				_mp1h = 4;
				_mp1l = 10;
				SFR_iar1.bits.b0 = 1;		
				SFR_iar1.bits.b1 = 1;		
				SFR_iar1.bits.b2 = 1;		
				_mp1l ++;	
				SFR_iar1.bits.b0 = 1;		
				SFR_iar1.bits.b2 = 1;		
				_mp1l ++;				
				SFR_iar1.bits.b2 = 1;		
           }
       }
}

uint8 bian(uint16 da)
  { 
  	uint8 i=0;;
	if(da>159)
	{
		i=8;
	}
	else if(da>149)
	{
		i=7;
	}
	else if(da>139)
	{
		i=6;
	}	
	else if(da>123)
	{
		i=5;
	}
	else if(da>106)
	{
		i=4;
	}
	else if(da>89)
	{
		i=3;
	}
	else if(da>59)
	{
		i=2;
	}
	else
	{
	    i=1;	
	}
	return(i);
 }





// ******************************************************************************************
// ** 函数名称: LCD_init_off
// ** 函数描述: LCD全亮
// ** 输入参数: 无
// ** 输出参数: 无 
// ******************************************************************************************
void LCD_INIT_OFF(void)
{
     uint8 i;
	 for(i=0;i<32;i++)	              //全亮	   
	 {
	    SEG[i].Val=0;
	 }

}
// ******************************************************************************************
// ** 函数名称: LCD_init_on
// ** 函数描述: LCD全亮
// ** 输入参数: 无
// ** 输出参数: 无 
// ******************************************************************************************
void LCD_INIT_ON(void)
{
      uint8 i;
 	 for(i=0;i<32;i++)	              //全亮	   
 	 {
 	    SEG[i].Val=0xFF;
 	 }
}
///////////////////////////////////
//DATA  + COLD  没有COLD
void  SBR_DISP_DOT_COLD_ON()
{
    SEG[3].bits.b1 = 1;
}

void  SBR_DISP_DOT_COLD_OFF()
{
    SEG[3].bits.b1 = 0;
}
//COL
void  SBR_DISP_DOT_COL_ON()
{
    SEG[10].bits.b3 = 1;
}
void  SBR_DISP_DOT_COL_OFF()
{
    SEG[10].bits.b3 = 0;
}

/*JIA S1*/
void  SBR_DISP_DOT_JIA_ON()
{
    SEG[8].bits.b0 = 1;

}
void  SBR_DISP_DOT_JIA_OFF()
{
    SEG[8].bits.b0 = 0;
}

/*JIAN S2*/
void  SBR_DISP_DOT_JIAN_ON()
{
    SEG[22].bits.b1 = 1;
}
void  SBR_DISP_DOT_JIAN_OFF()
{
    SEG[22].bits.b1 = 0;
}

//TIME11p
//void  SBR_DISP_DOT_TIME_ON()
//{
//    SEG[6].bits.b4 = 1;
//}
//
//
//void  SBR_DISP_DOT_TIME_OFF()
//{
//    SEG[6].bits.b4 = 0;
//}


//mmhg mmhg1
void  SBR_DISP_DOT_DIA_ON()
{
    SEG[15].bits.b2 = 1;  
}

void  SBR_DISP_DOT_DIA_OFF()
{
    SEG[15].bits.b2 = 0;
}
//DP1
void  SBR_DISP_DP1_ON()
{
    SEG[12].bits.b0 = 1;
}

void  SBR_DISP_DP1_OFF()
{
    SEG[12].bits.b0 = 0;
}
//DP2
void  SBR_DISP_DP2_ON()
{
    SEG[17].bits.b2 = 1;
}

void  SBR_DISP_DP2_OFF()
{
    SEG[17].bits.b2 = 0;
}

//kpa
void  SBR_DISP_DOT_KPA_ON()
{
    SEG[18].bits.b2 = 1;
}

void  SBR_DISP_DOT_KPA_OFF()
{
    SEG[18].bits.b2 = 0;
}


void  SBR_DISP_DOT_MEMORY_ON()
{
    SEG[23].bits.b3 = 1;
}

void  SBR_DISP_DOT_MEMORY_OFF()
{
    SEG[23].bits.b3 = 0;
}
//H1
void  SBR_DISP_DOT_HEART_ON()
{
    SEG[21].bits.b3 = 1;
}

void  SBR_DISP_DOT_HEART_OFF()
{
    SEG[21].bits.b3 = 0;
}

//H2
void  SBR_DISP_DOT_HEART2_ON()
{
    SEG[20].bits.b3 = 1;
}

void  SBR_DISP_DOT_HEART2_OFF()
{
    SEG[20].bits.b3 = 0;
}

//battery 1
void  SBR_DISP_DOT_LO_ON()
{
    SEG[6].bits.b0 = 1;
}
void  SBR_DISP_DOT_LO_OFF()
{
    SEG[6].bits.b0 = 0;
}
//GPRSTINN
void  SBR_DISP_DOT_GPRST_ON()
{
    SEG[22].bits.b3 = 1;
}
void  SBR_DISP_DOT_GPRST_OFF()
{
    SEG[22].bits.b3 = 0;
} 
//GPRSS
void  SBR_DISP_DOT_GPRSS_ON()
{
    SEG[20].bits.b5 = 1;
}
void  SBR_DISP_DOT_GPRSS_OFF()
{
    SEG[20].bits.b5 = 0;
} 
////TANHAO
//void  SBR_DISP_DOT_TANHAO_ON()
//{
//    SEG[21].bits.b1 = 1;
//}
//
//void  SBR_DISP_DOT_TANHAO_OFF()
//{
//    SEG[21].bits.b1 = 0;
//}

//	X2
//void  SBR_DISP_DOT_BT_ON()
//{
//    SEG[20].bits.b4 = 1;
//}
//void  SBR_DISP_DOT_BT_OFF()
//{
//    SEG[20].bits.b4 = 0;
//} 

//	N3 
void  SBR_DISP_DOT_MOVE_ON()
{
    SEG[22].bits.b2 = 1;
}
void  SBR_DISP_DOT_MOVE_OFF()
{
    SEG[22].bits.b2 = 0;
} 



void  SBR_DISP_DOT_ASCVD_ON()
{
    SEG[20].bits.b4 = 1;
}
void  SBR_DISP_DOT_ASCVD_OFF()
{
    SEG[20].bits.b4 = 0;
} 
void  SBR_DISP_DOT_U2_ON()
{
	SEG[8].bits.b2 = 1;
}
void  SBR_DISP_DOT_U2_OFF()
{
	SEG[8].bits.b2 = 0;
}		
void  SBR_DISP_DOT_U1_ON()
{
	SEG[7].bits.b2 = 1;
}
void  SBR_DISP_DOT_U1_OFF()
{
	SEG[7].bits.b2 = 0;
}
		
		
void  SBR_DISP_DOT_OK_ON()
{
	SEG[21].bits.b5 = 1;
}
void  SBR_DISP_DOT_OK_OFF()
{
	SEG[21].bits.b5 = 0;
}

void  SBR_DISP_DOT_OKQ_ON()
{
	SEG[21].bits.b4 = 1;
}
void  SBR_DISP_DOT_OKQ_OFF()
{
	SEG[21].bits.b4 = 0;
}


////////////////////////////////

//;;******************************************************************************************
//;; 函数名称: SBR_DISP_DOT_WX
//;; 函数描述: 
//;; 输入参数: ACC
//;; 输出参数:此款机型无进度条
//;;******************************************************************************************
//void	SBR_DISP_DOT_WX(uint8 w_level)
//{
//	uint8 i ;
//	UINT8_VAL	DOT_WX_BUFF;
//	DOT_WX_BUFF.Val = 1;
//	for	(i = 0; i<w_level;i++)
//	{
//		DOT_WX_BUFF.Val *= 2;
//	}
//	DOT_WX_BUFF.Val -= 1;
//	//清除S10-S13
////	SEG[22].Val &= 0b11000111;
////	SEG[23].Val &= 0b00000000;		
////	SEG[24].Val &= 0b11100111;
//    SEG[0].bits.b3 = 0;
//    SEG[2].bits.b3 = 0;
//    SEG[11].bits.b3 = 0;
//    SEG[17].bits.b3 = 0;	
//	if(DOT_WX_BUFF.bits.b0)
//	{
//		SEG[0].bits.b3 = 1;
//	}
//	if(DOT_WX_BUFF.bits.b2)
//	{
//		SEG[2].bits.b3 = 1;		
//	}	
//	if(DOT_WX_BUFF.bits.b2)
//	{
//		SEG[11].bits.b3 = 1;		
//	}
//	if(DOT_WX_BUFF.bits.b3)
//	{
//		SEG[17].bits.b3 = 1; 		
//	}	
//
//}
void DISP_SN(void)
{
	LCD_INIT_OFF();	
	
 	r_TempDataH = SBR_EEPROM_READDATA(0x08);  
 	r_Temp0.Val = display_num[r_TempDataH & 0x0F];//'7'; 	//年
	r_Temp1.Val = display_num[(r_TempDataH>>4) & 0x0F];//'1'
	r_Temp2.Val = Display_all_off;
	SBR_DISP_MONTH();
		
	r_TempDataH = SBR_EEPROM_READDATA(0x09);
 	r_Temp0.Val = display_num[r_TempDataH & 0x0F];    //'2'; 	//月
	r_Temp1.Val = display_num[(r_TempDataH>>4) & 0x0F];//'1'
	r_Temp2.Val = Display_all_off;	
	SBR_DISP_DAY();
		
    r_TempDataH = SBR_EEPROM_READDATA(0x0C);
 	r_Temp0.Val = display_num[r_TempDataH & 0x0F];    //'2'
	r_Temp1.Val = display_num[(r_TempDataH>>4) & 0x0F];//'1'
	r_Temp2.Val = Display_all_off;    
	SBR_DISP_SYS();	 	             
			                 							  
    r_TempDataH = SBR_EEPROM_READDATA(0x0B);
 	r_Temp0.Val = display_num[r_TempDataH & 0x0F];    //'4'
	r_Temp1.Val = display_num[(r_TempDataH>>4) & 0x0F];//'3'
	r_Temp2.Val = Display_all_off;    
	SBR_DISP_DIA();	 	   
						
    r_TempDataH = SBR_EEPROM_READDATA(0x0A);				
 	r_Temp0.Val = display_num[r_TempDataH & 0x0F];    //'6'
	r_Temp1.Val = display_num[(r_TempDataH>>4) & 0x0F];//'5'
	r_Temp2.Val = Display_all_off;    
	SBR_DISP_PLUSE();
	
	Delay_ms(20000);
	Delay_ms(20000);
	Delay_ms(20000);
    keyval = key_scan();	
	keyval =0;
	KEYFLAG.Val = 0; 
	do
	{	
	  keyval = key_scan();
	}while(keyval==0);
	keyval =0;
	close_time=17000;
	
}
//;;******************************************************************************************
//;; 函数名称: SBR_DISP_DOT_WX
//;; 函数描述: 
//;; 输入参数: ACC
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_DISP_DOT_BTT(uint8 w_level)
{
	uint8 i ;
	UINT8_VAL	DOT_WX_BUFF;
	DOT_WX_BUFF.Val = 1;
	for	(i = 0; i<w_level;i++)
	{
		DOT_WX_BUFF.Val *= 2;
	}
	DOT_WX_BUFF.Val -= 1;
	//清除S10-S13
    SEG[22].bits.b4 = 0;
    SEG[23].bits.b4 = 0;
	if(DOT_WX_BUFF.bits.b0)
	{
		SEG[22].bits.b4 = 1;
	}
	if(DOT_WX_BUFF.bits.b1)
	{
		SEG[23].bits.b4 = 1;		
	}		

}


//;;******************************************************************************************
//;; 函数名称: SBR_DISP_DOT_WX
//;; 函数描述: 
//;; 输入参数: ACC
//;; 输出参数:此款机型无进度条
//;;******************************************************************************************
void	SBR_DISP_DOT_WX(uint8 w_level)
{
	uint8 i ;
	UINT8_VAL	DOT_WX_BUFF;
	DOT_WX_BUFF.Val = 1;
	for	(i = 0; i<w_level;i++)
	{
		DOT_WX_BUFF.Val *= 2;
	}
	DOT_WX_BUFF.Val -= 1;
	//睲埃w1-w5 
	SEG[23].Val &= 0b00111000;
	SEG[22].Val &= 0b00111110;
	SEG[7].Val &= 0b00111100;
	SEG[6].Val &= 0b00111001;
		
	if(DOT_WX_BUFF.bits.b0)
	{
		SEG[23].bits.b2 = 1;
	}
	if(DOT_WX_BUFF.bits.b1)
	{
		SEG[23].bits.b1 = 1;		
	}	
	if(DOT_WX_BUFF.bits.b2)
	{
		SEG[23].bits.b0 = 1;		
	}
	if(DOT_WX_BUFF.bits.b3)
	{
		SEG[22].bits.b0 = 1;		
	}	
	if(DOT_WX_BUFF.bits.b4)
	{
		SEG[7].bits.b0 = 1;		
	}
	if(DOT_WX_BUFF.bits.b5)
	{
		SEG[7].bits.b1 = 1;		
	}
	if(DOT_WX_BUFF.bits.b6)
	{
		SEG[6].bits.b2 = 1;		
	}
	if(DOT_WX_BUFF.bits.b7)
	{
		SEG[6].bits.b1 = 1;		
	}
	
}
//;;******************************************************************************************
//;; 函数名称: SBR_DISP_DOT_WX
//;; 函数描述: 
//;; 输入参数: ACC
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_DISP_DOT_WX_DIA(uint8 w_level)
{
	uint8 i ;
	UINT8_VAL	DOT_WX_BUFF;
	DOT_WX_BUFF.Val = 1;
	for	(i = 0; i<w_level;i++)
	{
		DOT_WX_BUFF.Val *= 2;
	}
	DOT_WX_BUFF.Val -= 1;
//    SEG[23].Val &= 0b00000111;
//    SEG[24].Val &= 0b00000000;
	if(DOT_WX_BUFF.bits.b0)
	{
		SEG[23].bits.b2 = 0;
	}
	if(DOT_WX_BUFF.bits.b1)
	{
		SEG[23].bits.b1 = 0;		
	}	
	if(DOT_WX_BUFF.bits.b2)
	{
		SEG[23].bits.b0 = 0;		
	}
	if(DOT_WX_BUFF.bits.b3)
	{
		SEG[22].bits.b0 = 0;		
	}	
	if(DOT_WX_BUFF.bits.b4)
	{
		SEG[7].bits.b0 = 0;		
	}
	if(DOT_WX_BUFF.bits.b5)
	{
		SEG[7].bits.b1 = 0;		
	}
	if(DOT_WX_BUFF.bits.b6)
	{
		SEG[6].bits.b2 = 0;		
	}
											
}


//;;******************************************************************************************
//;; 函数名称: _SBR_Disp_E1_ON/OFF,_SBR_Disp_E2_ON/OFF,_SBR_Disp_E3_ON/OFF
//;; 函数描述: 显示E1/E2/E3
//;; 输入参数: 无
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_Disp_E1_OFF()
{
	SBR_DISP_DIA_OFF();
}

void	SBR_Disp_E2_OFF()
{
	SBR_DISP_DIA_OFF();	
}
void	SBR_Disp_E3_OFF()
{
	SBR_DISP_DIA_OFF();	
}
void	SBR_DISP_CLR_ON()
{
	r_Temp0.Val = Display_t;
	r_Temp1.Val = Display_t;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();	

	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;	
	SBR_DISP_SYS();	
}

void	SBR_DISP_E1_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_1;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;	
	SBR_DISP_DIA();	
	SBR_DISP_DP2_OFF();
//	SBR_DISP_DOT_TANHAO_ON();	
}
void	SBR_DISP_E2_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_2;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;	
	SBR_DISP_DIA();	
	SBR_DISP_DP2_OFF();
//	SBR_DISP_DOT_TANHAO_ON();		
}
void	SBR_DISP_E3_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_3;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();		
	SBR_DISP_DP2_OFF();
//	SBR_DISP_DOT_TANHAO_ON();		
}

void	SBR_DISP_E4_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_4;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();		
	SBR_DISP_DP2_OFF();	
//	SBR_DISP_DOT_TANHAO_ON();	
}

void	SBR_DISP_E5_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_5;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();		
	SBR_DISP_DP2_OFF();
//	SBR_DISP_DOT_TANHAO_ON();		
}

void	SBR_DISP_E6_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_6;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();		
	SBR_DISP_DP2_OFF();	
//	SBR_DISP_DOT_TANHAO_ON();	
}

void	SBR_DISP_E7_ON()
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_7;
	r_Temp1.Val = Display_0;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();		
	SBR_DISP_DP2_OFF();
//	SBR_DISP_DOT_TANHAO_ON();		
}
void	SBR_DISP_E_NO(uint8 step1)
{
	r_Temp0.Val = Display_e;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	R_TEMPDATA.Val = step1;
    SBR_DISP_DIA_ON();
	SBR_DISP_DP2_OFF();
//	SBR_DISP_DOT_TANHAO_ON();
	SBR_DISP_PLUSE_OFF();		
}
void	SBR_DISP_U19_ON()
{
	r_Temp0.Val = Display_U;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_0;
	r_Temp1.Val = Display_1;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();	
	SBR_DISP_DP2_ON();	
//	SBR_DISP_DOT_P2_ON();	
}
void	SBR_DISP_NOMON_ON()
{
	r_Temp0.Val = Display_J;
	r_Temp1.Val = Display_J;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	r_Temp0.Val = Display_J;
	r_Temp1.Val = Display_J;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();		

}

void	SBR_DISP_KSK_ON()       //压力比对时用
{
	r_Temp0.Val = Display_H;
	r_Temp1.Val = Display_all_off;
    SBR_DISP_MONTH();

	r_Temp0.Val = Display_H;
	r_Temp1.Val = Display_5;
    SBR_DISP_DAY();
}


void	SBR_DISP_OFF_T_ON()
{
	r_Temp0.Val = Display_0;
	r_Temp1.Val = Display_all_off;
    SBR_DISP_MONTH();

	r_Temp0.Val = Display_f;
	r_Temp1.Val = Display_f;
    SBR_DISP_DAY();
}

void	SBR_DISP_ANO_T_ON()
{
	r_Temp0.Val = Display_a;
	r_Temp1.Val = Display_all_off;
    SBR_DISP_MONTH();
    SBR_DISP_DOT_COLD_ON();
	r_Temp0.Val = Display_n;
	r_Temp1.Val = Display_o;
    SBR_DISP_DAY();
}
void	SBR_DISP_ANO_NUM_ON()
{
	SBR_BIN_TO_BCD();
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	SBR_DISP_MINUTE();
	r_Temp0.Val = display_num[r_Temp2.Val];
	r_Temp1.Val = Display_all_off;
	SBR_DISP_HOUR();
	SBR_DISP_DOT_COL_ON();
		
}
void	SBR_DISP_CLL_ALL_T_ON()
{
	r_Temp0.Val = Display_c;
	r_Temp1.Val = Display_all_off;
    SBR_DISP_MONTH();
    SBR_DISP_DOT_COLD_ON();
	r_Temp0.Val = Display_r;
	r_Temp1.Val = Display_L;
    SBR_DISP_DAY();
    r_Temp0.Val = Display_a;
	r_Temp1.Val = Display_all_off;
    SBR_DISP_HOUR();
    SBR_DISP_DOT_COLD_ON();
	r_Temp0.Val = Display_L;
	r_Temp1.Val = Display_L;
    SBR_DISP_MINUTE();
    SBR_DISP_DOT_COLD_OFF();
}

void	SBR_Disp_YS_ON()
{
	r_Temp0.Val = Display_5;
	r_Temp1.Val = Display_y;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();			
}


void	SBR_Disp_NO_ON()
{
	r_Temp0.Val = Display_o;
	r_Temp1.Val = Display_n;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();			
}
void	SBR_Disp_ON_OFF()
{
	SBR_DISP_DIA_OFF();				
}

//void	SBR_Disp_OFF_ON()
//{
//	r_Temp0.Val = Display_f;
//	r_Temp1.Val = Display_f;
//	r_Temp2.Val = Display_o;
//	SBR_DISP_DIA();			
//}
void	SBR_Disp_OFF_OFF()
{
	SBR_DISP_DIA_OFF();				
}
void	SBR_Disp_OFF_ON()   // L0
{
	r_Temp0.Val = Display_o;
	r_Temp1.Val = Display_L;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_DIA();			
}

//低壓顯示
void	SBR_DISP_DIA()
{
	_mp1h = 4;
	_mp1l = 21;
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp2.bits.SEG_B)
	{
		SFR_iar1.bits.b0 = 1;		
	}	
	if(r_Temp2.bits.SEG_A)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp2.bits.SEG_E)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	_mp1l--;	
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp1.bits.SEG_F)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp1.bits.SEG_E)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp2.bits.SEG_C)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	

	_mp1l--;				
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp1.bits.SEG_G)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp1.bits.SEG_D)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	
	_mp1l--;	
	SFR_iar1.Val &= 0b00111100;
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b0 = 1;		
	}	
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	
	
	_mp1l--;
	SFR_iar1.Val &= 0b00111100;
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	
	_mp1l--;
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	_mp1l--;
	SFR_iar1.Val &= 0b00111100;
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b1 = 1;		
	}	

}


//高壓
void	SBR_DISP_SYS()
{
	
	_mp1h = 4;
	_mp1l = 8;
	SFR_iar1.Val &= 0b00111101;
	if(r_Temp2.bits.SEG_E)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	_mp1l ++;
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp2.bits.SEG_C)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp2.bits.SEG_A)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp2.bits.SEG_B)
	{
		SFR_iar1.bits.b2 = 1;		
	}		
	_mp1l ++;
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp1.bits.SEG_D)
	{
		SFR_iar1.bits.b0 = 1;		
	}	
	if(r_Temp1.bits.SEG_E)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp1.bits.SEG_F)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	_mp1l ++;	
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp1.bits.SEG_G)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b2 = 1;		
	}	
	_mp1l ++;				
	SFR_iar1.Val &= 0b00111001;
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b1 = 1;		
	}	
	_mp1l ++;				
	SFR_iar1.Val &= 0b00111000;	
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	_mp1l ++;				
	SFR_iar1.Val &= 0b00111000;	
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b2 = 1;		
	}	
}


//;;;******************************************************************************************
//;;; 函数名称: _SBR_Disp_DIA_On/Off
//;;; 函数描述: 显示DIA
//;;; 输入参数: _r_TempDataL/H
//;;; 输出参数: 无 
//;;;******************************************************************************************

void	SBR_DISP_DIA_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;	
	r_Temp2.Val = Display_all_off;	
	SBR_DISP_DIA();
}



//;;******************************************************************************************
//;; 函数名称: _SBR_Disp_SP_On/Off
//;; 函数描述: 显示DIA
//;; 输入参数: 无
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_DISP_SP_OFF()
{
	r_Temp2.Val = Display_all_off;
	r_Temp1.Val = Display_5;
	r_Temp0.Val = Display_P;
	SBR_DISP_SYS();
	r_Temp2.Val = Display_all_off;
	r_Temp1.Val = Display_o;
	r_Temp0.Val = Display_f;
	SBR_DISP_DIA();
}
void	SBR_DISP_SP_ON()
{
	r_Temp2.Val = Display_all_off;
	r_Temp1.Val = Display_5;
	r_Temp0.Val = Display_P;
	SBR_DISP_SYS();
	r_Temp2.Val = Display_all_off;
	r_Temp1.Val = Display_o;
	r_Temp0.Val = Display_n;
	SBR_DISP_DIA();
}


//;;******************************************************************************************
//;; 函数名称: _SBR_Disp_SYS_On/Off
//;; 函数描述: 显示DIA
//;; 输入参数: _r_TempDataL/H
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_DISP_SYS_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_SYS();
	
}

void	SBR_DISP_SYS_ON()
{
	SBR_BIN_TO_BCD();
	if(r_Temp2.Val >= 4)
	{
		r_Temp2.Val = 0;
	}
	if(r_Temp2.Val == 0)
	{
		r_Temp2.Val = 0x10;
		if(r_Temp1.Val== 0)
		{
			r_Temp1.Val = 0x10;
		}
	}
	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	r_Temp2.Val = display_num[r_Temp2.Val];
	SBR_DISP_SYS();	
}


void	SBR_DISP_DIA_ON()
{
	SBR_BIN_TO_BCD();
	if(r_Temp2.Val >= 4)
	{
		r_Temp2.Val = 0;
	}
	if(r_Temp2.Val == 0)
	{
		r_Temp2.Val = 0x10;
		if(r_Temp1.Val== 0)
		{
			r_Temp1.Val = 0x10;
		}
	}
	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	r_Temp2.Val = display_num[r_Temp2.Val];
	SBR_DISP_DIA();	
	
}

//;****************************************************************
//;16bit binary to BCD
//;input:_r_TempDataL(LSB),_r_TempDataH(MSB)
//;output:_r_Temp0(个位),_r_Temp1(十位),_r_Temp2(百位),_r_Temp3(千位),_r_Temp4(万位)
//;effect:_r_Temp5
//;****************************************************************
void	SBR_BIN_TO_BCD()
{
	uint8	i;
	uint16	BIN_TO_BCD_TEMP;
	BIN_TO_BCD_TEMP = R_TEMPDATA.Val;
	for(i=0;i<5;i++)
	{	
		BCD[i].Val = BIN_TO_BCD_TEMP%10;
		BIN_TO_BCD_TEMP = BIN_TO_BCD_TEMP/10;		
	}
}


//;;******************************************************************************************
//;; 函数名称: _SBR_Disp_Pluse_On/Off
//;; 函数描述: 显示脉搏
//;; 输入参数: _r_TempDataL/H
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_DISP_PLUSE_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	r_Temp2.Val = Display_all_off;
	SBR_DISP_PLUSE();	
}

void	SBR_DISP_PLUSE()
{
	_mp1h = 4;
	_mp1l = 19;
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp2.bits.SEG_B)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	if(r_Temp1.bits.SEG_F)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp1.bits.SEG_E)
	{
		SFR_iar1.bits.b4 = 1;		
	}

	_mp1l--;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b3 = 1;		
	}	
	if(r_Temp1.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp1.bits.SEG_D)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	
	_mp1l--;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b5 = 1;		
	}

		
	_mp1l--;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	
	
	_mp1l--;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b4 = 1;		
	}	
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b5 = 1;		
	}

}

void	SBR_DISP_PLUSE_ON()
{
	SBR_BIN_TO_BCD();
	if(r_Temp2.Val >= 2)
	{
		r_Temp2.Val = 0;
	}
	if(r_Temp2.Val == 0)
	{
		r_Temp2.Val = 0x10;
		if(r_Temp1.Val== 0)
		{
			r_Temp1.Val = 0x10;
		}
	}
	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	r_Temp2.Val = display_num[r_Temp2.Val];
	SBR_DISP_PLUSE();	
	
}


//;;;******************************************************************************************
//;;; 函数名称: _SBR_Disp_Memory_On/Off
//;;; 函数描述: 显示用户组
//;;; 输入参数: _r_TempDataL/H
//;;; 输出参数: 无 
//;;;******************************************************************************************
void	SBR_DISP_MEMORY_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	SBR_DISP_MEMORY();
	
}
void	SBR_DISP_MEMORY()
{
//	_mp1h = 4;
//	_mp1l = 4;
//	SFR_iar1.Val &= 0b00001111;	
//	if(r_Temp2.bits.SEG_B)
//	{
//		SFR_iar1.bits.b4 = 1;		
//	}	
//	if(r_Temp1.bits.SEG_F)
//	{
//		SFR_iar1.bits.b5 = 1;		
//	}
//	_mp1l++;
//	SFR_iar1.Val &= 0b00000111;
//	
//	if(r_Temp1.bits.SEG_E)
//	{
//		SFR_iar1.bits.b3 = 1;		
//	}
//	if(r_Temp1.bits.SEG_G)
//	{
//		SFR_iar1.bits.b4 = 1;		
//	}
//	if(r_Temp1.bits.SEG_A)
//	{
//		SFR_iar1.bits.b5 = 1;		
//	}
//	_mp1l++;
//	SFR_iar1.Val &= 0b00000111;
//	
//	if(r_Temp1.bits.SEG_D)
//	{
//		SFR_iar1.bits.b3 = 1;		
//	}
//	if(r_Temp1.bits.SEG_C)
//	{
//		SFR_iar1.bits.b4 = 1;		
//	}
//	if(r_Temp1.bits.SEG_B)
//	{
//		SFR_iar1.bits.b5 = 1;		
//	}
//	_mp1l++;
//	SFR_iar1.Val &= 0b00000111;
//	
//	if(r_Temp0.bits.SEG_E)
//	{
//		SFR_iar1.bits.b3 = 1;		
//	}
//	if(r_Temp0.bits.SEG_F)
//	{
//		SFR_iar1.bits.b4 = 1;		
//	}
//	if(r_Temp0.bits.SEG_A)
//	{
//		SFR_iar1.bits.b5 = 1;		
//	}
//	_mp1l++;
//	SFR_iar1.Val &= 0b00000111;
//	
//	if(r_Temp0.bits.SEG_D)
//	{
//		SFR_iar1.bits.b3 = 1;		
//	}
//	if(r_Temp0.bits.SEG_G)
//	{
//		SFR_iar1.bits.b4 = 1;		
//	}
//	if(r_Temp0.bits.SEG_B)
//	{
//		SFR_iar1.bits.b5 = 1;		
//	}	
//	_mp1l++;
//	SFR_iar1.bits.b3 = 0;
//	
//	if(r_Temp0.bits.SEG_C)
//	{
//		SFR_iar1.bits.b3 = 1;		
//	}
}
void	SBR_DISP_MEMORY_ON()
{
	SBR_BIN_TO_BCD();

//	if(r_Temp1.Val== 0)
//	{
//		r_Temp1.Val = 0x10;
//	}

	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	SBR_DISP_MEMORY();	
	
}


//;;******************************************************************************************
//;; 函数名称: _SBR_Disp_Month_On/Off
//;; 函数描述: 显示月份
//;; 输入参数: _r_TempDataL
//;; 输出参数: 无 
//;;******************************************************************************************
void	SBR_DISP_MONTH_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	SBR_DISP_MONTH();	
}

void	SBR_DISP_MONTH()
{
	_mp1h = 4;
	_mp1l = 23;
	SFR_iar1.Val &= 0b00011111;
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l--;
	SFR_iar1.Val &= 0b00011111;
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l=6;
	SFR_iar1.Val &= 0b00111110;
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b0 = 1;		
	}	
	_mp1l --;	
	SFR_iar1.Val &= 0b00111000;
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b2 = 1;		
	}	
	_mp1l --;	
	SFR_iar1.Val &= 0b00111000;	
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b1 = 1;		
	}
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b2 = 1;		
	}	
	_mp1l --;	
	SFR_iar1.Val &= 0b00111110;	
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b0 = 1;		
	}	
}
void	SBR_DISP_MONTH_ON()
{
	r_TempDataH = 0;
	SBR_BIN_TO_BCD();

	if(r_Temp1.Val== 0)
	{
		r_Temp1.Val = 0x10;
	}

	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
//	SBR_DISP_MONTH();	
//	與小時共用
	SBR_DISP_MONTH();	
}


//******************************************************************************************
// 函数名称: _SBR_Disp_Day_On/Off
// 函数描述: 显示月份
// 输入参数: _r_TempDataL
// 输出参数: 无 
//******************************************************************************************
void	SBR_DISP_DAY_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	SBR_DISP_DAY();	
}
void	SBR_DISP_DAY()
{
	
	_mp1h = 4;
	_mp1l = 2;
	SFR_iar1.Val &= 0b00000000;		
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b0 = 1;		
	}
	if(r_Temp1.bits.SEG_F)
	{
		SFR_iar1.bits.b1 = 1;		
	}		
	if(r_Temp1.bits.SEG_D)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp1.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}		
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l++;	
	SFR_iar1.Val &= 0b00000011;	
	if(r_Temp1.bits.SEG_E)
	{
		SFR_iar1.bits.b2 = 1;		
	}
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l++;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l++;	
	SFR_iar1.Val &= 0b00011111;		
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b5 = 1;		
	}	
}

void	SBR_DISP_DAY_ON()
{
	r_TempDataH = 0;
	SBR_BIN_TO_BCD();

//	if(r_Temp1.Val== 0)
//	{
//		r_Temp1.Val = 0x10;
//	}

	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
//	SBR_DISP_DAY();	
//	與分鐘共用
	SBR_DISP_DAY();	
}





//;;;******************************************************************************************
//;;; 函数名称: _SBR_Disp_Hour_On/Off
//;;; 函数描述: 显示小时
//;;; 输入参数: _r_TempDataL
//;;; 输出参数: 无 
//;;;******************************************************************************************
void	SBR_DISP_HOUR_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	SBR_DISP_HOUR();		
	
}
void	SBR_DISP_HOUR()
{	
	_mp1h = 4;
	_mp1l = 5;
	SFR_iar1.Val &= 0b00110111;		
	if(r_Temp1.bits.SEG_E)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	_mp1l ++;
	SFR_iar1.Val &= 0b00000111;		
	if(r_Temp1.bits.SEG_D)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp1.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	
	_mp1l ++;
	SFR_iar1.Val &= 0b00000111;		
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l ++;
	SFR_iar1.Val &= 0b00000111;		
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l ++;
	SFR_iar1.Val &= 0b00000111;		
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b5 = 1;		
	}

}
void	SBR_DISP_HOUR_ON()
{
	r_TempDataH = 0;
	SBR_BIN_TO_BCD();

	if(r_Temp1.Val== 0)
	{
		r_Temp1.Val = 0x10;
	}

	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	SBR_DISP_HOUR();	

	
}

//;;;******************************************************************************************
//;;; 函数名称: _SBR_DISP_MINUTE_ON/Off
//;;; 函数描述: 显示分钟
//;;; 输入参数: _r_TempDataL
//;;; 输出参数: 无 
//;;;******************************************************************************************
void	SBR_DISP_MINUTE_OFF()
{
	r_Temp0.Val = Display_all_off;
	r_Temp1.Val = Display_all_off;
	SBR_DISP_MINUTE();
}


void	SBR_DISP_MINUTE()
{
	_mp1h = 4;
	_mp1l = 10;
	SFR_iar1.Val &= 0b00001111;
	if(r_Temp1.bits.SEG_E)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp1.bits.SEG_F)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	_mp1l++;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp1.bits.SEG_D)
	{
		SFR_iar1.bits.b3 = 1;		
	}	
	if(r_Temp1.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp1.bits.SEG_A)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	
	_mp1l++;	
	SFR_iar1.Val &= 0b00000111;
	
	if(r_Temp0.bits.SEG_E)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp1.bits.SEG_C)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp1.bits.SEG_B)
	{
		SFR_iar1.bits.b5 = 1;		
	}	
	_mp1l++;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp0.bits.SEG_D)
	{
		SFR_iar1.bits.b3 = 1;		
	}
	if(r_Temp0.bits.SEG_G)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_F)
	{
		SFR_iar1.bits.b5 = 1;		
	}
	
	_mp1l++;	
	SFR_iar1.Val &= 0b00000111;
	if(r_Temp0.bits.SEG_C)
	{
		SFR_iar1.bits.b3 = 1;		
	}	
	if(r_Temp0.bits.SEG_B)
	{
		SFR_iar1.bits.b4 = 1;		
	}
	if(r_Temp0.bits.SEG_A)
	{
		SFR_iar1.bits.b5 = 1;		
	}		
}


void	SBR_DISP_MINUTE_ON()
{
	r_TempDataH = 0;
	SBR_BIN_TO_BCD();

//	if(r_Temp1.Val== 0)
//	{
//		r_Temp1.Val = 0x10;
//	}	
	r_Temp0.Val = display_num[r_Temp0.Val];
	r_Temp1.Val = display_num[r_Temp1.Val];
	SBR_DISP_MINUTE();	
}
