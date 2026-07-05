CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu99

LINKER = -T Src/linker.ld
LDFLAGS = -nostdlib $(LINKER) -Wl,-Map=$(BUILD_DIR)/flash.map

BUILD_DIR = Build
PREREQ = $(BUILD_DIR)/

all: $(PREREQ) $(BUILD_DIR)/flash.elf

$(PREREQ):
	mkdir $(PREREQ)

$(BUILD_DIR)/main.o : Src/main.s
	$(CC) $(CFLAGS) $^ -o $@
	
$(BUILD_DIR)/startup.o : Src/startup.c
	$(CC) $(CFLAGS) $^ -o $@
	
$(BUILD_DIR)/flash.elf : $(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o
	$(CC) $(LDFLAGS) $^ -o $@

load:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
	-c "program $(BUILD_DIR)/flash.elf verify reset exit"

clean:
	rm -rf $(BUILD_DIR)/*.o 