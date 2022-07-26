#ifndef _TYPEDEF_H__
#define _TYPEDEF_H__


//#ifndef TRUE
//#define TRUE  1
//#endif
//
//#ifndef FALSE
//#define FALSE 0
//#endif
/********************************************************************************/
/*                        CPU无关性定义                                         */
/********************************************************************************/
typedef unsigned char      uchar;                   //无符号8位整型变量
typedef unsigned short     uint;                    //无符号16位整型变量 

typedef unsigned char      uint8;                   //无符号8位整型变量
typedef signed   char      int8;                    //有符号8位整型变量
typedef unsigned short     uint16;                  //无符号16位整型变量 
typedef signed   short     int16;                   //有符号16位整型变量 
typedef unsigned long      uint32;                  //无符号32位整型变量 
typedef signed   long      int32;                   //有符号32位整型变量 
typedef float              fp32;                    //单精度浮点数（32位长度）
typedef double             fp64;                    //双精度浮点数（64位长度）

//typedef	bit				   Bit;
//typedef	bit				   Bool;
typedef	unsigned char	   Byte;
typedef	unsigned int	   Word;
typedef	unsigned long	   Dword;
typedef union
{
    uint16 Val;
    struct
    {
        uint8 BYTE_L:8;
        uint8 BYTE_H:8;
    } BYTE;
} UINT16_VAL;
typedef union
{
    uint16 Val;
    struct
    {
        uint16 b0:1;
        uint16 b1:1;
        uint16 b2:1;
        uint16 b3:1;
        uint16 b4:1;
        uint16 b5:1;
        uint16 b6:1;
        uint16 b7:1;
        uint16 b8:1;
        uint16 b9:1;
        uint16 b10:1;
        uint16 b11:1;
        uint16 b12:1;
        uint16 b13:1;
        uint16 b14:1;
        uint16 b15:1;  
        
    } bits;
} UINT16_BITS;
typedef union
{
    uint8 Val;
    struct
    {
        uint8 b0:1;
        uint8 b1:1;
        uint8 b2:1;
        uint8 b3:1;
        uint8 b4:1;
        uint8 b5:1;
        uint8 b6:1;
        uint8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union
{
	uint8 CHECKSUM[85];
    struct
    {
	   unsigned char Weakup[2]; 		//1.起始碼
	   unsigned char VER[1];  			//2.版本号
	   unsigned char CA_BUF;
	   unsigned char USER_BUF;  			//3.用户号
//	   unsigned char Customer[2];	  	//4.客戶碼
//	   unsigned char ModelCode[2];		//5.机型代码
	   unsigned char DeviceType[2];		//6.机种码
	   unsigned char Serialnumber[11];	//7.系列号
	   unsigned char SYS[3]; 			//8.高压(3)
	   unsigned char DIA[3]; 			//9.低压(3)
	   unsigned char PUL[3];  			//10.心率 (3)
	   unsigned char year[4];  			//11.年
	   unsigned char month[2];  		//12.0月
	   unsigned char day[2];  			//13.日                             	
	   unsigned char our[2]; 			//14.时
	   unsigned char mini[2];			//15.分	   
	   unsigned char SUM[4];			//16.校验码                      
	   unsigned char IMEI[17];
	   unsigned char IMSI[15];
	   unsigned char jinweidu[10];
    };
} _up_data;




#endif

