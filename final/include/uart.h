#ifndef LIB_UART_H_
#define LIB_UART_H_

#define BAUD F_UART

#include <util/setbaud.h>

namespace UART {
    /**
     * @brief   Initialize UART communication
     *
     * @details Intializes UART communication with baudrate set by F_UART
     */
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

    /**
     * @brief   Send a single character over UART
     *
     * @details Send a single character over UART. When a newline is end also add a carriage return (\r\n)
     *
     * @note    Blocking until byte sent
     *
     * @param[in]   c   Character to send
     */
    void putchar(char c) {
        /* Also add a carriage return whenever a newline is added (\r\n) */
        if (c == '\n') {
            putchar('\r');
        }

        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = c;
    }

    /**
     * @brief   Retrieve a single character from UART
     *
     * @note    Blocking until byte received
     *
     * @return  Character from UART
     *
     * @retval  char     Character from UART
     */
    char getchar() {
        loop_until_bit_is_set(UCSR0A, RXC0);
        return UDR0;
    }

    /**
     * @brief   Send string over UART
     *
     * @note    Blocking until string is sent
     *
     * @param[in]   c   Char array containing string to send
     */
    void puts(char c[]) {
        uint8_t index = 0;
        /* Loop until null termination character is found */
        while(c[index] != '\0') {
            putchar(c[index]);
            index++;
        }
    }

    /**
     * @brief   Checks if UART is able to transmit
     *
     * @return  Boolean indicating if UART is able to transmit.
     *
     * @retval  bool    True if UART can transmit.
     */
    bool can_transmit() {
        return (UCSR0A & (1 << UDRE0));
    }

    /**
     * @brief   Checks if UART is able to receive (current pending byte)
     *
     * @return  Boolean indicating if UART is able to receive data.
     *
     * @retval  bool    True if UART can receive data.
     */
    bool can_receive() {
        return (UCSR0A & (1 << RXC0));
    }
}

#endif /* LIB_UART_H_ */
