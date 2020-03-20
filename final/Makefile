###
# AVR Makefile
# 	Author: Matthijs Padding
# 	Date: 18/03/2020
# 	Version: v1.0.2
###

# AVR configuration
MCU    = atmega328p
PORT   = /dev/avr-nano
AVR_BAUD = 57600

F_CPU  = 16000000
F_UART = 115200
F_TWI  = 100000
#F_SPI  =

# Build configuration
BDIR = build
SDIR = src
OUT = main
INC = -I include

###
# Compiler configuration
###
# Compiler
CXX=avr-g++

# Compiler flags
CXXFLAGS=-g -Os -mmcu=$(MCU) -Wall -Wextra -std=c++11

# Hex generation flags
HFLAGS=-j .text -j .data -O ihex

###
# Actual building etc.
###
CXXDEFS =
CXXDEFS := $(CXXDEFS) $(if $(F_CPU),-DF_CPU=$(F_CPU))
CXXDEFS := $(CXXDEFS) $(if $(F_UART),-DF_UART=$(F_UART))
CXXDEFS := $(CXXDEFS) $(if $(F_TWI),-DF_TWI=$(F_TWI))
CXXDEFS := $(CXXDEFS) $(if $(F_SPI),-DF_SPI=$(F_SPI))

SOURCES := $(wildcard $(SDIR)/*.cpp)
OBJECTS := $(patsubst $(SDIR)/%.cpp,$(BDIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SDIR)/%.cpp,$(BDIR)/%.d,$(SOURCES))

.PHONY: all prebuild build flash clean

all: prebuild build flash

prebuild:
	@echo ""
	@echo " Building project"
	@echo ""

build: $(BDIR)/$(OUT)

flash:
	@echo ""
	@echo " Flashing project"
	@echo -n ""
	@avrdude -b $(AVR_BAUD) -e -c arduino -P $(PORT) -p $(MCU) -U flash:w:$(BDIR)/$(OUT).hex:i -q

clean:
	@echo ""
	@echo " Cleaning"
	@echo ""
	@rm -f $(OBJECTS) $(DEPENDS) $(BDIR)/$(OUT).elf $(BDIR)/$(OUT).hex

$(BDIR)/$(OUT): $(OBJECTS)
	@echo "Linking into $@.elf"
	@$(CXX) $(CXXFLAGS) $(CXXDEFS) -o $@.elf $^

	@echo "Generating hex file ($@.hex)"
	@avr-objcopy $(HFLAGS) $@.elf $@.hex
	@echo ""

	@echo ""
	@echo " Project Size"
	@echo ""
	@avr-size -C --mcu=$(MCU) -C $@.elf | awk '{if(NR>4 && NR<10 && NR!=6 && NR != 7&& NR != 9)print}'
	@echo ""


-include $(DEPENDS)

$(BDIR)/%.o: $(SDIR)/%.cpp Makefile
	@echo "Building $<..."
		@$(CXX) $(INC) $(CXXFLAGS) $(CXXDEFS) -MMD -c -o $@ $<
