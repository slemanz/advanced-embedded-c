CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu99
LDFLAGS = -nostdlib -T linker.ld -Wl,-Map=flash.map

INCLUDES+= -I Inc/

all: flash.elf

main.o : main.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 
	
startup.o : startup.c
	$(CC) $(CFLAGS) $^ -o $@
	
flash.elf : main.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^ 

load:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
	-c init -c "reset init" \
	-c "flash write_image erase flash.elf" -c "reset run" -c shutdown

clean:
	rm -rf *.o 