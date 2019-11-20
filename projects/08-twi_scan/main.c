/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2017-10-27
 * Last update: 2019-11-08
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Scan TWI bus for all connected slave devices and transmit info
 *    to UART.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"

/* Typedef -----------------------------------------------------------*/
typedef enum {
    IDLE_STATE = 1,
    TRY_STATE,
    WRITE_STATE,
    READ_START_STATE,
    READ_STATE,
    READ_LAST_STATE
} state_t;

/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
state_t current_state = IDLE_STATE;
/* Function prototypes -----------------------------------------------*/
void fsm_twi_scanner(void);
void fsm_twi_read_sensor(void);
/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Test all TWI slave addresses and scan 
 *          connected devices.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // TWI
    twi_init();

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART.
    uart_puts("\r\n---TWI scanner---");
//    uart_puts("\r\n     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Update state of TWI Finite
 *         State Machine.
 */
ISR(TIMER1_OVF_vect)
{
    //fsm_twi_scanner();
    fsm_twi_read_sensor();
}

/**
 *  Brief: Test one TWI address.
 */

void twi_read_sensor(void) {
    static uint8_t addr = 0x5c;
    static uint8_t reg_addr = 0x00;
    char uart_string[4];

    uint8_t H_i = 0, H_f = 0, T_i = 0, T_f = 0;
    
    twi_start((addr<<1) + TWI_WRITE);
    twi_write(reg_addr);
    twi_stop();

    twi_start((addr<<1) + TWI_READ);
    H_i = twi_read_ack();
    H_f = twi_read_ack();
    T_i = twi_read_ack();
    T_f = twi_read_nack();

    itoa(H_i, uart_string, 10);
    uart_puts(uart_string);
    uart_putc(',');

            
    itoa(H_f, uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\n\r");

    itoa(T_i, uart_string, 10);
    uart_puts(uart_string);
    uart_putc(',');
    itoa(T_f, uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\n\r");
}


void fsm_twi_read_sensor(void) {
    static uint8_t addr = 0x5c;
    static uint8_t reg_addr = 0x00;

    uint8_t data;
    uint8_t status;
    
    char uart_string[4];
    switch(current_state) {
        case IDLE_STATE:
            data = 0;
            current_state = TRY_STATE;
            break;
        case TRY_STATE:
            status = twi_start((addr<<1) + TWI_WRITE);
             if (status == 0) {
                current_state = WRITE_STATE;
            } else {
                current_state = IDLE_STATE;
            }
            break;
        case WRITE_STATE:
            twi_write(reg_addr);
            twi_stop();
            current_state = READ_START_STATE;
            break;
        case READ_START_STATE:
            status = twi_start((addr<<1) + TWI_READ);
            if(status == 0) {
                current_state = READ_STATE;
            }
            else {
                current_state = IDLE_STATE;
            }
        case READ_STATE:
            data = twi_read_ack();
            itoa(data, uart_string, 10);
            uart_puts(uart_string);
            current_state = READ_LAST_STATE;

           
            break;
        case READ_LAST_STATE:
            data = twi_read_nack();
            twi_stop();
            itoa(data, uart_string, 10);
            uart_putc(',');
            uart_puts(uart_string);
            uart_puts("\n\r");
            current_state = IDLE_STATE;
            break;
        default:
            current_state = IDLE_STATE;

    }

}