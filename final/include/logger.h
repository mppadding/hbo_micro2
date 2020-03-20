#ifndef _LIB_LOGGER_H
#define _LIB_LOGGER_H

#include <string.h>

#define LOGGER_ADDRESS 0x30

#include "twi.h"

namespace Log {
    void info(const char* msg) {
        char i[] = "[INFO]";
        TWI::write(LOGGER_ADDRESS, i[0], strlen(i)-1, (uint8_t*)info+1);
        TWI::write(LOGGER_ADDRESS, msg[0], strlen(msg)-1, (uint8_t*)msg+1);
    }

    void error(const char* msg) {
        char err[] = "[ERROR]";
        TWI::write(LOGGER_ADDRESS, err[0], strlen(err)-1, (uint8_t*)err+1);
        TWI::write(LOGGER_ADDRESS, msg[0], strlen(msg)-1, (uint8_t*)msg+1);
    }
}

#endif
