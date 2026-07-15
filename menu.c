#include "clcd.h"
#include "main.h"
#include "matrix_keypad.h"
#include "time.h"
#include <builtins.h>
#include <pic18.h>
#include <xc.h>

// main menu
unsigned char page = 0;

void menu(void)
{
    while (1)
    {
        unsigned char key = long_press_and_short_press(); // reads digital keypad

        if (key == SW2_SHORT_PRESS) // page down
        {
            CLEAR_DISP_SCREEN;
            if (page <= 2)
                page++;
            else
                page = 3;
        }
        else if (key == SW1_SHORT_PRESS) // page up
        {
            CLEAR_DISP_SCREEN;
            if (page > 1)
                page--;
            else
                page = 0;
        }

        //    if (!menutoggle)
        //        return;

        // page scrolling
        switch (page)
        {
        case 0:
        {
            clcd_print("1.SET EVENT", LINE1(0));
            clcd_print("2.VIEW EVENT", LINE2(0));
            clcd_putch('<', LINE1(14));
            if (key == SW1_LONG_PRESS)
            {
            }
            break;
        }
        case 1:
        {
            clcd_print("2.VIEW EVENT", LINE1(0));
            clcd_print("3.SET TIME", LINE2(0));
            clcd_putch('<', LINE1(14));
            if (key == SW1_LONG_PRESS)
            {
            }
            break;
        }
        case 2:
        {
            clcd_print("3.SET TIME", LINE1(0));
            clcd_print("4.SET DATE", LINE2(0));
            clcd_putch('<', LINE1(14));
            if (key == SW1_LONG_PRESS)
            {
                settime();

            }
            break;
        }
        case 3:
        {
            clcd_print("4.SET DATE", LINE1(0));
            clcd_putch('<', LINE1(14));
            if (key == SW1_LONG_PRESS)
            {

            }
            break;
        }
        }

    }
}





