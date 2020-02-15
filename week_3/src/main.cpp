#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "mcp3201.h"
#include "serial.h"

int main(void)
{
    MCP3201::init();
    UART::init();

    while (1)
    {
        uint16_t result = MCP3201::get_data();

        // Add the start indicator
        result |= (1 << 15);

        // Print result to serial, MSB first
        UART::putchar(result >> 8);
        UART::putchar(result & 0xFF);

        _delay_ms(500);
    }
}
