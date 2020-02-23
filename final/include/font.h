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

    constexpr uint8_t SPACE[WIDTH] = {0, 0, 0, 0, 0};

    constexpr uint8_t A[WIDTH] = {0, 0, 0, 0, 0}; // TODO
    constexpr uint8_t B[WIDTH] = {0, 0, 0, 0, 0}; // TODO
    constexpr uint8_t C[WIDTH] = {0, 0, 0, 0, 0}; // TODO
    constexpr uint8_t D[WIDTH] = {
        0b1111111,
        0b1000001,
        0b1000001,
        0b0100010,
        0b0011100,
    };
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
    constexpr uint8_t M[WIDTH] = {0, 0, 0, 0, 0}; // TODO
    constexpr uint8_t N[WIDTH] = {0, 0, 0, 0, 0}; // TODO

    constexpr uint8_t O[WIDTH] = {
        0b1111111,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1111111,
    };
    constexpr uint8_t P[WIDTH] = {0, 0, 0, 0, 0}; // TODO
    constexpr uint8_t Q[WIDTH] = {0, 0, 0, 0, 0}; // TODO

    constexpr uint8_t R[WIDTH] = {
        0b1111111,
        0b0001001,
        0b0011001,
        0b0101001,
        0b1000110,
    };

    constexpr uint8_t W[WIDTH] = {
        0b0111111,
        0b1000000,
        0b0111000,
        0b1000000,
        0b0111111,
    };
}

#endif