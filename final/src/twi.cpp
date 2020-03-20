/**
 * TWI library.
 *  Author:     Matthijs Padding
 *  Date:       20/03/2020
 *  Version:    v1.0.2
 */
#include "twi.h"

namespace TWI {
    // Anonymous namespace to hide helper methods
    namespace {
        /**
         * @brief   Sends TWI start condition
         *
         * @details Sends TWI start condition, enables TWI and then waits until TWI is finished.
         *
         * @note    Blocking method until TWI finishes
         */
        void start() {
            // TWINT - Clears TWINT flag, initiates TWI
            // TWSTA - Sends TWI start condition
            // TWEN  - Enable TWI
            TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);

            // Wait until hardware sets TWINT flag (indicates TWI finished)
            loop_until_bit_is_set(TWCR, TWINT);
        }

        /**
         * @brief   Sends TWI stop condition
         *
         * @details Sends TWI stop condition, enables TWI
         *
         * @note    Not-blocking
         */
        void stop() {
            // TWINT - Clears TWINT flag, initiates TWI
            // TWSTO - Sends TWI stop condition
            // TWEN  - Enable TWI
            TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
        }

        /**
         * @brief   Writes single byte to TWI
         *
         * @note    Blocking until transaction is complete
         */
        void write_byte(uint8_t byte) {
            // Write byte and enable TWI
            TWDR = byte;
            TWCR = _BV(TWINT) | _BV(TWEN);

            // Block until transaction is complete
            loop_until_bit_is_set(TWCR, TWINT);
        }

        /**
         * @brief   Writes slave address with correct method to TWI
         *
         * @note    Blocking until transaction is complete
         */
        void address(uint8_t address, uint8_t method) {
            write_byte(address | method);
        }

        /**
         * @brief   Reads a single byte from TWI and responds with ACK
         *
         * @note    Blocking until transaction is complete
         *
         * @return  Byte received from slave
         *
         * @retval  uint8_t     Unsigned 8 bit integer
         */
        uint8_t read_ack() {
            // Enable TWI and send ACK
            TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);

            // Wait until transaction is complete
            loop_until_bit_is_set(TWCR, TWINT);

            return TWDR;
        }

        /**
         * @brief   Reads a single byte from TWI and responds with NACK
         *
         * @note    Blocking until transaction is complete
         *
         * @return  Byte received from slave
         *
         * @retval  uint8_t     Unsigned 8 bit integer
         */
        uint8_t read_nack() {
            // Enable TWI
            TWCR = _BV(TWINT) | _BV(TWEN);

            // Wait until transaction is complete
            loop_until_bit_is_set(TWCR, TWINT);

            return TWDR;
        }
    }

    void initialize_master() { TWBR = TWBR_VALUE; }
    void initialize_slave(const uint8_t address) {
        TWAR = address;
        TWCR = _BV(TWEA) | _BV(TWEN); // Enable TWI slave acknowledge and enable TWI
    }
    uint8_t status() { return TW_STATUS; }

    void write(const uint8_t addr, const uint8_t reg, const uint8_t length, const uint8_t* buffer) {
        // Send TWI start and selects slave, write register
        start();
        address(addr, TW_WRITE);
        write_byte(reg);

        // Write bytes to slave
        for(uint8_t i = 0; i < length; i++) {
            write_byte(buffer[i]);
        }

        // Sends TWI stop
        stop();
    }

    void write_registers(const uint8_t addr, const uint8_t length, const uint8_t* buffer) {
        for(uint8_t i = 0; i < length; i+=2) {
            // Start TWI and send address
            start();
            address(addr, TW_WRITE);

            // Write register and write data
            write_byte(buffer[i]);
            write_byte(buffer[i+1]);

            // Stop TWI
            stop();
        }
    }

    void read(const uint8_t addr, const uint8_t reg, const uint8_t length, uint8_t* buffer) {
        // Send TWI start and select slave, write register
        start();
        address(addr, TW_WRITE);
        write_byte(reg);

        // Send TWI start and select slave
        start();
        address(addr, TW_READ);

        // Read bytes from slave
        for(uint8_t i = 0; i < length - 1; i++) {
            buffer[i] = read_ack();
        }

        // Last read is always responded with NACK
        buffer[length - 1] = read_nack();

        // Send TWI stop
        stop();
    }
}

