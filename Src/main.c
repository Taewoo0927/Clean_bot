#include <msp430.h>
#include "Drivers/io.h"

#define _1ms 1000
#define _number_of_ms 1

static void blink_led(void)
{
    volatile unsigned int ms = _1ms;
    volatile unsigned int loop_ms = _number_of_ms;

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

        for (loop_ms; loop_ms > 0; loop_ms--)
        {
            for (ms; ms > 0; ms--)
                ;
        }

        //__delay_cycles(250000); // 250 ms
    }
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    blink_led();
}
