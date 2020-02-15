#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#define DDR_SPI DDRB
#define DD_MOSI PB3
#define DD_SCK PB5

namespace SPI {
    void init() {
        /* Set MOSI and SCK to output, others as input */
        DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);

        /* Enable SPI, make this device master and set clock to Fosc/128 (and mode 0,0) */
        SPCR = (1<<SPE)| (1<<MSTR) | (1<<SPR1) | (1<<SPR0);
    }

    uint8_t transmit(uint8_t data) {
        SPDR = data;

        loop_until_bit_is_set(SPSR, SPIF);

        return SPDR;
    }

    bool can_transmit() { return bit_is_set(SPSR, SPIF); }
}

#endif
