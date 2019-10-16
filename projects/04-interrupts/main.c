/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
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
#include "gpio.h"
#include "timer.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_GREEN   PB5
#define LED_RED     PB0
#define LED_BLUE PB1
#define PIN_LOW 1

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
int main(void)
{
    /* LED_GREEN */
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write(&PORTB, LED_GREEN, PIN_LOW);
    /* LED_RED */
    GPIO_config_output(&DDRB, LED_RED);
    GPIO_write(&PORTB, LED_RED, PIN_LOW);
    // TODO: Configure red LED
    GPIO_config_output(&DDRB, LED_BLUE);
    GPIO_write(&PORTB, LED_BLUE, PIN_LOW);

    /* Set Timer0 */
    TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    /* Set Timer1 */
    // TODO: Configure Timer1 clock source and enable overflow interrupt
    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    /* Enable interrupts by setting the global interrupt mask */

    TIM_config_prescaler(TIM2, TIM_PRESC_128);
    TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);
    sei();

    /* Infinite loop */
    for (;;) {
    }

    return (0);
}

/**
 *  Brief: Timer/Counter0 overflow interrupt routine. Toggle green LED.
 */
ISR(TIMER0_OVF_vect)
{
    GPIO_toggle(&PORTB, LED_GREEN);
    
}

/**
 *  Brief: Timer/Counter1 overflow interrupt routine. Toggle red LED.
 */
ISR(TIMER1_OVF_vect)
{
    GPIO_toggle(&PORTB, LED_RED);
}

ISR(TIMER2_OVF_vect)
{
    GPIO_toggle(&PORTB, LED_BLUE);
}
