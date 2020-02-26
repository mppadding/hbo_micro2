#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "oled.h"
#include "font.h"

int main(void)
{
    /* OLED::init();
    _delay_ms(10);

    OLED::Configuration conf = {
        0xFF,   // Contrast
        true    // Charge pump
    };

    OLED::start(conf);
    _delay_ms(10);

    OLED::clear_display();

    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::H[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::E[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::L[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::L[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::O[i]); }
    OLED::write_byte(Font::SEPARATOR);

    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::SPACE[i]); }
    OLED::write_byte(Font::SEPARATOR);

    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::W[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::O[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::R[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::L[i]); }
    OLED::write_byte(Font::SEPARATOR);
    for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::D[i]); }
    OLED::write_byte(Font::SEPARATOR);

    OLED::set_horizontal_scroll(false, OLED::PAGE::PAGE0, OLED::PAGE::PAGE7, OLED::SCROLL_INTERVAL::FRAMES_4);
    OLED::enable_scrolling(); */

    while (1)
    {
    }
}
