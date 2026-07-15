#include <xc.h>
#include "matrix_keypad.h"
#define _XTAL_FREQ 20000000
#include "clcd.h"
unsigned int presstime = 0;

unsigned char flag = 0;

unsigned char prekey = ALL_RELEASED;

unsigned char long_press_and_short_press(void)
{
    if (presstime > 10000)
    {
        clcd_print("LONG", LINE1(0));
    }

    static unsigned char onetime = 1;
    static unsigned char longpress = 0;

    unsigned char mkey = read_switches(LEVEL_CHANGE);
    clcd_putch(onetime + '0', LINE2(14));
    clcd_putch(mkey + '0', LINE2(15));

    if (mkey != ALL_RELEASED)
    {
        flag = 1;

        prekey = mkey;

        if (onetime && presstime > 20000)//switch is pressed more than 500ms
        {
            //it is long press
            onetime = 0;

            longpress = 1;

            presstime = 0; //or enable this by using a flag for longpress

            switch (mkey)
            {
            case MK_SW1:return SW1_LONG_PRESS;
            case MK_SW2:return SW2_LONG_PRESS;
            case MK_SW3:return SW3_LONG_PRESS;
            case MK_SW4:return SW4_LONG_PRESS;
            case MK_SW5:return SW5_LONG_PRESS;
            case MK_SW6:return SW6_LONG_PRESS;
            case MK_SW7:return SW7_LONG_PRESS;
            case MK_SW8:return SW8_LONG_PRESS;
            }
        }
    }
    else
    {
        flag = 0;

        onetime = 1;

        if (!longpress && presstime > 0 && presstime <= 20000)
        {
            //it is short press
            switch (prekey)
            {
            case MK_SW1:return SW1_SHORT_PRESS;
            case MK_SW2:return SW2_SHORT_PRESS;
            case MK_SW3:return SW3_SHORT_PRESS;
            case MK_SW4:return SW4_SHORT_PRESS;
            case MK_SW5:return SW5_SHORT_PRESS;
            case MK_SW6:return SW6_SHORT_PRESS;
            case MK_SW7:return SW7_SHORT_PRESS;
            case MK_SW8:return SW8_SHORT_PRESS;
            }
        }
        longpress = 0;
        presstime = 0;
        prekey = 0;
    }
    return NO_EVENT;
}

void init_matrix_keypad(void)
{
    /* Config PORTB as digital */
    ADCON1 = 0x0F;

    /* Set Rows (RB7 - RB5) as Outputs and Columns (RB4 - RB1) as Inputs */
    TRISB = 0x1E;

    /* Set PORTB input as pull up for columns */
    RBPU = 0;

    MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0xE0;
}

unsigned char scan_key(void)
{
    ROW1 = LO;
    ROW2 = HI;
    ROW3 = HI;

    if (COL1 == LO)
    {
        return 1;
    }
    else if (COL2 == LO)
    {
        return 4;
    }
    else if (COL3 == LO)
    {
        return 7;
    }
    else if (COL4 == LO)
    {
        return 10;
    }

    ROW1 = HI;
    ROW2 = LO;
    ROW3 = HI;

    if (COL1 == LO)
    {
        return 2;
    }
    else if (COL2 == LO)
    {
        return 5;
    }
    else if (COL3 == LO)
    {
        return 8;
    }
    else if (COL4 == LO)
    {
        return 11;
    }

    ROW1 = HI;
    ROW2 = HI;
    ROW3 = LO;
    /* TODO: Why more than 2 times? */
    ROW3 = LO;

    if (COL1 == LO)
    {
        return 3;
    }
    else if (COL2 == LO)
    {
        return 6;
    }
    else if (COL3 == LO)
    {
        return 9;
    }
    else if (COL4 == LO)
    {
        return 12;
    }

    return 0xFF;
}

unsigned char read_switches(unsigned char detection_type)
{
    static unsigned char once = 1, key;

    static unsigned char stable = ALL_RELEASED;

    static unsigned char count = 0;

    key = scan_key();

    if (key == stable)
    {
        count = 0;
    }
    else if (++count > 200)
    {
        stable = key;
        count = 0;
    }

    if (detection_type == STATE_CHANGE)
    {

        if (stable != ALL_RELEASED && once)
        {
            once = 0;

            return stable;
        }
        else if (stable == ALL_RELEASED)
        {
            once = 1;
        }
    }
    else if (detection_type == LEVEL_CHANGE)
    {
        return stable;
    }

    return ALL_RELEASED;
}