#ifndef __UART__
#define __UART__

#include "HT45F67.h"
#include  "DEFINEPORT.h"

typedef enum AT_COMMAND
{	
	E_COMMAND_AT_CPAS,
	E_COMMAND_AT_QPOWD_0,
	E_COMMAND_AT_QPOWD_1,

	E_COMMAND_END
}EAT_COMMAND;

typedef enum
{
	e_nb_CFUN,
	e_nb_ATE0,
	e_nb_QGMR,
	e_nb_CMEE,
	e_nb_GSN,
	e_nb_CPIN,
	e_nb_CIMI,
	e_nb_autosel,
	e_nb_QCCID,
	e_nb_QIACT,
	e_nb_QIACT2,
	e_nb_QICSGP,
	e_nb_BAND,
	e_nb_restart,
	e_nb_NWSCAN,
	e_nb_IOTOP,
	e_nb_SCANSEQ,
	e_nb_CSQ,
	e_nb_CGDCONT,
	e_nb_COPS,
	e_nb_QSSLCFG1,
	e_nb_QSSLCFG2,
	e_nb_QSSLCFG3,
	e_nb_QSSLCFG4,
	e_nb_QHTTPCFG1,
	e_nb_QHTTPCFG2,
	e_nb_QHTTPCFG3,
	e_nb_AUTOSEL,
	e_nb_AUTOSE,
	e_nb_QLTS,
	e_nb_CXREG,
	e_nb_INFO,
	e_nb_COPS1,
	e_nb_CTZU,	
	e_nb_CCLK,
	e_nb_QHTTPURL,		//14
	e_nb_QHTTPURL1,		//15
	e_nb_QHTTPURL2,		//16
	e_nb_QHTTPPOST,		//17
	e_nb_QHTTPPOST1,	//18
	e_nb_QHTTPREAD,		//19
	e_nb_END			//20
} E_NB_STATUS;

void nbIotSignal(void);
void ISR_UART();
void uart_init();
void Uart_delay(volatile uchar k);
void Send_data(uchar dat);
void Uart_Send(unsigned char *data,unsigned char len);
void wait_return(ushort i);
void Uart_Receice_9600(unsigned char *Pdat,unsigned char len);
void Send_data_9600(uchar ch);
void Uart_Send_9600(unsigned char *data,unsigned char len);
void uart_close();
void Receice_News();
void uart_tx_string(uchar *p);
uchar GSM_task(uchar step,ushort buff);
uchar TTS_task(uchar i);
uchar Send_GSM2(ushort a,uchar b);
#endif