#include <msp430.h>
#include "Drivers/io.h"

// For checking
/**
 * main.c
 */
static void blink_led(void)
{
    const struct io_configuration led_config =
        {
            .select = IO_SEL_GPIO,
            .direction = IO_DIR_OP,
            .resistor = IO_RESISTOR_DISABLED,
            .output = IO_PULL_STATE_LOW};
    io_configuration(IO_TEST_LED, &led_config);
    io_out_e op_state = IO_PULL_STATE_LOW;

    while (1)
    {
        // Toggle output state
        op_state = (op_state == IO_PULL_STATE_LOW) ? IO_PULL_STATE_HIGH : IO_PULL_STATE_LOW;
        // Set output of LED as out
        io_set_output(IO_TEST_LED, op_state);
        __delay_cycles(250000);
    }
}

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    blink_led();
    return 0;
}
