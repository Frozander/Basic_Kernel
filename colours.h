#ifndef __FROZ_COLOUR_H_
#define __FROZ_COLOUR_H_

#include <stdint.h>

extern uint8_t term_colour;

typedef enum __colour
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
} Colour;

#endif