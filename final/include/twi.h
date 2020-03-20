/**
 * TWI library.
 *  Author:     Matthijs Padding
 *  Date:       20/03/2020
 *  Version:    v1.0.2
 */
#ifndef _LIB_TWI_H
#define _LIB_TWI_H

#include <util/twi.h>

#ifndef F_CPU
    #error "F_CPU not defined"
#endif

#ifndef F_TWI
    #error "F_TWI not defined"
#endif

#define TWBR_VALUE (((F_CPU / F_TWI) - 15) / 2)

namespace TWI {

    /**
     * @brief Initializes TWI
     */
    void initialize_master();

    /**
     * @brief Initializes TWI as slave
     *
     * @param[in]   address     Slave address
     */
    void initialize_slave(const uint8_t address);

    /**
     * @brief   Returns status code from TWI.
     *
     * @details Returns status code from TWI, definition of codes can be found in <util/twi.h>.
     *
     * @return  TWI status code
     *
     * @retval  uint8_t     TWI status code
     */
    uint8_t status();

    /**
     * @brief   Write data from buffer to TWI
     *
     * @details Writes length bytes of data from buffer to TWI slave at address
     *
     * @param[in]   addr        TWI slave address
     * @param[in]   reg         Register to write to
     * @param[in]   length      Length of data to write
     * @param[in]   buffer      Data to write to slave
     */
    void write(const uint8_t addr, const uint8_t reg, const uint8_t length, const uint8_t* buffer);

    /**
     * @brief   Write data from buffer to TWI via registers
     *
     * @details Writes data from buffer to TWI via registers
     *
     * @note    Expects data to be in form of [register address, data, register address, data]
     *
     * @param[in]   addr    TWI slave address
     * @param[in]   length  Length of data including registers
     * @param[in]   buffer  Data to be written to slave, form of [register, data, register ...]
     */
    void write_registers(const uint8_t addr, const uint8_t length, const uint8_t* buffer);

    /**
     * @brief   Read data from TWI to buffer
     *
     * @details Reads length of bytes from TWI at address to buffer
     *
     * @param[in]   addr        TWI slave address
     * @param[in]   reg         Register to read from
     * @param[in]   length      Length of data to write
     * @param[out]  buffer      Data to write to slave
     */
    void read(const uint8_t addr, const uint8_t reg, const uint8_t length, uint8_t* buffer);
}

#endif
