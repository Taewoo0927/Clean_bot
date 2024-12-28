# To do:
# Remove local toolchains and use docker for efficiency.

# Compiler and MCU settings
MCU = msp430g2553

# Detect Operating System
ifeq ($(OS),Windows_NT)
    # Windows settings
	CC = msp430-elf-gcc
    INCLUDE_PATH = C:/ti/msp430-gcc/include
    CUSTOM_INCLUDE = ./include
    LIB_PATH = C:/ti/msp430-gcc/include
    LINKER_SCRIPT = C:/ti/msp430-gcc/include/$(MCU).ld
	OBJCOPY = msp430-elf-objcopy
else
    # Linux settings (GitHub Actions)
	CC = msp430-gcc
    CUSTOM_INCLUDE = ./include
    OBJCOPY = msp430-objcopy
endif

# Compiler flags default
CFLAGS = -mmcu=$(MCU) -Wall -I$(CUSTOM_INCLUDE)
# Add specified toolchain's directory if it's window
ifeq ($(OS),Windows_NT)
    CFLAGS += -I$(INCLUDE_PATH) 
endif

# Window and linux path
ifeq ($(OS),Windows_NT)
    LDFLAGS = -L$(LIB_PATH) -T$(LINKER_SCRIPT)
else
    LDFLAGS = -mmcu=$(MCU)
endif

CPPCHECK = cppcheck

# Source files and output file & directories
BUILD_DIR = Build
SRC = Src/main.c Src/Drivers/io.c Src/Drivers/system_init.c Src/Others/others.c Src/Test/test.c	# Add source codes as I add up
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
	$(OBJCOPY) -O ihex $(TARGET) $(HEX_FILE)

# Flash the code to the microcontroller
flash: $(HEX_FILE)
	C:/ti/MSPFlasher_1.3.20/MSP430Flasher.exe -n $(MCU) -w $(HEX_FILE) -v -g
	mspdebug ezfet -d COM7 "reset"

reset:
	mspdebug ezfet -d COM7 "reset"

cppcheck:
	$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unusedFunction \
	--suppress=unmatchedSuppression \
	-I $(CUSTOM_INCLUDE) \
	$(SRC)