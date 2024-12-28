#include "Test/test.h"
#include "Drivers/system_init.h"
#include "Drivers/io.h"
#include "Others/others.h"

// setting up the system
static void test_setup(void)
{
    system_init();
}

// Small blink test
void test_blink_led(void)
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

// Set all pins to output and test using logic analyzer
static const struct io_configuration_s io_test_output[IO_PIN_SIZE] = {
    [IO_TEST_LED] = IO_OUTPUT_TEST,
    [IO_UART_RXD] = IO_OUTPUT_TEST,
    [IO_UART_TXD] = IO_OUTPUT_TEST,
    [IO_UNUSED_1] = IO_OUTPUT_TEST,
    [IO_UNUSED_2] = IO_OUTPUT_TEST,
    [IO_UNUSED_3] = IO_OUTPUT_TEST,
    [IO_UNUSED_4] = IO_OUTPUT_TEST,
    [IO_UNUSED_5] = IO_OUTPUT_TEST,
    [IO_UNUSED_6] = IO_OUTPUT_TEST,
    [IO_UNUSED_7] = IO_OUTPUT_TEST,
    [IO_UNUSED_8] = IO_OUTPUT_TEST,
    [IO_UNUSED_9] = IO_OUTPUT_TEST,
    [IO_UNUSED_10] = IO_OUTPUT_TEST,
    [IO_UNUSED_11] = IO_OUTPUT_TEST,
    [IO_UNUSED_12] = IO_OUTPUT_TEST,
    [IO_UNUSED_13] = IO_OUTPUT_TEST

};

void test_io_output(void)
{
    test_setup();

    for (int portidx = 1; portidx < IO_PORT_SIZE; portidx++)
    {
        for (int pinidx = 0; pinidx < IO_PIN_CNT; pinidx++)
        {
            io_configuration((io_e)((IO_10 * portidx) + pinidx), &io_test_output[(portidx - 1) * IO_PIN_CNT + pinidx]);
        }
    }

    io_out_e output_state = IO_PULL_STATE_LOW;
    while (1)
    {
        for (int portidx = 1; portidx < IO_PORT_SIZE; portidx++)
        {
            for (int pinidx = 0; pinidx < IO_PIN_CNT; pinidx++)
            {
                io_set_output((io_e)((IO_10 * portidx) + pinidx), output_state);
                output_state = (output_state == IO_PULL_STATE_LOW ? IO_PULL_STATE_HIGH : IO_PULL_STATE_LOW);
                _delay_ms(_1SECOND);
                io_set_output((io_e)((IO_10 * portidx) + pinidx), output_state);
                output_state = (output_state == IO_PULL_STATE_LOW ? IO_PULL_STATE_HIGH : IO_PULL_STATE_LOW);
            }
        }
    }
}
