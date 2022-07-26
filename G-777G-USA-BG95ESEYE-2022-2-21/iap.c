#include "HT45F67.h"
#include "Defineport.h"
	

/********************************************************************
Function:	IAP
********************************************************************/
#define		WRITE_FLASH_MODE		0b10000000	//select write flash rom mode
#define		PAGE_ERASE_MODE			0b10010000	//select page erase mode	
#define		READ_FLASH_MODE			0b10110000	//select read flash rom mode & set fden=1
#define		ENABLE_FWEN_MODE		0b11100000	//select FWEN bit control mode & set bwt=1 

#define		FLASH_PAGE_SIZE			64
#define		FLASH_PAGE_BYTE			FLASH_PAGE_SIZE*2

#define		CONST_DATA_LENGTH		100			//<=128
#define		CONST_FLASH_ADDR		0x0600


//uchar gu8v_data_buffer[128];
//调试校准数据指定


//*************************************************************************************//
//function:	flash memory write enable
//Remark: 	
//*************************************************************************************//
uchar fun_enable_fwen(void)
{
	_emi = 0;
	_fc0 = ENABLE_FWEN_MODE;	//select FWEN (flash memory write enable) bit control mode 
	_fc0 |= 0b00001000;
	_fd1l = 0x00;		//write the correct data pattern into the Flash data registers during the counter
	_fd1h = 0x04;
	_fd2l = 0x0d;
	_fd2h = 0x09;
	_fd3l = 0xc3;
	_fd3h = 0x40;
	while(_fc0 & 0b00001000)		//the devices will clear the FWPEN bit automatically
	{
		_clrwdt();
	}
	_emi = 1;	
	if(_fc0 & 0b10000000)			
	{
		return	1;
	}
	else
	{
		return	0;
	}
}

//*************************************************************************************//
//function:	read the data at the address:flash_addr
//Remark: 	  
//*************************************************************************************//
ushort fun_read_word(ushort flash_addr)
{
	ushort	lu16v_return_read_word;
	_emi = 0;
	_fc0=READ_FLASH_MODE;	//select read flash rom mode
//	_frden=1;	//Flash memory Read Enable Bit
	_fc0 |= 0b00000010;	
	
	_farl=(unsigned char)(flash_addr&0xff);		//write data to Flash address register
	_farh=(unsigned char)((flash_addr>>8)&0xff);
//	_frd=1;		//activate a read cycle
	_fc0 |= 0b00000001;
//	while(_frd)	
	while(_fc0 & 0b00000001)
	
	{
		_clrwdt();
	}
//	_frden=0;	
	_fc0 &= 0b11111101;
	//Flash memory Read Enable Bit
	lu16v_return_read_word = 0;
	lu16v_return_read_word = _fd0h;
	lu16v_return_read_word = lu16v_return_read_word<< 8;
	lu16v_return_read_word+=_fd0l;	
	_emi = 1;	
	return	lu16v_return_read_word;
}


//*************************************************************************************//
//function:	read the data at the address:flash_addr
//Remark: 
//*************************************************************************************//
void fun_read_page_data(ushort flash_addr)
{
	uchar  i;

	_emi = 0;
	for(i=0;i<128;i++)
	{
		fun_read_word(flash_addr);
		BLOOD_Package.bytes[i] = _fd0l;
		//gu8v_data_buffer[i] = _fd0l;
		i++;
		BLOOD_Package.bytes[i]= _fd0h;
		//gu8v_data_buffer[i] = _fd0h;
		flash_addr++;		
	}
	_emi = 1;
}

void fun_read_page(ushort flash_addr)
{
#if 1
	uchar i=0;
	uchar temp1, temp2;
	uchar iDiff = 0;

	if(flash_addr == Mem_back_address)
	{
		fun_read_page_data(Mem_adjust_address);

		for(i = 0; i < 19; i++)
			test_buff[i] = BLOOD_Package.bytes[i];
		temp1 = BLOOD_Package.bytes[71];
		temp2 = BLOOD_Package.bytes[72];

		fun_read_page_data(flash_addr);
		
		for(i = 0; i < 19; i++)
		{
			if(BLOOD_Package.bytes[i] != test_buff[i])
//				BLOOD_Package.bytes[i] = test_buff[i];
				iDiff++;
		}
		if(BLOOD_Package.bytes[71] != temp1)
//			BLOOD_Package.bytes[71] = temp1;
			iDiff++;
		if(BLOOD_Package.bytes[72] != temp2)
//			BLOOD_Package.bytes[72] = temp2;
			iDiff++;
	
		if(iDiff > 0)
			fun_read_page_data(Mem_adjust_address);
	}
	else
		fun_read_page_data(flash_addr);
#else
	fun_read_page_data(flash_addr);
#endif


// #if testmode
//	BLOOD_Package.bytes[0] = 0x25;
//	BLOOD_Package.bytes[1] = 0x01;
//	BLOOD_Package.bytes[2] = 0x01;
//	BLOOD_Package.bytes[4] = 0x02;
//	BLOOD_Package.bytes[5] = 0x01;
//	BLOOD_Package.bytes[6] = 0x19;
//	BLOOD_Package.bytes[7] = 0xE4;
//	BLOOD_Package.bytes[8] = 0x10;
//	BLOOD_Package.bytes[11] = 0x71;
//	BLOOD_Package.bytes[12] = 0x80;
//	BLOOD_Package.bytes[13] = 0x67;
//	BLOOD_Package.bytes[18] = 0x31;
//	BLOOD_Package.bytes[71] = 0xEC;
//	BLOOD_Package.bytes[72] = 0x03;
//	BLOOD_Package.bytes[74] = 0x48;
//	BLOOD_Package.bytes[75] = 0x12;
//	BLOOD_Package.bytes[76] = 0x0A;
//	BLOOD_Package.bytes[77] = 0x01;
//	BLOOD_Package.bytes[78] = 0x09;
//	BLOOD_Package.bytes[79] = 0x2D;
//#endif
}

//*************************************************************************************//
//function:	erase the flash_addr' page 
//Remark: 	 
//*************************************************************************************//
void fun_erase_page(ushort flash_addr)
{
	_emi = 0;
	_fc0=PAGE_ERASE_MODE;						//select page erase mode
	_farl=(unsigned char)(flash_addr&0xff);		//write data to Flash address register
	_farh=(unsigned char)((flash_addr>>8)&0xff);
//	_fwt=1;		//activate a write cycle
	_fc0 |= 0b00000100;	
	while((_fc0 & 0b00000100))
	{
		_clrwdt();
	}
	_emi = 1;	
}


//*************************************************************************************//
//function:	write page with the data:data_buffer[128]
//Remark: 	flash_addr should be the first address of a page
//*************************************************************************************//
void fun_write_cpage(ushort flash_addr,uchar flash_wlength,uchar begin)
{
	unsigned char i;
	_emi = 0;	
	_fc2=0x01;		//initiate clear Write Buffer process
//	while(_clwb)
	while(_fc2 & 0b00000001)	
	{
		_clrwdt();
	}
	_fc0=WRITE_FLASH_MODE;	//select write flash rom mode
	_farl=(unsigned char)(flash_addr&0xff);		//write data to Flash address register
	_farh=(unsigned char)((flash_addr>>8)&0xff);
	for(i=0;i<flash_wlength;i++)	//write data to writer buffer
	{
		_fd0l=	BLOOD_Package.bytes[i + begin];
		i++;
		_fd0h=	BLOOD_Package.bytes[i + begin];
	}
//	_fwt=1;		//activate a write cycle
	_fc0 |= 0b00000100;	
//	while(_fwt)
	while(_fc0 & 0b00000100)
	{
		_clrwdt();
	}
//	_cfwen=0;	//disable the Flash write procedure
	_fc0 &= 0b01111111;		
	_emi = 1;	
}