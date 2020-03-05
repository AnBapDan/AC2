#include <detpic32.h>

void delay(unsigned int ms)
{
  for(; ms > 0; ms--)
  {
    resetCoreTimer();
    while(readCoreTimer() < 20000);
  }
}

void seg(int segment){
    switch (segment) {
      case 1:           LATB =  0x00FF;
                        LATBbits.LATB8 = 1;
                        break;
      case 2:           LATB =  0x00FF;
                        LATBbits.LATB9 = 1;
                        break;
      case 3:            LATB =  0x00FF;
                        LATBbits.LATB10 = 1;
                        break;
      case 4:           LATB =  0x00FF;
                        LATBbits.LATB11 = 1;
                        break;
      case 5:           LATB =  0x00FF;
                        LATBbits.LATB12 = 1;
                        break;
      case 6:           LATB =  0x00FF;
                        LATBbits.LATB13 = 1;
                        break;
      case 7:           LATB =  0x00FF;
                        LATBbits.LATB14 = 1;
                        break;
      case 8:            LATB =  0x00FF;
                        LATBbits.LATB15 = 1;
                        break;
      default :         LATB =  0x00FF;
    }
}

int main(void)
 {
   unsigned char segment;

   LATB = LATB & 0x00FF;
   LATD = LATD & 0xFF9F;
   TRISB = TRISB & 0x00FF;
   TRISD = TRISD & 0xFF9F;

   LATDbits.LATD6 = 1; // display high active
   LATDbits.LATD5 = 0; // display low inactive
   // configure RB8-RB14 as outputs
   // configure RD5-RD6 as outputs
   while(1)
   {
     LATDbits.LATD6 = !LATDbits.LATD6; //
     LATDbits.LATD5 = !LATDbits.LATD5; // toggle display selection
     segment = 1;
     int i;
     for(i=0; i <= 7; i++)
     {
       seg(segment);
       delay(500);
       // send "segment" value to display
       // wait 0.5 second
       segment++;
     }
   }
   return 0;
 }
