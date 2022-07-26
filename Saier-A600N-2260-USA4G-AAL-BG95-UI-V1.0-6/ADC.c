#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

/*******************************************************************************************
** 函数名称: Samlpe_Adc1
** 函数描述: 采样ADC
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
uint16 Samlpe_Adc1(uint8 ch)
{
	uint16 adval;
	uchar ad_cnt,tm_emi;

	tm_emi = _emi;
	_emi = 0;
	
	_sadc0 = 0B00111111;
	_sadc1 = 0B11101111;
	
	ad_cnt =0;
	switch(ch)
	{

		case 0:  _sadc0 &=0xf0;  _pcs05 =1 ;_pcs04 =1 ; break;	// pc2 an0
		case 1:  _sadc0 &=0xf1;  _pcs07 =1 ;_pcs06 =1 ; break;	// pc3 an1
		case 2:  _sadc0 &=0xf2;  _pcs01 =1 ;_pcs00 =1 ; break;	// pc0 an2
		case 3:  _sadc0 &=0xf3;  _pcs03 =1 ;_pcs02 =1 ; break;	// pc1 an3	
		case 4:  _sadc1 &=0x3f;  break;	// pgao2
		case 5:  _sadc1 &=0x5f;  break;	// vscf		
		case 6:  _sadc1 &=0x7f;  break;	// vscfr				
		case 7:  _sadc1 &=0x9f;  break;	// vbat		
	}
	_start = 0;
	_start = 1;
	_start = 0;		
	while(_adbz != 0)
	{
	} 
	//先讀低位后讀高位
	ad_cnt	= _sadol;
	adval=_sadoh;
	adval<<=8;
	adval=adval+ad_cnt;
	ADCVALV.Val =adval>>2;
	_emi = tm_emi;
	return(ADCVALV.Val);
}
 
/*******************************************************************************************
** 函数名称: Samlpe_Adc
** 函数描述: 采样ADC
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
uint16 Samlpe_Adc(uint8 ch)
{
	uint16 adval;
	uchar ad_cnt;
	_sadc0 = 0B00111111;
	_sadc1 = 0B11101111;
	
	ad_cnt =0;
	switch(ch)
	{

		case 0:  _sadc0 &=0xf0;  _pcs05 =1 ;_pcs04 =1 ; break;	// pc2 an0
		case 1:  _sadc0 &=0xf1;  _pcs07 =1 ;_pcs06 =1 ; break;	// pc3 an1
		case 2:  _sadc0 &=0xf2;  _pcs01 =1 ;_pcs00 =1 ; break;	// pc0 an2
		case 3:  _sadc0 &=0xf3;  _pcs03 =1 ;_pcs02 =1 ; break;	// pc1 an3	
		case 4:  _sadc1 &=0x3f;  break;	// pgao2
		case 5:  _sadc1 &=0x5f;  break;	// vscf		
		case 6:  _sadc1 &=0x7f;  break;	// vscfr				
		case 7:  _sadc1 &=0x9f;  break;	// vbat		
	}
	_start = 0;
	_start = 1;
	_start = 0;		
	while(_adbz != 0)
	{
	} 
	//先讀低位后讀高位
	ad_cnt	= _sadol;
	adval=_sadoh;
	adval<<=8;
	adval=adval+ad_cnt;
	return(adval>>2);	
}
