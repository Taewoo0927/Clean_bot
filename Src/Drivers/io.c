#include <msp430.h>
#include <stdint.h>
#include "Drivers/io.h"
#include "Others/others.h"

/* Creating mask to find port */
#define IO_PORT(io) (((io) / 10) - 1)        // Extract Port number, -1 is to account for lookup table 0 -> P1, 1 -> P2
#define IO_PIN_IDX(io) (((io) % 10))         // Extract Pin Index
#define IO_PIN_BIT(io) (1 << IO_PIN_IDX(io)) // Shift to compute Pin BIT
#define IO_PORT_SIZE 2
#define IO_PIN_SIZE 28 // port10 to port 27 total 28
#define UNUSED_PINS {IO_SEL_GPIO, IO_RESISTOR_ENABLED, IO_DIR_OP, IO_PULL_STATE_LOW}

// Create Look Up table for optimizing Port1 & Port2 select in switch statement
/* Register lookup */
static volatile uint8_t *const PXSEL1[IO_PORT_SIZE] = {&P1SEL, &P2SEL};
static volatile uint8_t *const PXSEL2[IO_PORT_SIZE] = {&P1SEL2, &P2SEL2};
static volatile uint8_t *const PXDIR[IO_PORT_SIZE] = {&P1DIR, &P2DIR};
static volatile uint8_t *const PXOUT[IO_PORT_SIZE] = {&P1OUT, &P2OUT};
static volatile uint8_t *const PXREG[IO_PORT_SIZE] = {&P1REN, &P2REN};
static volatile uint8_t *const PXIN[IO_PORT_SIZE] = {&P1IN, &P2IN};

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
void io_configuration(io_e io, const struct io_configuration *config)
{
    io_set_sel(io, config->select);
    io_set_dir(io, config->direction);
    io_set_resistor(io, config->resistor);
    io_set_output(io, config->output);
}

// Needs to be different for dev board and pcb
static const struct io_configuration io_default_init[IO_PIN_SIZE] = {
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

void io_init()
{
    for (int i = 0; i < ARRAY_SIZE(io_default_init); i++)
    {
        io_configuration((io_e)(IO_10 + i), &io_default_init[i]);
    }
}
