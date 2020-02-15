#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "oled.h"

int main(void)
{
    OLED::init();
    _delay_ms(10);

    OLED::Configuration conf = {
        0xFF,   // Contrast
        true    // Charge pump
    };

    OLED::start(conf);
    _delay_ms(10);

    for(uint16_t i = 0; i < (4 * 128 /* 127*/); i++) {
        OLED::write_byte(0x00);
        OLED::write_byte(0x00);
    }

    // H
    OLED::write_byte(0b01111111);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b00001000);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b00001000);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b00001000);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01111111);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }

    // Sep
    for(uint8_t i = 0; i < 8; i++) { OLED::write_byte(0x00); }

    // E
    OLED::write_byte(0b01111111);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01001001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01001001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01000001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01000001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }

    // Sep
    for(uint8_t i = 0; i < 8; i++) { OLED::write_byte(0x00); }

    // L
    for(uint8_t x = 0; x < 2; x++) {
        OLED::write_byte(0b01111111);
        for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
        OLED::write_byte(0b01000000);
        for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
        OLED::write_byte(0b01000000);
        for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
        OLED::write_byte(0b01000000);
        for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
        OLED::write_byte(0b01000000);
        for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }

        // Sep
        for(uint8_t i = 0; i < 8; i++) { OLED::write_byte(0x00); }
    }

    // O
    OLED::write_byte(0b01111111);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01000001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01000001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01000001);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }
    OLED::write_byte(0b01111111);
    for(uint8_t i = 0; i < 7; i++) { OLED::write_byte(0x00); }

    while (1)
    {
    }
}
