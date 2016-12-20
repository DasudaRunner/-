#ifndef __PACKAGE_H_
#define __PACKAGE_H_

#include "reg51.h"

#define uchar unsigned char
#define uint unsigned int

#define SEND_MAX 15 //ÿ�η������֡����

extern uchar send_flag;
extern uchar receive_ok;
extern uchar receive_data[SEND_MAX];

char InPackage(unsigned char *usart_data,unsigned char ID);
unsigned char DePackage(void);
unsigned char check_data(void);
#endif