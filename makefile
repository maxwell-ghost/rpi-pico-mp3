CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion -ffreestanding \
            -g3 -Os -ffunction-sections -fdata-sections -I. \
            -mcpu=cortex-m0plus -mthumb $(EXTRA_CFLAGS)
LDFLAGS ?= -Tlink.ld -nostartfiles --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = $(SRC)/main.c $(SRC)/startup.c $(SRC)/hal.c
SOURCES += $(SRC)/oled.c $(SRC)/rpi_time.c $(SRC)/key.c $(SRC)/audio.c

SOURCES_NO_HEADER += $(SRC)/music_scripts.c $(SRC)/syscalls.c


CFLAGS += -DMG_ARCH=MG_ARCH_NEWLIB -DMG_ENABLE_CUSTOM_MILLIS=1 -DMG_ENABLE_MIP=1

BIN2UF2 = ./tools/bin2uf2
BUILD = ./build
SRC = ./src
RM = rm -f

build: $(BUILD)/firmware.uf2
	cp $< /mnt/d/Dev/shared


test: $(BIN2UF2)

$(BIN2UF2): tools/bin2uf2.c
	$(CC) -W -Wall $< -o $@

$(BUILD)/firmware.elf: $(SOURCES) $(SOURCES_NO_HEADER)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

$(BUILD)/firmware.uf2: $(BUILD)/firmware.bin $(BIN2UF2)
	$(BIN2UF2) $< $@

clean:
	$(RM) $(BUILD)/firmware.* $(BIN2UF2)