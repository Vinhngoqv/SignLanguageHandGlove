#include <16F877A.h>
#use delay (clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#fuses NOWDT,NOPUT,NOLVP,HS,NOPROTECT,NOBROWNOUT,NOCPD,NOWRT
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void main ()
{
   char f1[3] = "01";
   char f2[3] = "00";
   char f3[3] = "00";
   char f4[3] = "11";
   char f5[3] = "11";
   char f6[3] = "00";
   char f7[3] = "00";
   char fcode[15];
   char fcode_std[15] = "01000011110000";
   int x; 
   strcpy(fcode,f1);
   strcat(fcode,f2);
   strcat(fcode,f3);
   strcat(fcode,f4);
   strcat(fcode,f5);
   strcat(fcode,f6);
   strcat(fcode,f7);
   x = strcmp(fcode,fcode_std);
   if (x==0)
         printf("%d",88);
   //x=(int16)atoi(c); 
   //printf("%d",x);
}
