#include "Others/others.h"

#define DELAY_ITERATIONS_PER_MS 72

void _delay_ms(uint16_t miliseconds)
{
    while (miliseconds-- > 0)
    {
        uint8_t _1ms = DELAY_ITERATIONS_PER_MS;
        while (_1ms-- > 0)
            ;
    }
}
