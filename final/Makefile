# AVR configuration
MCU=atmega328p
PORT=/dev/avr-uno

# Build configuration
BDIR = build
SDIR = src
OUT = main
INC = -I include

# Compiler configuration
CXX=avr-g++
CXXFLAGS=-g -Os -mmcu=$(MCU) -Wall -Wextra
HFLAGS=-j .text -j .data -O ihex

###
# Actual building etc.
###
SOURCES := $(wildcard $(SDIR)/*.cpp)
OBJECTS := $(patsubst $(SDIR)/%.cpp,$(BDIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SDIR)/%.cpp,$(BDIR)/%.d,$(SOURCES))

.PHONY: all build flash clean stub

all: build flash

build: $(BDIR)/$(OUT)

flash:
	@avrdude -c arduino -P $(PORT) -p $(MCU) -U flash:w:$(BDIR)/$(OUT).hex

clean:
	@echo "Cleaning"
	@rm -f $(OBJECTS) $(DEPENDS) $(BDIR)/$(OUT).elf $(BDIR)/$(OUT).hex

stub:
	@echo $(DEPENDS)

$(BDIR)/$(OUT): $(OBJECTS)
	@echo "Linking into $@.elf"
	@$(CXX) $(CXXFLAGS) -o $@.elf $^

	@echo "Generating hex file ($@.hex)"
	@avr-objcopy $(HFLAGS) $@.elf $@.hex

	@avr-size -C --mcu=$(MCU) -C $@.elf


-include $(DEPENDS)

$(BDIR)/%.o: $(SDIR)/%.cpp Makefile
	@echo "Building $<..."
	@$(CXX) $(INC) $(CXXFLAGS) -MMD -c -o $@ $<
