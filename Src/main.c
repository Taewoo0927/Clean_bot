#include <msp430.h>
#include <stdint.h>
#include "Drivers/io.h"

#define IO_PORT(io) (((io) / 10) - 1)        // Extract Port number
#define IO_PIN_IDX(io) (((io) % 10))         // Extract Pin Index
#define IO_PIN_BIT(io) (1 << IO_PIN_IDX(io)) // Shift to compute Pin BIT

static volatile unsigned char *const PXDIR[2] = {&P1DIR, &P2DIR};
static volatile unsigned char *const PXOUT[2] = {&P1OUT, &P2OUT};

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // Test P1.0 (IO = 10)
    unsigned int io = 10;                  // Port 1, Pin 0
    unsigned int port = IO_PORT(io);       // Extract Port index
    unsigned int pin_bit = IO_PIN_BIT(io); // Extract Pin bitmask

    // Set P1.0 as output
    *PXDIR[port] |= pin_bit; // Set P1.0 as output

    while (1)
    {
        *PXOUT[port] ^= pin_bit; // Toggle P1.0
        // P1OUT |= 0X01;

        for (i = 10000; i > 0; i--)
            ;
    }
}
