CC=arm-none-eabi-gcc
TARGET=flash

MACH= -mcpu=cortex-m4
FLOAT=-mfloat-abi=hard

LINKER= -T linkers/linker.ld
MAP_FILE= -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

BUILD_DIR= Build

CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0 
LDFLAGS =  $(MACH) -mthumb $(FLOAT) --specs=nano.specs $(LINKER) $(MAP_FILE) -u _printf_float -Wl,--print-memory-usage
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I app/Inc/
INCLUDES+= -I Drivers/Inc/ 


############################################
# 				OUTPUT FILES

OBJS		+= $(BUILD_DIR)/main.o
OBJS		+= $(BUILD_DIR)/config.o
OBJS		+= $(BUILD_DIR)/syscalls.o
OBJS		+= $(BUILD_DIR)/startup.o
OBJS		+= $(BUILD_DIR)/constructors.o


DRIVERS		+= $(BUILD_DIR)/driver_fpu.o
DRIVERS		+= $(BUILD_DIR)/driver_systick.o
DRIVERS		+= $(BUILD_DIR)/driver_gpio.o
DRIVERS		+= $(BUILD_DIR)/driver_uart.o

PREREQ = $(BUILD_DIR)/

all: $(PREREQ) $(BUILD_DIR)/$(TARGET).elf

$(PREREQ):
	mkdir $(PREREQ)

$(BUILD_DIR)/%.o: app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o app/Src/$(*).c

$(BUILD_DIR)/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o Drivers/Src/$(*).c

$(BUILD_DIR)/%.o: linkers/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o linkers/$(*).c

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(DRIVERS) $(BSP)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
	arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf

load:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
	-c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

clean:
	rm -rf $(BUILD_DIR)/*.map $(BUILD_DIR)/*.o