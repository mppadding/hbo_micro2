/*
 * Week1_UART.cpp
 *
 * Created: 11/02/2020 11:42:44
 * Author : Matthijs Padding
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>

#include "adc.h"
#include "serial.h"

int main(void)
{
	Converter::init();
	UART::init();
	
    // Set D4, D5, D6, D7 as output
	DDRD |= 0xF0;
	
    while (1)
    {
        PORTD = (Converter::low_read() & 0xF0);
        // Write to led when uart has data
		if(UART::can_receive()) {
			char data = UART::getchar();
			PORTD = data;
		}
	
        // Write to uart when uart can transmit
		if(UART::can_transmit()) {
			UART::putchar(Converter::low_read() & 0xF0);
		}
    }
}
