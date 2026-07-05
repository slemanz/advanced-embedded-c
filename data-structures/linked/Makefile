CC=arm-none-eabi-gcc
TARGET=flash

MACH= -mcpu=cortex-m4
FLOAT=-mfloat-abi=hard

BUILD_DIR= Build

LINKER= -T linkers/STM32F411xC.ld
MAP_FILE= -Wl,-Map=$(BUILD_DIR)/$(TARGET).map


CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0 \
		--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS =  $(MACH) -mthumb $(FLOAT) --specs=nosys.specs  $(LINKER) $(MAP_FILE) \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm -Wl,--end-group \
 			-Wl,--print-memory-usage

OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I app/Inc/
INCLUDES+= -I drivers/Inc/ 
INCLUDES+= -I bsp/Inc/ 


############################################
# 				OUTPUT FILES

OBJS		+= $(BUILD_DIR)/main.o
OBJS		+= $(BUILD_DIR)/config.o
OBJS		+= $(BUILD_DIR)/syscalls.o
OBJS		+= $(BUILD_DIR)/startup.o


DRIVERS		+= $(BUILD_DIR)/driver_fpu.o
DRIVERS		+= $(BUILD_DIR)/driver_systick.o
DRIVERS		+= $(BUILD_DIR)/driver_gpio.o
DRIVERS		+= $(BUILD_DIR)/driver_uart.o
DRIVERS		+= $(BUILD_DIR)/driver_adc.o
DRIVERS		+= $(BUILD_DIR)/driver_spi.o
DRIVERS		+= $(BUILD_DIR)/driver_i2c.o
DRIVERS		+= $(BUILD_DIR)/driver_interrupt.o
DRIVERS		+= $(BUILD_DIR)/driver_rtc.o

BSP			+= $(BUILD_DIR)/led.o
BSP			+= $(BUILD_DIR)/button.o

PREREQ = $(BUILD_DIR)/

all: $(PREREQ) $(BUILD_DIR)/$(TARGET).elf

$(PREREQ):
	mkdir $(PREREQ)

$(BUILD_DIR)/%.o: app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o app/Src/$(*).c

$(BUILD_DIR)/%.o: drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o drivers/Src/$(*).c

$(BUILD_DIR)/%.o: bsp/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o bsp/Src/$(*).c

$(BUILD_DIR)/%.o: linkers/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o linkers/$(*).c

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(DRIVERS) $(BSP)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
	arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf

load:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset init" \
	-c "flash write_image erase Build/flash.elf" -c "reset run" -c shutdown

clean:
	rm -rf $(BUILD_DIR)/*.map $(BUILD_DIR)/*.o