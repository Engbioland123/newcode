#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"


volatile	UINT16_VAL 	PRE_SYS;
volatile	UINT16_VAL 	PRE_DIA;
//volatile	UINT16_VAL 	Temperature;
volatile	uint8 	R_PLUSE;
volatile	uchar 	keyval;
volatile	uchar 	keyvalGSM;
volatile	uchar 	GSM_DATA_CNT;
volatile	UINT16_VAL 	R_TEMPDATA;
volatile	UINT8_VAL  	BCD[6];
volatile	uint8 	R_DISPLAYTIME;
volatile	uint8 	R_DISPLAYCOUNTER;
volatile	uint8  	R_KEYHOLDTIME;
volatile	uint8  	R_TIMEBASE;
volatile	uint8  	R_BK_MP;
volatile	uint8  	R_DISPLAY_COUNT;
volatile	uint8  	R_10ms_COUNT;
volatile	UINT8_VAL  	R_alarm_clock;
//volatile	uint8  	R_A1_HOUR;
//volatile	uint8  	R_A1_MUNITE;
//volatile	uint8  	R_A2_HOUR;
//volatile	uint8  	R_A2_MUNITE;
//volatile	uint8  	R_A3_HOUR;
//volatile	uint8  	R_A3_MUNITE;

//volatile    uint8 WAVE_count;
//volatile    uint16  P0_BUF;
//volatile    uint8 OLD_M1_PH;// __attribute__((at(0x3CF)));
//volatile    uint8 OLD_M1_PL;// __attribute__((at(0x3CE)));
//volatile    uint8 M1_PL;// __attribute__((at(0x3CD)));
//volatile    uint8 M1_PH;// __attribute__((at(0x3CC)));
//volatile    uint8 M1_PRE;// __attribute__((at(0x3CB)));
//volatile    uint16  SPRE3; // __attribute__((at(0x3F2)));
//volatile    uint16  SPRE2; 
//volatile	uint8   EER_CNT;


/************************Key_Scan Variable****************/
volatile	UINT8_VAL   gu8v_KeyDown;			
volatile	uint8   	gu8v_KeyOld;
volatile	uint8	    gu8v_KeyNoChangedTime;
volatile	UINT8_VAL   gu8v_KeyPress;
volatile	UINT8_VAL	gu8v_KeyUp;
volatile	uint8	    gu8v_KeyLast;
volatile	uint16 	    gu8v_Keypress_time;
volatile	UINT8_VAL   gu8v_KeyCurrent;	


//volatile uint8	gu16v_scf_output_xbuff[3];
//volatile uint8	gu16v_scf_output_ybuff[3];



volatile	uint8	   R_TIMEOUT_SECOND;
volatile	UINT16_VAL PWMDATA;
volatile	UINT16_VAL ADCVALV;
volatile    UINT16_VAL pres_avl;
//uint8 e2flag;	        //标字
volatile	UINT8_VAL R_KEYSTATUS;
volatile	UINT16_BITS KEYFLAG;
/////////////////////////////////////////////////////////////////////////
//#define	SetKey		b0	//1=SET KEY DOWN
//#define	StartKey	b1	//1=START KEY DOWN
//#define	RecallKey	b2	//1=RECALL KEY DOWN
//#define	ModeKey		b3	//1=MODE KEY DOWN
//#define	SetKeyHold	b4	//1=SET KEY HOLD 3s
//#define	RecallKeyHold	b5	//1=RECALL KEY HOLD 3s
//#define	SetKHing	b6	//扫描按键内部使用
//#define	ReacllKHing	b7	//扫描按键内部使用
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL TIMERFLAG;
/////////////////////////////////////////////////////////////////////////
//#define TB0_INT		b0	//TB0中断
//#define TB1_INT		b1	//TB1中断
//#define Debounce	b2	//按键扫描去抖
//#define NewDay		b3	// 
//#define Flashing	b4	// 
//#define SearchOver	b5	//
////#define SetKHing	b6	//未定义
////#define ReacllKHing	b7	//未定义
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL R2FLAG;
///////////////////////////////////////////////////////////////////////
//              b0 1: 1.已经找到了一个完整的峰峰，0.没有找到完整的峰峰或要开始找
//             b1 1:
//             b2 1:
//             b3 1:
//             b4 1:
//             b5   未定义
//             b6   未定义
//             b7   未定义
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL R3FLAG;
//----------------------------------------------------------
// R3FLAG
// Bit 0 : 產生slope 20 的上升 
// Bit 1 : 第一個下降波形 c/16
// Bit 2 : 第二個下降波形 8/16
// Bit 3 : 整個量測波形，第一個波形不要 
// Bit 4 : 第一個波形儲存
// Bit 5 : 抓取波形使用，斜率已低於 MIN_BP 了
// Bit 6 : 
// Bit 7 : 有一個時心律不整的波形，下一個波形不要，但只存心跳值
//-----------------------------------------------------------
volatile	UINT8_VAL ERFLAG;
///////////////////////////////////////////////////////////////////////
//  ERFLAG     b0 1:     //没有需要再加压往下,再加压三次也要退出 
//             b1 1:      //退出显示错误EE
//             b2 1:     //加压及测量时超过180秒E2 
//             b3 1:
//             b4 1:     //停止测量，加压不足  
//             b5   未定义
//             b6   未定义
//             b7   未定义
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL Usflag;
///////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

volatile	UINT8_VAL MODEFLAG;
///////////////////////////////////////////////////////////////////////
//  MODEFLAG   b0 1:高度模式     0  : 低功耗模式  MODEFLAG.bits.b0             mode_low=0;
//             b1 1:开机到现在没有测量过 0  :开机到现在没有测量过Modeflag.bits.b1  test_1flg = 0;//开机到现在没有测量过
//             b2 1测试时间超180秒 //uint8 e2flag;	MODEFLAG.bits.b2    ,                                
//             b3 1:显示时间    0  ：不显时间	dis_time_off=1;	        //显示时间
//             b4 1: 语音开始 0:语音关闭              gbSPEAKFlag=1;//语音初始为开的状态
//             b5  //测试的人,0-1号,1为2号
//             b6  //语音是否播完
//             b7  //语音命令发送标志

//////////////////////////////////////////////////////////////////////
//wave_per

//FUN
volatile	UINT8_VAL	R_IAP_TEMP[10];

//volatile	uint8	R_EEPROM_DATA;
//volatile	uint8	R_EED_READ;
//
//volatile	uint8	R_CURRENT_SN;
//volatile	uint8   R_CURRENT_SN_DISP;
//
//volatile	uint8	R_SEARCH_SN_DISP;
//volatile	uint8	R_SEARCH_SN;

//volatile	uint8	gu8v_wake_up_time;


//volatile	uint8	gu8v_rx_guide;
//volatile	uint8	gu8v_tx_guide;
volatile	UINT8_VAL	gu8v_uart_flag;

//volatile    uint8 btt_cnt;
//volatile    uint8 step;
//volatile    uint8 MS10JSQ;
//volatile    uint8 timegsm;
//volatile    uint8 Rx_Size;
//volatile    uint8 Timer_Flag_t10ms_Count;

//volatile	uint8	Tx_Buff[8];
//volatile	uint8	array_uart_rxbuff[6];


//volatile	uint8   BAS_BP;
//volatile	uint8   CNTWL;

//volatile    uint16  SS[8];
//volatile    uint8   P1VAL[11];
//volatile    uint8   P1VAL_TEEP[11];