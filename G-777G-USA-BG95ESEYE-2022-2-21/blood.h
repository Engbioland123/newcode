#ifndef __BLOOD__
#define __BLOOD__
#include "HT45F67.h"
#include  "DEFINEPORT.h"
unsigned long  Calculate_blood(unsigned long myAD_value,unsigned long myBlood_glucose);
unsigned long  Calculate_contrul(unsigned long myAD_value,unsigned long myBlood_glucose);
#endif