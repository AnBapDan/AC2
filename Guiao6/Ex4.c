// Eduardo Almeida 93148
// Daniel Andrade 93313

#include <detpic32.h>
volatile unsigned char voltage = 0;
void delay(unsigned int ms)
{
  for(; ms > 0; ms--)
  {
    resetCoreTimer();
    while(readCoreTimer() < 20000);
  }
}

unsigned int display7codes(int i)
{
    int arr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    return arr[i];
}

int send2displays(unsigned int value, int base)
{
    static char displayFlag = 0;
    int high = value / base;
    int low = value % base;

    high = display7codes(high);
    low = display7codes(low);

    if(displayFlag)
    {
        LATDbits.LATD6 = 0;
        LATDbits.LATD5 = 1;
        LATB = (LATB & 0x80FF) | (high << 8);
    }
    else
    {
        LATDbits.LATD6 = 1;
        LATDbits.LATD5 = 0;
        LATB = (LATB & 0x80FF) | (low << 8);
    }
    displayFlag = !displayFlag;
    return 0;
}

void _int_(27) isr_adc(void){
  int *p = (int *)(&ADC1BUF0);
  int i;
  int x = 0;
  for(i = 0; i<4;i++){
    x+=p[i*4];
  }
  double val_ad = x /(AD1CON2bits.SMPI+1);
  voltage =(int)(val_ad*33+511)/1023;
//  AD1CON1bits.ASAM = 1; // Start conversion
  IFS1bits.AD1IF = 0;
}



int main(){
  TRISB = TRISB & 0x00FF;
  TRISD = TRISD & 0xFF9F;
  LATBbits.LATB15 = 1;
  TRISBbits.TRISB4 = 1;
  AD1PCFGbits.PCFG4 = 0;
  AD1CON1bits.SSRC = 7;

  AD1CON1bits.CLRASAM = 1;

  AD1CON3bits.SAMC = 16;
  AD1CON2bits.SMPI = 7;
  AD1CHSbits.CH0SA = 4;
  AD1CON1bits.ON = 1;

  IPC6bits.AD1IP = 2; // configure priority of A/D interrupts to 2
  IEC1bits.AD1IE = 1; // enable A/D interrupts
  IFS1bits.AD1IF = 0;
  EnableInterrupts();
  int cnt = 0;
  while(1){
    if(cnt % 25 == 0){
      AD1CON1bits.ASAM = 1; // Start conversion
    }
    send2displays(voltage,10);
    cnt++;
    delay(10);
  }
  return 0;
}
