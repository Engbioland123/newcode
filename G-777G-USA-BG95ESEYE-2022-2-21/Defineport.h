#ifndef __DEFINEPORT_H__
#define __DEFINEPORT_H__

typedef unsigned char   uchar;	//1 byte
typedef unsigned long   ulong;	//4 byte
typedef unsigned char   BOOL;	//1 byte 
typedef unsigned short	ushort;	//2 byte
typedef unsigned long   uint; 	//4 byte

#define Failure_buff_start_address 21 //计算方式，10组缓冲标号10个BYTE,10组缓冲内容40个BYTE
#define IMEI_start_address 41
#define IMSI_start_address 56
#define CELL_LAC_address 73
#define Mem_address_page 64
#define Mem_start_address 	0x77c0					//历史记录保存起始地址
#define Mem_url_address  	0x7f40					//URL地址
#define Mem_back_address  	0x7f80					//校准备份地址
#define Mem_adjust_address  0x7fc0					//校准地址
#define Mem_page_num 		24						//每页记录数
#define Mem_page_length 	21						//历史记录页数
#define Max_Mem_sequence 	500						//历史记录页数 * 每页记录数
#define Max_sequence 		1000		 			//历史记录最大数双倍
#define Mem_log_length 		5						//单条记录所占字节长度

#define GSM_max_time 105 //120秒左右

#define NB_MODE 		1 //NB模式
#define POWER_MODE 		0 //1则通讯模组常开，0则通讯模组需要时开启


#define  testmode 1

static volatile uchar LcdRam[32] __attribute__((at(0x180))); // LCD RAM 内存

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
		uchar Head[2];	//起始码
		uchar VER[2]; //版本
		uchar User; //用户
		uchar Customer[2];//客户码
		uchar Model[2];//机型码
		uchar Device[2];//机种码
		uchar Serial_ID[9];//序列号
		uchar Reserved[6];//预留
		uchar Value[3];//血糖值
		uchar Year[2];		//年
		uchar Month[2];		//月
		uchar Day[2];			//日
		uchar Hour[2];			//时
		uchar Minute[2];		//分
		uchar Check_sum[4];	//和校验
	}Package;
	struct BLOOD_Package_9_health
	{
		TPackage_header header;
		uchar UID[24];  //用户ID
		uchar DID[8];   //设备ID
		uint  D_SYNC;   //数据同步计算
		TPackage_time time;//测量的日期和时间
		float  GLU;		//血糖
		uchar FLAG[2];	//餐前餐后标志
		uchar RES[4];//机种码
		uchar CTYPE;//序列号
		uchar UPLOAD;//预留
	}Package_9_health;
}TFBLOOD_Package, *PFBLOOD_Package;
static volatile TFBLOOD_Package BLOOD_Package __attribute__((at(0x280)));

typedef union  tagMAINFlags
{
	uint MAINFlags;
 	struct
	{
		ushort May_reicev_uart		: 1;  //串口接收允许标志
		ushort NO_Temperature       : 1;  //无温补模式
		ushort Show_Memory         	: 1;  //查看记忆
		ushort trigger              : 1;  //试纸插入标志
		ushort Test_paper			: 1;  //试纸状态
		ushort CHRC                 : 1;  //正在充电
		ushort point				: 1;  //小数点
		ushort ready				: 1;  //小数点
		
		ushort KETONE               : 1;  //酮体偏高警示
		ushort Before               : 1;  //餐前餐后
		ushort TestKeyboad          : 1;  //键盘松开标导 
		ushort uart_reicev_flag     : 1;  //接收完成标志 
		ushort Blood_drop			: 1;  //滴血状态
		ushort Win_task			    : 1;  //是否进入休眠状态 
		ushort Mmol_falg            : 1;  //血糖单位
		ushort power_on 		    : 1;  //开机标志
		ushort test_falg			: 1;  //标定
		ushort Bluetooth            : 1;  //蓝牙
		ushort Battery_LO           : 1;  //低电
		ushort Memory_Send          : 1;  //正在发送数据
		ushort GSM_On				: 1;  //GSM模块上电状态 1为正在上电 
		ushort GSM_Open				: 1;  //GSM模块已打开 
		ushort GSM_Send_OK			: 1;  //GSM发送成功
		ushort GSM_Send_over		: 1;  //GSM发送结束
		ushort Send_begin			: 1;  //GSM发送开如标记
		ushort Mem_sequence_falg	: 1;  //储存是否已达最大化？
		ushort flash_flag			: 1;  //闪烁标志，1秒钟闪1次
		ushort Send_flag			: 1;  //上传标志，为1上传，为0不上传
		ushort Call_Ready			: 1;  //插试纸后，如果过一会才滴血，置1，传送时可免执行很多步骤
  	}Bits;  
}TMAINFlags;

typedef union tagtaskInfos
{
	uchar  bytes[14];
	struct
	{
		TMAINFlags  Flags;             		// 标识
		uchar       Class;					// 程序层次标志
		uchar       CTL_mode;				// 值控模式
		uchar		Battery_Val;			// 电池电量值
		uchar       uart_reicev_count;		// UART已接收个数
		uchar 		uart_reicev_count_set; 	// UART将要接收个数
		uchar       Error_Count;          	// 接收出错次数
		uchar       Error_Loop_Count;       // GSM出错次数
		uchar		Seconds;				// 滴血后计时秒数
		uchar 		GSM_Signal;				// 天线信号强度值
		
	}Datas;
}TtaskInfos, *PtaskInfos;

static volatile TtaskInfos SystemFlags __attribute__((at(0x380)));	//14 byte
static volatile uchar flash[16] __attribute__((at(0x38e)));//16 byte
static volatile uchar disp_buff[16] __attribute__((at(0x39e)));//16 byte
static volatile uchar sys_time __attribute__((at(0x3ae)));//1 byte
static volatile uchar Error_number __attribute__((at(0x3af)));//1 byte
//static volatile PFBLOOD_Package pData __attribute__((at(0x3b0)));	//2 byte

static volatile ushort sys_Year __attribute__((at(0x3b0))) ;//年		//2 byte
static volatile uchar sys_Month __attribute__((at(0x3b2))) ;//月		//1 byte
static volatile uchar sys_Day __attribute__((at(0x3b3)));//日			//1 byte
static volatile uchar sys_Hour __attribute__((at(0x3b4)));//时			//1 byte
static volatile uchar sys_Minute __attribute__((at(0x3b5)));//分		//1 byte
static volatile uchar sys_Second __attribute__((at(0x3b6)));//秒		//1 byte
//static volatile uchar Second __attribute__((at(0x3b7)));				//1 byte
//static volatile uchar Sleep_time __attribute__((at(0x3b8)));			//1 byte
static volatile uint Project_Sequence __attribute__((at(0x3b9)));   	//4 byte		//产品机身序列号		
static volatile ushort Mem_sequence __attribute__((at(0x3bd))) ;		//2 byte		//记忆组数
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
static volatile ushort Mem_sequence_count __attribute__((at(0x3fa)));		//2 byte	//当前记忆位置
static volatile uchar Old_Second __attribute__((at(0x3fc)));		//1 byte
static volatile uchar staic_Temperature __attribute__((at(0x3fd))); 	//1 byte
static volatile uchar Key_value __attribute__((at(0x3fe)));		//1 byte
//static volatile uchar Gsm_timer __attribute__((at(0x3ff)));		//1 byte

static volatile uchar comEnterStep __attribute__((at(0x480)));		//进入步骤
static volatile uchar comEnterCount	__attribute__((at(0x481)));		//进入次数
static volatile uchar comRestartflag	__attribute__((at(0x482)));		//重启标记
static volatile uchar comRestartCount	__attribute__((at(0x483)));		//重启次数
static volatile uchar productYear __attribute__((at(0x484)));		//产品生产年份
static volatile uchar productMonth __attribute__((at(0x485)));		//产品生产月份
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

#define  WDR()     _clrwdt()   // 喂狗
#define _NOP()     _nop()  // 空指令
#define _CLI()     asm("cli")  // 关闭总中断
#define _SEI()     asm("sei")  // 打开总中断
#define _SLEEP()   _halt()  // 休眠

#define TICK_T(x)                 ( x / 16 ) 

//	端口模式
//	DDRn  : 引脚的方向
//	PORTn : 输出值
//	PINn  : 输入值


#define IoGetCtrlDir(x)		_p ## x ## c
#define IoGetPort(x)        _p ## x 
#define IoGetPortPU(x)      _p ## x ## pu 
#define IoGetPortWU(x)      _p ## x ## wu 

#define IoModeOut       CLS_BIT
#define IoModeIn        SET_BIT

#define SetIoMode( x, y, set )	              set(IoGetCtrlDir(x), y);	
// 输出/推挽 
#define SetIoModeOut( x, y )	              SetIoMode(x, y, IoModeOut); 
// 输入 
#define SetIoModeIn( x, y )	                  SetIoMode(x, y, IoModeIn); 
 
#define IoPuHi( x, y )                        SET_BIT(IoGetPortPU(x), y)				 
#define IoPuLo( x, y )                        CLS_BIT(IoGetPortPU(x), y)

#define IoSetHi(x, y)                         SET_BIT(IoGetPort(x), y)
#define IoSetLo(x, y)                         CLS_BIT(IoGetPort(x), y)

#define IoIsTrue(x, y)                        ISTRUE( IoGetPort(x), y )
#define IoIsFalse(x, y)                       ISFALSE( IoGetPort(x), y )


//端口输入输出状态 此宏定义要求定义 PORT_

	    


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

#define TCPIP      	0		//注意如果选TCPIP方式，时间校验也要变
#define HTTP       	1
#define Project_code HTTP

#define POST       	0
#define Get			1
#define Send_mode	Get 


#define aiaole			10			//爱奥乐
#define dongruan		11			//东软
#define meiguotest		12			//美国卡测试
#define taiwantest		13			//台湾卡测试


#define customer	meiguotest

#if (customer == meiguotest)//美国卡测试
	#define HTTPS_MODE 		1 //HTTPS模式
#else
	#define HTTPS_MODE 		0 //HTTPS模式
#endif

#if (customer == meiguotest)//美国卡测试
	#define HTTPS_GET 		0
	#define HTTPS_POST 		1
#else
	#define HTTPS_GET 		1
	#define HTTPS_POST 		0
#endif

#if (customer == aiaole)//爱奥乐
	#define customer_url "http://tf.ydjk5.com/gprs/receive/api/data?data="
#elif (customer == dongruan)//东软
	#define customer_url "http://dm.xikang.com/cityapi/client/bioland/gluDataUpload?data="
#elif (customer == meiguotest)//美国卡测试地址
	//#define customer_url "https://API.evelyn.one/bioland"
	#define customer_url "https://api.evelyn.one/bioland?q="
#elif (customer == taiwantest)//台湾卡测试地址
	#define customer_url "http://tf.my-vcloud.com/gprs/receive/api/data?data="
#endif

////////////////////////////////// 初始化检测///////////////////////////////////// 
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
