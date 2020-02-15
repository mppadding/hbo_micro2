#define F_CPU 16000000UL

#include <avr/io.h>

#include "adc.h"
#include "serial.h"

int main(void)
{
	Converter::init();
	UART::init();
	
    while (1)
    {
        // Write to uart when uart can transmit
		if(UART::can_transmit()) {
			UART::putchar(Converter::low_read());
		}
    }
}
