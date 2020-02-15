#ifndef MCP3201_H_
#define MCP3201_H_

#include <avr/io.h>

#include "spi.h"

// Standard pins, can be overridden by defining MCP3201_SS_{DDR, PORT, PIN}
#ifndef MCP3201_SS_DDR
    #define MCP3201_SS_DDR  DDRB
#endif

#ifndef MCP3201_SS_PORT
    #define MCP3201_SS_PORT PORTB
#endif

#ifndef MCP3201_SS_PIN
    #define MCP3201_SS_PIN  PB2
#endif

namespace MCP3201 {
    void init() {
        SPI::init();

        // Enable SS pin as output and write high (deselect)
        MCP3201_SS_DDR |= _BV(MCP3201_SS_PIN);
        MCP3201_SS_PORT |= _BV(MCP3201_SS_PIN);
    }

    uint16_t get_data() {
        // Select chip
        MCP3201_SS_PORT &= ~_BV(MCP3201_SS_PIN);

        /***
         * Data gets clocked out by the MCP3201 MSB
         * Since most microcontrollers can only send in multiples of 8 bits the MCP3201 does not send the data as you would assume
         * The first transmit cycle the MCP3201 sends:
         *
         * ┌───┬───┬───┬─────┬─────┬────┬────┬────┐
         * │ ? │ ? │ 0 │ B11 │ B10 │ B9 │ B8 │ B7 │
         * └───┴───┴───┴─────┴─────┴────┴────┴────┘
         *
         * The second transmit cycle the MCP3201 sends:
         * ┌────┬────┬────┬────┬────┬────┬────┬────┐
         * │ B6 │ B5 │ B4 │ B3 │ B2 │ B1 │ B0 │ B1 │
         * └────┴────┴────┴────┴────┴────┴────┴────┘
         *
         * From here on should the SS stay low and more data clocked in the MCP3201 starts sending the same data, but LSB first
         **/
        uint8_t higher = SPI::transmit(0) & (0x1f);
        uint8_t lower = SPI::transmit(0) >> 1;

        // Combine higher and lower
        uint16_t result = (higher << 7) | lower;

        // Deselect chip
        MCP3201_SS_PORT |= _BV(MCP3201_SS_PIN);

        return result;
    }
}

#endif
