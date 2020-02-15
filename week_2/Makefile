# AVR configuration
MCU=atmega328p
PORT=/dev/ttyACM0

# Build configuration
BDIR = build
SDIR = src
OUT = main
INC = -I include

CC=avr-g++
CFLAGS=-g -Os -mmcu=$(MCU)
LFLAGS=-g -mmcu=$(MCU)
HFLAGS=-j .text -j .data -O ihex

# Enable colors
#COLOR=1

#OK_STRING=[OK]
#ERROR_STRING=[ERR]
#WARN_STRING=[ERR]

#ifeq ($(COLOR), 1)
#	NO_COLOR=\x1b[0m
#	OK_COLOR=\x1b[32;01m
#	ERR_COLOR=\x1b[31;01m
#	WARN_COLOR=\x1b[33;01m
#
#	OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
#	ERR_STRING=$(ERR_COLOR)[ERR]$(NO_COLOR)
#	WARN_STRING=$(WARN_COLOR)[WARN]$(NO_COLOR)
#endif

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

.PHONY: flash clean

flash:
	avrdude -c arduino -P $(PORT) -p $(MCU) -U flash:w:$(BDIR)/$(OUT).hex

clean:
	@echo "Cleaning"
	@rm -f $(BDIR)/*.o $(BDIR)/$(OUT).elf
