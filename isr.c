#include <xc.h>
#define LED PORTBbits.RB0 

extern volatile unsigned int presstime;

unsigned char flag;
void __interrupt() isr(void)
{

  if (TMR0IF)
  {
    TMR0 = TMR0 + 8;
    if (flag)
    {
      ++presstime;
    }
    TMR0IF = 0;
  }
}