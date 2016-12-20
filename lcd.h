#ifndef __LCD_H_
#define __LCD_H_

//#define LCD1602_4PINS

#include<reg51.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define LCD1602_DB  P1      
sbit LCD1602_RS = P2^5;
sbit LCD1602_RW = P2^6;
sbit LCD1602_EN = P2^7;	 

void Lcd1602_Delay1ms(uint c);   //��� 0us

void Read_Busy();           //æ��⺯�����ж�bit7��0������ִ�У�1��ֹ
void Lcd1602_Write_Cmd(unsigned char cmd);     //д����
void Lcd1602_Write_Data(unsigned char dat);   //д����
void LcdSetCursor(unsigned char x,unsigned char y);  //������ʾ
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //��ʾ�ַ���
void InitLcd1602();              //1602��ʼ��
void clearLCD();	//��Ļ���
void LcdShowStrV1(unsigned char x,unsigned char y,unsigned char str);

#endif
