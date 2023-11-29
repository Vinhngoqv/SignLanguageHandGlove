#include <16F877A.h>
#use delay (clock=20Mhz)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#fuses NOWDT,NOPUT,NOLVP,HS,NOPROTECT,NOBROWNOUT,NOCPD,NOWRT
#include <string.h>
#include <stdlib.h>
//#include "DFPlayerMP3.c"
/*
#define START_byte         0x7E
#define VER                0xFF
#define DATA_len           0x06  //not including parity
#define CMD                0x03  //mode play specify tracks
#define FBack_byte         0x00  //0x01: need answering, 0x00: do not need to return the response
#define DH                 0x00  // Track address high byte
//#define DL                 0x01  //1st track
#define Checksum_high      0xFF
#define Checksum_low       0xE6
#define END_byte           0xEF
*/

void do_MP3_cmd(byte DL)
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
         case 8:
               do_MP3_cmd(0x08); break;
         case 9: 
               do_MP3_cmd(0x09); break;
         case 10: 
               do_MP3_cmd(0x0A); break;
         case 11: 
               do_MP3_cmd(0x0B); break;
         case 12: 
               do_MP3_cmd(0x0C); break;
         case 13: 
               do_MP3_cmd(0x0D); break;
         case 14: 
               do_MP3_cmd(0x0E); break;
         case 15:
               do_MP3_cmd(0x0F); break;
         case 16: 
               do_MP3_cmd(0x10); break;
         case 17: 
               do_MP3_cmd(0x11); break;
         case 18: 
               do_MP3_cmd(0x12); break;
         case 19: 
               do_MP3_cmd(0x13); break;
         case 20: 
               do_MP3_cmd(0x14); break;
         case 21: 
               do_MP3_cmd(0x15); break;
         case 22: 
               do_MP3_cmd(0x16); break;
         case 23: 
               do_MP3_cmd(0x17); break;
         case 24: 
               do_MP3_cmd(0x18); break;
         case 25: 
               do_MP3_cmd(0x19); break;
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
   byte mp3_cmd_vol[8] = {0x7E,0xFF,0x06,0x06,0x00,0x00,0x0A,0xEF};
   for (int j=0; j<8; j++)
   {
      putchar(mp3_cmd_vol[j]);
      delay_ms(5);
   }
}

void main ()
{
   //output_b(0xFF);
   //while(1)
   setup_mp3_player();
   delay_ms(100);
  //{
  
      //unsigned char temp = input_b;
      //if (input(PIN_B0) == 0)
            //{
               //select_track(3);
      delay_ms(1000);
      select_track(1);
      delay_ms(2000);
      select_track(2);
      delay_ms(2000);
      select_track(3);
      delay_ms(2000);
      select_track(4);
      delay_ms(2000);
      select_track(5);
      delay_ms(2000);
      select_track(6);
      delay_ms(2000);
      select_track(7);
      delay_ms(1000);
      select_track(8);
      delay_ms(2000);
      select_track(9);
      delay_ms(2000);
      select_track(10);
     
               //do_MP3_cmd(0x03);
            //}  
   //}
  
}




