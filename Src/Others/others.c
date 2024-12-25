#include "Others/others.h"

#define DELAY_ITERATIONS_PER_MS 68

void _delay_ms(uint8_t miliseconds)
{
    uint8_t _1ms;
    while (miliseconds-- > 0)
    {
        _1ms = DELAY_ITERATIONS_PER_MS;
        while (_1ms-- > 0)
            ;
    }
}
