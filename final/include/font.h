/***
 * Default display font
 **/
#ifndef FONT_H_
#define FONT_H_

#include <stdint.h>

/***
 * NOTE: This font assumes horizontal layout
 **/
namespace Font {
    constexpr uint8_t WIDTH = 5;
    constexpr uint8_t SEPARATOR = 0x00;

    constexpr uint8_t E[WIDTH] = {
        0b1111111,
        0b1001001,
        0b1001001,
        0b1000001,
        0b1000001,
    };

    constexpr uint8_t H[WIDTH] = {
        0b1111111,
        0b0001000,
        0b0001000,
        0b0001000,
        0b1111111,
    };

    constexpr uint8_t L[WIDTH] = {
        0b1111111,
        0b1000000,
        0b1000000,
        0b1000000,
        0b1000000,
    };

    constexpr uint8_t O[WIDTH] = {
        0b1111111,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1111111,
    };
}

#endif
