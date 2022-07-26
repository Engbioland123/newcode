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
//uint8 e2flag;	        //����
volatile	UINT8_VAL R_KEYSTATUS;
volatile	UINT16_BITS KEYFLAG;
/////////////////////////////////////////////////////////////////////////
//#define	SetKey		b0	//1=SET KEY DOWN
//#define	StartKey	b1	//1=START KEY DOWN
//#define	RecallKey	b2	//1=RECALL KEY DOWN
//#define	ModeKey		b3	//1=MODE KEY DOWN
//#define	SetKeyHold	b4	//1=SET KEY HOLD 3s
//#define	RecallKeyHold	b5	//1=RECALL KEY HOLD 3s
//#define	SetKHing	b6	//ɨ�谴���ڲ�ʹ��
//#define	ReacllKHing	b7	//ɨ�谴���ڲ�ʹ��
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL TIMERFLAG;
/////////////////////////////////////////////////////////////////////////
//#define TB0_INT		b0	//TB0�ж�
//#define TB1_INT		b1	//TB1�ж�
//#define Debounce	b2	//����ɨ��ȥ��
//#define NewDay		b3	// 
//#define Flashing	b4	// 
//#define SearchOver	b5	//
////#define SetKHing	b6	//δ����
////#define ReacllKHing	b7	//δ����
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL R2FLAG;
///////////////////////////////////////////////////////////////////////
//              b0 1: 1.�Ѿ��ҵ���һ�������ķ�壬0.û���ҵ������ķ���Ҫ��ʼ��
//             b1 1:
//             b2 1:
//             b3 1:
//             b4 1:
//             b5   δ����
//             b6   δ����
//             b7   δ����
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL R3FLAG;
//----------------------------------------------------------
// R3FLAG
// Bit 0 : �a��slope 20 ������ 
// Bit 1 : ��һ���½����� c/16
// Bit 2 : �ڶ����½����� 8/16
// Bit 3 : �������y���Σ���һ�����β�Ҫ 
// Bit 4 : ��һ�����΃���
// Bit 5 : ץȡ����ʹ�ã�б���ѵ�� MIN_BP ��
// Bit 6 : 
// Bit 7 : ��һ���r���ɲ����Ĳ��Σ���һ�����β�Ҫ����ֻ������ֵ
//-----------------------------------------------------------
volatile	UINT8_VAL ERFLAG;
///////////////////////////////////////////////////////////////////////
//  ERFLAG     b0 1:     //û����Ҫ�ټ�ѹ����,�ټ�ѹ����ҲҪ�˳� 
//             b1 1:      //�˳���ʾ����EE
//             b2 1:     //��ѹ������ʱ����180��E2 
//             b3 1:
//             b4 1:     //ֹͣ��������ѹ����  
//             b5   δ����
//             b6   δ����
//             b7   δ����
//////////////////////////////////////////////////////////////////////
volatile	UINT8_VAL Usflag;
///////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

volatile	UINT8_VAL MODEFLAG;
///////////////////////////////////////////////////////////////////////
//  MODEFLAG   b0 1:�߶�ģʽ     0  : �͹���ģʽ  MODEFLAG.bits.b0             mode_low=0;
//             b1 1:����������û�в����� 0  :����������û�в�����Modeflag.bits.b1  test_1flg = 0;//����������û�в�����
//             b2 1����ʱ�䳬180�� //uint8 e2flag;	MODEFLAG.bits.b2    ,                                
//             b3 1:��ʾʱ��    0  ������ʱ��	dis_time_off=1;	        //��ʾʱ��
//             b4 1: ������ʼ 0:�����ر�              gbSPEAKFlag=1;//������ʼΪ����״̬
//             b5  //���Ե���,0-1��,1Ϊ2��
//             b6  //�����Ƿ���
//             b7  //��������ͱ�־

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