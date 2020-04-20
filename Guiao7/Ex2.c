#include <detpic32.h>
void main(void){
  //configure Timer T3 (2Hz with interrupts disabled)
  T3CONbits.TCKPS=7; // quinto prescaler (1:32)
  PR3 = 39062;  //Fout = 20MHz /(PRESCALER*(Prx+1)) = 2Hz
  TMR3 = 0;
  IPC2bits.T3IP = 2;
  IFS0bits.T3IF = 0;
  IEC0bits.T3IE = 1; // Enable timer T2 interrupts
  T3CONbits.TON = 1; //Enable timer Tx (last command)
  EnableInterrupts();
  while(1);
}

void _int_(12) isr_T3(void){

  putChar('.');
  IFS0bits.T3IF = 0;
}
