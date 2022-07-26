#ifndef _DEFINE_H_
#define _DEFINE_H_

#define BPF_ALARM_MP3 01   //	ལ���������			
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
#define BPF_10_MP3   13	     //һʮ			
//14	һʮһ			
//15	һʮ��			
//16	һʮ��			
//17	һʮ��			
//18	һʮ��			
//19	һʮ��			
//20	һʮ��			
//21	һʮ��			
//22	һʮ��			
#define BPF_20_MP3    23	  //��ʮ			
//24	��ʮ			
//25	��ʮ			
//26	��ʮ			
//27	��ʮ			
//28	��ʮ			
//29	��ʮ			
//30	��ʮ			
#define BPF_100_MP3   31  //	��			
//32	ʮ			
#define BPF_TEST_NUS_MP3   33  //	��ӭʹ�ã���ѡ����Ҫ�������û�			
#define BPF_TEST_STA_MP3   34  //	�뱣�ְ����������ɣ�����������ಿλ����ͬ�ߣ����ڿ�ʼ������			
#define BPF_SHOUSUOYA_MP3  35  //	����Ѫѹ�� ����ѹ��			
#define BPF_SHUZHANGYA_MP3 36  //	��ѹ��			
#define BPF_MAIBO_MP3      37  //	����ÿ���ӣ�			
#define BPF_MMHG_MP3       38  //	���׹���			
#define BPF_CHI_MP3        39  //	��			
#define BPF_WHO_MP3        40  //	��������������֯��׼ ������Ѫѹ��			
#define BPF_AB_NORMAL_MP3  41  //	����			
#define BPF_HIGH_MP3       42  //	ƫ��			
#define BPF_LOWPOWER_MP3   43  //	�������㣬����			
#define BPF_TEST_ERR_MP3   44  //	����,�����²���			
#define BPF_NXTE_MP3       45  //	��һ��			
//46	����			
#define BPF_GPRS_SUC_MP3   48	//�����ϴ��ɹ�			
#define BPF_GPRS_ERR_MP3   49	//����ǰ�������ź����������ѱ��棬�´β����ɹ����ϴ���			
#define BPF_GPRS_STA_MP3   47	//�����������ݣ�����ػ�			


//#define MAX_BP 70
//#define MIN_BP 3 
//
//#define BPF_TEST_NUS_MP3    0x51//	����֮ǰ����������һ���������滺����
//#define BPF_TEST_STA_MP3    0x52//	ע�⣺׼�����⣬��ȷ�ϰ�������ಿλͬ�ߣ���Ҫ�ƶ���˵��
//#define BPF_TEST_END_MP3    0x53//	��������.
//#define BPF_KP_MP3          0x54//	ǧ��
//#define BPF_TEST_AVG_MP3    0x55//	ƽ��Ѫѹ
//#define BPF_TEST_VAR_MP3    0x56//  ����������Ϊ
//#define BPF_SHOUSUOYA_MP3   0x57//	��ѹ
//#define BPF_SHUZHANGYA_MP3  0x58//	��ѹ
//#define BPF_MAIBO_MP3       0x59//	����ÿ����
//#define BPF_WHO_MP3         0x60//	��������������֯��׼,����Ѫѹ.
//#define BPF_AB_NORMAL_MP3   0x61//	����.
//#define BPF_HIGH_MP3        0x62//	���.
//#define BPF_HIGHH_MP3	    0x63//	�ظ�.
//
//#define BPF_THANKS_MP3      0xA0//	�x�xʹ��,ף������
//#define BPF_MMHG_MP3        0xA1//	���׹���
//#define BPF_DIAN_MP3        0xA2//	��
//#define BPF_CHI_MP3         0xA3//	��
//#define BPF_LOWPOWER_MP3    0xA4//  �������� ��������
//#define BPF_TEST_ERR_MP3    0xA5//	������������Ϣ�����Ӻ������²���
//#define BPF_BAI_MP3         0xA6//	��
//#define BPF_ALARM_MP3       0xA7//	ˮ�����ӣ�
//#define BPF_NXTE_MP3        0xA8//	��һ��
//#define BPF_ZZY_MP3 	    0xA9//  ��֮��1��.wav
//
//#define BPF_0_MP3		   0x0001//	��
//
//#define BPF_SHI_MP3	       0x0002//	ʮ
//
//#define BPF_100_MP3	       0x0003//	һ��
//#define BPF_200_MP3        0x0003//	�ɰ�
//#define BPF_300_MP3        0x0003// �ΰ�


#define  SK080G_CountTG11 _pbc2 
#define  SK080G_ResetTG33 _pbc1

#define  SK080G_CountTG1 _pb2
#define  SK080G_ResetTG3 _pb1
#define  SK080G_BusyTG4  _pb0

#define  REL1  _pc3  //��ŷ����ƿ�

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
 
#define  SPEAKBUSYFLAG  MODEFLAG.bits.b6      //�����Ƿ���    
#define  mmHg_Kpa	    MODEFLAG.bits.b7      //��λ�л� 

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
#define	STARTKEYSetKeyHold	b6	//ɨ�谴���ڲ�ʹ��
#define	STARTKEYRecallKeyHold	b7	//ɨ�谴���ڲ�ʹ��
#define	STARTKEYHold	        b8	

//UINT8_VAL TIMERFLAG;
///////////////////////////////////////////////////////////////////////
#define TB0_INT		b0	//TB0�ж�
#define TB1_INT		b1	//TB1�ж�
#define Debounce	b2	//����ɨ��ȥ��
#define NewDay		b3	// 
#define Flashing	b4	// 
#define SearchOver	b5	//
//#define SetKHing	b6	//δ����
//#define ReacllKHing	b7	//δ����

///////////////////////////////////////////////////////////////////////
#define TB0_INT		b0	//TB0�ж�
#define TB1_INT		b1	//TB1�ж�
#define TB1_INT_625	b2	//����ɨ��ȥ��
#define NewDay		b3	// 
#define Display		b4	// 
#define SearchOver	b5	//

///////////////////////////////////////////////////////////////////////
#define Up_dateTime		b0	//TB0�ж�
#define DisplayTime		b3	//TB1�ж�
#define User			b5	//����ɨ��ȥ��

///////////////////////////////////////////////////////////////////////
//#define	SetKey		b0	    //1=SET KEY DOWN
//#define	StartKey	b1	    //1=START KEY DOWN
//#define	RecallKey	b2	    //1=RECALL KEY DOWN
//#define	Modeadd		b3	    //1=MODE KEY DOWN
//#define	SetKeyHold	b4	    //1=SET KEY HOLD 3s
//#define	RecallKeyHold	b5	//1=RECALL KEY HOLD 3s
//#define	Modesub		b6	    //ɨ�谴���ڲ�ʹ��
//#define	ReacllKHing	b7	    //ɨ�谴���ڲ�ʹ��#define RECALLKEY	b3	//set���I����



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

//�Д���ڵ�ַ
#define	START_VECTOR			0x000		//������
#define	INT0_VECTOR				0x004		//Intrrupt 0
#define	INT1_VECTOR				0x008		//Intrrupt 1
#define ADC_VECTOR				0x0C		//ADC �Д�
#define	MF0_VECTOR				0x0010		//�ͺ��Д� 0
#define	MF1_VECTOR				0x0014		//�ͺ��Д� 1
#define MF2_VECTOR				0x018		//�ͺ��Д� 2
#define SCF_VECTOR				0x01C		//SCF�Д� 
#define TB0_VECTOR				0x020		//TB0�Д� 
#define TB1_VECTOR				0x024		//TB1�Д� 
#define UART_VECTOR				0x028		//UART�Д� 
#define SIM_VECTOR				0x02C		//SIM�Д� 
#define SPIA_VECTOR				0x030		//SPIA�Д� 

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