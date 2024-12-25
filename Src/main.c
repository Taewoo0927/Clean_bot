#include <msp430.h>
#include "Drivers/io.h"

#define DELAY_ITERATIONS_PER_MS 60
#define DELAY_MS 1

static void blink_led(void)
{
    unsigned int _1ms;

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

        unsigned int miliseconds = DELAY_MS;
        while (miliseconds-- > 0)
        {
            _1ms = DELAY_ITERATIONS_PER_MS;
            while (_1ms-- > 0)
                ;
        }
    }
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    blink_led();
}
