#include <detpic32.h>
typedef struct {
 unsigned int TRISE0 : 1; // 1-bit field (least significant bit)
 unsigned int TRISE1 : 1; // ...
 unsigned int TRISE2 : 1; // ...
 unsigned int TRISE3 : 1; // ...
 unsigned int TRISE4 : 1; // ...
 unsigned int TRISE5 : 1; // ...
 unsigned int TRISE6 : 1; // ...
 unsigned int TRISE7 : 1; // 1-bit field (most significant bit)
 } __TRISEbits_t;


typedef struct {
 unsigned int LATE0 : 1;
 unsigned int LATE1 : 1;
 unsigned int LATE2 : 1;
 unsigned int LATE3 : 1;
 unsigned int LATE4 : 1;
 unsigned int LATE5 : 1;
 unsigned int LATE6 : 1;
 unsigned int LATE7 : 1;
} __LATEbits_t;

void delay(unsigned int ms)
{
  int k =
  for(; ms > 0; ms--)
  {
    resetCoreTimer();
    while(readCoreTimer() < K);
  }
}
  int main(void){
   LATEbits.LATE0 = 0; // The initial value should be set
   // before configuring the port as output
   TRISEbits.TRISE0 = 0; // RD0 configured as output
   while(1){
     delay(500); // half period = 0.5s
     LATEbits.LATE0 = !LATEbits.LATE0;
   }
   return 0;
  }
