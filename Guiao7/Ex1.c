#include <detpic32.h>
void main(void){
  //configure Timer T3 (2Hz with interrupts disabled)
  T3CONbits.TCKPS=7;
  PR3 = 39062;  //Fout = 20MHz /(PRESCALER*(Prx+1)) = 2Hz
  TMR3 = 0; //Reset Tx count
  IPC2bits.T3IP = 2;
  IFS0bits.T3IF = 0;
  IEC0bits.T3IE = 0;
  T3CONbits.TON = 1; //Enable timer Tx (last command)
  while(1){
      //Wait til T3IF=1
      while(IFS0bits.T3IF==0);
      //Reset T3IF
      IFS0bits.T3IF = 0;
      putChar('.');
  }
}
