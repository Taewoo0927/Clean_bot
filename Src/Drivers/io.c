#include <msp430.h>
#include "Drivers/io.h"

/* Creating mask to find port */
#define IO_PORT(io) ((io) / 10)               // Extract Port number
#define IO_PIN_IDX(io) (io % 10)              // Extract Pin Index
#define IO_PINT_BIT(io) (1 << IO_PIN_IDX(io)) // Shift to compute Pin BIT

// Create Look Up table for optimizing Port1 & Port2 select in switch statement
static volatile unsigned char *PXSEL1[2] = {&P1SEL, &P2SEL};
static volatile unsigned char *PXSEL2[2] = {&P1SEL2, &P2SEL2};

void io_set_sel(io_e io, io_sel_e sel)
{
    unsigned int port = IO_PORT(io);        // Extract Port number
    unsigned int pin_bit = IO_PINT_BIT(io); // Extract Pin Bit

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