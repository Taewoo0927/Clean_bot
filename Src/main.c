#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    volatile unsigned int i;
	WDTCTL = WDTPW | WDTHOLD;	                // stop watchdog timer
    P1DIR |= 0x01;                              // Set P1.0 to output direction

    while(1)
    {
        P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

        for (i=1000000; i>0; i--);
    }
}

