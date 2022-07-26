#ifndef _VARIABLE_H_
#define _VARIABLE_H_



extern	volatile	UINT16_VAL 	PRE_SYS;
extern	volatile	UINT16_VAL 	PRE_DIA;
//extern	volatile	UINT16_VAL 	Temperature;
extern	volatile	uint8 	R_PLUSE;
extern	volatile	uchar 	keyval;
extern	volatile	uchar 	keyvalGSM;
extern	volatile	uchar 	GSM_DATA_CNT;
extern	volatile	UINT16_VAL 	R_TEMPDATA;
#define r_TempDataL	R_TEMPDATA.BYTE.BYTE_L
#define r_TempDataH	R_TEMPDATA.BYTE.BYTE_H
extern	volatile	UINT8_VAL  	BCD[6];
#define r_Temp0	BCD[0]
#define r_Temp1	BCD[1]
#define r_Temp2	BCD[2]
#define r_Temp3	BCD[3]
#define r_Temp4	BCD[4]
#define r_Temp5	BCD[5]


extern	volatile	uint8 	R_DISPLAYTIME; 
extern	volatile	uint8 	R_DISPLAYCOUNTER;
extern	volatile	uint8  	R_KEYHOLDTIME;
extern	volatile	uint8  	R_TIMEBASE;
extern	volatile	uint8  	R_BK_MP;
extern	volatile	uint8	R_TIMEOUT_SECOND;
extern	volatile	UINT16_VAL PWMDATA;
extern	volatile	UINT16_VAL ADCVALV;
extern  volatile    UINT16_VAL pres_avl;
extern	volatile	UINT8_VAL R_KEYSTATUS;
extern	volatile	UINT16_BITS KEYFLAG;
extern	volatile	UINT8_VAL TIMERFLAG;
extern	volatile	UINT8_VAL R2FLAG;
extern	volatile	UINT8_VAL R3FLAG;
extern	volatile	UINT8_VAL ERFLAG;
extern	volatile	UINT8_VAL Usflag;
extern	volatile	UINT8_VAL MODEFLAG;

//extern	volatile uint8	gu16v_scf_output_xbuff[3];
//extern	volatile uint8	gu16v_scf_output_ybuff[3];

//extern  volatile   uint8 WAVE_count;
//extern  volatile   uint16 P0_BUF;
//extern  volatile   uint8 OLD_M1_PH;// __attribute__((at(0x3CF)));
//extern  volatile   uint8 OLD_M1_PL;// __attribute__((at(0x3CE)));
//extern  volatile   uint8 M1_PL;// __attribute__((at(0x3CD)));
//extern  volatile   uint8 M1_PH;// __attribute__((at(0x3CC)));
//extern  volatile   uint8 M1_PRE;// __attribute__((at(0x3CB)));

//extern  volatile uint16  SPRE3; // __attribute__((at(0x3F2)));
//extern  volatile uint16  SPRE2; // __attribute__((at(0x3F0)));

/************************Key_Scan Variable****************/
extern	volatile	UINT8_VAL   gu8v_KeyDown;			
extern	volatile	uint8	gu8v_KeyOld;
extern	volatile	uint8	gu8v_KeyNoChangedTime;
extern	volatile	UINT8_VAL  gu8v_KeyPress;
extern	volatile	UINT8_VAL	gu8v_KeyUp;
extern	volatile	uint8	gu8v_KeyLast;
extern	volatile	uint16 	gu8v_Keypress_time;
extern	volatile	UINT8_VAL  gu8v_KeyCurrent;	
extern	volatile	uint8  	R_10ms_COUNT;

extern	volatile	UINT8_VAL  	R_alarm_clock;
//#define		BTT_OFF	    R_alarm_clock.bits.b0
//#define		A2_ON_OFF	R_alarm_clock.bits.b1
//#define		XUNLIAN     R_alarm_clock.bits.b2
//#define		TIME_12		R_alarm_clock.bits.b3
//#define		Up_dateBTT  R_alarm_clock.bits.b4

#define		BTT_OFF   	R_alarm_clock.bits.b0
#define		Up_dateBTT	R_alarm_clock.bits.b1
#define		wudongzuo	R_alarm_clock.bits.b2
#define		CLRMON		R_alarm_clock.bits.b3
#define		ASCVD   	R_alarm_clock.bits.b4
//#define		Up_dateBTT	R_alarm_clock.bits.b5
//#define		wudongzuo	R_alarm_clock.bits.b6
//#define		CLRMON		R_alarm_clock.bits.b7


extern	volatile	UINT8_VAL	R_IAP_TEMP[10];

#define	R_IAP_TEMP0	R_IAP_TEMP[0]	
#define	R_IAP_TEMP1	R_IAP_TEMP[1]
#define	R_IAP_TEMP2	R_IAP_TEMP[2]	
#define	R_IAP_TEMP3	R_IAP_TEMP[3]	
#define	R_IAP_TEMP4	R_IAP_TEMP[4]	
#define	R_IAP_TEMP5	R_IAP_TEMP[5]
#define	R_MINUTE_SEARCH	R_IAP_TEMP[5]	
#define	R_IAP_TEMP6	R_IAP_TEMP[6]
#define	R_HOUR_SEARCH	R_IAP_TEMP[6]	
#define	R_IAP_TEMP7	R_IAP_TEMP[7]
#define	R_DAY_SEARCH	R_IAP_TEMP[7]	
#define	R_IAP_TEMP8	R_IAP_TEMP[8]
#define	R_MONTH_SEARCH	R_IAP_TEMP[8]	
#define	R_IAP_TEMP9	R_IAP_TEMP[9]
#define	R_YEAR_SEARCH	R_IAP_TEMP[9]

//extern	volatile	uint8	R_EEPROM_DATA;
//extern	volatile	uint8	R_EED_READ;
//extern	volatile	uint8	R_CURRENT_SN;
//extern	volatile	uint8   R_CURRENT_SN_DISP;
//
//extern	volatile	uint8	R_SEARCH_SN_DISP;
//extern	volatile	uint8	R_SEARCH_SN;
//extern	volatile	uint8	gu8v_wake_up_time;
//extern	volatile	uint8   ;
//extern	volatile	uint8   BAS_BP;
//extern	volatile	uint8   CNTWL;
//
//extern  volatile    uint16  SS[8];
//extern  volatile    uint8   P1VAL[11];
//extern  volatile    uint8   P1VAL_TEEP[11];

//extern	volatile	uint8	gu8v_rx_guide;
//extern	volatile	uint8	gu8v_tx_guide;
//extern	volatile	__byte_type	gu8v_uart_flag;
//extern	volatile	uint8	Tx_Buff[8];
//extern	volatile	uint8	array_uart_rxbuff[6];

extern	volatile	UINT8_VAL	gu8v_uart_flag;
#define gbv_tx_success 			gu8v_uart_flag.bits.b0
#define gbv_rx_success			gu8v_uart_flag.bits.b1
#define gbv_tb0_flag	 		gu8v_uart_flag.bits.b2
#define gu8v_uart_flag3 		gu8v_uart_flag.bits.b3
#define gu8v_uart_flag4			gu8v_uart_flag.bits.b4
#define GPRST	 		        gu8v_uart_flag.bits.b5
#define TI			            gu8v_uart_flag.bits.b6
#define RI			            gu8v_uart_flag.bits.b7
//extern	volatile    uint8 btt_cnt;
//extern	volatile    uint8 step;
//extern	volatile    uint8 MS10JSQ;
//extern	volatile    uint8 timegsm;
//extern	volatile    uint8 Rx_Size;
//extern	volatile    uint8 Timer_Flag_t10ms_Count;
//static volatile uint16 PLS_SOT1[24]__attribute__((at(0x280)));


static volatile uint8	R_TIME[6]	__attribute__((at(0x380)));
#define	R_YEAR  R_TIME[0]
#define	R_MONTH R_TIME[1]
#define	R_DAY R_TIME[2]
#define	R_CLOCK_HOUR R_TIME[3]
#define	R_CLOCK_MINUTE R_TIME[4]
#define	R_CLOCK_SECOND R_TIME[5]


static volatile uint8 gsm_pow    			__attribute__((at(0xB2)));

static volatile uint8 R_SEARCH_SN    __attribute__((at(0x3AF)));
static volatile uint8 R_SEARCH_SN_DISP __attribute__((at(0x3AE)));
static volatile uint8 R_CURRENT_SN_DISP __attribute__((at(0x3AD)));
static volatile uint8 R_CURRENT_SN __attribute__((at(0x3AC)));

//static volatile uint16 old_pres_avl __attribute__((at(0x3AA)));
//static volatile uint16 s_pres_avl2 __attribute__((at(0x3A8)));
//static volatile uint16 s_pres_avl15 __attribute__((at(0x3A6)));
//
static volatile uint8 gu8v_wake_up_time __attribute__((at(0x3A5)));
static volatile uint8 Timer_Flag_t10ms_Count __attribute__((at(0x3A4)));
static volatile uint8 Rx_Size __attribute__((at(0x3A3)));
static volatile uint8 btt_cnt __attribute__((at(0x3A2)));
static volatile uint8 R_EED_READ __attribute__((at(0x3A1)));
static volatile uint8 R_EEPROM_DATA __attribute__((at(0x3A0)));

static volatile uint8 step    __attribute__((at(0x39F)));
static volatile uint8 MS10JSQ __attribute__((at(0x39E)));
static volatile uint8 timegsm __attribute__((at(0x39D)));
static volatile uint8 EER_CNT __attribute__((at(0x39C)));

static volatile uint16 old_pres_avl __attribute__((at(0x39A)));
static volatile uint16 s_pres_avl2 __attribute__((at(0x398)));
static volatile uint16 s_pres_avl15 __attribute__((at(0x396)));

static volatile uint16 PLSFTM __attribute__((at(0x394)));
static volatile uint16 PLSBUF __attribute__((at(0x392)));
static volatile uint8 OLD_PLSCNT __attribute__((at(0x391)));
static volatile uint8 PROCESS __attribute__((at(0x390)));

static volatile uint8 PLSFTM1 __attribute__((at(0x3FF)));
static volatile uint8 PLSFTM0 __attribute__((at(0x3FE)));
static volatile uint8 MAXIHB __attribute__((at(0x3FD)));
static volatile uint8 MINIHB __attribute__((at(0x3FC))); 
static volatile uint8 IHB_COUNT __attribute__((at(0x3FB)));
static volatile uint8 P_PWMCNT  __attribute__((at(0x3FA)));

static volatile uint16  OLD_PRE_SYS __attribute__((at(0x3F8)));
static volatile uint16  OLD_PRE_DIA __attribute__((at(0x3F6)));
static volatile uint16  LOW_V __attribute__((at(0x3F4)));
static volatile uint16  SPRE3 __attribute__((at(0x3F2)));
static volatile uint16  SPRE2 __attribute__((at(0x3F0)));


static volatile uint16 P012_avg __attribute__((at(0x3EE)));
static volatile uint16 close_time __attribute__((at(0x3EC)));
static volatile uint16 close_time1 __attribute__((at(0x3EA)));
static volatile uint16 JIANE __attribute__((at(0x3E8)));
static volatile uint16 pres_ad_0 __attribute__((at(0x3E6)));		  //4压力点
static volatile uint16 pres_ad_100 __attribute__((at(0x3E4)));
static volatile uint16 pres_ad_200 __attribute__((at(0x3E2)));
static volatile uint16 pres_ad_300 __attribute__((at(0x3E0)));

static volatile uint8  MAX_PRE __attribute__((at(0x3DF)));
static volatile uint8  COUNT1_JIA __attribute__((at(0x3DE)));
static volatile uint8  BAS_L1 __attribute__((at(0x3DD)));
static volatile uint8  Uart_tx_buf __attribute__((at(0x3DC)));
static volatile uint8  counter2ms __attribute__((at(0x3DB)));
static volatile uint8  Over300 __attribute__((at(0x3DA)));
static volatile uint8  P1VAL_B __attribute__((at(0x3D9)));
static volatile uint8 po1 __attribute__((at(0x3D8)));
static volatile uint8 max616 __attribute__((at(0x3D7)));
static volatile uint8 max816 __attribute__((at(0x3D6)));
static volatile uint8 S_PCNT __attribute__((at(0x3D5)));
static volatile uint8 COUNT1_XIA __attribute__((at(0x3D4)));
static volatile uint8 COUNT1 __attribute__((at(0x3D3)));
static volatile uint8 PRE_BUF __attribute__((at(0x3D2)));
static volatile uint8 MAX_WAVE_BUF __attribute__((at(0x3D1)));
static volatile uint8 dowm_time __attribute__((at(0x3D0)));

static volatile uint8 OLD_M1_PH __attribute__((at(0x3CF)));
static volatile uint8 OLD_M1_PL __attribute__((at(0x3CE)));
static volatile uint8 M1_PL __attribute__((at(0x3CD)));
static volatile uint8 M1_PH __attribute__((at(0x3CC)));
static volatile uint8 M1_PRE __attribute__((at(0x3CB)));
static volatile uint8 OLD_PRE __attribute__((at(0x3CA)));
static volatile uint8 DASP1 __attribute__((at(0x3C9)));
static volatile uint8 S_PCNT2 __attribute__((at(0x3C8)));
static volatile uint8 S_PCNT15 __attribute__((at(0x3C7)));
static volatile uint8 CNT_WL __attribute__((at(0x3C6)));
static volatile uint8 WAVE_count __attribute__((at(0x3C5)));
static volatile uint8 MAX_WAVE __attribute__((at(0x3C4)));
static volatile uint8 PLSCNT __attribute__((at(0x3C3)));
static volatile uint8 BUF_M1PRE __attribute__((at(0x3C2)));
static volatile uint8 BUF_M1PH __attribute__((at(0x3C1)));
static volatile uint8 BUF_M1PL __attribute__((at(0x3C0)));

static volatile uint16  pwm_val1 __attribute__((at(0x3BE)));
static volatile uint16  counter9ms __attribute__((at(0x3BC)));
static volatile uint16  P0_BUF __attribute__((at(0x3BA)));
static volatile uint16  M1_PH_tp __attribute__((at(0x3B8)));
static volatile uint16  ELE_CNT __attribute__((at(0x3B6)));
static volatile uint16  s_pres_avl   __attribute__((at(0x3B4)));
static volatile uint16  FTM31 __attribute__((at(0x3B2)));
static volatile uint16  PUMPPRE __attribute__((at(0x3B0)));

static volatile uint8 Rx_Buff0[85]__attribute__((at(0x280)));
static volatile uint8 R6BUF_SOT[48]__attribute__((at(0x280)));
//bank4都定义完了
static volatile uint16 P1_ad[8]__attribute__((at(0x2F0)));
static volatile uint16 P0_ad[8]__attribute__((at(0x1F0))); 
static volatile uint8 PLS_SOT[48]__attribute__((at(0x180)));
static volatile uint8 R5BUF_SOT[48]__attribute__((at(0x1b0)));
//static volatile uint16 R5BUF_SOT11[16]__attribute__((at(0x180)));
//static volatile uint16 PLS_SOT11[16]__attribute__((at(0x1b0)));
    
static volatile _up_data  up_data __attribute__((at(0x180))); 

static volatile UINT8_VAL SEG[32]__attribute__ ((at(0x400)));     //这里是设为LCD的SEG数组


static volatile uint8 SFR_FC0	__attribute__ ((at(0x143)));     //
static volatile uint8 SFR_FC1	__attribute__ ((at(0x144)));     //
static volatile uint8 SFR_FC2	__attribute__ ((at(0x145)));     //

static volatile UINT8_VAL SFR_iar1	__attribute__ ((at(0x02)));     //

#endif