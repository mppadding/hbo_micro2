# AVR configuration
MCU=atmega328p
PORT=/dev/ttyACM0

# Build configuration
BDIR = build
SDIR = src
OUT = main
INC = -I include

CC=avr-g++
CFLAGS=-g -Os -mmcu=$(MCU) -Wall -Wextra
LFLAGS=-g -mmcu=$(MCU)
HFLAGS=-j .text -j .data -O ihex

_OBJS = main.o
OBJS = $(patsubst %,$(BDIR)/%,$(_OBJS))

$(BDIR)/%.o: $(SDIR)/%.cpp
	@echo "Building $<..."
	@$(CC) $(INC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(OUT): $(OBJS)
	@echo "Linking into $@.elf"
	@$(CC) $(LFLAGS) -o $@.elf $^

	@echo "Generating hex file ($@.hex)"
	@avr-objcopy $(HFLAGS) $@.elf $@.hex

	@avr-size -C --mcu=$(MCU) -C $@.elf

.PHONY: flash clean

flash:
	avrdude -c arduino -P $(PORT) -p $(MCU) -U flash:w:$(BDIR)/$(OUT).hex

clean:
	@echo "Cleaning"
	@rm -f $(BDIR)/*.o $(BDIR)/$(OUT).elf $(BDIR)/$(OUT).hex
