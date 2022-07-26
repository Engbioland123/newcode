#ifndef _DEFINE_H_
#define _DEFINE_H_

#define BPF_ALARM_MP3 01   //	嘟（蜂鸣音）			
     //02	[]			
#define BPF_0_MP3     03   //	0			
//04	1			
//05	2			
//06	3			
//07	4			
//08	5			
//09	6			
//10	7			
//11	8			
//12	9			
#define BPF_10_MP3   13	     //一十			
//14	一十一			
//15	一十二			
//16	一十三			
//17	一十四			
//18	一十五			
//19	一十六			
//20	一十七			
//21	一十八			
//22	一十九			
#define BPF_20_MP3    23	  //二十			
//24	三十			
//25	四十			
//26	五十			
//27	六十			
//28	七十			
//29	八十			
//30	九十			
#define BPF_100_MP3   31  //	百			
//32	十			
#define BPF_TEST_NUS_MP3   33  //	欢迎使用，请选择需要测量的用户			
#define BPF_TEST_STA_MP3   34  //	请保持安静，放轻松，将袖袋与心脏部位保持同高！现在开始测量；			
#define BPF_SHOUSUOYA_MP3  35  //	您的血压是 ，高压：			
#define BPF_SHUZHANGYA_MP3 36  //	低压：			
#define BPF_MAIBO_MP3      37  //	脉搏每分钟：			
#define BPF_MMHG_MP3       38  //	毫米汞柱			
#define BPF_CHI_MP3        39  //	次			
#define BPF_WHO_MP3        40  //	根据世界卫生组织标准 ，您的血压，			
#define BPF_AB_NORMAL_MP3  41  //	正常			
#define BPF_HIGH_MP3       42  //	偏高			
#define BPF_LOWPOWER_MP3   43  //	电量不足，请充电			
#define BPF_TEST_ERR_MP3   44  //	错误,请重新测量			
#define BPF_NXTE_MP3       45  //	上一次			
//46	叮咚			
#define BPF_GPRS_SUC_MP3   48	//数据上传成功			
#define BPF_GPRS_ERR_MP3   49	//您当前的网络信号弱，数据已保存，下次测量成功后上传；			
#define BPF_GPRS_STA_MP3   47	//即将传输数据，请勿关机			


//#define MAX_BP 70
//#define MIN_BP 3 
//
//#define BPF_TEST_NUS_MP3    0x51//	测试之前请您先欣赏一段音乐以舒缓心情
//#define BPF_TEST_STA_MP3    0x52//	注意：准备量测，请确认绑带与心脏部位同高，不要移动和说话
//#define BPF_TEST_END_MP3    0x53//	测量结束.
//#define BPF_KP_MP3          0x54//	千帕
//#define BPF_TEST_AVG_MP3    0x55//	平均血压
//#define BPF_TEST_VAR_MP3    0x56//  您的量测结果为
//#define BPF_SHOUSUOYA_MP3   0x57//	高压
//#define BPF_SHUZHANGYA_MP3  0x58//	低压
//#define BPF_MAIBO_MP3       0x59//	心率每分钟
//#define BPF_WHO_MP3         0x60//	根据世界卫生组织标准,您的血压.
//#define BPF_AB_NORMAL_MP3   0x61//	正常.
//#define BPF_HIGH_MP3        0x62//	轻高.
//#define BPF_HIGHH_MP3	    0x63//	重高.
//
//#define BPF_THANKS_MP3      0xA0//	謝謝使用,祝您健康
//#define BPF_MMHG_MP3        0xA1//	毫米汞柱
//#define BPF_DIAN_MP3        0xA2//	点
//#define BPF_CHI_MP3         0xA3//	次
//#define BPF_LOWPOWER_MP3    0xA4//  电力不足 请更换电池
//#define BPF_TEST_ERR_MP3    0xA5//	测量错误，请休息两分钟后再重新测量
//#define BPF_BAI_MP3         0xA6//	百
//#define BPF_ALARM_MP3       0xA7//	水晶闹钟，
//#define BPF_NXTE_MP3        0xA8//	上一次
//#define BPF_ZZY_MP3 	    0xA9//  寂之音1段.wav
//
//#define BPF_0_MP3		   0x0001//	零
//
//#define BPF_SHI_MP3	       0x0002//	十
//
//#define BPF_100_MP3	       0x0003//	一百
//#define BPF_200_MP3        0x0003//	兩百
//#define BPF_300_MP3        0x0003// 参百


#define  SK080G_CountTG11 _pbc2 
#define  SK080G_ResetTG33 _pbc1

#define  SK080G_CountTG1 _pb2
#define  SK080G_ResetTG3 _pb1
#define  SK080G_BusyTG4  _pb0

#define  REL1  _pc3  //电磁阀控制口

#define  LEDR  _pc1
#define  FUL_DET  _pa1

#define  GSM_PWRKEY  _pe6

#define     RxBufMAX            					85
#define     UART_BACK_OK            		 		0
#define     UART_BACK_OVER_RAM            			1
#define     UART_BACK_OVER_time          			2
#define     UART_BACK_ERROR          				3
#define     UART_BACK_NO_OK            	 			4
//#define     UART_BACK_Duplicated     				5
#define     UART_BACK_DOWN     	 				    6
#define     UART_BACK_APP_RDY				 	    7
#define     UART_BACK_SIM_READY				 		8
#define     UART_BACK_CONNECT					 	9
#define     UART_BACK_NOT_INSERTED					10

#define     UART_BACK_No_S						    11

#define On                  (1)
#define Off                 (0)

#define TRUE                (1)
#define true                (1)
#define FALSE               (0)
#define false               (0)
 
#define  SPEAKBUSYFLAG  MODEFLAG.bits.b6      //语音是否播完    
#define  mmHg_Kpa	    MODEFLAG.bits.b7      //单位切换 

#define  GSM_OFF_ON           Usflag.bits.b0
#define  Uart_overtine1       Usflag.bits.b1
#define  Uart_overtine        Usflag.bits.b2
#define  TIME_TEEP_flag       Usflag.bits.b3 
#define  OVERMEMORY           Usflag.bits.b4 
#define  CHARGE               Usflag.bits.b5 
#define  MEMO_INT_SPEAK       Usflag.bits.b6
#define  vodisplay            Usflag.bits.b7
 

#define	C_Memory_Num			50
//UINT8_VAL KEYFLAG;
///////////////////////////////////////////////////////////////////////
#define	SetKey		b0	//1=SET KEY DOWN
#define	StartKey	b1	//1=START KEY DOWN
#define	RecallKey	b2	//1=RECALL KEY DOWN
#define	RecallSetKeyHold		b3	//1=MODE KEY DOWN
#define	SetKeyHold	b4	//1=SET KEY HOLD 3s
#define	RecallKeyHold	b5	//1=RECALL KEY HOLD 3s
#define	STARTKEYSetKeyHold	b6	//扫描按键内部使用
#define	STARTKEYRecallKeyHold	b7	//扫描按键内部使用
#define	STARTKEYHold	        b8	

//UINT8_VAL TIMERFLAG;
///////////////////////////////////////////////////////////////////////
#define TB0_INT		b0	//TB0中断
#define TB1_INT		b1	//TB1中断
#define Debounce	b2	//按键扫描去抖
#define NewDay		b3	// 
#define Flashing	b4	// 
#define SearchOver	b5	//
//#define SetKHing	b6	//未定义
//#define ReacllKHing	b7	//未定义

///////////////////////////////////////////////////////////////////////
#define TB0_INT		b0	//TB0中断
#define TB1_INT		b1	//TB1中断
#define TB1_INT_625	b2	//按键扫描去抖
#define NewDay		b3	// 
#define Display		b4	// 
#define SearchOver	b5	//

///////////////////////////////////////////////////////////////////////
#define Up_dateTime		b0	//TB0中断
#define DisplayTime		b3	//TB1中断
#define User			b5	//按键扫描去抖

///////////////////////////////////////////////////////////////////////
//#define	SetKey		b0	    //1=SET KEY DOWN
//#define	StartKey	b1	    //1=START KEY DOWN
//#define	RecallKey	b2	    //1=RECALL KEY DOWN
//#define	Modeadd		b3	    //1=MODE KEY DOWN
//#define	SetKeyHold	b4	    //1=SET KEY HOLD 3s
//#define	RecallKeyHold	b5	//1=RECALL KEY HOLD 3s
//#define	Modesub		b6	    //扫描按键内部使用
//#define	ReacllKHing	b7	    //扫描按键内部使用#define RECALLKEY	b3	//set按鍵按下



#define LU8C_KEY_DEBOUNCE_TIME	4


//***********************Key_Scan ***************

#define	GPIO_STARTKEY	_pa3
#define	GPIO_RECALLKEY	_pa5
#define	GPIO_SETKEY		_pa4
#define	GPIO_SETKEY_TEST	_pac4

//#define	GPIO_MODEKEY	_pa1
//#define	GPIO_STARTKEY	_pa5
//#define	GPIO_RECALLKEY	_pa6
//#define	GPIO_SETKEY		_pa2

//#define	GPIO_MODEKEY	_pa2
//#define	GPIO_STARTKEY	_pa5
//#define	GPIO_RECALLKEY	_pa6
//#define	GPIO_SETKEY		_pa1


//;display number
#define			SEG_A	b0
#define			SEG_F	b1
#define			SEG_G	b2
#define			SEG_D	b3
#define			SEG_E	b4
#define			SEG_B	b5
#define			SEG_C	b6


#define	GPIO_UART_TX_IO	_pcc4
#define	GPIO_UART_TX	_pc4

/********************************************************************
Function:	DEFINE
********************************************************************/
#define		cmd_return_op1adnum			30
#define		cmd_return_op2adnum			31
#define		cmd_adjust_bandgap_up		32
#define		cmd_adjust_bandgap_down		33
#define		cmd_data_to_pref			34
#define		cmd_data_to_rom				35
#define		cmd_adjust_daco_up			37
#define		cmd_adjust_daco_down		38
#define		UCR1_8_N_1     				0x80      //8bits-Data  NONE-Parity 1bit-Stop Format
#define 	UCR1_7_O_1     				0x0B0     //7bits-Data  Odd-Parity  1bit-Stop Format
#define		UCR1_7_E_1     				0x0A0     //7bits-Data  Even-Parity 1bit-Stop Format
#define		UCR1_9_N_1     				0x0C0     //9bits-Data  NONE-Parity 1bit-Stop Format
#define		UCR1_8_O_1    				0x0F0     //8bits-Data  Odd-Parity  1bit-Stop Format
#define		UCR1_8_E_1     				0x0E0     //8bits-Data  Even-Parity 1bit-Stop Format
#define		UCR1_8_N_2     				0x88      //8bits-Data  NONE-Parity 2bits-Stop Format
#define		UCR1_7_O_2     				0x0B8     //7bits-Data  Odd-Parity  2bits-Stop Format
#define		UCR1_7_E_2     				0x0A8     //7bits-Data  Even-Parity 2bits-Stop Format
#define		UCR1_9_N_2     				0x0C8     //9bits-Data  NONE-Parity 2bits-Stop Format
#define		UCR1_8_O_2     				0x0F8     //8bits-Data  Odd-Parity  2bits-Stop Format
#define		UCR1_8_E_2     				0x0E8     //8bits-Data  Even-Parity 2bits-Stop Format
#define		UCR2Data       				0x0E4     //Enable TXEN RXEN BRGH RIE 
#define		UCR2Data1       			0x0Ef     //Enable TXEN RXEN BRGH RIE 

#define		BRGData        				51		  //4mhz0x19       //Baud=9600,BRGH=1,N=25 

//中斷入口地址
#define	START_VECTOR			0x000		//主程序
#define	INT0_VECTOR				0x004		//Intrrupt 0
#define	INT1_VECTOR				0x008		//Intrrupt 1
#define ADC_VECTOR				0x0C		//ADC 中斷
#define	MF0_VECTOR				0x0010		//復合中斷 0
#define	MF1_VECTOR				0x0014		//復合中斷 1
#define MF2_VECTOR				0x018		//復合中斷 2
#define SCF_VECTOR				0x01C		//SCF中斷 
#define TB0_VECTOR				0x020		//TB0中斷 
#define TB1_VECTOR				0x024		//TB1中斷 
#define UART_VECTOR				0x028		//UART中斷 
#define SIM_VECTOR				0x02C		//SIM中斷 
#define SPIA_VECTOR				0x030		//SPIA中斷 

#define _txr_rxr  _txr_rxr0
#define _ferr     _ferr0
#define _perr     _perr0
#define _nf       _nf0
#define _oerr     _oerr0
#define _usr      _u0sr  
#define _rxif     _rxif0
#define _txif     _txif0

#define _brg      _brg0
#define _rie      _rie0
#define _ucr2     _u0cr2
#define _ucr1     _u0cr1
#define _stm0c0   _stmc0
#define	_stm0c1   _stmc1
#define	_stm0al   _stmal
#define	_stm0ah   _stmah
#define _stm0rp   _stmrp	
#define _st0on    _ston

#endif