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

void Lcd1602_Delay1ms(uint c);   //Îó²î 0us

void Read_Busy();           //Ã¦¼ì²âº¯Êı£¬ÅĞ¶Ïbit7ÊÇ0£¬ÔÊĞíÖ´ĞĞ£»1½ûÖ¹
void Lcd1602_Write_Cmd(unsigned char cmd);     //Ğ´ÃüÁî
void Lcd1602_Write_Data(unsigned char dat);   //Ğ´Êı¾İ
void LcdSetCursor(unsigned char x,unsigned char y);  //×ø±êÏÔÊ¾
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //ÏÔÊ¾×Ö·û´®
void InitLcd1602();              //1602³õÊ¼»¯
void clearLCD();	//ÆÁÄ»Çå¿Õ
void LcdShowStrV1(unsigned char x,unsigned char y,unsigned char str);

#endif
