#include "Drivers/io.h"

/* Creating mask to fine port */
#define IO_PORT_OFFSET (3u)
#define IO_PORT_MASK (0x3u << IO_PORT_OFFSET)

void io_set_sel(io_e io, io_sel_e sel)
{
    switch (sel)
    {
    case IO_SEL_GPIO:
        // Not decided yet
        break;
    }
}