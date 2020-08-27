#include <detpic32.h>

void delay(int ms){
  for(; ms> 0; ms--){
    resetCoreTimer();
    while (readCoreTimer() < 20000);
  }
}

void configUart(int baudrate, int databits, char pbits,  int stopbits){

  U1BRG =((PBCLK+ 8 * baudrate)/ (16*baudrate))-1;
  U1MODEbits.BRGH = 0;

  /*Stopbits*/
  if(stopbits==1){
    U1MODEbits.STSEL = 0;
  }else{
    U1MODEbits.STSEL = 1;
  }

  /*Paritybits*/
  switch(pbits){
    case 'N': U1MODEbits.PDSEL = 0; break;
    case 'E': U1MODEbits.PDSEL = 1; break;
    case 'O': U1MODEbits.PDSEL = 2; break;
  }

  /*EnableUart*/
  U1STAbits.URXEN = 1;
  U1STAbits.UTXEN = 1;
  U1MODEbits.ON = 1;

  IEC0bits.U1RXIE = 1;
  IEC0bits.U1TXIE = 1;

  IPC6bits.U1IP = 2;
}


char getc(){
  while(U1STAbits.URXDA == 0);
  char c = U1RXREG;
  return c ;
}

void putc(char c){
  while(U1STAbits.UTXBF == 1);
  U1TXREG = c;
}

int main(void){
  EnableInterrupts();
  configUart(57600,8, 'O', 1);

  TRISB = (TRISB & 0xFFF0) | 0x000F; //SWITCHES
  while(1);

  return 0;
}

void _int_(24) isr_u1(){
  char t = getc();
  char x = (PORTB & 0x000F) + '0';
  char* y = "Daniel";
  int i = 0;
  switch(t){
    case 'L':
              putc(x);
              break;

    case 'S':
              for(i = 0; i < 6; i++){
                putc(*y);
                y++;
              }
              break;

    case 'Q': exit(0);
              break;

  }
//  putc('\r');
  IFS0bits.U1RXIF = 0;
  IFS0bits.U1TXIF = 0;
}
