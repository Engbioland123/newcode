#include "BH67F2260.h"
#include "typedef.h"
#include "function.h"
#include "Variable.h"
#include "define.h"

const unsigned	char  overtime[]=	"timeout";
const unsigned	char  overram[]=	"出";

//const char urlHead[] = "POST /bioland-bp HTTP/1.1\r\nHost: api.tellihealth.com\r\nContent-Length: 209\r\n\r\n";
const char urlHead[] = "POST /bioland/a600n/1 HTTP/1.1\r\nHost: api.tellihealth.com\r\nContent-Length: 299\r\n";
const char dakuohao1[] = "{";

//const char imei[] = "\r\n\t\"IMEI\":";
//const char sn[] = "\r\n\t\"SN\":";
//const char checkTime[] = "\r\n\t\"Check Time\":";
//const char checkData[] = "\r\n\t\"Check Data\":\r\n\t{";
//const char dakuohao[] = "}";
//const char huanhangkong[] = "\r\n\t";
//const char huanhang[] = "\r\n";
//"Model":"A600N"
//"User":"1"
//"SYS":"160mmHg"
//"DIA":"100mmHg"
//"BPM":"100times"
//"CA":"0"
//-------------------------------------------------------------
unsigned char HEX_TO_Char(unsigned char Hex)
{
	switch(Hex)
	{
		case	0x00:	return	'0';
		case	0x01:	return	'1';
		case	0x02:	return	'2';
		case	0x03:	return	'3';
		case	0x04:	return	'4';
		case	0x05:	return	'5';
		case	0x06:	return	'6';
		case	0x07:	return	'7';
		case	0x08:	return	'8';
		case	0x09:	return	'9';
		case	0x0A:	return	'A';
		case	0x0B:	return	'B';
		case	0x0C:	return	'C';
		case	0x0D:	return	'D';
		case	0x0E:	return	'E';
		case	0x0F:	return	'F';
		default:		return	'*';
	}
}
unsigned char Char_TO_HEX(unsigned char Hex)
{
	switch(Hex)
	{
		case	'0':	return	0x00;
		case	'1':	return	0x01;
		case	'2':	return	0x02;
		case	'3':	return	0x03;
		case	'4':	return	0x04;
		case	'5':	return	0x05;
		case	'6':	return	0x06;
		case	'7':	return	0x07;
		case	'8':	return	0x08;
		case	'9':	return	0x09;
		case	'A':	return	0x0A;
		case	'B':	return	0x0B;
		case	'C':	return	0x0C;
		case	'D':	return	0x0D;
		case	'E':	return	0x0E;
		case	'F':	return	0x0F;
		default:		return	Hex-48;
	}
}

//5A25121060115A000297134082074151203102707D4_460040124507017_FFFFFFFFFFFFFFFFFFFFFFFFF
void test_data_int(void)
{
//unsigned char i;
//   up_data.Weakup[0]='5'; 		    //1.起始碼
//   up_data.Weakup[1]='A';

//   up_data.VER[0]='2';  			//2.版本号
//   up_data.VER[1]='6';
   up_data.CA_BUF = '0';
   up_data.USER_BUF='1';  			    //3.用户号

//
//   up_data.Customer[0]='0';	    	//4.客戶碼
//   up_data.Customer[1]='1';

//   up_data.ModelCode[0]='0';		//5.机型代码
//   up_data.ModelCode[1]='5';

   up_data.DeviceType[0]='0';		//6.机种码
   up_data.DeviceType[1]='1';
   
   up_data.Serialnumber[0]='\"';	    //7.系列号
   up_data.Serialnumber[1]='1';	    //7.系列号
   up_data.Serialnumber[2]='8';
   up_data.Serialnumber[3]='C';
   up_data.Serialnumber[4]='2';
   up_data.Serialnumber[5]='2'; 
   up_data.Serialnumber[6]='3'; 
   up_data.Serialnumber[7]='4'; 
   up_data.Serialnumber[8]='5';
   up_data.Serialnumber[9]='6';
   up_data.Serialnumber[10]='\"';   
//
//   up_data.SYS[0]='1'; 			//8.高压(3)
//   up_data.SYS[1]='3';
//   up_data.SYS[2]='4';
//
//   up_data.DIA[0]='0';		//9.低压(3)
//   up_data.DIA[1]='8';
//   up_data.DIA[2]='2';
//
//   up_data.PUL[0]='0';			//10.心率 (3)
//   up_data.PUL[1]='7';
//   up_data.PUL[2]='4';
//
   up_data.year[0]='2';  			//11.年
   up_data.year[1]='0';
   up_data.year[2]='2';  			//11.年
   up_data.year[3]='1';

   up_data.month[0]='0';  		//12.0月
   up_data.month[1]='3';

   up_data.day[0]='3';  			//13.日 
   up_data.day[1]='1';  
                               	
   up_data.our[0]='0';			  //14.时
   up_data.our[1]='9';

   up_data.mini[0]='0';		 	//15.分	
   up_data.mini[1]='3';  
//      
//   up_data.SUM[0]='A';			//16.校验码   
//   up_data.SUM[1]='B';
//   up_data.SUM[2]='C';
//   up_data.SUM[3]='D';

//   up_data.connector0='_';			//连接符
    
   up_data.IMEI[0]='\"';
   up_data.IMEI[1]='F';
   up_data.IMEI[2]='F';
   up_data.IMEI[3]='F';		   
   up_data.IMEI[4]='F';
   up_data.IMEI[5]='F';
   up_data.IMEI[6]='F';
   up_data.IMEI[7]='F';			  
   up_data.IMEI[8]='F';
   up_data.IMEI[9]='F';
   up_data.IMEI[10]='F';
   up_data.IMEI[11]='F';
   up_data.IMEI[12]='F';		  
   up_data.IMEI[13]='F';
   up_data.IMEI[14]='F';
   up_data.IMEI[15]='F';
   up_data.IMEI[16]='\"';   

//   up_data.connector1='_';
//   up_data.IMSI[0]='F';
//   up_data.IMSI[1]='F';
//   up_data.IMSI[2]='F';
//   up_data.IMSI[3]='F';		   
//   up_data.IMSI[4]='F';
//   up_data.IMSI[5]='F';
//   up_data.IMSI[6]='F';
//   up_data.IMSI[7]='F';			  
//   up_data.IMSI[8]='F';
//   up_data.IMSI[9]='F';
//   up_data.IMSI[10]='F';
//   up_data.IMSI[11]='F';
//   up_data.IMSI[12]='F';		  
//   up_data.IMSI[13]='F';
//   up_data.IMSI[14]='F';
//	for(i=0;i<10;i++)
//    up_data.jinweidu[i]='F';

}

const uchar data_time2[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

unsigned char gettime(void)
{
  unsigned char i,j,k;
  unsigned char time[18];
  k=0;	
  _emi=0;
  for(i=0;i<Rx_Size;i++)
	{
	  if(Rx_Buff0[i]=='"')
	   {
		 i+=3;                               
		 for(j=0;j<18;j++,i++)				//	+QLTS: "2022/06/20,21:30:49-16,1"
		   { 
		   	 time[j]=Rx_Buff0[i];       //+QNTP: 0,"2022/06/20,21:32:20-16"
		   }
		 for(j=0;j<18;j++)					//转成数字
		   {												
	    	 time[j]=Char_TO_HEX(time[j]);
	       }
         if((time[0]*10+time[1])<80&&(time[0]*10+time[1])>21&&(time[3]*10+time[4])<13&&(time[3]*10+time[4])>0&&(time[6]*10+time[7])<32&&(time[9]*10+time[10])<25&&(time[12]*10+time[13])<61)                       
		   {
					   												
			 R_YEAR=	time[0]*10+time[1];				
			 R_MONTH=	time[3]*10+time[4];				
			 R_DAY=		time[6]*10+time[7];				
			 R_CLOCK_HOUR=		time[9]*10+time[10];				
			 R_CLOCK_MINUTE=	time[12]*10+time[13];				
			 R_CLOCK_SECOND=	time[15]*10+time[16];

			 if(R_CLOCK_HOUR>3)// 减4小时
			 {
					R_CLOCK_HOUR-=4;
			 }
			 else
			 {
					R_CLOCK_HOUR=(R_CLOCK_HOUR+24-4)%24;
					R_DAY--;
					if(R_DAY==0)
					{						
					   R_MONTH--;		    	   
					   if(R_MONTH==0)
						 {
							R_MONTH=12;
							R_YEAR--;
						 }		    	    
					   R_DAY=data_time2[R_MONTH];		    	   		    	   
					   if(R_YEAR%4==0 && R_MONTH==2)//如果是闰年
						  R_DAY=29;
					}			  				 			 	
			  }
			  MODEFLAG.bits.Up_dateTime=1;
			  SBR_UPDATE_TIME();
			  k=1;
			  break;				
		   }
          			  
	   }	 
    }        
 return k;
}

unsigned char START_GSM(void)
{
	 unsigned char i,j,flag,restart,Repeat;
     GPRST =1;        //开始闪那个天线柱子符
 	 Repeat=0;
	 step=1;		  //不能返回错误为0的错误号，血压计端不能认别，因为0代表返回成功，其它的为相应错误。	
     flag=1;
     restart=0;
	 while(1)
	 { 
			if(KEYFLAG.bits.StartKey ==1)
			 {
		 	    return false;							
			 }
			 switch(step)
			  {
			  	
//--------------------------------------------------- 
			  	
		        case 1:	if(read_GSM_data(60)==UART_BACK_APP_RDY);		        
						 {
						 	
						 	

						 	
					   		step++;
							Repeat=0;							   
			   				break;
						 }
						if(++Repeat>5)
						 {
					 	    return false;							
						 }
						 else
						 {
					 	    GSM_PWRKEY =1; 
	                        Delay_ms(12000);
	                        GSM_PWRKEY =0; 
	                        break;						 	
						 }								
	                	break;
//--------------------------------------------------- 	                	
//ATE0	                				  	
		        case 2:	     
		                print_with_Enter((const unsigned char*)"ATE0");		         //固定支持频段5   8   20
						if(read_GSM_data(10)==UART_BACK_OK)                          //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
							delay_ms(10);									   
			   				break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break;	 
//---------------------------------------------------
//AT+CPIN?
		        case 3:	print_with_Enter((const unsigned char*)"AT+CPIN?");		 //固定支持频段5   8   20
						if(read_GSM_data(10)==UART_BACK_OK)                          //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
							print_with_Enter((const unsigned char*)"AT+CIMI");
							delay_ms(1000);									   
			   				break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break;
//--------------------------------------------------- 		            	
// AT+QGMR		            				
		        case 4:
						print_with_Enter((const unsigned char*)"AT+QGMR");
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step ++;
							Repeat=0;
						//	delay_ms(1000);									   
			   				break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break;
//--------------------------------------------------- 		            	
		        case 5: 
						print_with_Enter((const unsigned char*)"AT+QMBNCFG=\"autosel\"");
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
							    step ++;
							 	flag=1;//set err
	
								for(i=0;i<Rx_Size;i++)
								{
									if(Rx_Buff0[i]=='l'&& Rx_Buff0[i+2]==','&& Rx_Buff0[i+3]=='0')	//+QMBNCFG: "autosel",1	
									  {
									   		flag=0;								   
							   				break;					  	
									  }
						 	    }
						 	    if(flag)
						 	    {								  	
						           
						        	print_with_Enter((const unsigned char*)"AT+QMBNCFG=\"autosel\",0");									        
						        	delay_ms(3000);
						        	print_with_Enter((const unsigned char*)"AT+CFUN=1,1");//reboot modem
						        	step=1;						        	
						        	
						        	
						 	    }
						 	    Repeat=0;
						 	    break;						 	    
						 }
						if(++Repeat>5)	
							return false;	
						delay_ms(1000);
		            	break;		            	
		            	
//--------------------------------------------------- 
//AT+QCFG=\"band\""						            		
		        case 6:
                        print_with_Enter((const unsigned char*)"AT+QCFG=\"band\"");	//Lock all frequency bands by default
                        if(whait_still_OK(20)==UART_BACK_OK) 
						 {
						   	step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break;	
	            	break;
//--------------------------------------------------- 	            				            	
//AT+QCFG=\"iotopmode\"		            			
		        case 7: 
						print_with_Enter((const unsigned char*)"AT+QCFG=\"iotopmode\"");
                        	
  
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {	
					 	    
							    step ++;
							 	flag=1;
	
								for(i=0;i<Rx_Size;i++)
								{
									if(Rx_Buff0[i]=='e'&& Rx_Buff0[i+2]==','&& Rx_Buff0[i+3]=='0')	//+QCFG: "iotopmode",0
									  {
									   		flag=0;								   
							   				break;					  	
									  }
						 	    }
						 	    if(flag)
						 	    {								  	
						            restart=1;
						        	print_with_Enter((const unsigned char*)"AT+QCFG=\"iotopmode\",0,1");									        
						        	delay_ms(3000);
						 	    }
						 	    Repeat=0;
						 	    break;					 	    
					 	    
						 }							 		 						 	
						
						if(++Repeat>2)	
							return false;	
						delay_ms(1000);
		            	break;	
//---------------------------------------------------
//AT+QCFG=\"nwscanseq\""
		        case 8:
                        print_with_Enter((const unsigned char*)"AT+QCFG=\"nwscanseq\"");	 
                        
						if(read_GSM_data(10)==UART_BACK_OK)                                       
						 {	
		

							    step ++;
							 	flag=1;
	
								for(i=0;i<Rx_Size;i++)
								{
									if(Rx_Buff0[i]=='0'&& Rx_Buff0[i+1]=='2'&& Rx_Buff0[i+2]=='0'&& Rx_Buff0[i+3]=='1'&& Rx_Buff0[i+4]=='0'&& Rx_Buff0[i+5]=='3')
									  {
									   		flag=0;								   
							   				break;					  	
									  }
						 	    }
						 	    if(flag)
						 	    {								  	
						            restart=1;
						        	print_with_Enter((const unsigned char*)"AT+QCFG=\"nwscanseq\",020103,1");									        
						        	delay_ms(3000);

						        	
						 	    }
						 	    Repeat=0;
						 	    break;					 	    
					 	    
						 }
	 						 	
						
						if(++Repeat>2)	
							return false;
						delay_ms(1000);									   
					   	break;  
//---------------------------------------------------					   	
//AT+QCFG=\"nwscanmode\""						   	
		        case 9:
                        print_with_Enter((const unsigned char*)"AT+QCFG=\"nwscanmode\"");                        	
 
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {	

							    step ++;
							 	flag=1;
	
								for(i=0;i<Rx_Size;i++)
								{
									if(Rx_Buff0[i]=='e'&& Rx_Buff0[i+2]==','&& Rx_Buff0[i+3]=='0')//+QCFG: "nwscanmode",0
									  {
									   		flag=0;								   
							   				break;					  	
									  }
						 	    }
						 	    if(flag)
						 	    {								  	
						            restart=1;
						        	print_with_Enter((const unsigned char*)"AT+QCFG=\"nwscanmode\",0,1");										        
						        	delay_ms(3000);
						 	    }
						 	    Repeat=0;
						 	    break;						 	    
					 	    
						 }						 				 	
						
						if(++Repeat>2)	
							return false;
						delay_ms(1000);									   
					   	break; 
//---------------------------------------------------					   	
		        case 10:					   	
				//	   	restart=1;
					   	if(restart)
					   	{
					   		
	                        print_with_Enter((const unsigned char*)"AT+CFUN=0");//set all QCFG values to preferred
							if(read_GSM_data(20)==UART_BACK_OK) 
							{}  					   		
					   		
					   		
					   		
					   	
	                        print_with_Enter((const unsigned char*)"AT+CFUN=1");
							if(read_GSM_data(20)==UART_BACK_OK)                                
							 {
							 	restart=0;
								Repeat=0;
						   	//	step++;							
								step=3;	//	wait for +CPIN: READY						   
					   			break;
							 }	                        
	                        		
							if(++Repeat>2)	
								return false;
							delay_ms(1000);	
							

					   	}
					   	else
					   	 step++;
					   	break; 				   	
					   	
					   	
//---------------------------------------------------					   	     
					   	
					   	  	
//AT+CGDCONT=2,\"IPV4V6\",\"vzwadmin\";+CGDCONT=3;+CGDCONT=4;+QICSGP=1,1,\"Eseye1\",\"\",\"\",0"	
								
		        case 11:										
                        print_with_Enter((const unsigned char*)"AT+CGDCONT=2,\"IPV4V6\",\"vzwadmin\";+CGDCONT=3;+CGDCONT=4;+QICSGP=1,1,\"Eseye1\",\"\",\"\",0");
						if(whait_still_OK(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 		

//---------------------------------------------------
//AT+QSSLCFG=\"seclevel\",1,0"

		        case 12:
                        print_with_Enter((const unsigned char*)"AT+QSSLCFG=\"seclevel\",1,0");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 
//---------------------------------------------------
//AT+QSSLCFG=\"sni\",1,1"

		        case 13:
                        print_with_Enter((const unsigned char*)"AT+QSSLCFG=\"sni\",1,1");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 
//---------------------------------------------------
//AT+QSSLCFG="sslversion",1,4

		        case 14:
                        print_with_Enter((const unsigned char*)"AT+QSSLCFG=\"sslversion\",1,4");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 
//---------------------------------------------------
//"AT+QSSLCFG=\"ciphersuite\",1,0XFFFF"

		        case 15:
                        print_with_Enter((const unsigned char*)"AT+QSSLCFG=\"ciphersuite\",1,0XFFFF");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 
		            			            			            			            	
//---------------------------------------------------
//AT+QHTTPCFG=\"contextid\",1"

		        case 16:
                        print_with_Enter((const unsigned char*)"AT+QHTTPCFG=\"contextid\",1");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 
//---------------------------------------------------
//AT+QHTTPCFG=\"sslctxid\",1"

		        case 17:
                        print_with_Enter((const unsigned char*)"AT+QHTTPCFG=\"sslctxid\",1");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 		            			            	
		            	
//---------------------------------------------------
//AT+QHTTPCFG=\"requestheader\",1"

		        case 18:
                        print_with_Enter((const unsigned char*)"AT+QHTTPCFG=\"requestheader\",1");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
					   		step++;
//					   		step++;
							Repeat=0;
						//	delay_ms(1000);									   
				  			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 
//---------------------------------------------------
//AT+QHTTPCFG=\"autosel\"--The manufacturer replied that this AT command is not supported

//		        case 19:   /* FIXME: autosel value must be checked as 0 and if not set to 0 and modem reset with AT+CFUN=1,1 */
//                        print_with_Enter((const unsigned char*)"AT+QHTTPCFG=\"autosel\"");	
//						if(read_GSM_data(20)==UART_BACK_OK)                                        //如回 OK  下一条
//						 {
//							    step ++;
							    
//							 	flag=1;//set err
//	
//								for(i=0;i<Rx_Size;i++)
//								{
//									if(Rx_Buff0[i]=='l'&& Rx_Buff0[i+2]==','&& Rx_Buff0[i+3]=='0')	//
//									  {
//									   		flag=0;								   
//							   				break;					  	
//									  }
//						 	    }
//						 	    if(flag)
//						 	    {								  	
//						           
//						        	print_with_Enter((const unsigned char*)"AT+QHTTPCFG=\"autosel\",0");									        
//						        	delay_ms(3000);
//						        	print_with_Enter((const unsigned char*)"AT+CFUN=1,1");//reboot modem
//						        	step=1;						        	
//						        	
//						        	
//						 	    }
//						 	    Repeat=0;
//						 	    break;						 	    
//						 }
//						 
//						 
//						 
//						if(++Repeat>5)	
//							return false;	
//						delay_ms(1000);
//		            	break;
		            			            			            			            	

//---------------------------------------------------
//AT+QICSGP=1,1,\"Eseye1\",\"\",\"\",1

		        case 20:
                        print_with_Enter((const unsigned char*)"AT+QICSGP=1,1,\"Eseye1\",\"\",\"\",1");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
							Repeat=0;
							//delay_ms(1000);									   
			   				break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 		            			            	
		            	
//---------------------------------------------------
//AT+QIACT?
		        case 21://	
                        print_with_Enter((const unsigned char*)"AT+QIACT?");	
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
					   		step++;
					   		step++;
							Repeat=0;
							delay_ms(50);			   
				   			break;
						 }
						 else
						 {
					 		step++;
							Repeat=0;
							delay_ms(1000);									   
			   				break;
						 }
//---------------------------------------------------
//AT+QIACT=1		            	
		        case 22://	
                        print_with_Enter((const unsigned char*)"AT+QIACT=1");	
                        step++;
                        Repeat=0;
						if(read_GSM_data(60)==UART_BACK_OK); 
						{                                      //如回 OK  下一条															   
			   				break;
						}

						delay_ms(1000);									   
		   				break;
		            			            	
//---------------------------------------------------
//AT+COPS?		            	
		        case 23:	//
                        print_with_Enter((const unsigned char*)"AT+COPS?");	
     		       	    if(read_GSM_data(10)==UART_BACK_OK)
						 {
							flag=0;
							for(i=1;i<Rx_Size;i++)
							{
							   if(Rx_Buff0[i]=='0' && Rx_Buff0[i+1]==','/*  && Rx_Buff0[i+2]=='0'*/)
							   {
								  flag=1;
								  break;	    
							   }
							}
							if(flag)
						    {
						   	   step++;
							   Repeat=0;									   
				   			   break;
						    }
						 }
						 /* FIXME: This timeout needs to be extended to 180s */
						if(++Repeat>90)	
						return false;	
						delay_ms(3000);
		            	break;	  	            				            	

		        case 24: 
//--------------------------------------------------- 		        
//AT+CREG?;+CEREG?;+CGREG?	
	        
                        print_with_Enter((const unsigned char*)"AT+CREG?;+CEREG?;+CGREG?");	      //这里17，5683，1  改为1
				       	if(read_GSM_data(10)==UART_BACK_OK)
						 {
							flag=0;
							for(i=1;i<Rx_Size;i++)
							if(Rx_Buff0[i]==',' && Rx_Buff0[i-1]=='0'  && (Rx_Buff0[i+1]=='1'||Rx_Buff0[i+1]=='5'))
							  {
								 flag=1;
								 break;	    
							  }
							if(flag)
							  {
						   		 step++;
								 Repeat=0;									   
				   				 break;
							  }
						 }
						if(++Repeat>250)	
							return false;	
						delay_ms(1000);
		            	break;
//---------------------------------------------------         		
		        case 25:
//AT+CSQ	---if(CSQ>7 && CSQ<35) can transmit, otherwise terminate
	        
                        print_with_Enter((const unsigned char*)"AT+CSQ");	//0,1 OR 5
						if(read_GSM_data(10)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
			   	 	        flag=0;
						    for(i=0;i<Rx_Size;i++)
						      {							
								if(	Rx_Buff0[i]==',' && ((Rx_Buff0[i-2]>='0'&&Rx_Buff0[i-2]<='9') || (Rx_Buff0[i-1]>='0'&&Rx_Buff0[i-1]<='9')))
					 		      {
					 		      	if(Rx_Buff0[i-2]>='0'&&Rx_Buff0[i-2]<='9')
					 		      	  {
									     j=(Rx_Buff0[i-2]-48)*10;		//转成int型数据	
					 		      	  }
					 		      	else
					 		      	  {
					 		      	     j=0;	
					 		      	  }							
									j=j+(Rx_Buff0[i-1]-48);
									if(j>7 && j<35)               //信号小于31大于10会好一些，
									  {
										 flag=1;
										 break;			//out of for loop							
									  }
								  }
						      }
							if(flag)
							  {
						   		 step++;
								 Repeat=0;
								 delay_ms(1000);									   
				   				 break;
							  }
						 }
						if(++Repeat>125)	
							return false;	
						delay_ms(1000);
		            	break; 
//--------------------------------------------------- 		            	
		        case 26:
//AT+QNWINFO--This information is only used to check what network is registered to
                        print_with_Enter((const unsigned char*)"AT+QNWINFO");	
						if(read_GSM_data(20)==UART_BACK_OK)                                        //如回 OK  下一条
						 {
						   	step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break; 	
//--------------------------------------------------- 		            			            		
		        case 27:
		        
//AT+QHTTPURL=38,80
                        print_with_Enter((const unsigned char*)"AT+QHTTPURL=47,80");	
						if(read_GSM_data(40)==UART_BACK_CONNECT)                                        //如回 OK  下一条
						 {
						   	step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;				
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break;					
//--------------------------------------------------- 
		        case 28:
		        
//https://api.tellihealth.com/bioland-bp

                        print_with_Enter((const unsigned char*)"https://dev-api.tellihealth.com/bioland/a600n/1");	
						if(read_GSM_data(40)==UART_BACK_OK)                           //如回 OK  下一条
						 {
						   	step++;
							Repeat=0;
						//	delay_ms(1000);									   
				   			break;
						 }
						if(++Repeat>5)	
						return false;	
						delay_ms(1000);
		            	break;
//--------------------------------------------------- 		            	
		        case 29:
		        
//AT+CGSN
                        print_with_Enter((const unsigned char*)"AT+CGSN");	
						up_data.IMEI[0]  ='\"';
						up_data.IMEI[16] ='\"';
						if(read_GSM_data(10)==UART_BACK_OK)
						  {
						  	  flag=0;
	   						  for(i=0;i<Rx_Size;i++)
								{
								    if(Rx_Buff0[i]>='0'&&Rx_Buff0[i]<='9')
									 {
										for(j=1;j<16;j++,i++)
										{
										  up_data.IMEI[j]=Rx_Buff0[i];
										}
								   		flag=1;
		    							break;
									 }
							    }
							  if(flag)
							    {
							   		step++;
									Repeat=0;
									delay_ms(1000);									   
				   			  	    break;													   
							    }
						  }										
						if(Repeat++>3)
						return false;
						delay_ms(1000);
						break;
//--------------------------------------------------- 						
//AT+QLTS		/* FIXME: Time management code needs to be updated. See notes */		GMT		
		        case 30:
					
		        
		        		print_with_Enter((const unsigned char*)"AT+QLTS");//有时不会更新时间。
		        	
                        timegsm=10;
                        Rx_Size=0;
                        j=0;
                        while(timegsm)
                        {
							if(RI)
							{
							  Rx_Buff0[Rx_Size++]=_txr_rxr;
							  RI=0; 
							  if(_txr_rxr=='\"')
							     {
							     	j++;
							     	if(j>1)
							     	  break;
							     }
							}				  
							if(GPIO_STARTKEY == 0)									
							{
								return false;	
							}   							                      	

                        }
						if(j>1)
						 {

						 	if(gettime())
						 	{
						  		return true;								   
				   			}													    						 							   

						 }

						if(++Repeat>2)
						{	
							step++;
							Repeat=0;
						}	
//--------------------------------------------------- 		            							
		        case 31:
//AT+CCLK?
                      //  print_with_Enter((const unsigned char*)"AT+CCLK?");	
                	  //  print_with_Enter("AT+QNTP=1,\"time.apple.com\"");
                	  
                	  
                        print_with_Enter((const unsigned char*)"AT+QNTP=1,\"192.168.111.2\",123,1");//更新本地时间，AT+CMGL
                        timegsm=10;
                        Rx_Size=0;
                        j=0;
                        while(timegsm)
                        {
							if(RI)
							{
							  Rx_Buff0[Rx_Size++]=_txr_rxr;
							  RI=0; 
							  if(_txr_rxr=='\"')
							     {
							     	j++;
							     	if(j>1)
							     	  break;
							     }
							}				  
							if(GPIO_STARTKEY == 0)									
							{
								return false;	
							}   							                      	

                        }
						if(j>1)
						 {

						 	if(gettime())
						 	{
						  		return true;								   
				   			}													    						 							   

						 }

						if(++Repeat>2)
						{	
							return false;
						}	

		            	break;

		            	
//--------------------------------------------------- 		            	
		            	
		            	
		            	
		            				
			  }	 
	 }
}

//const char Model[] = "\r\n\t\t\"Model\":\"A600N\"";
//const char Ver[] = "\r\n\t\t\"ver\":\"A600N_1.0\"";
//const char User[] = "\r\n\t\t\"User\":\"";
//const char SYS[] = "\r\n\t\t\"SYS\":\"";
//const char DIA[] = "\r\n\t\t\"DIA\":\"";
//const char BPM[] = "\r\n\t\t\"BPM\":\"";
//const char CA[]  = "\r\n\t\t\"CA\":\"";
//const char mmHg[] = "mmHg\"";
//const char times[] = "times\"";

//----------------GSM-------------------------------
unsigned char GSM_STNT_DATA(void)
{
   unsigned char Repeat;
   Repeat=0;
   //
   step=34;
   while(1)
	{    
		 switch(step)
		  { 
	        case 34:   // delay_ms(10000);
                        //print_with_Enter((const unsigned char*)"AT+QHTTPPOST=288,30,30")
                         print_with_Enter((const unsigned char*)"AT+QHTTPPOST=381,30,30");	
						if(read_GSM_data(30)==UART_BACK_CONNECT)                                        //如回 OK  下一条
						 {
						   		step++;
								Repeat=0;
							//	delay_ms(1000);									   
				   				break;
						 }
						if(++Repeat>5||KEYFLAG.bits.StartKey ==1)	
						return false;	
						delay_ms(1000);
		            	break;			  	
//--------------------------------------------------- 		  		    											
		    case 35:
		             
		             
					//	printb((unsigned char*)urlHead,sizeof(urlHead));
						print(urlHead);
						print((const unsigned char*)"\r\n\{\r\n");
						
						print((const unsigned char*)"    \"IMEI\":");						
						printb((unsigned char*)up_data.IMEI,sizeof(up_data.IMEI));
						print((const unsigned char*)",\r\n");
						

						print((const unsigned char*)"    \"SN\":");
						printb((unsigned char*)up_data.Serialnumber,sizeof(up_data.Serialnumber)-1);
				

						print((const unsigned char*)"\",\r\n    \"Check Time\":\"");
						
					
						printb((unsigned char*)up_data.year,sizeof(up_data.year));	
						printb((unsigned char*)up_data.month,sizeof(up_data.month));
						printb((unsigned char*)up_data.day,sizeof(up_data.day));
						printb((unsigned char*)up_data.our,sizeof(up_data.our));
						printb((unsigned char*)up_data.mini,sizeof(up_data.mini));
						printb((unsigned char*)up_data.mini,sizeof(up_data.mini));	  //秒发分					
						print((const unsigned char*)"\",\r\n");
						

						print((const unsigned char*)"    \"Check Data\":\r\n    {\r\n");
																

						print((const unsigned char*)"        \"Model\":\"A600N\",\r\n");
						

						print((const unsigned char*)"        \"ver\":\"A600N_1.0\",\r\n");
							
										

						print((const unsigned char*)"        \"User\":\"");						
						DRV_PutChar(up_data.USER_BUF);												
						print((const unsigned char*)"\",\r\n");	
	
						print((const unsigned char*)"        \"SYS\":\"");					
						printb((unsigned char*)up_data.SYS,sizeof(up_data.SYS));
						print((const unsigned char*)"mmHg\",\r\n");

						print((const unsigned char*)"        \"DIA\":\"");
						printb((unsigned char*)up_data.DIA,sizeof(up_data.DIA));

						print((const unsigned char*)"mmHg\",\r\n");
						

						print((const unsigned char*)"        \"BPM\":\"");
						printb((unsigned char*)up_data.PUL,sizeof(up_data.PUL));
							print((const unsigned char*)"times\",\r\n");

							print((const unsigned char*)"        \"CA\":\"");

						DRV_PutChar(up_data.CA_BUF);
						
						print((const unsigned char*)"\"\r\n    }\r\n}\r\n");	
																		


                        if(wait_Call_Ready(50)==UART_BACK_CONNECT) 
                        {
                        	return true;
                        }
                        else
                        {                           
                            return false;
                        }
       			        break;
			            		 
		           default:						

				   return false;
				   break;

	  	  }
	}
}


void GSM_OFF(void)
{
	
	print_with_Enter((const unsigned char*)"\r\nAT+QIDEACT=1");
	if(read_GSM_data(10)==UART_BACK_OK)
	{		
	}
	else
	{
	 delay_ms(1000);
	}	
	print_with_Enter((const unsigned char*)"AT+QPOWD");
//	delay_ms(3000);	

}

//=======================================================================

void print_with_Enter(const unsigned	char *t)
{ 
	while(*t != 0)
	   	{
			DRV_PutChar(*t);
			t++ ;
		}
	DRV_PutChar('\r');
	DRV_PutChar('\n');	   //在dos窗口中按回车键，其实是输入了两个字符0x0A,0x0D，对应到c中，就是\r(回车)\n(换行)

}

//-------------------------------------------------------------
void print(const unsigned	char *t)
{ 
	while(*t != 0)
	   	{
			DRV_PutChar(*t);
			t++ ;
		}
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void printb(unsigned	char *t,int L)
{ 
	if(L==0)
	   return;

	while(L)
	   	{
			DRV_PutChar(*t);
			t++ ;
			L-- ;
		}
}
//---------------------------------------------------
unsigned char whait_still_OK(unsigned char Time)  //收时间
{
	uint8 i;
	timegsm=Time*2;	
	while(1)
	{
//	   	while(!RI && timegsm!=0);
	   	while(!RI && timegsm!=0)
		   {
		  	 	//这里面要扫按键  
		  	  if(GPIO_STARTKEY == 0)									
		      {
			    KEYFLAG.bits.StartKey =1;
			    return UART_BACK_OVER_time;
			  }     
		   }		
	   	
		if(timegsm==0)
			{
			 	print_with_Enter(overtime);
				return UART_BACK_OVER_RAM;
			}				   
	 	RI=0;
	 	Rx_Buff0[40]=_txr_rxr;
	 	for(i=0;i<40;i++)
	 	{
	 	   Rx_Buff0[i]=Rx_Buff0[i+1];	
	 	}
	
		if(Rx_Buff0[38]=='O'&&Rx_Buff0[39]=='K')
		    return UART_BACK_OK;			 
	}
}
//-------------------------------------------------------------
//功能：等Call Ready出现。
//Time:时间限制

unsigned char wait_Call_Ready(unsigned char Time)
{
	 Rx_Size=0;
	 timegsm=Time*2;
	 while(1)
	 {
	   	  while(!RI && timegsm!=0)
		  {
	   	 	//这里面要扫按键  
      	    if(GPIO_STARTKEY == 0)									
		    {
			  KEYFLAG.bits.StartKey =1;
			  return UART_BACK_OVER_time;
		    }     
		  }				  
		 RI=0;
		 if(timegsm==0)
		  {
		    print_with_Enter(overtime);
			return  UART_BACK_OVER_time;				  //超时错误
		  }
	 	 Rx_Buff0[Rx_Size]=_txr_rxr;
////ERROR
		 if(Rx_Buff0[Rx_Size-8]=='E' && Rx_Buff0[Rx_Size-7]=='R' && Rx_Buff0[Rx_Size-6]=='R'&&Rx_Buff0[Rx_Size-5]=='O'&&Rx_Buff0[Rx_Size-4]=='R')
		   {
			   return  UART_BACK_ERROR;				   
		   }
//+QHTTPPOST: 0,204,0
		 if(Rx_Buff0[Rx_Size-3]=='0' && Rx_Buff0[Rx_Size-2]==','&&Rx_Buff0[Rx_Size-1]=='2'&&Rx_Buff0[Rx_Size]=='0')
		   {

			   return  UART_BACK_CONNECT;				   
		   }

		 if(++Rx_Size>RxBufMAX)
		  {
			print_with_Enter(overram);
			return  UART_BACK_OVER_RAM;				  //溢出错误
		  } 
	 }
}

//-------------------------------------------------------------

//UART_BACK_OVER_time
//UART_BACK_OK
//UART_BACK_ERROR
//UART_BACK_Duplicated
//UART_BACK_Success
//UART_BACK_OVER_RAM
//UART_BACK_SIM_READY;
//UART_BACK_Call_Ready
//UART_BACK_CONNECT

unsigned char read_GSM_data(unsigned char Time)
{
	 Rx_Size=0;
	 timegsm=Time*2;
	 while(1)
	 {
	   	  while(!RI && timegsm!=0)
		  {
	   	 	//这里面要扫按键  
      	    if(GPIO_STARTKEY == 0)									
		    {
			  KEYFLAG.bits.StartKey =1;
			  return UART_BACK_OVER_time;
		    }     
		  }				  
		 RI=0;
		 if(timegsm==0)
		  {
		    print_with_Enter(overtime);
			return  UART_BACK_OVER_time;				  //超时错误
		  }
	 	 Rx_Buff0[Rx_Size]=_txr_rxr;
//OK
		 if((Rx_Buff0[Rx_Size]=='K' && Rx_Buff0[Rx_Size-1]=='O')||Rx_Buff0[Rx_Size]=='>')
		   {
			   return  UART_BACK_OK;				   
		   }
//DOWN
		 if(Rx_Buff0[Rx_Size-4]==' ' && Rx_Buff0[Rx_Size-3]=='D' && Rx_Buff0[Rx_Size-2]=='O'&&Rx_Buff0[Rx_Size-1]=='W'&&Rx_Buff0[Rx_Size]=='N')
		   {
			   return  UART_BACK_DOWN;				   
		   }
//00,00000050000011,Saved Success
		 if(Rx_Buff0[Rx_Size-4]=='N' && Rx_Buff0[Rx_Size-3]=='o' && Rx_Buff0[Rx_Size-2]==' ' && Rx_Buff0[Rx_Size-1]=='S' && Rx_Buff0[Rx_Size]=='e')
		   {
			   return  UART_BACK_No_S;				   
		   }
//RDY
		 if(Rx_Buff0[Rx_Size-4]=='P' && Rx_Buff0[Rx_Size-3]==' ' && Rx_Buff0[Rx_Size-2]=='R'&&Rx_Buff0[Rx_Size-1]=='D'&&Rx_Buff0[Rx_Size]=='Y')
		   {
			   return  UART_BACK_APP_RDY;				   
		   }
//CONNECT
		 if(Rx_Buff0[Rx_Size-4]=='N' && Rx_Buff0[Rx_Size-3]=='N' && Rx_Buff0[Rx_Size-2]=='E'&&Rx_Buff0[Rx_Size-1]=='C'&&Rx_Buff0[Rx_Size]=='T')
		   {

			   return  UART_BACK_CONNECT;				   
		   }

		 if(++Rx_Size>RxBufMAX)
		  {
			print_with_Enter(overram);
			return  UART_BACK_OVER_RAM;				  //溢出错误
		  } 
	 }

}
//=-================================================================
void DRV_PutChar(char u8Char)
{
	TI = 0; 
	_emi=1;
    _txr_rxr = u8Char;                 // transfer to uart // wait transfer completing
    Uart_overtine1 =0;
    Uart_overtine =0;
    while(TI==0&&Uart_overtine ==0);                   // check flag
//  while(TI==0);                   // check flag
    TI = 0;                         // clear flag
}

