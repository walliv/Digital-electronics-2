/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include "gpio.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */

 uint16_t value = 0;
 uint8_t count = 0;
 char uart_string[4];
 char counter_string[4];
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_puts("LCD testing");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    GPIO_write(&ADCSRA,ADEN,1);
    GPIO_write(&ADMUX,REFS0,1);

    GPIO_write(&ADMUX,MUX0,0); 
    GPIO_write(&ADMUX,MUX1,0); 
    GPIO_write(&ADMUX,MUX2,0); 
    GPIO_write(&ADMUX,MUX3,0);

    GPIO_write(&ADCSRA,ADPS0,1);
    GPIO_write(&ADCSRA,ADPS1,1);
    GPIO_write(&ADCSRA,ADPS2,1);
    GPIO_write(&ADCSRA,ADIE,1);

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n ");

    uint8_t c;
    // Infinite loop
    for (;;) {
        c = uart_getc();
        if(c != '\0'){
            if( c == '1'){
                uart_puts(uart_string);
                uart_puts("\r\n");
                c = 0;
            }
            else if(c == '2'){
                itoa(count,counter_string, 10);
                uart_puts(counter_string);
                uart_puts("\r\n");
                c = 0;
            } else if(c == '3'){
                TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
                c = 0;
            } else if(c == '4'){
                TCCR1B |= (0 << CS12)|(1 << CS11)|(1 << CS10);
                c = 0;
            }
        }

    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    count += 1;
    // TODO: Start ADC conversion
    GPIO_write(&ADCSRA,ADSC,1);
    //GPIO_toggle(&ADCSRA,ADSC);

}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    lcd_clrscr();
	// Read 10-bit ACD value
    value = ADC;
    // TODO: Update LCD and UART transmite
     itoa(value ,uart_string , 10);
    lcd_puts(uart_string);
}