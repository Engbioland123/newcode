#ifndef __runTask_h__
#define __runTask_h__

#include "HT45F67.h"
#include  "DEFINEPORT.h"


void Buzzer();
void GSM_turn_ON();
uchar Get_Temperature();
void Get_Battery();
void Get_Charge();
void Put_Memroy(ushort adr);
ushort Get_Memroy(ushort adr);

void Store_Failure_buff();
void Send_Failure_buff();
void SysSleep();
void reivce_data();
uchar Power_ON_OFF();
void run_time();
uchar check_sum();
uchar Gsm_power_off(uchar type);

#endif