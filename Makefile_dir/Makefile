# Compiler and MCU settings
CC = msp430-elf-gcc
MCU = msp430g2553
INCLUDE_PATH = C:/ti/msp430-gcc/include
LIB_PATH = C:/ti/msp430-gcc/include
LINKER_SCRIPT = msp430g2553.ld
CFLAGS = -mmcu=$(MCU) -Wall -I$(INCLUDE_PATH)
LDFLAGS = -L$(LIB_PATH) -T$(LINKER_SCRIPT)

# Source files and output file
SRC = src/main.c 
OBJ = $(SRC:.c=.o)
TARGET = main.elf

# Default rule: build the target
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET) main.txt

# Convert ELF to TI-TXT format for flashing
main.txt: $(TARGET)
	msp430-elf-objcopy -O ihex $(TARGET) main.txt

# Flash the code to the microcontroller
flash: main.txt
	C:/ti/MSPFlasher_1.3.20/MSP430Flasher.exe -n $(MCU) -w main.txt -v -g
