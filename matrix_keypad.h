#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H


	
#define MAX_ROW				4
#define MAX_COL				3

#define STATE_CHANGE				1
#define LEVEL_CHANGE				0
#define MATRIX_KEYPAD_PORT			PORTB
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1


#define MK_SW1					1
#define MK_SW2					2
#define MK_SW3					3
#define MK_SW4					4
#define MK_SW5					5
#define MK_SW6					6
#define MK_SW7					7
#define MK_SW8					8
#define MK_SW9					9
#define MK_SW10				10
#define MK_SW11				11
#define MK_SW12				12

#define ALL_RELEASED	0xFF

#define NO_EVENT         0

#define SW1_SHORT_PRESS  1
#define SW1_LONG_PRESS   2

#define SW2_SHORT_PRESS  3
#define SW2_LONG_PRESS   4

#define SW3_SHORT_PRESS  5
#define SW3_LONG_PRESS   6
#define SW4_SHORT_PRESS  7
#define SW4_LONG_PRESS   8
#define SW5_SHORT_PRESS  9
#define SW5_LONG_PRESS   10
#define SW6_SHORT_PRESS  11
#define SW6_LONG_PRESS   12
#define SW7_SHORT_PRESS  13
#define SW7_LONG_PRESS   14
#define SW8_SHORT_PRESS  15
#define SW8_LONG_PRESS   16

#define HI				1
#define LO				0

void init_matrix_keypad(void);
unsigned char scan_key(void);
unsigned char read_switches(unsigned char detection_type);
unsigned char long_press_and_short_press(void);

#endif
