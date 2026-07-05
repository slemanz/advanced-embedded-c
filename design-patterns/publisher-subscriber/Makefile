TARGET=flash
CC=arm-none-eabi-gcc
MACH=cortex-m0plus
FLOAT=soft
LINKER_SCRIPT=linkers/STM32G0B1.ld

#DEFINES+= -DNDEBUG

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) -std=gnu11 -Wall -O0 -ggdb $(DEFINES)
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) --specs=nano.specs -T $(LINKER_SCRIPT) -Wl,-Map=app/Build/$(TARGET).map -ggdb -u _printf_float -Wl,--print-memory-usage
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I app/Inc/
INCLUDES+= -I Drivers/Inc/ 


############################################
# 				OUTPUT FILES

OBJS		+= app/Build/main.o
OBJS		+= app/Build/syscalls.o
OBJS		+= app/Build/startup.o
OBJS		+= app/Build/config.o

OBJS		+= app/Build/driver_systick.o
OBJS		+= app/Build/driver_gpio.o
OBJS		+= app/Build/driver_uart.o
OBJS		+= app/Build/driver_adc.o

OBJS		+= app/Build/env_sensor.o
OBJS		+= app/Build/fertilizer_mixer_client.o
OBJS		+= app/Build/env_display_client.o



all: app/Build app/Build/$(TARGET).elf 

app/Build:
	mkdir app/Build

app/Build/%.o: app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o app/Src/$(*).c

app/Build/%.o: Src/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o app/Src/$(*).S

app/Build/%.o: linkers/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o linkers/$(*).c

app/Build/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o Drivers/Src/$(*).c

app/Build/%.o: Common/Src/utils/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o Common/Src/utils/$(*).c

app/Build/%.o: Common/Src/comms/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o Common/Src/comms/$(*).c

app/Build/$(TARGET).elf: $(OBJS) $(COMMS) $(UTILS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary app/Build/$(TARGET).elf app/Build/$(TARGET).bin
	arm-none-eabi-size app/Build/$(TARGET).elf

load:
	openocd -f interface/stlink-dap.cfg -f target/stm32g0x.cfg -c init -c "reset init" \
	-c "flash write_image erase app/Build/$(TARGET).elf" -c "reset run" -c shutdown

clean:
	rm -rf *.o *.map app/Build/*.o