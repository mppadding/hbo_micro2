#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "mcp9800.h"
#include "serial.h"

#define CHECKSUM_FACTOR 140

int main(void)
{
    MCP9800::init();
    UART::init();

    while (1)
    {
        uint16_t tmp = MCP9800::get_temperature_raw();
        UART::putchar(tmp >> 8);
        UART::putchar(tmp & 0xFF);
        UART::putchar((tmp & 0xFF) ^ CHECKSUM_FACTOR);
    }
}
