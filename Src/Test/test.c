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
/*
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
*/

/* Commenting out this function to save memory */
/*
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
}*/

/* Test single state for LED */
static void led_init(void)
{
    const struct io_configuration_s led_config = {
        .select = IO_SEL_GPIO,
        .resistor = IO_RESISTOR_DISABLED,
        .direction = IO_DIR_OP,
        .output = IO_PULL_STATE_LOW};
    io_configuration(IO_TEST_LED, &led_config);
}

static void set_led(void)
{
    io_out_e output_state = IO_PULL_STATE_HIGH;
    io_set_output(IO_TEST_LED, output_state);
}

static void clear_led(void)
{
    io_out_e output_state = IO_PULL_STATE_LOW;
    io_set_output(IO_TEST_LED, output_state);
}

/* Test ISR */
static void io_13_isr(void)
{
    clear_led();
    // set_led();
}
static void io_14_isr(void)
{
    // clear_led();
    set_led();
}
static void io_15_isr(void)
{
    // clear_led();
    set_led();
}
static void io_16_isr(void)
{
    // clear_led();
    set_led();
}
static void io_17_isr(void)
{
    // clear_led();
    set_led();
}
static void io_20_isr(void)
{
    set_led();
    // clear_led();
}

/* Test usage of the interrupt set up,
 * In this case it is falling edge so it will trigger when input reads low */

void test_io_interrupt(void)
{
    test_setup();
    const struct io_configuration_s io_interrupts_config = {
        .select = IO_SEL_GPIO,
        .resistor = IO_RESISTOR_ENABLED,
        .direction = IO_DIR_IP,
        .output = IO_PULL_STATE_HIGH};

    io_configuration(IO_13, &io_interrupts_config);
    io_configuration(IO_14, &io_interrupts_config);
    io_configuration(IO_15, &io_interrupts_config);
    io_configuration(IO_16, &io_interrupts_config);
    io_configuration(IO_17, &io_interrupts_config);

    io_configuration(IO_20, &io_interrupts_config);
    led_init();
    io_configure_interrupt(IO_13, IO_EDGE_FALLING, io_13_isr);
    io_configure_interrupt(IO_14, IO_EDGE_FALLING, io_14_isr);
    io_configure_interrupt(IO_15, IO_EDGE_FALLING, io_15_isr);
    io_configure_interrupt(IO_16, IO_EDGE_FALLING, io_16_isr);
    io_configure_interrupt(IO_17, IO_EDGE_FALLING, io_17_isr);

    io_configure_interrupt(IO_20, IO_EDGE_FALLING, io_20_isr);
    io_enable_interrupt(IO_13);

    io_enable_interrupt(IO_14);

    io_enable_interrupt(IO_15);

    io_enable_interrupt(IO_16);

    io_enable_interrupt(IO_17);

    io_enable_interrupt(IO_20);
    while (1)
        ;
}