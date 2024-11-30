#include <msp430.h>
#include "Drivers/io.h"
#include <stdio.h>

#define IO_PORT_MASK 3u
#define IO_PORT_MASK (1u << 3u)

// For checking
/**
 * main.c
 */
int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= 0x01;            // Set P1.0 to output direction
    printf(IO_PORT_MASK);

    while (1)
    {
        P1OUT ^= 0x01; // Toggle P1.0 using exclusive-OR

        for (i = 10000; i > 0; i--)
            ;
    }
}
