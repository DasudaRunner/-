#include "KeyDel.h"
#include "package.h"
#include "lcd.h"
unsigned char temp,matrix_cnt=0,ConfigMode,key_temp[3]={0x00,0x00,'\0'};
unsigned char key[3]={0x30,0x30,'\0'};

unsigned char speed_Config[3]={0x30,0x30,'\0'};
unsigned char old_speed[3]={0x30,0x30,'\0'};

uchar send_data[2]={0x00,0x00};
uchar send_ok;//���ڷ��ͳɹ�
uchar buzzer_can;//1����������1s
uchar Red_On;//�����˸
uchar Green_On;//�̵���˸
uchar CancleFlag=0;

sbit red_led1=P2^1;
sbit green_led1=P2^0;
//��ʱ1ms
void delay_1(int time)
{

	int a,b;
	for(a=time;a>0;a--)
	{
		for(b=125;b>0;b--);
	}

}
//ɨ���û�������������
//			ɨ�跽�����ã�����ɨ�跽��
void ScanKey()
{
		LcdShowStr(0,0,"Pre_Speed:");
		LcdShowStr(10,0,old_speed);
		LcdShowStr(0,1,"New_Speed:");
	
		matrix_key=0X7F;
    temp=matrix_key;
    temp=temp&0x0F;
    if(temp!=0x0F)
    {
      delay_1(10);
      if(temp!=0x0F)
      {
				CancleFlag=0;
				
				key_temp[matrix_cnt]=0;
				matrix_cnt++;
         while(temp!=0x0F)
         {
           temp=matrix_key;
           temp=temp&0x0F;
         }
					key[0]=key_temp[0]+0x30;
					key[1]=key_temp[1]+0x30;
					LcdShowStrV1((matrix_cnt+9),1,key[matrix_cnt-1]);		
      }
    }
			
		matrix_key=0XbF;
    temp=matrix_key;
    temp=temp&0x0F;
    if(temp!=0x0F)
    {
      delay_1(10);
      if(temp!=0x0F)
      {
				CancleFlag=0;
       temp=matrix_key;
			switch(temp)
			{
				case 0xbe:
						 key_temp[matrix_cnt]=7;
						 break;

				case 0xbd:
						 key_temp[matrix_cnt]=8;
						 break;

				case 0xb7:
						 key_temp[matrix_cnt]=9;
						 break;

			 }
				matrix_cnt++;
         while(temp!=0x0F)
         {
           temp=matrix_key;
           temp=temp&0x0F;
//           //beep=0;
         }
					key[0]=key_temp[0]+0x30;
					key[1]=key_temp[1]+0x30;
					LcdShowStrV1((matrix_cnt+9),1,key[matrix_cnt-1]);			
      }
    }
	
		matrix_key=0XdF;
    temp=matrix_key;
    temp=temp&0x0F;
    if(temp!=0x0F)
    {
      delay_1(10);
      if(temp!=0x0F)
      {
				CancleFlag=0;
       temp=matrix_key;
			switch(temp)
			{
				case 0xde:
						 key_temp[matrix_cnt]=4;
						 break;

				case 0xdd:
						 key_temp[matrix_cnt]=5;
						 break;

				case 0xd7:
						 key_temp[matrix_cnt]=6;
						 break;

			 }
				matrix_cnt++;
         while(temp!=0x0F)
         {
           temp=matrix_key;
           temp=temp&0x0F;
         }
					key[0]=key_temp[0]+0x30;
					key[1]=key_temp[1]+0x30;
					LcdShowStrV1((matrix_cnt+9),1,key[matrix_cnt-1]);		
      }
    }

		matrix_key=0XEF;
    temp=matrix_key;
    temp=temp&0x0F;
    if(temp!=0x0F)
    {
      delay_1(10);
      if(temp!=0x0F)
      {
				CancleFlag=0;
       temp=matrix_key;
			switch(temp)
			{
				case 0xee:
						 key_temp[matrix_cnt]=1;
						 break;

				case 0xed:
						 key_temp[matrix_cnt]=2;
						 break;

				case 0xe7:
						 key_temp[matrix_cnt]=3;
						 break;

			 }
				matrix_cnt++;
         while(temp!=0x0F)
         {
           temp=matrix_key;
           temp=temp&0x0F;
         }
					key[0]=key_temp[0]+0x30;
					key[1]=key_temp[1]+0x30;
					LcdShowStrV1((matrix_cnt+9),1,key[matrix_cnt-1]);			

      }
    }		
		//���û��Ѿ��������������������ִ�����������һ��ˢ��LCD��Ļ����ʾ
			if(matrix_cnt==2)
			{
				
				switch(ConfigMode)
				{
					case 1:
							speed_Config[0]=key[0];
							speed_Config[1]=key[1];
							old_speed[0]=speed_Config[0];
							old_speed[1]=speed_Config[1];	

							send_data[0]=speed_Config[0]-0x30;
							send_data[1]=speed_Config[1]-0x30;
							delay_1(500);

							clearLCD();
							LcdShowStr(3,0,"Setting...");
							send_ok=InPackage(send_data,0x01);
							if(send_ok)
							{
								Green_On=1;
								Red_On=0;
							}else
							{
								Green_On=0;
								Red_On=1;
							}
							delay_1(1000);
							clearLCD();
							
							Green_On=0;
							green_led1=1;
							 break;

					case 2:

								break;
				 }
				ConfigMode=0;
				matrix_cnt=0;
			}
	
}