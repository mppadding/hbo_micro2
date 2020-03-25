#ifndef GYRO_H_
#define GYRO_H_

#include <avr/io.h>
#include <util/delay.h>

#include "twi.h"
#include "logger.h"
#include "uart.h"

#define GYRO_BIAS_X 50
#define GYRO_BIAS_Y 0

namespace Gyro {
    constexpr uint8_t ADDR = 0xD0;

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

        constexpr uint8_t CONFIG = 0x1B;

        constexpr uint8_t RANGE_250     = 0x00;
        constexpr uint8_t RANGE_500     = 0x08;
        constexpr uint8_t RANGE_1000    = 0x10;
        constexpr uint8_t RANGE_2000    = 0x18;

        constexpr uint8_t GYRO_OFFSET_XH = 0x13;
        constexpr uint8_t GYRO_OFFSET_XL = 0x14;
        constexpr uint8_t GYRO_OFFSET_X = GYRO_OFFSET_XH;

        constexpr uint8_t GYRO_OFFSET_YH = 0x15;
        constexpr uint8_t GYRO_OFFSET_YL = 0x16;
        constexpr uint8_t GYRO_OFFSET_Y = GYRO_OFFSET_YH;

        constexpr uint8_t GYRO_OFFSET_ZH = 0x17;
        constexpr uint8_t GYRO_OFFSET_ZL = 0x18;
        constexpr uint8_t GYRO_OFFSET_Z = GYRO_OFFSET_ZH;
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

        constexpr uint8_t CONFIG = 0x1C;
    }

    namespace Temperature {
        constexpr uint8_t TEMP_H = 0x41;
        constexpr uint8_t TEMP_L = 0x42;

        // For reading 16 bit temp
        constexpr uint8_t TEMP_16 = TEMP_H;
    }

    namespace FIFO {
        constexpr uint8_t TEMP      = (1 << 7);
        constexpr uint8_t GYRO_X    = (1 << 6);
        constexpr uint8_t GYRO_Y    = (1 << 5);
        constexpr uint8_t GYRO_Z    = (1 << 4);
        constexpr uint8_t ACCEL     = (1 << 3);
        constexpr uint8_t SLAVE_2   = (1 << 2);
        constexpr uint8_t SLAVE_1   = (1 << 1);
        constexpr uint8_t SLAVE_0   = (1 << 0);

        constexpr uint8_t ENABLE    = 0x20;
    }

    namespace Interrupt {
        namespace Config {
            constexpr uint8_t REGISTER      = 0x37;

            constexpr uint8_t LEVEL         = (1 << 7);
            constexpr uint8_t OPEN          = (1 << 6);
            constexpr uint8_t LATCH         = (1 << 5);
            constexpr uint8_t READ_CLEAR    = (1 << 4);
            constexpr uint8_t FSYNC_LEVEL   = (1 << 3);
            constexpr uint8_t FSYNC_ENABLE  = (1 << 2);
            constexpr uint8_t BYPASS_ENABLE = (1 << 1);
        }

        namespace Enable {
            constexpr uint8_t REGISTER      = 0x38;

            constexpr uint8_t MOTION_ENABLE = (1 << 6);
            constexpr uint8_t FIFO_OVERFLOW = (1 << 4);
            constexpr uint8_t I2C_MASTER    = (1 << 3);
            constexpr uint8_t DATA_READY    = (1 << 0);
        }

        namespace Status {
            constexpr uint8_t REGISTER      = 0x3A;

            constexpr uint8_t MOTION        = (1 << 6);
            constexpr uint8_t FIFO_OVERFLOW = (1 << 4);
            constexpr uint8_t I2C_MASTER    = (1 << 3);
            constexpr uint8_t DATA_READY    = (1 << 0);
        }

    }

    namespace UserControl {
        constexpr uint8_t REGISTER                  = 0x6A;

        constexpr uint8_t FIFO_ENABLE               = (1 << 6);
        constexpr uint8_t I2C_MASTER_ENABLE         = (1 << 5);
        // I2C_IF_DIS removed due to always writing 0 to this register for this IC

        // Not in the datasheet, can be found here https://invensense.tdk.com/developers/software-downloads/
        // in MPU/eMD 6.12
        constexpr uint8_t DMP_RESET                 = (1 << 3);

        constexpr uint8_t FIFO_RESET                = (1 << 2);
        constexpr uint8_t I2C_MASTER_RESET          = (1 << 1);
        constexpr uint8_t SIGNAL_REGISTERS_RESET    = (1 << 0);
    }

    namespace PowerManagement {
        namespace R_1 {
            constexpr uint8_t REGISTER                  = 0x6B;

            constexpr uint8_t DEVICE_RESET              = (1 << 7);
            constexpr uint8_t SLEEP                     = (1 << 6);
            constexpr uint8_t CYCLE                     = (1 << 5);
            constexpr uint8_t TEMPERATURE_DISABLE       = (1 << 3);

            constexpr uint8_t CLK_INTERNAL_8MHZ         = 0x0;
            constexpr uint8_t CLK_PLL_GYRO_X            = 0x1;
            constexpr uint8_t CLK_PLL_GYRO_Y            = 0x2;
            constexpr uint8_t CLK_PLL_GYRO_Z            = 0x3;
            constexpr uint8_t CLK_PLL_EXTERNAL_32KHZ    = 0x4;
            constexpr uint8_t CLK_PLL_EXTERNAL_19MHZ    = 0x5;
            constexpr uint8_t CLK_STOP                  = 0x7;

        }

        namespace R_2 {
            constexpr uint8_t REGISTER = 0x6C;

            constexpr uint8_t LP_WAKE_FREQ_1HZ  = 0x00;
            constexpr uint8_t LP_WAKE_FREQ_5HZ  = 0x40;
            constexpr uint8_t LP_WAKE_FREQ_20HZ = 0x80;
            constexpr uint8_t LP_WAKE_FREQ_40HZ = 0xC0;

            constexpr uint8_t STANDBY_ACCEL_X   = (1 << 5);
            constexpr uint8_t STANDBY_ACCEL_Y   = (1 << 4);
            constexpr uint8_t STANDBY_ACCEL_Z   = (1 << 3);

            constexpr uint8_t STANDBY_GYRO_X    = (1 << 2);
            constexpr uint8_t STANDBY_GYRO_Y    = (1 << 1);
            constexpr uint8_t STANDBY_GYRO_Z    = (1 << 0);
        }
    }


    // TODO: Implement I2C Registers

    constexpr uint8_t SAMPLE_RATE_DIV   = 0x19;
    constexpr uint8_t CONFIG            = 0x1A; // TODO: Fix me
    constexpr uint8_t MOTION_THRESHOLD  = 0x1F;

    constexpr uint8_t BANK_SELECT = 0x6D;
    constexpr uint8_t MEMORY_READ_WRITE = 0x6F;
    constexpr uint8_t PROGRAM_START_H = 0x70;

    constexpr uint8_t FIFO_COUNT_H  = 0x72;
    constexpr uint8_t FIFO_COUNT_L  = 0x73;
    constexpr uint8_t FIFO_COUNT    = FIFO_COUNT_H;

    constexpr uint8_t FIFO_READ_WRITE = 0x74;
    constexpr uint8_t WHO_AM_I = 0x75;

    uint16_t read_gyro_x() {
        uint8_t buff[2] = {};
        TWI::read(ADDR, Gyroscope::GYRO_X16, 2, buff);

        return (buff[0] << 8) | buff[1];
    }

    uint16_t read_accel_x() {
        uint8_t buff[2] = {};
        TWI::read(ADDR, Accelerometer::ACCEL_X16, 2, buff);

        return (buff[0] << 8) | buff[1];
    }

    void read_accel(uint8_t* buff) {
        TWI::read(ADDR, Accelerometer::ACCEL_XH, 6, buff);
    }

    void set_biases() {
        // Read current config
        uint8_t config[1];
        TWI::read(ADDR, Gyroscope::CONFIG, 1, config);

        // Write new config: no self-test and sensitivity at 1000 Deg/s
        uint8_t new_config[2] = { Gyroscope::CONFIG, 0x16 };
        TWI::write_registers(ADDR, 2, new_config);

        // Read all axes
        uint8_t data[6];
        TWI::read(ADDR, Gyroscope::GYRO_XH, 6, data);

        // Write offsets
        TWI::write(ADDR, Gyroscope::GYRO_OFFSET_XH, 6, data);

        // Write previous config
        TWI::write(ADDR, Gyroscope::CONFIG, 1, config);
    }

    bool init(uint8_t power_1) {
        // Initial power on delay
        _delay_ms(150);

        uint8_t config[6] = {
            PowerManagement::R_1::REGISTER, power_1,
        };

        TWI::write_registers(ADDR, 2, config);

        return true;
    }

}

#endif
