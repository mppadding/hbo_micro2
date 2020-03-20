#define CHECKSUM_FACTOR 69

#define BAUD_TOL 3

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "twi.h"
#include "uart.h"

#include "oled.h"
#include "gyro.h"
#include "font.h"
#include <stdio.h>

#define RAD_TO_DEG 57.2956695f
#define ACCEL_SCALE 16384.0f
#define OLED_SIZE 128*8
#define X_SCALE_FACTOR 0.622222f

uint8_t screen_buff[OLED_SIZE] = {};

void calculate_angles(int16_t x, int16_t y, int16_t z, int16_t* out) {
    double dx = x / ACCEL_SCALE;
    double dy = y / ACCEL_SCALE;
    double dz = z / ACCEL_SCALE;

    out[0] = atan2(dx, sqrt(dy*dy + dz*dz)) * RAD_TO_DEG;
    out[1] = atan2(dy, sqrt(dx*dx + dz*dz)) * RAD_TO_DEG;
}

void get_num(uint8_t num, uint8_t* buff) {
    switch(num) {
        case 0:
            memcpy(buff, Font::N_0, Font::WIDTH);
            break;
        case 1:
            memcpy(buff, Font::N_1, Font::WIDTH);
            break;
        case 2:
            memcpy(buff, Font::N_2, Font::WIDTH);
            break;
        case 3:
            memcpy(buff, Font::N_3, Font::WIDTH);
            break;
        case 4:
            memcpy(buff, Font::N_4, Font::WIDTH);
            break;
        case 5:
            memcpy(buff, Font::N_5, Font::WIDTH);
            break;
        case 6:
            memcpy(buff, Font::N_6, Font::WIDTH);
            break;
        case 7:
            memcpy(buff, Font::N_7, Font::WIDTH);
            break;
        case 8:
            memcpy(buff, Font::N_8, Font::WIDTH);
            break;
        default:
            memcpy(buff, Font::N_9, Font::WIDTH);
            break;
    }
}

void draw_num(int16_t num, uint8_t xpos, uint8_t ypos) {
    uint8_t num_char = 0;
    if(num < 0) {
        num = -num;
        memcpy(screen_buff + ypos*128 + xpos + Font::WIDTH*num_char + num_char, Font::MINUS, Font::WIDTH);
    } else {
        memcpy(screen_buff + ypos*128 + xpos + Font::WIDTH*num_char + num_char, Font::PLUS, Font::WIDTH);
    }
    num_char++;

    uint8_t tenfold = num / 10;
    uint8_t single = num % 10;

    uint8_t buf[Font::WIDTH];
    get_num(tenfold, buf);

    memcpy(screen_buff + ypos*128 + xpos + Font::WIDTH*num_char + num_char, buf, Font::WIDTH);
    num_char++;

    get_num(single, buf);
    memcpy(screen_buff + ypos*128 + xpos + Font::WIDTH*num_char + num_char, buf, Font::WIDTH);
}

void draw_header(int16_t x, int16_t y) {
    /***
     * Drawing Axes with arrows
     */
    uint8_t xpos = 8;
    memcpy(screen_buff + xpos, Font::X, Font::WIDTH);
    xpos += 5 + 1;

    memcpy(screen_buff + xpos, Font::ARROW_LEFT, Font::WIDTH);
    xpos += 5 + 3;

    memcpy(screen_buff + xpos, Font::Y, Font::WIDTH);
    xpos += 5 + 1;

    memcpy(screen_buff + xpos, Font::ARROW_DOWN, Font::WIDTH);

    /***
     * Drawing X with value in degrees
     */
    xpos = 54;
    memcpy(screen_buff + xpos, Font::X, Font::WIDTH);
    xpos += 5 + 1;
    draw_num(x, xpos, 0);
    xpos += 15 + 3;
    memcpy(screen_buff + xpos, Font::DEGREE, Font::WIDTH);

    /***
     * Drawing Y with value in degrees
     */
    xpos = 92;
    memcpy(screen_buff + xpos, Font::Y, Font::WIDTH);
    xpos += 5 + 1;
    draw_num(y, xpos, 0);
    xpos += 15 + 3;
    memcpy(screen_buff + xpos, Font::DEGREE, Font::WIDTH);
}

void draw_center() {
    screen_buff[3*128 + 63] |= 0b10000000;
    screen_buff[3*128 + 64] |= 0b10000000;

    screen_buff[4*128 + 63] |= 0b00000001;
    screen_buff[4*128 + 64] |= 0b00000001;
}

void clear_bubble_area() {
    memset(screen_buff + 128, 0x00, 128*6);
}

void draw_crosshair() {
    uint8_t xpos = 8;
    screen_buff[3*128 + xpos] |= 0b10000000;
    screen_buff[4*128 + xpos] |= 0b00000001;
    xpos += 3;

    for(uint8_t i = 0; i < 13; i++) {
        screen_buff[3*128 + xpos] |= 0b10000000;
        screen_buff[4*128 + xpos] |= 0b00000001;
        xpos += 4;
    }

    screen_buff[3*128 + xpos] |= 0b10000000;
    screen_buff[4*128 + xpos] |= 0b00000001;
    xpos++;

    for(uint8_t i = 0; i < 14; i++) {
        screen_buff[3*128 + xpos] |= 0b10000000;
        screen_buff[4*128 + xpos] |= 0b00000001;
        xpos += 4;
    }
    xpos--;
    screen_buff[3*128 + xpos] |= 0b10000000;
    screen_buff[4*128 + xpos] |= 0b00000001;

    xpos = 63;
    screen_buff[1*128 + xpos]       |= 0b10001001;
    screen_buff[1*128 + xpos + 1]   |= 0b10001001;
    screen_buff[2*128 + xpos]       |= 0b10001000;
    screen_buff[2*128 + xpos + 1]   |= 0b10001000;
    screen_buff[3*128 + xpos]       |= 0b10001000;
    screen_buff[3*128 + xpos + 1]   |= 0b10001000;

    screen_buff[4*128 + xpos]       |= 0b00010001;
    screen_buff[4*128 + xpos + 1]   |= 0b00010001;
    screen_buff[5*128 + xpos]       |= 0b00010001;
    screen_buff[5*128 + xpos + 1]   |= 0b00010001;
    screen_buff[6*128 + xpos]       |= 0b10010001;
    screen_buff[6*128 + xpos + 1]   |= 0b10010001;
}

void draw_bubble(int16_t x, int16_t y) {
    uint16_t bubble[] = {
        0b0000001111000000,
        0b0000010000100000,
        0b0000010000100000,
        0b0000010000100000,
        0b0000010000100000,
        0b0000001111000000,
    };

    uint8_t xpos = 61 + (x * X_SCALE_FACTOR);

    uint8_t ypos = 30;

    screen_buff[3*128 + xpos]       |= bubble[0] & 0xFF;
    screen_buff[3*128 + xpos + 1]   |= bubble[1] & 0xFF;
    screen_buff[3*128 + xpos + 2]   |= bubble[2] & 0xFF;
    screen_buff[3*128 + xpos + 3]   |= bubble[3] & 0xFF;
    screen_buff[3*128 + xpos + 4]   |= bubble[4] & 0xFF;
    screen_buff[3*128 + xpos + 5]   |= bubble[5] & 0xFF;

    screen_buff[4*128 + xpos]       |= bubble[0] >> 8;
    screen_buff[4*128 + xpos + 1]   |= bubble[1] >> 8;
    screen_buff[4*128 + xpos + 2]   |= bubble[2] >> 8;
    screen_buff[4*128 + xpos + 3]   |= bubble[3] >> 8;
    screen_buff[4*128 + xpos + 4]   |= bubble[4] >> 8;
    screen_buff[4*128 + xpos + 5]   |= bubble[5] >> 8;
}

int main(void)
{
    TWI::initialize_master();
    Gyro::init(0x01);
    UART::init();
    _delay_ms(100);
    OLED::init();

    _delay_ms(10);

    OLED::Configuration conf = {
        0xFF,   // Contrast
        true    // Charge pump
    };

    OLED::start(conf);
    _delay_ms(10);

    OLED::clear_display();

    /*for(uint8_t i = 0; i < Font::WIDTH; i++) { OLED::write_byte(Font::H[i]); }
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

    uint8_t buff[6];
    int16_t angles[2];

    //draw_header(0, 0);

    while (1)
    {
        Gyro::read_accel(buff);

        calculate_angles(
                (buff[0] << 8) | buff[1],
                (buff[2] << 8) | buff[3],
                (buff[4] << 8) | buff[5],
                angles
        );

        uint8_t num_char = 0;

        for(uint8_t i = 0; i < 2; i++) {
            int16_t ang = angles[i];

        }
        draw_header(angles[0], angles[1]);
        clear_bubble_area();
        draw_crosshair();
        draw_bubble(angles[0], angles[1]);
        _delay_ms(40);
        OLED::write_buffer(screen_buff);
    }
}
