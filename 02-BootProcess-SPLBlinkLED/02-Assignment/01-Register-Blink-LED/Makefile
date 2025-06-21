# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as

# Flags
CFLAGS = -mcpu=cortex-m3 -mthumb -std=c11 -Wall -g -O0 \
	-Iinclude \
    -Ilib \
	-DSTM32F10X_MD\

LDFLAGS = -Tlinker.ld -nostartfiles -Wl,--gc-sections
LIBS = -lm -lc

# Sources
SRC = $(wildcard src/*.c) \

STARTUP = startup/startup_stm32f10x_md.s

OBJ = $(SRC:.c=.o) $(STARTUP:.s=.o)
OUT = build/test.elf

# Rules
build: $(OUT)

$(OUT): $(OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

clean:
	rm -rf src/*.o lib/SPL/src/*.o build startup/*.o

flash: $(OUT)
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(OUT) verify reset exit"