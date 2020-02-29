#ifndef GYRO_H_
#define GYRO_H_

#include <avr/io.h>

namespace Gyro {
    constexpr uint8_t ADDR = 0xD0;

    // Init: [0xD0 0x6B 0x00]
    //
    // Gyro X: [0xD0 0x43] [0xD1 rr]
    // Gyro Y: [0xD0 0x45] [0xD1 rr]
    // Gyro Z: [0xD0 0x47] [0xD1 rr]
    //
    // Accel X: [0xD0 0x3B] [0xD1 rr]
    // Accel Y: [0xD0 0x3D] [0xD1 rr]
    // Accel Z: [0xD0 0x3F] [0xD1 rr]
    //
    // Temp: [0xD0 0x41] [0xD1 rr]

    namespace Gyroscope {
        constexpr uint8_t GYRO_XH = 0x43;
        constexpr uint8_t GYRO_XL = 0x44;

        constexpr uint8_t GYRO_YH = 0x45;
        constexpr uint8_t GYRO_YL = 0x46;

        constexpr uint8_t GYRO_ZH = 0x47;
        constexpr uint8_t GYRO_ZL = 0x48;

        // 16 bit reading
        constexpr uint8_t GYRO_X16 = GYRO_XH;
        constexpr uint8_t GYRO_Y16 = GYRO_YH;
        constexpr uint8_t GYRO_Z16 = GYRO_ZH;
    }

    namespace Accelerometer {
        constexpr uint8_t ACCEL_XH = 0x3B;
        constexpr uint8_t ACCEL_XL = 0x3C;

        constexpr uint8_t ACCEL_YH = 0x3D;
        constexpr uint8_t ACCEL_YL = 0x3E;

        constexpr uint8_t ACCEL_ZH = 0x3F;
        constexpr uint8_t ACCEL_ZL = 0x40;

        // 16 bit reading
        constexpr uint8_t ACCEL_X16 = ACCEL_XH;
        constexpr uint8_t ACCEL_Y16 = ACCEL_YH;
        constexpr uint8_t ACCEL_Z16 = ACCEL_ZH;
    }

    namespace Temperature {
        constexpr uint8_t TEMP_H = 0x41;
        constexpr uint8_t TEMP_L = 0x42;

        // For reading 16 bit temp
        constexpr uint8_t TEMP_16 = TEMP_H;
    }

    void init() {
        
    }

}

#endif
