#ifndef MCP9800_H_
#define MCP9800_H_

#include <avr/io.h>

#include "i2c.h"

#include <util/twi.h>

namespace MCP9800 {

    namespace Register {
        constexpr uint8_t TEMPERATURE   = 0x00;
        constexpr uint8_t CONFIGURATION = 0x01;
        constexpr uint8_t HYSTERESIS    = 0x02;
        constexpr uint8_t LIMIT         = 0x03;
    }

    constexpr uint8_t ADDR = 0x92;

    void init() {
        I2C::init();
    }

    void _select_register(uint8_t reg) {
        I2C::start();
        I2C::address(ADDR, I2C_WRITE);
        I2C::write(reg);
        I2C::stop();
    }

    void write_config(uint8_t config) {
        // Write value to register
        I2C::start();
        I2C::address(ADDR, I2C_WRITE);
        I2C::write(Register::CONFIGURATION);
        I2C::write(config);
        I2C::stop();
    }

    uint8_t read_config() {
        _select_register(Register::CONFIGURATION);

        // Read value from register
        I2C::start();

        I2C::address(ADDR, I2C_READ);
        uint8_t res = I2C::read_nack();

        I2C::stop();

        return res;
    }

    int16_t get_temperature_raw() {
        _select_register(Register::TEMPERATURE);

        // Read value from register
        I2C::start();

        I2C::address(ADDR, I2C_READ);
        uint8_t msb = I2C::read_ack();
        uint8_t lsb = I2C::read_nack();

        I2C::stop();

        return (msb << 4) | (lsb >> 4);
    }

    float get_temperature() {
        int16_t raw = get_temperature_raw();

        return raw * 0.0625f;
    }
}

#endif
