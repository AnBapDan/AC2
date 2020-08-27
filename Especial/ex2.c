#include <detpic32.h>


unsigned int temp = 0;
unsigned int flag = 1;
unsigned int display7codes(int i)
{
    int arr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    return arr[i];
}

void delay(int ms){
  for(; ms>0; ms--){
    resetCoreTimer();
    while(readCoreTimer()<20000);
  }
}


void ConfigADC(){
  TRISBbits.TRISB4 = 1;
  AD1PCFGbits.PCFG4= 0;
  AD1CON1bits.SSRC = 7;
  AD1CON1bits.CLRASAM = 1;
  AD1CON3bits.SAMC = 16;
  AD1CON2bits.SMPI = 0;
  AD1CHSbits.CH0SA = 4;
  AD1CON1bits.ON = 1;

}

void ConfigT2(){

  T2CONbits.TCKPS = 0;
  PR2 = 49999 ;
  TMR2 = 0;
  T2CONbits.TON = 1;

  IFS0bits.T2IF = 1;
  IEC0bits.T2IE = 1;
  IPC2bits.T2IP = 3;

}

void ConfigOC2(){
  OC2RS = (49999 +1) * 0.25;
  OC2CONbits.OCM = 6;
  OC2CONbits.OCTSEL = 0;// Use timer T2 as the time base for PWM generation
  OC2CONbits.ON = 1;   // Enable OC2 module

  IFS0bits.OC2IF = 1;
  IEC0bits.OC2IE = 1;
  IPC2bits.OC2IP = 1;
}

int main(void){
  ConfigADC();
  ConfigT2();
  ConfigOC2();
  EnableInterrupts();
  int ms = 100/5;

  //Displays
  TRISDbits.TRISD5 = 0;
  TRISDbits.TRISD6 = 0;
  TRISB = TRISB & 0x00FF;

  while(1){
    AD1CON1bits.ASAM = 1;
    while(IFS1bits.AD1IF == 0);
    temp = (ADC1BUF0*70 +511)/1023;
    printInt(temp ,10);
    putChar('\r');
    IFS1bits.AD1IF = 0 ;
    delay(ms);
  }

  return 0;
}

void _int_(8) isr_t2(){
  int u = temp % 10;
  int d = temp / 10;

  if(flag){
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    LATB = (LATB & 0x00FF) | display7codes(d)<<8;


  }else{
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;
    LATB = (LATB & 0x00FF) | display7codes(u)<<8;

  }
  flag = !flag;
  IFS0bits.T2IF = 0;
}

void _int_(10) isr_oc2(){
  IFS0bits.OC2IF = 0;
}
