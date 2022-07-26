#ifndef __ad__
#define __ad__

#include "HT45F67.h"
#include "DEFINEPORT.h"

void OP_set();
void AD_set();
void test_OP();
void get_lowPwd(uchar Channel,uchar flag);//标定读AD时，flag为0

#endif