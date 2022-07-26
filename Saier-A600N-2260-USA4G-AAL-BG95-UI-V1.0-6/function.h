#ifndef _FUNCTION_H_
#define _FUNCTION_H_


void INT_IO(void);
void INT_POWER(void);
void INT_TMR(void);
void INT_LCD(void);
void INT_DAC(void);
void INT_OP(void);
void INT_AD(void);
void INT_INTP(void);
void INT_SYSTEM(void);
void Uart_Init(void);
void FUN_INT1_2_INIT(void);
//-----------------------------------------------------------------------------
void	Ram_Init();

//////////////////////////////////////////////////////////////////////////////////

void GAUGE(void);
uint16 Samlpe_Adc(uint8 ch);
uint16 Samlpe_Adc1(uint8 ch);
uint pres(uint ad);
void STUDY_PRE(void);
void STUDY_PRE1(void);
void STUDY_PRE2(void);
void STUDY_PRE3(void);
//////////////////////////////////////////////////////////////////////////////////
void INT_AD(void);
//////////////////////////////////////////////////////////////////////////////////
void SBR_ENTER_HALTMODE(void);
//////////////////////////////////////////////////////////////////////////////////
void KEYSCAN_INIT(void);
void KEYSCAN(void);//
void SBR_UPDATE_TIME(void);//
void SBR_UPDATE_BTT(void);   
void INT_DATE_TIME(void);//
//////////////////////////////////////////////////////////////////////////////////
void SBR_SAVE_MEMORY(void);//
void SBR_READ_MEMORY(void);//
void SBR_CLEAR_MEMORY(void);//
void SBR_EEPROM_WRITEDATA(uint8);//address:ACC	Data:_R_EEPROM_DATA
uint8 SBR_EEPROM_READDATA(uint8);//address:ACC	Return Data:ACC
//////////////////////////////////////////////////////////////////////////////////
void SBR_FLASHING_ENABLE(void);//
void SBR_FLASHING_DISABLE(void);//
void SBR_FLASHING_TIME(void);

void SBR_TIME_SETTING(void);//
//////////////////////////////////////////////////////////////////////////////////
void LCD_INIT_OFF(void);//全暗
void LCD_INIT_ON(void); //全亮

void  SBR_DISP_DOT_COLD_ON(void);
void  SBR_DISP_DOT_COLD_OFF(void);
void  SBR_DISP_DOT_COL_ON(void);
void  SBR_DISP_DOT_COL_OFF(void);
void  SBR_DISP_DOT_JIA_ON(void);
void  SBR_DISP_DOT_JIA_OFF(void);
void  SBR_DISP_DOT_JIAN_ON(void);
void  SBR_DISP_DOT_JIAN_OFF(void);
void  SBR_DISP_DOT_DIA_ON(void);
void  SBR_DISP_DOT_DIA_OFF(void);
void  SBR_DISP_DOT_TIME_ON(void);
void  SBR_DISP_DOT_TIME_OFF(void);
void  SBR_DISP_DOT_MEMORY_ON(void);
void  SBR_DISP_DOT_MEMORY_OFF(void);
void  SBR_DISP_DOT_HEART_ON(void);
void  SBR_DISP_DOT_HEART_OFF(void);
void  SBR_DISP_DOT_HEART2_ON(void);
void  SBR_DISP_DOT_HEART2_OFF(void);
void  SBR_DISP_DOT_LO_ON(void);
void  SBR_DISP_DOT_LO_OFF(void);
//DP1
void  SBR_DISP_DP1_ON();
void  SBR_DISP_DP1_OFF();
//DP2
void  SBR_DISP_DP2_ON();
void  SBR_DISP_DP2_OFF();
//kpa
void  SBR_DISP_DOT_KPA_ON();
void  SBR_DISP_DOT_KPA_OFF();

//void  SBR_DISP_DOT_LO2_ON(void);
//void  SBR_DISP_DOT_LO2_OFF(void);
void  SBR_DISP_DOT_U1_ON(void);
void  SBR_DISP_DOT_U1_OFF(void);
void  SBR_DISP_DOT_U2_ON(void);
void  SBR_DISP_DOT_U2_OFF(void);
//void  SBR_DISP_DOT_U3_ON(void);
//void  SBR_DISP_DOT_U3_OFF(void);
//void  SBR_DISP_DOT_AVG_ON(void);
//void  SBR_DISP_DOT_AVG_OFF(void);
void  SBR_DISP_DOT_P2_ON(void);
void  SBR_DISP_DOT_P2_OFF(void);
void  SBR_DISP_DOT_P1_ON(void);
void  SBR_DISP_DOT_P1_OFF(void);
void  SBR_DISP_DOT_TANHAO_ON(void);
void  SBR_DISP_DOT_TANHAO_OFF(void);

void  SBR_DISP_DOT_GPRST_ON(void);
void  SBR_DISP_DOT_GPRST_OFF(void);
void  SBR_DISP_DOT_GPRSS_ON(void);
void  SBR_DISP_DOT_GPRSS_OFF(void);
void  SBR_DISP_DOT_MOVE_ON(void);
void  SBR_DISP_DOT_MOVE_OFF(void);
void  SBR_DISP_DOT_ASCVD_ON(void);
void  SBR_DISP_DOT_ASCVD_OFF(void);
void  SBR_DISP_DOT_OK_ON(void);
void  SBR_DISP_DOT_OK_OFF(void);
void  SBR_DISP_DOT_OKQ_ON(void);
void  SBR_DISP_DOT_OKQ_OFF(void);

void SBR_DISP_CLR_ON(void);
void SBR_DISP_E1_ON(void);
void SBR_DISP_E1_OFF(void);
void SBR_DISP_E2_ON(void);
void SBR_DISP_E2_OFF(void);
void SBR_DISP_E3_ON(void);
void SBR_DISP_E3_OFF(void);
void SBR_DISP_E4_ON(void);
void SBR_DISP_E5_ON(void);
void SBR_DISP_E6_ON(void);
void SBR_DISP_E7_ON(void);
void SBR_DISP_E_NO(uint8 step1);
void SBR_DISP_U19_ON(void);
void SBR_DISP_NOMON_ON(void);
void SBR_DISP_KSK_ON(void);       //压力比对时用
void SBR_DISP_OFF_T_ON(void);
void SBR_DISP_ANO_T_ON(void);
void SBR_DISP_ANO_NUM_ON(void);
void SBR_DISP_CLL_ALL_T_ON(void);
void SBR_Disp_YS_ON(void);
void SBR_Disp_NO_ON(void);

void SBR_DISP_DOT_BTT(uint8);
void SBR_DISP_DOT_WX(uint8);
void SBR_DISP_DOT_WX_DIA(uint8);
void SBR_DISP_SYS_ON(void);
void SBR_DISP_SYS_OFF(void);
void SBR_DISP_DIA_ON(void);
void SBR_DISP_DIA_OFF(void);
void SBR_DISP_PLUSE_ON(void);
void SBR_DISP_PLUSE_OFF(void);
void SBR_DISP_MEMORY_ON(void);
void SBR_DISP_MEMORY_OFF(void);
void SBR_DISP_MONTH_ON(void);
void SBR_DISP_MONTH_OFF(void);
void SBR_DISP_DAY_ON(void);
void SBR_DISP_DAY_OFF(void);
void SBR_DISP_HOUR_ON(void);
void SBR_DISP_HOUR_OFF(void);
void SBR_DISP_MINUTE_ON(void);
void SBR_DISP_MINUTE_OFF(void);
void SBR_DISP_DOT_SPK_ON();
void SBR_Disp_ON_ON();
void SBR_Disp_ON_OFF();
void SBR_Disp_OFF_ON();
void SBR_Disp_OFF_OFF();
void SBR_DISP_DP1_KPA_ON();
void SBR_DISP_DP1_KPA_OFF();
void SBR_DISP_DOT_TIME_ON();
void SBR_DISP_DOT_TIME_OFF();
void SBR_BIN_TO_BCD(void);
void T_LCD_NUMBER(void);
void DISPLAY_DOT(void);
void SBR_DISP_SP_ON(void);
void SBR_DISP_SP_OFF(void);
void DSIPLAYWHO(void);
void BPPLAYWHO(void);
void SK080G_PlaySoundIndex(uint8 index);
void AKW_IsPlaySound(void);
void ISD_SpeakNum(uint16 val);
void BPPLAYINFOEND(void);
void BPPLAY_ONE_INFOEND(uint16 idnumb);

void SBR_READ_MEM_ADDR();
void SBR_WRITE_FLASH_ENABLE();
void SBR_SELECT_WRITE_FLASH_MODE();
void	SBR_WRITE_FLASH_BUFFER(uchar Data_Length);
void SBR_WRITE_FLASH();
void SBR_READ_MEN_DATA();
void SBR_FLASH_PAGE_ERASE();
void EEPROM_WRITING(uchar add,uchar da);
void SBR_NEXT_MEM_DAAR();

void DISP_SN(void);



void SBR_Previous_Mem_Addr();
void SBR_READ_MEN_DATA();
void SBR_ADD_MEM();
void SBR_DIVIDE_2BY1();

void SBR_DISP_MONTH_ON();
void SBR_DISP_DAY_ON();
void SBR_DISP_HOUR_ON();

void SBR_SEARCH_MEM_ADDR();
void DISPLAYWHO();
void SBR_DISP_DIA();
void SBR_DISP_SYS();
void SBR_DISP_PLUSE();

void SBR_DISP_MEMORY();
void SBR_DISP_MONTH();
void SBR_DISP_DAY();
void SBR_DISP_HOUR();
void	SBR_DISP_MINUTE();
void	SBR_Disp_A1_ON();


void disp_pu(uint16 da);	      //DIA位置显示数值,da是16进制数0-199
void disp_dia(uint16 da);	      //DIA位置显示数值,da是16进制数0-399
void disp_sys(uint16 da);	      //SYS位置显示数值,da是16进制数0-399
void DISPLAYWHO(void);
 void delay_ms(uint16 cnt);
void Delay_ms(uint16 cnt);
void EEPROM_WRITING(uchar add,uchar da);
void EEPROM_WRITING_INT(uint8 addr,uint8 data1);
uint8 key_scan(void);
void Init_val(void);
void INT_OP1(void);
void STO_WAVE(void);
void STO_PLS(void);
void STO_BUF_WAVE(void);		 //只是对相应的值做一次备份
void DAN3_0(void);
void DAN3_1(void);	             //加压过程波形处理完成，退出重找下一个波形
void DAN3_2(void);	             //加压过程波形处理完成，退出重找下一个波形
void DAN3_3(void);	             //波形处理完成，退出重找下一个波形
void ADJUAST_MAX(void);
uint FOX_H(uchar BATE);
uint FOX_L(uchar BATE);
void SBR_INI_TIMEBASE(void);	
void TEST_CON(void);
void DEFLATION(void);
void PWMGVAL1(uint16 pwm_val);	
void SYSDAS_DE(void);
void CNT_PLS(void);

void SK080G_PlaySoundIndex(uint8 index);
void AKW_IsPlaySound(void);
void ISD_SpeakNum(uint16 val);
void playSDFile(uint8 len);
void BPPLAYINFOEND(void);
void BPPLAY_ONE_INFOEND(uint16 idnumb);


void STP_PUMP_ON();
void STP_PUMP_OFF();
void STP_VALUE_ON();
void STP_VALUE_OFF();


unsigned char HEX_TO_Char(unsigned char Hex);
unsigned char Char_TO_HEX(unsigned char Hex);
void test_data_int(void);
unsigned char START_GSM(void);
unsigned char GSM_STNT_DATA(void);
void print_with_Enter(const unsigned	char *t);
void print(const unsigned	char *t);
void printb(unsigned	char *t,int L);
void print_int(unsigned int v);	 	
unsigned char baud_rate_synchronization(unsigned char Time);
unsigned char whait_still_OK(unsigned char Time);
unsigned char wait_Call_Ready(unsigned char Time);
unsigned char readlines(unsigned char Time,unsigned char Line);
unsigned char readbyes(unsigned char Time,unsigned char byes);
unsigned char read_GSM_data(unsigned char Time);
void DRV_PutChar(char u8Char);
void DRV_PutChar1(char u8Char);
unsigned char Get_Check_SUM(unsigned char *pData, unsigned char Size);

void  UPDATA_MEMORY(uint8 GSM_DATA_CNT);
void GSM_OFF(void);
#endif
