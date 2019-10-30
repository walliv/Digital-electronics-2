/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */

uint8_t value = 0;
int main(void)
{
    
    //char lcd_string_hex[3];
    //char lcd_string_bin[9];
    char lcd_string_dec[4];

    /* LCD display
     * TODO: See Peter Fleury's online manual for LCD library 
     * http://homepage.hispeed.ch/peterfleury/avr-software.html
     * Initialize display and test different types of cursor */
    lcd_init(LCD_DISP_ON);

    // Display string without auto linefeed
    //lcd_puts("LCD testing");

    // TODO: Display variable value in decimal, binary, and hexadecimal

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    /* TODO: Design at least two user characters and store them in 
     *       the display memory */

     uint8_t customChar[16] = {
	0b00100,
	0b10101,
	0b01110,
	0b10101,
	0b01110,
	0b10101,
	0b00100,
	0b00000,
    0b00000,
	0b11111,
	0b10001,
	0b10101,
	0b11111,
	0b10101,
	0b10101,
	0b01110
};

    lcd_command(1 << LCD_CGRAM);
    int i;
    for(i = 0; i < 16; i++)
        lcd_data(customChar[i]);

/* lcd_clrscr();
lcd_puts("Counter:");
lcd_gotoxy(0,1);
lcd_putc('$');
lcd_gotoxy(6,1);
lcd_puts("0b");
lcd_gotoxy(13,0);
lcd_putc(0xff);
lcd_gotoxy(14,0);
lcd_putc(0x00);
lcd_gotoxy(15,0);
lcd_putc(0x01); */

lcd_clrscr();
lcd_puts("Value:");
lcd_gotoxy(14,0);
lcd_putc('%');


    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    for (;;) {

   /*  itoa(value ,lcd_string_hex , 16);
   itoa(value, lcd_string_bin, 2);
   itoa(value, lcd_string_dec, 10);

    lcd_gotoxy(9,0);
    lcd_puts(lcd_string_dec);
    lcd_gotoxy(1, 1);
    lcd_puts(lcd_string_hex);
    lcd_gotoxy(8, 1);
    lcd_puts(lcd_string_bin); */  
    itoa(value, lcd_string_dec, 10); 
    lcd_gotoxy(6,0);
    lcd_puts(lcd_string_dec);

    switch(value / 16)
    {
        case 0:
            lcd_gotoxy(0,1);
            lcd_putc(0xff);
            break;
        case 1:
            lcd_gotoxy(1,1);
            lcd_putc(0xff);
            break;
        case 2:
            lcd_gotoxy(2,1);
            lcd_putc(0xff);
            break;
        case 3:
            lcd_gotoxy(3,1);
            lcd_putc(0xff);
            break;
        case 4:
            lcd_gotoxy(4,1);
            lcd_putc(0xff);
            break;
        case 5:
            lcd_gotoxy(5,1);
            lcd_putc(0xff);
            break;
        case 6:
            lcd_gotoxy(6,1);
            lcd_putc(0xff);
            break;
        case 7:
            lcd_gotoxy(7,1);
            lcd_putc(0xff);
            break;
        case 8:
            lcd_gotoxy(8,1);
            lcd_putc(0xff);
            break;
        case 9:
            lcd_gotoxy(9,1);
            lcd_putc(0xff);
            break;
        case 10:
            lcd_gotoxy(10,1);
            lcd_putc(0xff);
            break;
        case 11:
            lcd_gotoxy(11,1);
            lcd_putc(0xff);
            break;
        case 12:
            lcd_gotoxy(12,1);
            lcd_putc(0xff);
            break;
        case 13:
            lcd_gotoxy(13,1);
            lcd_putc(0xff);
            break;
        case 14:
            lcd_gotoxy(14,1);
            lcd_putc(0xff);
            break;
        case 15:
            lcd_gotoxy(15,1);
            lcd_putc(0xff);
            break;
        
        default:
            break;
    }
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Increment counter value form 0 to 255
        value += 1;
}