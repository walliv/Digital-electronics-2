#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "gpio.h"

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */

 uint16_t horizontal = 0;
 uint16_t vertical = 0;
 uint8_t count = 0;
 char uart_string[4];
 char counter_string[4];
int main(void)
{

    //Configer output pin for PWM regulation(otput pin OC1A)
    GPIO_config_output(&DDRD, PB1);

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
    //GPIO_write(&ADCSRA,ADIE,1);           //probably redundant

    //set ADC trigger on Timer0 overflow
    GPIO_write(&ADCSRB,ADTS0,0);
    GPIO_write(&ADCSRB,ADTS1,0);
    GPIO_write(&ADCSRB,ADTS2,1);


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
    GPIO_write(&TCCR1A, COM1A0,1);

    ICR1 = 39999;               //defines TOP of the TIM1, causes counter reset to BOTTOM

    sei();

    for (;;) {
        OCR1A = ICR1 - horizontal;              //updates on BOTTOM
    }

    return (0);
}

//interrupt triggers ADC conversion
ISR(TIMER0_OVF_vect)
{}

ISR(TIMER1_OVF_vect)            //overflow interrupt
{}

ISR(ADC_vect)       //conversion done interrupt
{
	// Read 10-bit ACD value
    switch (ADMUX)
    {
        case 0xC0:
            horizontal = ADC;
            ADC = 0;
            ADMUX = 0xC1;
            break;
        case 0xC1:
            vertical = ADC;
            ADC = 0;
            ADMUX = 0xC0;
            break;
        default:
            //Default code
            break;
    }
    
}