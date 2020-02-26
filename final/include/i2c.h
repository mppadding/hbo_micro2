#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/twi.h>

#define I2C_READ  0x01
#define I2C_WRITE 0x00

namespace I2C {
    void init() {
        // Use 100 kHz SCL
        TWBR = 72;
    }

    uint8_t status() {
        return TWSR & 0xF8;
    }

    uint8_t write(uint8_t data) {
        TWDR = data;
        TWCR = _BV(TWINT) | _BV(TWEN);

        loop_until_bit_is_set(TWCR, TWINT);

        return status();
    }

    // Send start condition, returns status
    uint8_t start() {
        TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
        loop_until_bit_is_set(TWCR, TWINT);

        return status();
    }

    // Sends address
    uint8_t address(uint8_t addr, uint8_t method) {
        return write(addr | method);
    }

    // Read without sending ACK
    uint8_t read_nack() {
        TWCR = _BV(TWINT) | _BV(TWEN);
        loop_until_bit_is_set(TWCR, TWINT);

        return TWDR;
    }

    // Read with sending ACK
    uint8_t read_ack() {
        TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
        loop_until_bit_is_set(TWCR, TWINT);

        return TWDR;
    }

    // Send stop condition
    void stop() {
        TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
    }
}

#endif
