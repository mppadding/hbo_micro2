#ifndef SERIAL_H_
#define SERIAL_H_

/* Serial baud rate */
#define BAUD	9600

#include <util/setbaud.h>

namespace UART {
	/* Initialize serial communication with PC */
	void init() {
		UBRR0H = UBRRH_VALUE;
		UBRR0L = UBRRL_VALUE;
		
		#if USE_2X
		UCSR0A |= (1 << U2X0);
		#else
		UCSR0A &= ~(1 << U2X0);
		#endif

		/* 8-bit data */
		UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
		
		/* Enable RX and TX */
		UCSR0B = (1<<RXEN0)|(1 << TXEN0);
	}

	void putchar(char c) {
		/* Also add a carriage return whenever a newline is added (\r\n) */
		if (c == '\n') {
			putchar('\r');
		}
		
		loop_until_bit_is_set(UCSR0A, UDRE0);
		UDR0 = c;
	}

	char getchar() {
		loop_until_bit_is_set(UCSR0A, RXC0);
		return UDR0;
	}

	void puts(char c[]) {
		uint8_t index = 0;
		
		/* Loop until null termination character is found */
		while(c[index] != '\0') {
			putchar(c[index]);
			index++;
		}
	}

	bool can_transmit() {
		return (UCSR0A & (1 << UDRE0));
	}

	bool can_receive() {
		return (UCSR0A & (1 << RXC0));
	}
}

#endif /* SERIAL_H_ */
