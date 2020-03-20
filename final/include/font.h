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

    constexpr uint8_t ARROW_LEFT[WIDTH] = {
        0b0001000,
        0b0011100,
        0b0101010,
        0b0001000,
        0b0001000,
    };

    constexpr uint8_t ARROW_DOWN[WIDTH] = {
        0b0010000,
        0b0100000,
        0b1111111,
        0b0100000,
        0b0010000,
    };

    constexpr uint8_t DEGREE[WIDTH] = {
        0b0000110,
        0b0001001,
        0b0001001,
        0b0000110,
        0b0000000,
    };

    constexpr uint8_t PLUS[WIDTH] = {
        0b0001000,
        0b0001000,
        0b0111110,
        0b0001000,
        0b0001000,
    };

    constexpr uint8_t MINUS[WIDTH] = {
        0b0001000,
        0b0001000,
        0b0001000,
        0b0001000,
        0b0001000,
    };

    constexpr uint8_t N_0[WIDTH] = {
        0b0111110,
        0b1010001,
        0b1001001,
        0b1000101,
        0b0111110,
    };

    constexpr uint8_t N_1[WIDTH] = {
        0b1000100,
        0b1000010,
        0b1111111,
        0b1000000,
        0b1000000,
    };

    constexpr uint8_t N_2[WIDTH] = {
        0b1000010,
        0b1100001,
        0b1010001,
        0b1001001,
        0b1000110,
    };

    constexpr uint8_t N_3[WIDTH] = {
        0b0000000,
        0b1000001,
        0b1001001,
        0b1001001,
        0b0111110,
    };

    constexpr uint8_t N_4[WIDTH] = {
        0b0001100,
        0b0001010,
        0b0001001,
        0b1111111,
        0b0001000,
    };

    constexpr uint8_t N_5[WIDTH] = {
        0b0000000,
        0b1001111,
        0b1001001,
        0b1001001,
        0b0110001,
    };

    constexpr uint8_t N_6[WIDTH] = {
        0b0000000,
        0b1111111,
        0b1001001,
        0b1001001,
        0b1111001,
    };

    constexpr uint8_t N_7[WIDTH] = {
        0b0000000,
        0b0000001,
        0b1100001,
        0b0011001,
        0b0000111,
    };

    constexpr uint8_t N_8[WIDTH] = {
        0b0000000,
        0b0110110,
        0b1001001,
        0b1001001,
        0b0110110,
    };

    constexpr uint8_t N_9[WIDTH] = {
        0b0000000,
        0b1001111,
        0b1001001,
        0b1001001,
        0b1111111,
    };

    constexpr uint8_t A[WIDTH] = {
        0b1111110,
        0b0001001,
        0b0001001,
        0b0001001,
        0b1111110,
    };
    constexpr uint8_t B[WIDTH] = {0, 0, 0, 0, 0}; // TODO
    constexpr uint8_t C[WIDTH] = {
        0b0111110,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1000001,
    };
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

    constexpr uint8_t F[WIDTH] = {
        0b1111111,
        0b0001001,
        0b0001001,
        0b0000001,
        0b0000001,
    };

    constexpr uint8_t G[WIDTH] = {
        0b1111111,
        0b1000001,
        0b1000001,
        0b1001001,
        0b1111001,
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

    constexpr uint8_t X[WIDTH] = {
        0b1100011,
        0b0010100,
        0b0001000,
        0b0010100,
        0b1100011,
    };

    constexpr uint8_t Y[WIDTH] = {
        0b0000011,
        0b0000100,
        0b1111000,
        0b0000100,
        0b0000011,
    };
}

#endif
