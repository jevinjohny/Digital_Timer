#include "time.h"
#include "clcd.h"
#include "ds1307.h"
#include "main.h"
#include "matrix_keypad.h"
#include <xc.h>

extern volatile unsigned int presstime;


unsigned int val = 0;
unsigned char clock_reg[3] = {0};
unsigned char calender_reg[4] = {0};
unsigned char time[9];
unsigned char date[11];

void get_date(void)
{
    calender_reg[0] = read_ds1307(YEAR_ADDR);
    calender_reg[1] = read_ds1307(MONTH_ADDR);
    calender_reg[2] = read_ds1307(DATE_ADDR);
    calender_reg[3] = read_ds1307(DAY_ADDR);

    date[6] = '2';
    date[7] = '0';
    date[8] = '0' + ((calender_reg[0] >> 4) & 0x0F);
    date[9] = '0' + (calender_reg[0] & 0x0F);
    date[5] = '-';
    date[3] = '0' + ((calender_reg[1] >> 4) & 0x0F);
    date[4] = '0' + (calender_reg[1] & 0x0F);
    date[2] = '-';
    date[0] = '0' + ((calender_reg[2] >> 4) & 0x0F);
    date[1] = '0' + (calender_reg[2] & 0x0F);
    date[10] = '\0';
}

void display_date(void)
{
    clcd_print("DATE:", LINE2(0));
    clcd_print(date, LINE2(5));
}

// void display_time(void)
// {
// 	clcd_print(time, LINE2(2));

// 	if (clock_reg[0] & 0x40)
// 	{
// 		if (clock_reg[0] & 0x20)
// 		{
// 			clcd_print("PM", LINE2(12));
// 		}
// 		else
// 		{
// 			clcd_print("AM", LINE2(12));
// 		}
// 	}
// }

void display_time(void)
{
    clcd_print((const unsigned char *) "TIME:", LINE1(0));
    clcd_print(time, LINE1(5));
}

void get_time(void)
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40)
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    else
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
}

void settime(void)
{
    CLEAR_DISP_SCREEN;
    unsigned char sec = 0;
    unsigned char min = 0;
    unsigned char hr = 0;

    hr = read_ds1307(HOUR_ADDR);
    min = read_ds1307(MIN_ADDR);
    sec = read_ds1307(SEC_ADDR);

    hr = (((hr >> 4) & 0x03) * 10) + (hr & 0x0F);
    min = (((min >> 4) * 10) + (min & 0x0F));
    sec = (((sec >> 4) * 10) + (sec & 0x0F));

    clcd_print((const unsigned char *) "SET  TIME", LINE1(0));
    __delay_ms(1000);

    unsigned char mode = 0;

    CLEAR_DISP_SCREEN;

    while (1)
    {
        unsigned char key = read_switches(STATE_CHANGE);

        if (key == MK_SW1)
        {
            mode++;
            if (mode > 2)
                mode = 0;
        }
        else if (key == MK_SW6)
        {
            CLEAR_DISP_SCREEN;
            return;
        }
        else if (key == MK_SW5)
        {
            sec = (((sec / 10) << 4 | (sec % 10)));
            min = (((min / 10) << 4 | (min % 10)));
            hr = (((hr / 10) << 4 | (hr % 10)));

            // Clear bit 6 to ensure 24-hour mode
            hr &= 0xBF; // Clear bit 6 (0x40)

            write_ds1307(SEC_ADDR, sec);
            write_ds1307(MIN_ADDR, min);
            write_ds1307(HOUR_ADDR, hr);

            CLEAR_DISP_SCREEN;
            clcd_print((const unsigned char *) "TIME SET!...", LINE1(0));
            __delay_ms(1000);
            CLEAR_DISP_SCREEN;
            return;
        }

        switch (mode)
        {
        case 0:
        {
            if (key == MK_SW3)
            {
                //                CLEAR_DISP_SCREEN;
                hr++;
                if (hr > 23)
                {
                    hr = 0;
                }
            }
            else if (key == MK_SW2)
            {
                //                CLEAR_DISP_SCREEN;
                hr--;
                if (hr == 255)
                    hr = 23;
            }
            break;
        }
        case 1:
        {
            if (key == MK_SW1)
            {
                //                CLEAR_DISP_SCREEN;
                min++;
                if (min > 59)
                {
                    min = 0;
                }
            }
            else if (key == MK_SW2)
            {
                //                CLEAR_DISP_SCREEN;
                min--;
                if (min == 255)
                    min = 59;
            }
            break;
        }
        case 2:
        {
            if (key == MK_SW1)
            {
                //                CLEAR_DISP_SCREEN;
                sec++;
                if (sec > 59)
                {
                    sec = 0;
                }
            }
            else if (key == MK_SW2)
            {
                //                CLEAR_DISP_SCREEN;
                sec--;
                if (sec == 255)
                    sec = 59;
            }
            break;
        }
        }
        time[0] = (hr / 10) + '0';
        time[1] = (hr % 10) + '0';
        time[2] = ':';

        time[3] = (min / 10) + '0';
        time[4] = (min % 10) + '0';
        time[5] = ':';

        time[6] = (sec / 10) + '0';
        time[7] = (sec % 10) + '0';
        time[8] = '\0';

        clcd_print(time, LINE2(0));

        if (mode == 0)
        {
            clcd_print((const unsigned char *) "EDIT HOURS  ", LINE1(0));
        }
        else if (mode == 1)
        {
            clcd_print((const unsigned char *) "EDIT MINUTES", LINE1(0));
        }
        else if (mode == 2)
        {
            clcd_print((const unsigned char *) "EDIT SEC    ", LINE1(0));
        }
    }
}