#include <16F877A.h>  
#device ADC=10
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#use delay(crystal=20MHz)       
#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#define MPU_SDA PIN_C4                               
#define MPU_SCL PIN_C3                         
#use I2C(master, sda=MPU_SDA, scl=MPU_SCL)       
#include "MPU6050.c"               
#include "math.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define RAD_TO_DEG 180/PI         

char f1[3],f2[3],f3[3],f4[3],f5[3],f6[3];
/*char fcode_std_A_1[13] = "011111111100";
char fcode_std_A_2[13] = "001111111100";
char fcode_std_B_1[13] = "011000000000";
char fcode_std_B_2[13] = "010100000000";
char fcode_std_C_1[13] = "011011111000";
char fcode_std_C_2[13] = "011011101000";
char fcode_std_V_1[13] = "011000101100";
char fcode_std_V_2[13] = "010100101100";*/

//int8 temp;

unsigned int16 value0,value1,value3,value2,value4;
unsigned int16 flex1,flex2,flex3,flex4,flex5;
unsigned int16 y_min = 300, y_max = 600;
unsigned int16 x1_min = 368, x1_max = 536, x2_min = 420, x2_max = 560, x3_min = 384, x3_max = 510;
unsigned int16 x4_min = 428, x4_max = 529, x5_min = 460, x5_max = 579;

signed int16 accX,accY,accZ;
DOUBLE accXangle,accYangle;
double fil_accX,fil_accY,fil_accZ; 
double yacc_min = -2, yacc_max = 2;
double xi_min = -1.93, xi_max = 1.9, yi_min = -2.042, yi_max = 1.97, zi_min = -2.01, zi_max = 1.92;
int8 z;
char fcode[13];
int8 t=0;
/*#int_timer0
void ngat()
{
   t=t+1;
   set_timer0(60);
}*/

/*void do_MP3_cmd(byte DL)
{
   byte mp3_cmd[8] = {0x7E,0xFF,0x06,0x03,0x00,0x00};
   for (int i=0; i<6; i++)
   {
      putchar(mp3_cmd[i]);
      delay_ms(5);
   }
   putchar(DL);
   delay_ms(5);
   putchar(0xEF);
}
void select_track(int8 num)
{
   switch (num)
         {
         case 1:
               do_MP3_cmd(0x01); break;
         case 2: 
               do_MP3_cmd(0x02); break;
         case 3: 
               do_MP3_cmd(0x03); break;
         case 4: 
               do_MP3_cmd(0x04); break;
         case 5: 
               do_MP3_cmd(0x05); break;
         case 6: 
               do_MP3_cmd(0x06); break;
         case 7: 
               do_MP3_cmd(0x07); break;
         }
}

void setup_mp3_player ()
{
   byte mp3_cmd[8] = {0x7E,0xFF,0x06,0x09,0x00,0x00,0x01,0xEF};
   for (int i=0; i<8; i++)
   {
      putchar(mp3_cmd[i]);
      delay_ms(5);
   }
   delay_ms(100);
   byte mp3_cmd_vol[8] = {0x7E,0xFF,0x06,0x06,0x00,0x00,0x14,0xEF};
   for (int j=0; j<8; j++)
   {
      putchar(mp3_cmd_vol[j]);
      delay_ms(5);
   }
}*/

#separate void Read_flexsensor()
{
      set_adc_channel(0);
      value0=read_adc();
      if (value0 >= x1_min)
         flex1 = y_min+((y_max-y_min)*(value0-x1_min))/(x1_max-x1_min);
      else  
         flex1 = y_min-((y_max-y_min)*(x1_min-value0))/(x1_max-x1_min);
      delay_ms(1);
      
      set_adc_channel(1);
      value1=read_adc();
      if (value1 >= x2_min)
         flex2 = y_min+((y_max-y_min)*(value1-x2_min))/(x2_max-x2_min);
      else  
         flex2 = y_min-((y_max-y_min)*(x2_min-value1))/(x2_max-x2_min);
      delay_ms(1);
      
      set_adc_channel(2);
      value2=read_adc();
      if (value2 >= x3_min)
         flex3 = y_min+((y_max-y_min)*(value2-x3_min))/(x3_max-x3_min);
      else  
         flex3 = y_min-((y_max-y_min)*(x3_min-value2))/(x3_max-x3_min);
      delay_ms(1);
      
      set_adc_channel(3);
      value3=read_adc();
      if (value3 >= x4_min)
         flex4 = y_min+((y_max-y_min)*(value3-x4_min))/(x4_max-x4_min);
      else  
         flex4 = y_min-((y_max-y_min)*(x4_min-value3))/(x4_max-x4_min);
      delay_ms(1);
      
      set_adc_channel(4);
      value4=read_adc();
      if (value4 >= x5_min)
         flex5 = y_min+((y_max-y_min)*(value4-x5_min))/(x5_max-x5_min);
      else  
         flex5 = y_min-((y_max-y_min)*(x5_min-value4))/(x5_max-x5_min);
      delay_ms(1);
}

#separate void Read_ACC_XYZ ()
{
      accX = Mpu6050_GetData (MPU6050_RA_ACCEL_XOUT_H); 
      delay_ms(1);
      accY = Mpu6050_GetData (MPU6050_RA_ACCEL_YOUT_H);
      delay_ms(1);
      accZ = Mpu6050_GetData (MPU6050_RA_ACCEL_ZOUT_H);  
      delay_ms(1);    
      fil_accX = (double)accX/8192;
      fil_accX = yacc_min+((yacc_max-yacc_min)*(fil_accX-xi_min))/(xi_max-xi_min);
      delay_ms(1);
      fil_accY = (double)accY/8192;
      fil_accY = yacc_min+((yacc_max-yacc_min)*(fil_accY-yi_min))/(yi_max-yi_min);
      delay_ms(1);
      fil_accZ = (double)accZ/8192;
      fil_accZ = yacc_min+((yacc_max-yacc_min)*(fil_accZ-zi_min))/(zi_max-zi_min);
      delay_ms(1);
      
      accXangle = atan2 (fil_accY,fil_accZ) * RAD_TO_DEG; 
      accYangle = atan2 (fil_accX,fil_accZ) * RAD_TO_DEG;
}
   
#separate void Identify_gesture()
{
      if (flex1>500)
         f1 = "00";
      else if (flex1>460 && flex1<500)
         f1 = "01";
      else if (flex1>380 && flex1<460)
         f1 = "10";
      else if (flex1<380)
         f1 = "11";
         
      if (flex2>500)
         f2 = "00";
      else if (flex2>395 && flex2<500)
         f2 = "01";
      else if (flex2>290 && flex2<395)
         f2 = "10";
      else if (flex2<290)
         f2 = "11";
         
      if (flex3>590)
         f3 = "00";
      else if (flex3>420 && flex3<590)
         f3 = "01";
      else if (flex3>250 && flex3<420)
         f3 = "10";
      else if (flex2<250)
         f3 = "11";
         
      if (flex4>600)
         f4 = "00";
      else if (flex4>425 && flex4<600)
         f4 = "01";
      else if (flex4>250 && flex4<425)
         f4 = "10";
      else if (flex4<250)
         f4 = "11";
         
      if (flex5>570)
         f5 = "00";
      else if (flex5>395 && flex5<570)
         f5 = "01";
      else if (flex5>220 && flex5<395)
         f5 = "10";
      else if (flex5<220)
         f5 = "11";
      
      if (accXangle>70 && accXangle <105)
         f6 = "00";
      else if (accXangle>40 && accXangle <70)
         f6 = "01";
      else if (accXangle>-10 && accXangle <10)
         f6 = "10";
      else if (accXangle>-110 && accXangle <-80)
         f6 = "11";
      
      
      strcpy(fcode,f6);
      strcat(fcode,f5);
      strcat(fcode,f4);
      strcat(fcode,f3);
      strcat(fcode,f2);
      strcat(fcode,f1);
      /*if(strcmp(fcode,fcode_std_A_1) == 0 || strcmp(fcode,fcode_std_A_2) == 0 )
         {z = 1;}
      if(strcmp(fcode,fcode_std_B_2) == 0 )
         {z = 2;}
      if(strcmp(fcode,fcode_std_C_1) == 0 || strcmp(fcode,fcode_std_C_2) == 0 )
         {z = 3;}
      if(strcmp(fcode,fcode_std_V_1) == 0 || strcmp(fcode,fcode_std_V_2) == 0 )
         {z = 21;}*/
      
}


void main()
{
   //setup_mp3_player();
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   setup_adc(ADC_CLOCK_DIV_8);
   Mpu6050_Init () ;
   delay_ms (500) ;
   INT8 x;
   
   x = Mpu6050_Read(MPU6050_RA_WHO_AM_I);
                                                       
   IF (x != 0x68)
   {
      
      printf ("Connection ERR!!!");
      return;
   }                    

   
   WHILE (true)
   {    
      //------------Khoi Flex sensor-----------    
      Read_flexsensor();
      delay_ms(1);

   
      //------------Khoi MPU6050----------
      Read_ACC_XYZ();
      delay_ms(1);
  
   
      //--------------Khoi module am thanh DFPlayer MP3 Mini---------------
      Identify_gesture();
      delay_ms(1);
      //printf("%s\n",fcode);
      if (t==2)
         {
            t = 0;
            //printf("%d\n",z);
            //printf("%s\n",fcode); //lay mau 
            printf("a%Lub%Luc%Lud%Lue%Luf%0.0fg%sh\n",flex1,flex2,flex3,flex4,flex5,accXangle,fcode);
         }
      //printf("%d\n",z);
      //z=0;
      t=t+1;
      delay_ms(100);
   }
}

