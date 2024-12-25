#include <msp430.h>
#include "Drivers/io.h"

// For checking
/**
 * main.c
 */
static void blink_led(void)
{
    volatile unsigned int i = 0;
    const struct io_configuration test_led = {
        .direction = IO_DIR_OP,
        .output = IO_PULL_STATE_LOW,
        .resistor = IO_RESISTOR_DISABLED,
        .select = IO_SEL_GPIO};

    io_configuration(IO_TEST_LED, &test_led);
    io_out_e output_state = IO_PULL_STATE_LOW;

    while (1)
    {
        // Toggle output state
        output_state = (output_state == IO_PULL_STATE_LOW ? IO_PULL_STATE_HIGH : IO_PULL_STATE_LOW);
        io_set_output(IO_TEST_LED, output_state);
        __delay_cycles(250000);
    }
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    blink_led();
}
