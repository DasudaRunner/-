//板1：人机交互板
//板2：地盘控制板
#include "reg51.h"
#include "lcd.h"
#include "KeyDel.h"
#include "package.h"
/*
2016.11.05 程序框架
2016.11.10-2016.11.11 完成协议的封装
2016.11.15 完成板1部分细节功能
2016.11.16 完成接收地盘速度信息功能
2016.11.20 完成矩阵键盘部分
2016.11.22 完成细节 LED及BUZZER,配置模式超时自动退出
2016.11.23 完成速度设定功能
2016.11.25-2016.11.30 两板联调


按键接INT0
*/
#define CANCLE_TIME 3  //进入速度配置模式后，用户长时间未按键，则自动退出配置模式。单位：秒

#define uchar unsigned char
#define uint unsigned int
//test
uchar toggle=0;
uchar buzzerFlag=1;

uchar NowSpeed[4]={0x30,0x2e,0x30,'\0'};

sbit buzzer=P2^2;
sbit red_led=P2^1;
sbit green_led=P2^0;

void INT0_init()
{
	IT0=1;
	EX0=1;
	EA=1;
}
void TimerConfig()
{
	TMOD = 0x21;	
	TH0 = (65536 - 50000)/256;//50MS
	TL0 = (65536 - 50000)%256;
		
	TR0=1;
	ET0=1;
	EA=1;
}
void UsartConfiguration()
{
	SCON=0X50;			//串口工作方式2
	TMOD=0X21;			
	PCON=0X80;			
	TH1=0XF3;				//baud 4800
	TL1=0XF3;
	ES=1;						
	EA=1;						
	TR1=1;					
}
void main(void)
{
	InitLcd1602();	
	LcdShowStr(2,0,"system_init");
	
	INT0_init();
	TimerConfig();
	UsartConfiguration();
	
	toggle=1;
	while(1)
	{
		
		if(ConfigMode)
		{
			ScanKey();
		}else
		{
			if(toggle)
			{
				clearLCD();
				toggle=0;
			}			
			
			if(receive_ok)
			{
				receive_ok=0;
				if(check_data())
				{
					NowSpeed[0]=receive_data[4]*100+receive_data[5]*10+receive_data[6];
					if(NowSpeed[0]==0)
					{
						red_led=0;
						if(buzzerFlag)
						{
							buzzer_can=1;
							buzzerFlag=0;
						}
					}
					else
					{
						buzzerFlag=1;
						red_led=1;
					}
					NowSpeed[2]=NowSpeed[0]%20/2+0x30-2;
					if(NowSpeed[2]<0x30)
					{
						NowSpeed[2]=0x30;
					}
					NowSpeed[0]=NowSpeed[0]/20+0x30;
				}
			}
			
			LcdShowStr(0,0,"ConfigSp:");
			LcdShowStr(9,0,speed_Config);	
			LcdShowStr(0,1,"NowSp:");
			LcdShowStr(6,1,NowSpeed);	
		}

	}
	
}
void int0_SERVICE() interrupt 0
{
	if(ConfigMode)
	{
		//SBUF=
	}else
	{
		ConfigMode=1;
		CancleFlag=1;
	}
}
void Timer0_SERVICE()	interrupt 1
{	
	static uint cnt=0,BuzzerCnt=0,CancleCnt=0;
	TH0 = (65536 - 10000)/256;//10ms
	TL0 = (65536 - 10000)%256;
	cnt++;
	if(buzzer_can)
	{
		buzzer=~buzzer;
		BuzzerCnt++;
		if(BuzzerCnt>=100)
		{
			buzzer_can=0;
			BuzzerCnt=0;
		}
	}
	if(cnt>=10)
	{
		cnt=0;
		if(Red_On)//检测红灯
		{
			red_led=~red_led;
		}
		if(Green_On)//检测绿灯
		{
			green_led=~green_led;
		}
	}
	//用户长时间未操作，自动退出
	if(CancleFlag)
	{
		CancleCnt++;
		if(CancleCnt>=(CANCLE_TIME*100))
		{			
			toggle=1;
			ConfigMode=0;
			CancleFlag=0;
			CancleCnt=0;
		}
	}else
	{
		CancleCnt=0;
	}
	
}
void Usart_SERVICE() interrupt 4 using 3
{
	if(RI)
	{
		RI = 0;
		DePackage();

	}else if (TI)
	{
		TI = 0;
		send_flag=0;
		green_led=~green_led;
	}
					
}