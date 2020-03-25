// Needed since we cannot get 115.2k with 2% tolerance
#define BAUD_TOL 3

#define OLED_WIDTH 128
#define OLED_HEIGHT 8

#define OLED_SIZE (OLED_WIDTH*OLED_HEIGHT)

#include <avr/io.h>
#include <util/delay.h>
#include <util/crc16.h>

#include <math.h>
#include <stdio.h>

#include "twi.h"
#include "uart.h"

#include "gyro.h"
#include "oled.h"
#include "ui.h"

#define RAD_TO_DEG 57.2956695f
#define ACCEL_SCALE 16384.0f

// Calculate angles from accelerometer data
void calculate_angles(int16_t x, int16_t y, int16_t z, int8_t* out) {
    double dx = x / ACCEL_SCALE;
    double dy = y / ACCEL_SCALE;
    double dz = z / ACCEL_SCALE;

    out[0] = atan2(dx, sqrt(dy*dy + dz*dz)) * RAD_TO_DEG;
    out[1] = atan2(dy, sqrt(dx*dx + dz*dz)) * RAD_TO_DEG;
}

int main(void) {
    uint8_t screen_buff[OLED_SIZE] = {};

    TWI::initialize_master();
    Gyro::init(0x01);
    UART::init();
    OLED::init();

    _delay_ms(10);

    OLED::Configuration conf = {
        0xFF,   // Contrast
        true    // Charge pump
    };

    OLED::start(conf);
    _delay_ms(10);

    OLED::clear_display();

    uint8_t buff[6];
    int8_t angles[2];
    uint8_t crc;

    while (1)
    {
        Gyro::read_accel(buff);

        // Raw accel to angles in degrees
        calculate_angles(
                (buff[0] << 8) | buff[1],
                (buff[2] << 8) | buff[3],
                (buff[4] << 8) | buff[5],
                angles
        );

        // Calculate CRC
        crc = _crc_ibutton_update(0, angles[0]);
        crc = _crc_ibutton_update(crc, angles[1]);

        // Push angles to UART
        UART::_putchar((uint8_t) angles[0]);
        UART::_putchar((uint8_t) angles[1]);
        UART::_putchar(crc);

        // Draw UI
        UI::draw_header(screen_buff, angles[0], angles[1]);
        UI::clear_bubble_area(screen_buff);
        UI::draw_crosshair(screen_buff);
        UI::draw_bubble(screen_buff, angles[0], angles[1]);
        _delay_ms(40);
        OLED::write_buffer(screen_buff);
    }
}
