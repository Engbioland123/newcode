#ifndef __DEFINEPORT_H__
#define __DEFINEPORT_H__

typedef unsigned char   uchar;	//1 byte
typedef unsigned long   ulong;	//4 byte
typedef unsigned char   BOOL;	//1 byte 
typedef unsigned short	ushort;	//2 byte
typedef unsigned long   uint; 	//4 byte

#define Failure_buff_start_address 21 //���㷽ʽ��10�黺����10��BYTE,10�黺������40��BYTE
#define IMEI_start_address 41
#define IMSI_start_address 56
#define CELL_LAC_address 73
#define Mem_address_page 64
#define Mem_start_address 	0x77c0					//��ʷ��¼������ʼ��ַ
#define Mem_url_address  	0x7f40					//URL��ַ
#define Mem_back_address  	0x7f80					//У׼���ݵ�ַ
#define Mem_adjust_address  0x7fc0					//У׼��ַ
#define Mem_page_num 		24						//ÿҳ��¼��
#define Mem_page_length 	21						//��ʷ��¼ҳ��
#define Max_Mem_sequence 	500						//��ʷ��¼ҳ�� * ÿҳ��¼��
#define Max_sequence 		1000		 			//��ʷ��¼�����˫��
#define Mem_log_length 		5						//������¼��ռ�ֽڳ���

#define GSM_max_time 105 //120������

#define NB_MODE 		1 //NBģʽ
#define POWER_MODE 		0 //1��ͨѶģ�鳣����0��ͨѶģ����Ҫʱ����


#define  testmode 1

static volatile uchar LcdRam[32] __attribute__((at(0x180))); // LCD RAM �ڴ�

typedef struct Package_header
{	
	uchar  FLAG1;          		  
	uchar  FLAG2;	       
	uchar  VER;
	uchar  ID;
	uchar  RES[4];
	ushort  LEN;
	uchar  H_CHK;
	uchar  D_CHK;
}TPackage_header;
typedef struct Package_time
{	
	ushort  YEAR;
	uchar  MONTH;     // 		  
	uchar  DAY;	      // 
	uchar  HOUR;
	uchar  MINUTE;
	uchar  SECOND;
	uchar  RES;
}TPackage_time;
typedef union	tagBLOOD_Package
{	
	uchar   bytes[128];
	ushort	adc_buff[64];
	struct BLOOD_Package
	{
		uchar Head[2];	//��ʼ��
		uchar VER[2]; //�汾
		uchar User; //�û�
		uchar Customer[2];//�ͻ���
		uchar Model[2];//������
		uchar Device[2];//������
		uchar Serial_ID[9];//���к�
		uchar Reserved[6];//Ԥ��
		uchar Value[3];//Ѫ��ֵ
		uchar Year[2];		//��
		uchar Month[2];		//��
		uchar Day[2];			//��
		uchar Hour[2];			//ʱ
		uchar Minute[2];		//��
		uchar Check_sum[4];	//��У��
	}Package;
	struct BLOOD_Package_9_health
	{
		TPackage_header header;
		uchar UID[24];  //�û�ID
		uchar DID[8];   //�豸ID
		uint  D_SYNC;   //����ͬ������
		TPackage_time time;//���������ں�ʱ��
		float  GLU;		//Ѫ��
		uchar FLAG[2];	//��ǰ�ͺ��־
		uchar RES[4];//������
		uchar CTYPE;//���к�
		uchar UPLOAD;//Ԥ��
	}Package_9_health;
}TFBLOOD_Package, *PFBLOOD_Package;
static volatile TFBLOOD_Package BLOOD_Package __attribute__((at(0x280)));

typedef union  tagMAINFlags
{
	uint MAINFlags;
 	struct
	{
		ushort May_reicev_uart		: 1;  //���ڽ��������־
		ushort NO_Temperature       : 1;  //���²�ģʽ
		ushort Show_Memory         	: 1;  //�鿴����
		ushort trigger              : 1;  //��ֽ�����־
		ushort Test_paper			: 1;  //��ֽ״̬
		ushort CHRC                 : 1;  //���ڳ��
		ushort point				: 1;  //С����
		ushort ready				: 1;  //С����
		
		ushort KETONE               : 1;  //ͪ��ƫ�߾�ʾ
		ushort Before               : 1;  //��ǰ�ͺ�
		ushort TestKeyboad          : 1;  //�����ɿ��굼 
		ushort uart_reicev_flag     : 1;  //������ɱ�־ 
		ushort Blood_drop			: 1;  //��Ѫ״̬
		ushort Win_task			    : 1;  //�Ƿ��������״̬ 
		ushort Mmol_falg            : 1;  //Ѫ�ǵ�λ
		ushort power_on 		    : 1;  //������־
		ushort test_falg			: 1;  //�궨
		ushort Bluetooth            : 1;  //����
		ushort Battery_LO           : 1;  //�͵�
		ushort Memory_Send          : 1;  //���ڷ�������
		ushort GSM_On				: 1;  //GSMģ���ϵ�״̬ 1Ϊ�����ϵ� 
		ushort GSM_Open				: 1;  //GSMģ���Ѵ� 
		ushort GSM_Send_OK			: 1;  //GSM���ͳɹ�
		ushort GSM_Send_over		: 1;  //GSM���ͽ���
		ushort Send_begin			: 1;  //GSM���Ϳ�����
		ushort Mem_sequence_falg	: 1;  //�����Ƿ��Ѵ���󻯣�
		ushort flash_flag			: 1;  //��˸��־��1������1��
		ushort Send_flag			: 1;  //�ϴ���־��Ϊ1�ϴ���Ϊ0���ϴ�
		ushort Call_Ready			: 1;  //����ֽ�������һ��ŵ�Ѫ����1������ʱ����ִ�кܶಽ��
  	}Bits;  
}TMAINFlags;

typedef union tagtaskInfos
{
	uchar  bytes[14];
	struct
	{
		TMAINFlags  Flags;             		// ��ʶ
		uchar       Class;					// �����α�־
		uchar       CTL_mode;				// ֵ��ģʽ
		uchar		Battery_Val;			// ��ص���ֵ
		uchar       uart_reicev_count;		// UART�ѽ��ո���
		uchar 		uart_reicev_count_set; 	// UART��Ҫ���ո���
		uchar       Error_Count;          	// ���ճ������
		uchar       Error_Loop_Count;       // GSM�������
		uchar		Seconds;				// ��Ѫ���ʱ����
		uchar 		GSM_Signal;				// �����ź�ǿ��ֵ
		
	}Datas;
}TtaskInfos, *PtaskInfos;

static volatile TtaskInfos SystemFlags __attribute__((at(0x380)));	//14 byte
static volatile uchar flash[16] __attribute__((at(0x38e)));//16 byte
static volatile uchar disp_buff[16] __attribute__((at(0x39e)));//16 byte
static volatile uchar sys_time __attribute__((at(0x3ae)));//1 byte
static volatile uchar Error_number __attribute__((at(0x3af)));//1 byte
//static volatile PFBLOOD_Package pData __attribute__((at(0x3b0)));	//2 byte

static volatile ushort sys_Year __attribute__((at(0x3b0))) ;//��		//2 byte
static volatile uchar sys_Month __attribute__((at(0x3b2))) ;//��		//1 byte
static volatile uchar sys_Day __attribute__((at(0x3b3)));//��			//1 byte
static volatile uchar sys_Hour __attribute__((at(0x3b4)));//ʱ			//1 byte
static volatile uchar sys_Minute __attribute__((at(0x3b5)));//��		//1 byte
static volatile uchar sys_Second __attribute__((at(0x3b6)));//��		//1 byte
//static volatile uchar Second __attribute__((at(0x3b7)));				//1 byte
//static volatile uchar Sleep_time __attribute__((at(0x3b8)));			//1 byte
static volatile uint Project_Sequence __attribute__((at(0x3b9)));   	//4 byte		//��Ʒ�������к�		
static volatile ushort Mem_sequence __attribute__((at(0x3bd))) ;		//2 byte		//��������
static volatile uint Blood_Sequence __attribute__((at(0x3bf)));			//4 byte
static volatile uint Blood_glucose __attribute__((at(0x3c3)));			//4 byte
static volatile uchar IP_address[20] __attribute__((at(0x3c7)));			//20 byte
static volatile uchar test_buff[22] __attribute__((at(0x3db)));		//20 byte
//static volatile PFBLOOD_Package pData __attribute__((at(0x3ef)));		//2 byte

static volatile uchar Mem_sequence_falg __attribute__((at(0x3f1)));		//1 byte
static volatile uint AD_value __attribute__((at(0x3f2))) ;//4 byte
static volatile uchar Temperature_coefficient __attribute__((at(0x3f6)));		//1 byte
static volatile uchar Temperature_CTL_coefficient __attribute__((at(0x3f7)));		//1 byte
static volatile ushort Pub_temp __attribute__((at(0x3f8)));				//2 byte
static volatile ushort Mem_sequence_count __attribute__((at(0x3fa)));		//2 byte	//��ǰ����λ��
static volatile uchar Old_Second __attribute__((at(0x3fc)));		//1 byte
static volatile uchar staic_Temperature __attribute__((at(0x3fd))); 	//1 byte
static volatile uchar Key_value __attribute__((at(0x3fe)));		//1 byte
//static volatile uchar Gsm_timer __attribute__((at(0x3ff)));		//1 byte

static volatile uchar comEnterStep __attribute__((at(0x480)));		//���벽��
static volatile uchar comEnterCount	__attribute__((at(0x481)));		//�������
static volatile uchar comRestartflag	__attribute__((at(0x482)));		//�������
static volatile uchar comRestartCount	__attribute__((at(0x483)));		//��������
static volatile uchar productYear __attribute__((at(0x484)));		//��Ʒ�������
static volatile uchar productMonth __attribute__((at(0x485)));		//��Ʒ�����·�
static volatile char httptemp[35]	__attribute__((at(0x486)));		//35 byte
static volatile ushort Second __attribute__((at(0x4BB)));				//2 byte
static volatile ushort Sleep_time __attribute__((at(0x4BD)));			//2 byte
static volatile ushort  uart_time __attribute__((at(0x4BF)));			//2 byte

static volatile ushort Gsm_timer __attribute__((at(0xF0)));		//2 byte

#define  Temperature_Channel   1
#define  Battery_Channel       2
#define  Blood_Channel         3
 
#define BIT(X)          (1 << X)
#define BIT_REV(X)      (~BIT(X))


#define MSB(x)          (((x) >> 8) & 0xFF)
#define LSB(x)          ((x) & 0xFF)

#define SET_BIT(x, y)   (x |= BIT(y))
#define GET_BIT(x, y)   (x & BIT(y))
#define CLS_BIT(x, y)   (x &= BIT_REV(y))
#define ISTRUE(x, y)    ( GET_BIT(x, y) == BIT(y) )
#define ISFALSE(x, y)   ( GET_BIT(x, y) != BIT(y) )

#define BitIsHi(x, y)   ( GET_BIT(x, y) == BIT(y) )
#define BitIsLo(x, y)   ( GET_BIT(x, y) != BIT(y) )
#define SetBitHi(x, y)  (x |= BIT(y))
#define SetBitLo(x, y)  (x & BIT(y))

#define  WDR()     _clrwdt()   // ι��
#define _NOP()     _nop()  // ��ָ��
#define _CLI()     asm("cli")  // �ر����ж�
#define _SEI()     asm("sei")  // �����ж�
#define _SLEEP()   _halt()  // ����

#define TICK_T(x)                 ( x / 16 ) 

//	�˿�ģʽ
//	DDRn  : ���ŵķ���
//	PORTn : ���ֵ
//	PINn  : ����ֵ


#define IoGetCtrlDir(x)		_p ## x ## c
#define IoGetPort(x)        _p ## x 
#define IoGetPortPU(x)      _p ## x ## pu 
#define IoGetPortWU(x)      _p ## x ## wu 

#define IoModeOut       CLS_BIT
#define IoModeIn        SET_BIT

#define SetIoMode( x, y, set )	              set(IoGetCtrlDir(x), y);	
// ���/���� 
#define SetIoModeOut( x, y )	              SetIoMode(x, y, IoModeOut); 
// ���� 
#define SetIoModeIn( x, y )	                  SetIoMode(x, y, IoModeIn); 
 
#define IoPuHi( x, y )                        SET_BIT(IoGetPortPU(x), y)				 
#define IoPuLo( x, y )                        CLS_BIT(IoGetPortPU(x), y)

#define IoSetHi(x, y)                         SET_BIT(IoGetPort(x), y)
#define IoSetLo(x, y)                         CLS_BIT(IoGetPort(x), y)

#define IoIsTrue(x, y)                        ISTRUE( IoGetPort(x), y )
#define IoIsFalse(x, y)                       ISFALSE( IoGetPort(x), y )


//�˿��������״̬ �˺궨��Ҫ���� PORT_

	    


#define IoIsHi(x)           IoIsTrue( PORT_ ## x, x )
#define IoIsLo(x)           IoIsFalse( PORT_ ## x, x )

#define SetIoHi( x )        IoSetHi( PORT_ ## x, x) 					 
#define SetIoLo( x )        IoSetLo( PORT_ ## x, x) 

#define SetPortHi( x )      IoSetHi( PORT_ ## x, x)  					 
#define SetPortLo( x )      IoSetLo( PORT_ ## x, x) 

#define SetIoOutHi( x )     SetIoModeOut( PORT_ ## x, x); IoSetHi( PORT_ ## x, x);  IoPuLo( PORT_ ## x, x)
#define SetIoOutLo( x )     SetIoModeOut( PORT_ ## x, x); IoSetLo( PORT_ ## x, x);  IoPuLo( PORT_ ## x, x)

#define SetIoInHi( x )      SetIoModeIn( PORT_ ## x,  x); IoPuHi( PORT_ ## x, x)
#define SetIoInLo( x )      SetIoModeIn( PORT_ ## x, x);  IoPuLo( PORT_ ## x, x)
 
#define SetIoOut( x )       SetIoModeOut( PORT_ ##  x, x)				 
#define SetIoIn( x )        SetIoModeIn( PORT_ ##  x, x) 

#define type_G999		0
#define type_429		1
#define Line_type	type_G999

#define V23   		0	
#define V25   		1
#define V27   		2
#define V29   		3	
#define V30   		4
#define Number9		5
#define Project_mode V25

#define TCPIP      	0		//ע�����ѡTCPIP��ʽ��ʱ��У��ҲҪ��
#define HTTP       	1
#define Project_code HTTP

#define POST       	0
#define Get			1
#define Send_mode	Get 


#define aiaole			10			//������
#define dongruan		11			//����
#define meiguotest		12			//����������
#define taiwantest		13			//̨�忨����


#define customer	meiguotest

#if (customer == meiguotest)//����������
	#define HTTPS_MODE 		1 //HTTPSģʽ
#else
	#define HTTPS_MODE 		0 //HTTPSģʽ
#endif

#if (customer == meiguotest)//����������
	#define HTTPS_GET 		0
	#define HTTPS_POST 		1
#else
	#define HTTPS_GET 		1
	#define HTTPS_POST 		0
#endif

#if (customer == aiaole)//������
	#define customer_url "http://tf.ydjk5.com/gprs/receive/api/data?data="
#elif (customer == dongruan)//����
	#define customer_url "http://dm.xikang.com/cityapi/client/bioland/gluDataUpload?data="
#elif (customer == meiguotest)//���������Ե�ַ
	//#define customer_url "https://API.evelyn.one/bioland"
	#define customer_url "https://api.evelyn.one/bioland?q="
#elif (customer == taiwantest)//̨�忨���Ե�ַ
	#define customer_url "http://tf.my-vcloud.com/gprs/receive/api/data?data="
#endif

////////////////////////////////// ��ʼ�����///////////////////////////////////// 
#define TGbusy   				0
#define PORT_TGbusy				d
#define TGdata 					5
#define PORT_TGdata				b
#define TGReset  				6
#define PORT_TGReset			b
#define LED_SDA					5
#define PORT_LED_SDA    		b
#define LED_CLK					6
#define PORT_LED_CLK    		b
#define LED_CS					6
#define PORT_LED_CS     		d
#define Uart_Tx					0
#define PORT_Uart_Tx    		h
#define LED_VCC					1
#define PORT_LED_VCC    		d
#define GSM_Power1              7       
#define PORT_GSM_Power1		    a
#define GSM_Power2              6       
#define PORT_GSM_Power2		    a
#define UART_WAKE               5       
#define PORT_UART_WAKE          a        
#define STRIP                   4       
#define PORT_STRIP              a
#define M_Key                   3       
#define PORT_M_Key              a
#define S_Key                   2       
#define PORT_M_Key              a
#endif
