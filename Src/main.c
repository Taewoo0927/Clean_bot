#include <msp430.h>
#include "Drivers/system_init.h"
#include "Drivers/io.h"
#include "Others/others.h"

#define _1SECOND 1000

// Small test unit
static void test_setup(void)
{
    system_init();
}
static void test_blink_led(void)
{
    test_setup();
    io_out_e output_state = IO_PULL_STATE_LOW;
    while (1)
    {
        // Toggle output state
        output_state = (output_state == IO_PULL_STATE_LOW ? IO_PULL_STATE_HIGH : IO_PULL_STATE_LOW);
        io_set_output(IO_TEST_LED, output_state);
        _delay_ms(_1SECOND);
    }
}

int main(void)
{
    test_blink_led();
}
