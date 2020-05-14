#include <detpic32.h>
#include "../util.h"

void configUart(unsigned int baud, char parity, unsigned int stopbits){
  //1-Configurar BaudRate Generator
  U1BRG=((20000000+8*baud)/(16*baud))-1;
  U1MODEbits.BRGH = 0;
  //2-Configurar numero de databits,paridade e stopbits
  if(parity == 'N'){
    U1MODEbits.PDSEL = 00;
  }else if (parity == 'E'){
    U1MODEbits.PDSEL = 01;
  }else{
    U1MODEbits.PDSEL = 10;
  }
  U1MODEbits.STSEL = stopbits;

  //3-Ativa transmitor/recetor
  U1STAbits.UTXEN = 1;
  U1STAbits.URXEN = 1;
  //4-Ativar UART
  U1MODEbits.ON=1;
}

void putc(char byte2send){
  while(U1STAbits.UTXBF == 1);
  U1TXREG = byte2send;
}

void main(void){
  configUart(115200, 'N',1);
  EnableInterrupts();
  while(1){
    putc('+');
    delay(1000);
  }
}
