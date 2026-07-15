#include <xc.h>
#define LED PORTBbits.RB0 

extern unsigned int presstime;

extern unsigned char flag;

void __interrupt() isr(void)
{

    if (TMR0IF)
    {
        TMR0 = TMR0 + 8;
        if (flag)
        {
            if (presstime < 65535)
                ++presstime;
        }
        else
        {
            presstime = 0;
        }
        TMR0IF = 0;
    }
}