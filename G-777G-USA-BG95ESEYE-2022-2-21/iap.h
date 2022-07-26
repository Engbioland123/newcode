#ifndef __IAP_H__
#define __IAP_H__

#include "HT45F67.h"
#include "Defineport.h"  
//extern uchar gu8v_data_buffer[128];
uchar	fun_enable_fwen(void);
void	fun_erase_page(uint flash_addr);
uint	fun_read_word(uint flash_addr);
void	fun_write_cpage(ushort flash_addr,uchar flash_wlength,uchar begin);	 
void	fun_read_page(	uint flash_addr);

#endif
