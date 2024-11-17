# Compiler and MCU settings
CC = msp430-elf-gcc
MCU = msp430g2553
INCLUDE_PATH = C:/ti/msp430-gcc/include
LIB_PATH = C:/ti/msp430-gcc/include
LINKER_SCRIPT = msp430g2553.ld
CFLAGS = -mmcu=$(MCU) -Wall -I$(INCLUDE_PATH)
LDFLAGS = -L$(LIB_PATH) -T$(LINKER_SCRIPT)

# Source files and output file & directories
BUILD_DIR = Build
SRC = src/main.c 
OBJ = $(SRC:.c=.o)
TARGET = $(BUILD_DIR)/main.elf
HEX_FILE = $(BUILD_DIR)/main.txt

# Default rule: build the target
all: $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link all object files into the final executable
$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET) $(HEX_FILE)

# Convert ELF to TI-TXT format for flashing
$(HEX_FILE): $(TARGET)
	msp430-elf-objcopy -O ihex $(TARGET) $(HEX_FILE)

# Flash the code to the microcontroller
flash: $(HEX_FILE)
	C:/ti/MSPFlasher_1.3.20/MSP430Flasher.exe -n $(MCU) -w $(HEX_FILE) -v -g
	mspdebug ezfet -d COM7 "reset"

reset:
	mspdebug ezfet -d COM7 "reset"