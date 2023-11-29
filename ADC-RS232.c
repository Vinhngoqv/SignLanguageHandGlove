#include <16F877A.h>
#device ADC=10
#use delay (clock=20000000)
#use rs232(baud=19200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#fuses NOWDT,NOPUT,NOLVP,HS,NOPROTECT,NOBROWNOUT,NOCPD,NOWRT
unsigned int16 value0,value1,value3,value2,value4;
unsigned int16 flex1,flex2,flex3,flex4,flex5;
unsigned int16 y_min = 300, y_max = 600;
unsigned int16 x1_min = 368, x1_max = 536, x2_min = 420, x2_max = 560, x3_min = 384, x3_max = 510;
unsigned int16 x4_min = 428, x4_max = 529, x5_min = 460, x5_max = 579;

void main()
{
   //lcd_init();
   //set_tris_d(0x00);
   //set_tris_e(0x00);
   //enable_interrupts(GLOBAL);
   //enable_interrupts(int_rda);
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   setup_adc(ADC_CLOCK_DIV_8);
   
   
   
   while (1)
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
      
      
      
      printf("a%Lu   b%Lu  c%Lu  d%Lu  e%Luf\n",flex1,flex2,flex3,flex4,flex5);
      delay_ms(100);
   }
}



