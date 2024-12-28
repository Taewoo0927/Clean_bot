#ifndef OTHERS_H
#define OTHERS_H

#include <stdint.h>
/* Some useful functions that I'll be using on the main.c or anywhere else */

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

void _delay_ms(uint16_t miliseconds);

#endif // OTHERS_H
