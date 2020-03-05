#include <detpic32.h>

void delay(unsigned int ms)
{
  for(; ms > 0; ms--)
  {
    resetCoreTimer();
    while(readCoreTimer() < 20000);
  }
}

int main(void)
{
  LATB = LATB & 0x00FF;
  LATD = LATD & 0xFF9F;
  TRISB = TRISB & 0x00FF;
  TRISD = TRISD & 0xFF9F;
  LATDbits.LATD5 = 1;
  LATDbits.LATD6 = 0;

  while(1){
    char c = getChar();
    switch (c) {
      case 'A' | 'a': LATBbits.LATB8 = 1;
                        break;
      case 'B' | 'b': LATBbits.LATB9 = 1;
                        break;
      case 'C' | 'c': LATBbits.LATB10 = 1;
                        break;
      case 'D' | 'd': LATBbits.LATB11 = 1;
                        break;
      case 'E' | 'e': LATBbits.LATB12 = 1;
                        break;
      case 'F' | 'f': LATBbits.LATB13 = 1;
                        break;
      case 'G' | 'g': LATBbits.LATB14 = 1;
                        break;
      case '.':  LATBbits.LATB15 = 1;
                        break;
    }
  }
  return 0;
}
