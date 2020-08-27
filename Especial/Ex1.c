#include <detpic32.h>

unsigned int display7codes(int i)
{
    int arr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    return arr[i];
}




int main(void){

  TRISB = (TRISB & 0xFFF0) | 0x000F;     //SWITCHES
  TRISE = TRISE & 0xFFF0;     //LEDS
  TRISB = (TRISB & 0x00FF);
  //TRISDbits.TRISD5 = 0;
//  TRISDbits.TRISD6 = 0;
  TRISD = (TRISD & 0xFF9F);
  LATDbits.LATD5 = 0;
  LATDbits.LATD6 = 1;

  while(1){
    LATE = (LATE & 0xFFF0) | (PORTB & 0x000F);
    LATB = (LATB & 0x00FF) | display7codes(PORTB & 0x000F)<<8;
  }


  return 0;
}
