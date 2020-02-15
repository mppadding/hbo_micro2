#ifndef OLED_H_
#define OLED_H_

#include <avr/io.h>

#include "spi.h"

/***
 * Default pin config:
 * ┌───────┬─────┐
 * │ Reset │ PB0 │
 * ├───────┼─────┤
 * │ DataC │ PB1 │
 * ├───────┼─────┤
 * │ SS    │ PB2 │
 * └───────┴─────┘
 **/
#define OLED_RESET          PB0
#define OLED_RESET_DDR      DDRB
#define OLED_RESET_PORT     PORTB

#define OLED_DATACOM        PB1
#define OLED_DATACOM_DDR    DDRB
#define OLED_DATACOM_PORT   PORTB

#define OLED_SS             PB2
#define OLED_SS_DDR         DDRB
#define OLED_SS_PORT        PORTB

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <util/delay.h>

namespace OLED {

    namespace VCOMH_LEVELS {
        constexpr uint8_t VCC_065 = 0x00;
        constexpr uint8_t VCC_077 = 0x20;
        constexpr uint8_t VCC_083 = 0x30;
    }

    // Use base, then or with the wanted configuration
    namespace COM_HARDWARE {
        constexpr uint8_t BASE                      = 0x02;

        constexpr uint8_t SEQUENTIAL_COM_PIN        = 0x00;
        constexpr uint8_t ALTERNATIVE_COM_PIN       = 0x10;

        constexpr uint8_t DISABLE_LEFT_RIGHT_REMAP  = 0x00;
        constexpr uint8_t ENABLE_LEFT_RIGHT_REMAP   = 0x20;
    }

    namespace MEM_ADDRESS_MODES {
        constexpr uint8_t HORIZONTAL    = 0x00;
        constexpr uint8_t VERTICAL      = 0x01;
        constexpr uint8_t PAGE          = 0x02;
    }

    namespace Command {
        /***
         * Fundamental commands
         **/
        constexpr uint8_t CONTRAST_CONTROL  = 0x81;
        constexpr uint8_t DISPLAY_RAM       = 0xA4;
        constexpr uint8_t DISPLAY_FULL      = 0xA5;
        constexpr uint8_t NORMAL_DISPLAY    = 0xA6;
        constexpr uint8_t INVERSE_DISPLAY   = 0xA7;
        constexpr uint8_t DISPLAY_OFF       = 0xAE;
        constexpr uint8_t DISPLAY_ON        = 0xAF;

        /***
         * Scrolling commands
         * TODO: 0x29/0x2A
         **/
        constexpr uint8_t DEACTIVATE_SCROLL     = 0x2E;
        constexpr uint8_t ACTIVATE_SCROLL       = 0x2F;
        constexpr uint8_t VERTICAL_SCROLL_AREA  = 0xA3;

        /***
         * Addressing setting commands
         * TODO: 0x00 ~ 0x0F
         * TODO: 0x10 ~ 0x1F
         * TODO: 0xB0 ~ 0xB7
         **/
        constexpr uint8_t MEMORY_ADDRESS_MODE = 0x20;
        constexpr uint8_t COLUMN_ADDRESS = 0x21;
        constexpr uint8_t PAGE_ADDRESS = 0x22;

        /***
         * Hardware configuration commands
         **/
        constexpr uint8_t DISPLAY_START_LINE            = 0x40; // NOTE: B5-B0 is used to set the data, or with this command
        constexpr uint8_t SEGMENT_MAP_LOW               = 0xA0;
        constexpr uint8_t SEGMENT_MAP_HIGH              = 0xA1;
        constexpr uint8_t MULTIPLEX_RATIO               = 0xA8;
        constexpr uint8_t COM_SCAN_DIRECTION_NORMAL     = 0xC0;
        constexpr uint8_t COM_SCAN_DIRECTION_REVERSE    = 0xC8;
        constexpr uint8_t DISPLAY_OFFSET                = 0xD3;
        constexpr uint8_t COM_HARDWARE_CONFIGURATION    = 0xDA;

        /***
         * Timing & Driving scheme setting commands
         **/
        constexpr uint8_t DISPLAY_CLK_DIV_OSC_FREQ  = 0xD5;
        constexpr uint8_t PRE_CHARGE_PERIOD         = 0xD9;
        constexpr uint8_t VCOMH_DESELECT_LEVEL      = 0xDB;
        constexpr uint8_t NOP                       = 0xE3;

        /***
         * Charge pump commands
         **/
        constexpr uint8_t CHARGE_PUMP_SETTING   = 0x8D;
        constexpr uint8_t DISABLE_CHARGE_PUMP   = 0x10;
        constexpr uint8_t ENABLE_CHARGE_PUMP    = 0x14;

        //constexpr uint8_t <++> = 0x<++>;
    }

    struct Configuration {
        uint8_t contrast;
        bool charge_pump;
    };

    void dc_data() { OLED_DATACOM_PORT |= _BV(OLED_DATACOM); }
    void dc_command() { OLED_DATACOM_PORT &= ~(_BV(OLED_DATACOM)); }

    void select() { OLED_SS_PORT &= ~(_BV(OLED_SS)); }
    void deselect() { OLED_SS_PORT |= _BV(OLED_SS); }

    void reset() {
        OLED_RESET_PORT &= ~(_BV(OLED_RESET));
        _delay_us(4);
        OLED_RESET_PORT |= _BV(OLED_RESET);
    }

    void init() {
        // Enable Reset pin as output and write high (active-low)
        OLED_RESET_DDR |= _BV(OLED_RESET);
        OLED_RESET_PORT |= _BV(OLED_RESET);

        // Enable DataCom pin as output and write low
        OLED_DATACOM_DDR |= _BV(OLED_DATACOM);
        OLED_DATACOM_PORT &= ~(_BV(OLED_DATACOM));

        // Enable SS pin as output and write high (deselect)
        OLED_SS_DDR |= _BV(OLED_SS);
        OLED_SS_PORT |= _BV(OLED_SS);

        SPI::init();
    }

    // Starts the display, enabling default settings and such
    void start(Configuration& config) {
        select();

        dc_command();
        // Set display off
        SPI::transmit(Command::DISPLAY_OFF);

        // Use ram for display
        SPI::transmit(Command::DISPLAY_RAM);

        // Set display start line
        SPI::transmit(Command::DISPLAY_START_LINE | 0x00);
        SPI::transmit(Command::SEGMENT_MAP_HIGH);
        SPI::transmit(Command::DISPLAY_OFFSET);
        SPI::transmit(0x00);

        // Default direction is down to up, reverse it to up to down
        SPI::transmit(Command::COM_SCAN_DIRECTION_REVERSE);

        SPI::transmit(Command::PAGE_ADDRESS);
        SPI::transmit(0x00);
        SPI::transmit(0x07);

        SPI::transmit(Command::COLUMN_ADDRESS);
        SPI::transmit(0x00);
        SPI::transmit(0x7F);

        SPI::transmit(Command::MEMORY_ADDRESS_MODE);
        SPI::transmit(MEM_ADDRESS_MODES::VERTICAL);

        // Set contrast
        SPI::transmit(Command::CONTRAST_CONTROL);
        SPI::transmit(config.contrast);

        // Set charge pump
        SPI::transmit(Command::CHARGE_PUMP_SETTING);
        SPI::transmit(config.charge_pump ? Command::ENABLE_CHARGE_PUMP : Command::DISABLE_CHARGE_PUMP);

        // Set display on
        SPI::transmit(Command::DISPLAY_ON);

        deselect();
    }

    void set_page(uint8_t addr) {
        select();
        dc_command();
    }

    void set_contrast(uint8_t contrast) {
        select();

        dc_command();
        SPI::transmit(Command::CONTRAST_CONTROL);
        SPI::transmit(contrast);

        deselect();
    }

    void write_byte(uint8_t byte) {
        select();

        dc_data();
        SPI::transmit(byte);

        deselect();
    }
}

#endif
