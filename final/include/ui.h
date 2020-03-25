#ifndef _UI_H
#define _UI_H

#include <string.h>

#include "font.h"

// Scale factor from angle to pixel
#define X_SCALE_FACTOR 0.622222f
#define Y_SCALE_FACTOR 0.266666f

namespace UI {

    void num_to_font(uint8_t num, uint8_t* buff) {
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

    void draw_num(uint8_t* buffer, int8_t num, uint8_t xpos, uint8_t ypos) {
        uint8_t num_char = 0;
        if(num < 0) {
            num = -num;
            memcpy(buffer + ypos*OLED_WIDTH + xpos + Font::WIDTH*num_char + num_char, Font::MINUS, Font::WIDTH);
        } else {
            memcpy(buffer + ypos*OLED_WIDTH + xpos + Font::WIDTH*num_char + num_char, Font::PLUS, Font::WIDTH);
        }
        num_char++;

        uint8_t tenfold = num / 10;
        uint8_t single = num % 10;

        uint8_t buf[Font::WIDTH];
        num_to_font(tenfold, buf);

        memcpy(buffer + ypos*OLED_WIDTH + xpos + Font::WIDTH*num_char + num_char, buf, Font::WIDTH);
        num_char++;

        num_to_font(single, buf);
        memcpy(buffer + ypos*OLED_WIDTH + xpos + Font::WIDTH*num_char + num_char, buf, Font::WIDTH);
    }

    void draw_header(uint8_t* buffer, int8_t x, int8_t y) {
        /***
         * Drawing Axes with arrows
         */
        uint8_t xpos = 8;
        memcpy(buffer + xpos, Font::X, Font::WIDTH);
        xpos += 5 + 1;

        memcpy(buffer + xpos, Font::ARROW_LEFT, Font::WIDTH);
        xpos += 5 + 3;

        memcpy(buffer + xpos, Font::Y, Font::WIDTH);
        xpos += 5 + 1;

        memcpy(buffer + xpos, Font::ARROW_DOWN, Font::WIDTH);

        /***
         * Drawing X with value in degrees
         */
        xpos = 54;
        memcpy(buffer + xpos, Font::X, Font::WIDTH);
        xpos += 5 + 1;
        draw_num(buffer, x, xpos, 0);
        xpos += 15 + 3;
        memcpy(buffer + xpos, Font::DEGREE, Font::WIDTH);

        /***
         * Drawing Y with value in degrees
         */
        xpos = 92;
        memcpy(buffer + xpos, Font::Y, Font::WIDTH);
        xpos += 5 + 1;
        draw_num(buffer, y, xpos, 0);
        xpos += 15 + 3;
        memcpy(buffer + xpos, Font::DEGREE, Font::WIDTH);
    }

    void draw_center(uint8_t* buffer) {
        buffer[3*OLED_WIDTH + 63] |= 0b10000000;
        buffer[3*OLED_WIDTH + 64] |= 0b10000000;

        buffer[4*OLED_WIDTH + 63] |= 0b00000001;
        buffer[4*OLED_WIDTH + 64] |= 0b00000001;
    }

    void clear_bubble_area(uint8_t* buffer) {
        memset(buffer + OLED_WIDTH, 0x00, OLED_WIDTH*6);
    }

    void draw_crosshair(uint8_t* buffer) {
        uint8_t xpos = 8;
        buffer[3*OLED_WIDTH + xpos] |= 0b10000000;
        buffer[4*OLED_WIDTH + xpos] |= 0b00000001;
        xpos += 3;

        for(uint8_t i = 0; i < 13; i++) {
            buffer[3*OLED_WIDTH + xpos] |= 0b10000000;
            buffer[4*OLED_WIDTH + xpos] |= 0b00000001;
            xpos += 4;
        }

        buffer[3*OLED_WIDTH + xpos] |= 0b10000000;
        buffer[4*OLED_WIDTH + xpos] |= 0b00000001;
        xpos++;

        for(uint8_t i = 0; i < 14; i++) {
            buffer[3*OLED_WIDTH + xpos] |= 0b10000000;
            buffer[4*OLED_WIDTH + xpos] |= 0b00000001;
            xpos += 4;
        }
        xpos--;
        buffer[3*OLED_WIDTH + xpos] |= 0b10000000;
        buffer[4*OLED_WIDTH + xpos] |= 0b00000001;

        xpos = 63;
        buffer[1*OLED_WIDTH + xpos]       |= 0b10001001;
        buffer[1*OLED_WIDTH + xpos + 1]   |= 0b10001001;
        buffer[2*OLED_WIDTH + xpos]       |= 0b10001000;
        buffer[2*OLED_WIDTH + xpos + 1]   |= 0b10001000;
        buffer[3*OLED_WIDTH + xpos]       |= 0b10001000;
        buffer[3*OLED_WIDTH + xpos + 1]   |= 0b10001000;

        buffer[4*OLED_WIDTH + xpos]       |= 0b00010001;
        buffer[4*OLED_WIDTH + xpos + 1]   |= 0b00010001;
        buffer[5*OLED_WIDTH + xpos]       |= 0b00010001;
        buffer[5*OLED_WIDTH + xpos + 1]   |= 0b00010001;
        buffer[6*OLED_WIDTH + xpos]       |= 0b10010001;
        buffer[6*OLED_WIDTH + xpos + 1]   |= 0b10010001;
    }

    void draw_bubble(uint8_t* buffer, int8_t x, int8_t y) {
        uint16_t bubble[] = {
            0b0000000000011110,
            0b0000000000100001,
            0b0000000000100001,
            0b0000000000100001,
            0b0000000000100001,
            0b0000000000011110,
        };

        uint8_t xpos = 61 + (x * X_SCALE_FACTOR);
        uint8_t ypos = 29 - (y * Y_SCALE_FACTOR);

        uint8_t shift = ypos % OLED_HEIGHT;
        ypos /= OLED_HEIGHT;

        bubble[0] <<= shift;
        bubble[1] <<= shift;
        bubble[2] <<= shift;
        bubble[3] <<= shift;
        bubble[4] <<= shift;
        bubble[5] <<= shift;

        buffer[ypos*OLED_WIDTH + xpos]       |= bubble[0] & 0xFF;
        buffer[ypos*OLED_WIDTH + xpos + 1]   |= bubble[1] & 0xFF;
        buffer[ypos*OLED_WIDTH + xpos + 2]   |= bubble[2] & 0xFF;
        buffer[ypos*OLED_WIDTH + xpos + 3]   |= bubble[3] & 0xFF;
        buffer[ypos*OLED_WIDTH + xpos + 4]   |= bubble[4] & 0xFF;
        buffer[ypos*OLED_WIDTH + xpos + 5]   |= bubble[5] & 0xFF;

        buffer[(ypos + 1)*OLED_WIDTH + xpos]       |= bubble[0] >> 8;
        buffer[(ypos + 1)*OLED_WIDTH + xpos + 1]   |= bubble[1] >> 8;
        buffer[(ypos + 1)*OLED_WIDTH + xpos + 2]   |= bubble[2] >> 8;
        buffer[(ypos + 1)*OLED_WIDTH + xpos + 3]   |= bubble[3] >> 8;
        buffer[(ypos + 1)*OLED_WIDTH + xpos + 4]   |= bubble[4] >> 8;
        buffer[(ypos + 1)*OLED_WIDTH + xpos + 5]   |= bubble[5] >> 8;
    }
}

#endif
