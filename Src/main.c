#include <msp430.h>
#include <stdint.h>
#include "Drivers/io.h"
#include "Others/others.h"

#define _1S 1000

static void blink_led(void)
{
    uint16_t _1sec = _1S;

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
        _delay_ms(_1sec);
    }
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    blink_led();
}
