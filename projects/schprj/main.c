/*
 * ---------------------------------------------------------------------
 * Author:      Vladislav Valek, Jakub Lokaj
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-11-27
 * Last update: 2019-12-11
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Controlling two servos with analog joystick using ADC value to set
 *     the PWM output. 
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "gpio.h"

uint16_t horizontal = 0;
uint16_t vertical = 0;
char uart_string[4];
char counter_string[4];

int main(void)
{
//Configer output pin for PWM regulation(otput pin OC1A)
    GPIO_config_output(&DDRB, PB1);
    GPIO_config_output(&DDRB, PB2);

    //Set pins PC0, PC1 as ADC inputs
    DDRC &= ~(_BV(PC0) | _BV(PC1));
    
    //enable ADC
    GPIO_write(&ADCSRA,ADEN,1);
    
    //set refference voltage to 5V
    GPIO_write(&ADMUX,REFS0,1);

    //set input channel to ADC0(pin PC0)
    ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
    
    //set ADC prescaler as 64
    GPIO_write(&ADCSRA,ADPS0,0);
    GPIO_write(&ADCSRA,ADPS1,1);
    GPIO_write(&ADCSRA,ADPS2,1);

    //enable ADC interrupt
    GPIO_write(&ADCSRA,ADIE,1);           //probably redundant

    //set Timer0 prescaler and interrupt (controls ADC)
    TIM_config_prescaler(TIM0, TIM_PRESC_64);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    //set Timer1 prescaler and interrupt (controls PWM)
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    //configure Timer1 for Fast PWM operation (WGM13:0 = 14)
    GPIO_write(&TCCR1A,WGM11,1);    
    GPIO_write(&TCCR1B,WGM12,1);
    GPIO_write(&TCCR1B,WGM13,1);

    //defines mode when OC1A pin is enabled on compare match and clears when BOTTOM
    GPIO_write(&TCCR1A, COM1A1,1);
    GPIO_write(&TCCR1A, COM1A0,0);

    GPIO_write(&TCCR1A, COM1B1,1);
    GPIO_write(&TCCR1A, COM1B0,0);

    ICR1 = 39999;               //defines TOP of the TIM1, causes counter reset to BOTTOM

    sei();

    for (;;) {

        OCR1A = 1500 + (horizontal * 3.71);
        OCR1B = 1500 + (vertical * 3.71);
    }

    return (0);
}

//interrupt triggers ADC conversion
ISR(TIMER0_OVF_vect)
{
   GPIO_write(&ADCSRA,ADSC,1);
}

ISR(TIMER1_OVF_vect)            //overflow interrupt
{}

ISR(ADC_vect)       //conversion done interrupt
{
    switch (ADMUX)
    {
        case 0x40:
            horizontal = ADC;
            ADMUX = 0x41;
            break;
        case 0x41:
            vertical = ADC;
            ADMUX = 0x40;
            break;
        default:
            break;
    }
    ADC = 0;
}
