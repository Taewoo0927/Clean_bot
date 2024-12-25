#include "Drivers/system_init.h"
#include <msp430.h>

static void stop_watchdog(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
}
void system_init(void)
{
    stop_watchdog();
}