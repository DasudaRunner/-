#ifndef __KEYDEL_H_
#define __KEYDEL_H_

#include "reg51.h"
#include "intrins.h"
#include "lcd.h"


#define matrix_key P0  //其中Px^2没用到，因为只有10个键

extern unsigned char ConfigMode;
extern unsigned char speed_Config[3];
extern uchar buzzer_can;
extern uchar Red_On;
extern uchar Green_On;//绿灯闪烁
extern uchar CancleFlag;

void ScanKey();
void delay_1(int time);
#endif