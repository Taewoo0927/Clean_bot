#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include "Drivers/io.h"
#include "Others/others.h"

// Create Look Up table for optimizing Port1 & Port2 select in switch statement
/* Register lookup */
static volatile uint8_t *const PXSEL1[IO_PORT_SIZE] = {&P1SEL, &P2SEL};
static volatile uint8_t *const PXSEL2[IO_PORT_SIZE] = {&P1SEL2, &P2SEL2};
static volatile uint8_t *const PXDIR[IO_PORT_SIZE] = {&P1DIR, &P2DIR};
static volatile uint8_t *const PXOUT[IO_PORT_SIZE] = {&P1OUT, &P2OUT};
static volatile uint8_t *const PXREG[IO_PORT_SIZE] = {&P1REN, &P2REN};
static volatile uint8_t *const PXIN[IO_PORT_SIZE] = {&P1IN, &P2IN};

// Interrupt Registers -> Same for pcb since p1 and p2 is available only to interrupt
static volatile uint8_t *const PXIFG[IO_PORT_SIZE] = {&P1IFG, &P2IFG}; // Interrupt flag
static volatile uint8_t *const PXIE[IO_PORT_SIZE] = {&P1IE, &P2IE};    // Interrupt enable
static volatile uint8_t *const PXIES[IO_PORT_SIZE] = {&P1IES, &P2IES}; // Interrupt edge select

void io_set_sel(io_e io, io_sel_e sel)
{
    unsigned int port = IO_PORT(io);       // Extract Port number
    unsigned int pin_bit = IO_PIN_BIT(io); // Extract Pin Bit

    // Switch statement to set the sel register
    switch (sel)
    {
    case IO_SEL_GPIO:
        *PXSEL1[port] &= ~pin_bit;
        *PXSEL2[port] &= ~pin_bit;
        break;

    case IO_SEL_ALT1:
        *PXSEL1[port] |= pin_bit;
        *PXSEL2[port] &= ~pin_bit;
        break;

    case IO_SEL_ALT2:
        *PXSEL1[port] &= ~pin_bit;
        *PXSEL2[port] |= pin_bit;
        break;

    case IO_SEL_ALT3:
        *PXSEL1[port] |= pin_bit;
        *PXSEL2[port] |= pin_bit;
        break;
    }
}

void io_set_dir(io_e io, io_dir_e dir)
{
    unsigned int port = IO_PORT(io);
    unsigned int pin_bit = IO_PIN_BIT(io);

    // Switch statement to set the dir register
    switch (dir)
    {
    case IO_DIR_IP:
        *PXDIR[port] &= ~pin_bit;
        break;

    case IO_DIR_OP:
        *PXDIR[port] |= pin_bit;
        break;
    }
}

void io_set_output(io_e io, io_out_e out)
{
    unsigned int port = IO_PORT(io);
    unsigned int pin_bit = IO_PIN_BIT(io);

    // Switch statement to set the o/p register
    switch (out)
    {
    case IO_PULL_STATE_LOW:
        *PXOUT[port] &= ~pin_bit;
        break;

    case IO_PULL_STATE_HIGH:
        *PXOUT[port] |= pin_bit;
        break;
    }
}

void io_set_resistor(io_e io, io_resistor_e resistor)
{
    unsigned int port = IO_PORT(io);
    unsigned int pin_bit = IO_PIN_BIT(io);

    // Switch statement to set the resistor register
    switch (resistor)
    {
    case IO_RESISTOR_DISABLED:
        *PXREG[port] &= ~pin_bit;
        break;

    case IO_RESISTOR_ENABLED:
        *PXREG[port] |= pin_bit;
        break;
    }
}

io_input_state_e io_get_input(io_e io)
{
    return (*PXIN[IO_PORT(io)] & IO_PIN_BIT(io)) ? IO_INPUT_HIGH : IO_INPUT_LOW;
}

// Pass by reference but in const so we can save memory instead of copying structure
void io_configuration(io_e io, const struct io_configuration_s *config)
{
    io_set_sel(io, config->select);
    io_set_dir(io, config->direction);
    io_set_resistor(io, config->resistor);
    io_set_output(io, config->output);
}

// Needs to be different for dev board and pcb
static const struct io_configuration_s io_default_init[IO_PIN_SIZE] = {
    [IO_TEST_LED] = {IO_SEL_GPIO, IO_RESISTOR_DISABLED, IO_DIR_OP, IO_PULL_STATE_LOW},
    [IO_UART_RXD] = {IO_SEL_ALT3, IO_RESISTOR_DISABLED, IO_DIR_IP, IO_PULL_STATE_LOW},
    [IO_UART_TXD] = {IO_SEL_ALT3, IO_RESISTOR_DISABLED, IO_DIR_OP, IO_PULL_STATE_LOW},
    [IO_UNUSED_1] = UNUSED_PINS,
    [IO_UNUSED_2] = UNUSED_PINS,
    [IO_UNUSED_3] = UNUSED_PINS,
    [IO_UNUSED_4] = UNUSED_PINS,
    [IO_UNUSED_5] = UNUSED_PINS,
    [IO_UNUSED_6] = UNUSED_PINS,
    [IO_UNUSED_7] = UNUSED_PINS,
    [IO_UNUSED_8] = UNUSED_PINS,
    [IO_UNUSED_9] = UNUSED_PINS,
    [IO_UNUSED_10] = UNUSED_PINS,
    [IO_UNUSED_11] = UNUSED_PINS,
    [IO_UNUSED_12] = UNUSED_PINS,
    [IO_UNUSED_13] = UNUSED_PINS

};

// Can't find c99 error
void io_init()
{
    for (int portidx = 1; portidx < IO_PORT_SIZE; portidx++)
    {
        for (int pinidx = 0; pinidx < IO_PIN_CNT; pinidx++)
        {
            /*
                Being little bit creative here:
                io_default_init is structs of arrays which means to access it needs to be 0~15
                but when we pass io_e we want to pass IO_10 ~IO_27 which is 10~17 and 20~27

                ((IO_10 * portidx) + pinidx) <- it will check port and pinidx which will iterate 0~7 and add port 10 and 20
                [(portidx - 1) * IO_PIN_CNT + pinidx] <- "(portidx - 1) * IO_PIN_CNT" this part will give 0 in first loop and 8 in the second loop
                therefore adds up with pinidx 0~7 and then gives 8~15

            */
            io_configuration((io_e)((IO_10 * portidx) + pinidx), &io_default_init[(portidx - 1) * IO_PIN_CNT + pinidx]);
        }
    }
}

/*  Interrupt Functions */

/* Quick guides:
 * We will first configue interrupt per port-pin by "io_configure_interrupt"
 * Which will assign the isr to itself if it's not assigned and set edge
 * Now if interrupt is called it will check flag and isr to be called by io_isr
 */

// ISR vector table
// For individual port it can have total 8 isr since there is 8 pins so 2D array size is [2][8]
static isr_function isr_functions[IO_PORT_SIZE][IO_PIN_CNT] = {
    [IO_PORT1] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    [IO_PORT2] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
};

static void io_clear_interrupt_flag(io_e io)
{
    *PXIFG[IO_PORT(io)] &= ~IO_PIN_BIT(io);
}

void io_disable_interrupt(io_e io)
{
    *PXIE[IO_PORT(io)] &= ~IO_PIN_BIT(io);
}

void io_enable_interrupt(io_e io)
{
    *PXIE[IO_PORT(io)] |= IO_PIN_BIT(io);
}

static void io_set_interrupt_edge(io_e io, io_edge_e edge)
{
    const unsigned int port = IO_PORT(io);
    const unsigned int pin_bit = IO_PIN_BIT(io);

    // Turn off interrupt while setting the edge
    io_disable_interrupt(io);

    // Switch statement to set the resistor register
    switch (edge)
    {
    case IO_EDGE_RISING:
        *PXIES[port] &= ~pin_bit;
        break;
    case IO_EDGE_FALLING:
        *PXIES[port] |= pin_bit;
        break;
    }

    // Make sure to clear interrupt flage
    io_clear_interrupt_flag(io);
}

static void io_assign_isr(io_e io, isr_function isr)
{
    unsigned int port = IO_PORT(io);
    // Port is extracted as 1 or 2 but isr_functions uses 0 or 1
    unsigned int interrupt_port = port - 1;
    unsigned int pin_idx = IO_PIN_IDX(io);

    if (isr_functions[interrupt_port][pin_idx] == NULL)
    {
        isr_functions[interrupt_port][pin_idx] = isr;
    }
}

void io_configure_interrupt(io_e io, io_edge_e edge, isr_function isr)
{
    io_set_interrupt_edge(io, edge);
    io_assign_isr(io, isr);
}

// Call interrupt service routine
static void io_isr(io_e io)
{
    unsigned int port = IO_PORT(io);
    // Port is extracted as 1 or 2 but isr_functions uses 0 or 1
    unsigned int interrupt_port = port - 1;
    unsigned int pin_idx = IO_PIN_IDX(io);
    unsigned int pin_bit = IO_PIN_BIT(io);

    // Check if the interrupt flag pin is set
    if (*PXIFG[port] & pin_bit)
    {
        // Check isr table is not empty or not assigned
        if (isr_functions[interrupt_port][pin_idx] != NULL)
        {
            // Call ISR function
            isr_functions[interrupt_port][pin_idx]();
        }

        // Explicitly clear interrupt flag to come out from interrupt
        io_clear_interrupt_flag(io);
    }
}

void __attribute__((interrupt(PORT1_VECTOR))) isr_port1(void)
{
    // Check individual IO pins of PORT1 if there are any interrupt flagged
    for (io_generic_e io = IO_10; io <= IO_17; io++)
    {
        io_isr(io);
    }
}

void __attribute__((interrupt(PORT2_VECTOR))) isr_port2(void)
{
    // Check individual IO pins of PORT2 if there are any interrupt flagged
    for (io_generic_e io = IO_20; io <= IO_27; io++)
    {
        io_isr(io);
    }
}