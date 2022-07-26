#include "HT45F67.h"
#include "Defineport.h"
#include "DELAY.h"

void me_delay_100us()
{
	volatile uchar i=18;	
	while(i)
	{
		i--;
	}
}

void me_delay_ms(ushort k)
{
	volatile ushort i;
	volatile uchar i2;
	for(i=0;i<k;i++)
	{
		for(i2=0;i2<11;i2++)
		{
			me_delay_100us();
			WDR();	
		}		
	}
}