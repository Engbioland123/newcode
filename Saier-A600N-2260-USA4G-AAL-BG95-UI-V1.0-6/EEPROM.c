#include "BH67F2260.h"
#include "typedef.h"
#include "define.h"

/********************************************************************
Function:	Read_EEprom
INPUT	:	
OUTPUT	:	
NOTE	:
*******************************************************************/
uint8	SBR_EEPROM_READDATA(uint8 addr)
{
	uint8 rdata,tm_emi;

	tm_emi = _emi;
	_emi = 0;
	_eea = addr;
	_mp1h = 1;
	_mp1l = 0x40;
	_iar1 |=0x2;				//enable RDEN
	_iar1 |=0x1;				//active READ 
	while((_iar1 & 0x01) !=0);		//wait read end
	rdata = _eed;
	_iar1 &=	0xfD;				//disable RDEN	
	_emi = tm_emi;
	return (rdata);
}
 
/********************************************************************
Function:	Write_EEprom
INPUT	:	
OUTPUT	:	
NOTE	:
*******************************************************************/
void EEPROM_WRITING(uint8 addr,uint8 data1)
{
	uint8 tm_emi;
	tm_emi = _emi;
	_emi = 0;	
	_eea = addr;
	_eed = data1;
	_mp1h = 1;
	_mp1l = 0x40;
	_iar1	|=	0x8;				//enable WREN
	_iar1	|=	0x4;				//active write 
	GCC_NOP();
	while((_iar1 & 0x04) !=0);		//wait write end
	_iar1	&=	0xf7;				//disable WREN	
	_emi = tm_emi;	
}

/********************************************************************
Function:	Write_EEprom
INPUT	:	
OUTPUT	:	
NOTE	:
*******************************************************************/
void EEPROM_WRITING_INT(uint8 addr,uint8 data1)
{
	uint8 tm_emi;
	tm_emi = _emi;
	_emi = 0;	
	_eea = addr;
	_eed = data1;
	_mp1h = 1;
	_mp1l = 0x40;
	_iar1	|=	0x8;				//enable WREN
	_iar1	|=	0x4;				//active write 
	GCC_NOP();
	while((_iar1 & 0x04) !=0);		//wait write end
	_iar1	&=	0xf7;				//disable WREN	
	_emi = tm_emi;	
}

