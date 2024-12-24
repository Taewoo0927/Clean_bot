#include <msp430.h>
#include <stdint.h>
#include "Drivers/io.h"

#define IO_PORT(io) (((io) / 10))            // Extract Port number
#define IO_PIN_IDX(io) (((io) % 10))         // Extract Pin Index
#define IO_PIN_BIT(io) (1 << IO_PIN_IDX(io)) // Shift to compute Pin BIT

static volatile unsigned char *const PXDIR[2] = {&P1DIR, &P2DIR};
static volatile unsigned char *const PXOUT[2] = {&P1OUT, &P2OUT};

// For checking
/**
 * main.c
 */

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // Test P1.0 (IO = 10)
    unsigned int io = 10; // Port 1, Pin 0
    unsigned int port = 0;
    unsigned int pin_bit = 0;

    // Set P1.0 as output
    *PXDIR[port] |= pin_bit;

    while (1)
    {
        *PXOUT[port] ^= pin_bit;
        // P1OUT |= 0X01;

        for (i = 10000; i > 0; i--)
            ;
    }
}
