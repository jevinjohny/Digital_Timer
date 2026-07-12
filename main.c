/*
 * File:   main.c
 * Author: jevin
 *
 * Created on 10 July, 2026, 4:08 PM
 */
#include <xc.h>
#include "i2c.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ds1307.h"
#include  "main.h"
#include "timer0.h"
#include "time.h"

void main(void)
{
    init_i2c();

    init_clcd();

    init_matrix_keypad();

    init_ds1307();
  
    init_timer0();

    GIE = 1;

    PEIE = 1;
    
    while (1)
    {
        unsigned char key = read_switches(STATE_CHANGE);

        
        switch(key)
        {
            case ALL_RELEASED:
            {
                get_time();
                display_time();

                get_date();
                display_date();
                
                break;
            }
            case MK_SW1:
            {
                settime();
                break;
            }

        }
    }
    return;
}
