#include <detpic32.h>


void main(void){
  PR3 =50000;
  TMR3= 0;
  T3CONbits.TCKPS=2;
  T3CONbits.TON=1;

  OC1CONbits.OCM=6;
  OC1CONbits.OCTSEL = 1;
  OC1RS = 12500;
  OC1CONbits.ON=1;
  TRISBbits.TRISB5=1;

  while(1){
    //ton
    while(PORTBbits.RB5!=0);
    while(PORTBbits.RB5!=1);
    resetCoreTimer();
    while(PORTBbits.RB5!=0);
    int Ton = readCoreTimer() / 20;
    printInt10(Ton);
    putChar(' ');

    //toff
    while(PORTBbits.RB5!=1);
    while(PORTBbits.RB5!=0);
    resetCoreTimer();
    while(PORTBbits.RB5!=1);
    int Toff = readCoreTimer() / 20;
    printInt10(Toff);
    putChar(' ');

    int periodo = Ton +Toff;
    printInt10(periodo);
    putChar(' ');
    int freq = 1000000/periodo;
    printInt10(freq);
    putChar('\n');
  }
}
