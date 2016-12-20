#ifndef __KEYDEL_H_
#define __KEYDEL_H_

#include "reg51.h"
#include "intrins.h"
#include "lcd.h"


#define matrix_key P0  //����Px^2û�õ�����Ϊֻ��10����

extern unsigned char ConfigMode;
extern unsigned char speed_Config[3];
extern uchar buzzer_can;
extern uchar Red_On;
extern uchar Green_On;//�̵���˸
extern uchar CancleFlag;

void ScanKey();
void delay_1(int time);
#endif