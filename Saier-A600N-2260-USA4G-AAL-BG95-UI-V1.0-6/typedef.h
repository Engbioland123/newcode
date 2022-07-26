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
/*                        CPU�޹��Զ���                                         */
/********************************************************************************/
typedef unsigned char      uchar;                   //�޷���8λ���ͱ���
typedef unsigned short     uint;                    //�޷���16λ���ͱ��� 

typedef unsigned char      uint8;                   //�޷���8λ���ͱ���
typedef signed   char      int8;                    //�з���8λ���ͱ���
typedef unsigned short     uint16;                  //�޷���16λ���ͱ��� 
typedef signed   short     int16;                   //�з���16λ���ͱ��� 
typedef unsigned long      uint32;                  //�޷���32λ���ͱ��� 
typedef signed   long      int32;                   //�з���32λ���ͱ��� 
typedef float              fp32;                    //�����ȸ�������32λ���ȣ�
typedef double             fp64;                    //˫���ȸ�������64λ���ȣ�

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
	   unsigned char Weakup[2]; 		//1.��ʼ�a
	   unsigned char VER[1];  			//2.�汾��
	   unsigned char CA_BUF;
	   unsigned char USER_BUF;  			//3.�û���
//	   unsigned char Customer[2];	  	//4.�͑��a
//	   unsigned char ModelCode[2];		//5.���ʹ���
	   unsigned char DeviceType[2];		//6.������
	   unsigned char Serialnumber[11];	//7.ϵ�к�
	   unsigned char SYS[3]; 			//8.��ѹ(3)
	   unsigned char DIA[3]; 			//9.��ѹ(3)
	   unsigned char PUL[3];  			//10.���� (3)
	   unsigned char year[4];  			//11.��
	   unsigned char month[2];  		//12.0��
	   unsigned char day[2];  			//13.��                             	
	   unsigned char our[2]; 			//14.ʱ
	   unsigned char mini[2];			//15.��	   
	   unsigned char SUM[4];			//16.У����                      
	   unsigned char IMEI[17];
	   unsigned char IMSI[15];
	   unsigned char jinweidu[10];
    };
} _up_data;




#endif

