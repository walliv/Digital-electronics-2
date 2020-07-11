/*
 * ---------------------------------------------------------------------
 * Author:      Vladislav Valek
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-09-26
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define UART_BAUD_RATE 9600

uint16_t buffer[64];

int main(void)
{
    //nastaveni portu uart
    DDRD |= _BV(PD1);
    DDRD &= ~(_BV(PD0));

    //ovladani slave, ve vychozim stavu je vypnuty
    DDRB |= _BV(PB0);
    PORTB &= ~(_BV(PB0));

    //inicializace uart
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));

    uart_puts("Velikost bufferu:");

    PORTB |= _BV(PB0);        //zapnuti periferie
    /*uart_putc(128);             //restartovani ukazatele datoveho registru

    for (int i = 0; i < 63; i++)
    {
      uart_putc(0x09);      //odresa datoveho registru
      buffer[i] = uart_getc();    //cteni obsahu registru
    }
    
    PORTB &= ~(_BV(PB0));       //vypnuti periferie
*/
    
  
    for (;;)
    {  
      uart_putc(0x0A);    //adresa registru s objemem dat
      _delay_ms(100);    
    }

    return (0);
}
