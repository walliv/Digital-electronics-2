#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
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

 uint16_t horizontal = 0;
 uint16_t vertical = 0;
 uint8_t count = 0;
 char uart_string[4];
 char counter_string[4];
int main(void)
{

    GPIO_config_output(&DDRD, PD5);
    DDRC = 0;

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    GPIO_write(&ADCSRA,ADEN,1);
    GPIO_write(&ADMUX,REFS0,1);

    GPIO_write(&ADMUX,MUX0,0); 
    GPIO_write(&ADMUX,MUX1,0); 
    GPIO_write(&ADMUX,MUX2,0); 
    GPIO_write(&ADMUX,MUX3,0);

    GPIO_write(&ADCSRA,ADPS0,0);
    GPIO_write(&ADCSRA,ADPS1,1);
    GPIO_write(&ADCSRA,ADPS2,1);
    GPIO_write(&ADCSRA,ADIE,1);

    GPIO_write(&TCCR1A,WGM11,1);
    GPIO_write(&TCCR1B,WGM12,1);
    GPIO_write(&TCCR1B,WGM13,1);

    GPIO_write(&TCCR1A, COM1A1, 1);
    GPIO_write(&TCCR1A, COM1A0, 1);


    ICR1 = 20000;

    OCR1A = ICR1 - horizontal;

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop

    // Enables interrupts by setting the global interrupt mask
    sei();


    // Infinite loop
    for (;;) {
        
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

}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
	// Read 10-bit ACD value
    //value = ADC;
    // TODO: Update LCD and UART transmite
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