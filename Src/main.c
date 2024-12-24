#include <msp430.h>
#include "Drivers/io.h"

// For checking
/**
 * main.c
 */

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    io_set_sel(IO_TEST_LED, IO_SEL_GPIO);
    io_set_dir(IO_TEST_LED, IO_DIR_OP);

    io_out_e output = IO_PULL_STATE_LOW;

    while (1)
    {
        io_set_output(IO_TEST_LED, IO_PULL_STATE_LOW);

        for (i = 10000; i > 0; i--)
            ;
        io_set_output(IO_TEST_LED, IO_PULL_STATE_HIGH);
    }
}
