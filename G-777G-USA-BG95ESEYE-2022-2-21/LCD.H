#ifndef __LCD__
#define __LCD__
#include "HT45F67.h"
#include  "DEFINEPORT.h"
void show_display();
void transformation();
//void Bat_run();
void show_battery();
//void Blood_over(uchar i);
//void displey_CTL();
void displey_YES();
void displey_DEL();
void displey_EB();
void displey_EU();

void Show_VER();
void Show_PC();
void Show_usb();
void Show_CLOSE();
void Show_OPEN();
void Show_OFF();
void Show_Et();
void Show_EF();
void Show_EE();
void Show_000();
void Show_END();
void displey_test();
void Update_time();
void Show_Big_number(uchar *p,ushort dat,uchar flag);
void disp(uchar uiAddress,uchar ucData);
#endif