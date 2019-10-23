/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include "segment.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_D1          PB5
#define BTN_S1          PC1 // PCINT 9
#define BTN_S2          PC2 // PCINT 10
#define BTN_S3          PC3 // PCINT 11

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */

 uint8_t c = 0;
 uint8_t p = 0;

int main(void)
{
    /* D1 led */
    // TODO: Configure D1 led at Multi-Function Shield
    GPIO_config_output(&DDRB, LED_D1);
    GPIO_write(&PORTB, LED_D1, 0);
    /* Pin Change Interrupts 11:9 */
    // TODO: Configure Pin Change Interrupts 11, 10, and 9
    PCICR |= _BV(PCIE1);

    PCMSK1 |= _BV(PCINT9) | _BV(PCINT10)| _BV(PCINT11);
    /* 7-segment display interface */
    // TODO: Configure 7-segment display pins
    GPIO_config_output(&DDRD, PD7);
    GPIO_config_output(&DDRD, PD4);
    GPIO_config_output(&DDRB, PB0);

    GPIO_write(&PORTD, PD4, 0);
    GPIO_write(&PORTD, PD7, 0);
    GPIO_write(&PORTB, PB0, 0);
    /* Enable interrupts by setting the global interrupt mask */

    TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    sei();

    /* Infinite loop */
    for (;;) {
        // TODO: Use function to display digit 1 at position 0
       
        SEG_putc(c, p);
    }

    return (0);
}

/**
 *  Brief: Pin Change Interrupt 11:9 routine. Toggle a LED.
 */ 

ISR(PCINT1_vect)
{
    GPIO_toggle(&PORTB, LED_D1);
}

ISR(TIMER0_OVF_vect)
{
    
}

ISR(TIMER1_OVF_vect)
{
    if(c < 9){c++;}
    else c = 0;
}


