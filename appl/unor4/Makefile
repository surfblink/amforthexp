
REVISION := $(shell git status -bs -u no|tr / -)
CROSS=arm-none-eabi-
LANG=C

# Based on what Arduino IDE uses to program the Uno R4
# https://www.shumatech.com/web/products/bossa
# BOSSAC=/Users/martin/Library/Arduino15/packages/arduino/tools/bossac/1.9.1-arduino5/bossac
BOSSAC = bossac
# Must match ./memmap
FLASH_IMAGE_START = 0x4000
PORT=cu.usbmodemB43A45B4700C2

BOARD = unor4
LANG=C
%.lst: %.elf
	$(CROSS)objdump -D $< >$@

%.hex: %.elf
	$(CROSS)objcopy -O ihex $< $@

%.bin: %.elf
	$(CROSS)objcopy -O binary $< $@

%.o: %.asm buildinfo
	$(CROSS)as -g --warn --fatal-warnings -achlms=unor4.list -I../../arm -I ../../arm/devices/cortex-m4 -I ../../shared -o $@ $<

all: unor4.hex unor4.lst

unor4.elf: unor4.o ../../arm/amforth.s buildinfo
	$(CROSS)ld -T memmap $< -o $@

clean:
	rm -f *.elf *.bin *.o *.log *.lst *.hex *.list words/build-info.s

upload: unor4.bin
	$(BOSSAC) -d --port=$(PORT) -o $(FLASH_IMAGE_START) -w unor4.bin -v -a

download:
	$(BOSSAC) -d --port=$(PORT) -r0x4000 unor4.bin2

inspect:
	stty -f /dev/$(PORT) 1200
	bossash

buildinfo: words/build-info.tmpl
	cat words/build-info.tmpl | sed "s/%d/ `date`/" | sed "s/%r/${REVISION}/" > words/build-info.s


ARDUINO_LIB = /Users/martin/Library/Arduino15/packages/arduino
ARDUINO_PLUGINS = /Applications/Arduino IDE.app/Contents/Resources/app/plugins
OPENOCD = $(ARDUINO_LIB)/tools/openocd/0.11.0-arduino2

ocd: unor4.elf
	$(OPENOCD)/bin/openocd -c "gdb_port 50000" -c "tcl_port 50001" -c "telnet_port 50002" \
	-f "$(ARDUINO_PLUGINS)/cortex-debug/extension/support/openocd-helpers.tcl" \
	-f $(OPENOCD)/share/openocd/scripts/interface/cmsis-dap.cfg \
	-f $(ARDUINO_LIB)/hardware/renesas_uno/1.5.1/debugger/select_swd.cfg \
	-f $(ARDUINO_LIB)/hardware/renesas_uno/1.5.1/debugger/R7FA4M1AB.cfg

gdb: unor4.elf
	$(CROSS)gdb -tui ./unor4.elf \
    -ex "layout asm" \
	-ex "layout reg" \
	-ex "target extended-remote localhost:50000" \
	-ex "bp XT_LED_INIT" \
	-ex "monitor reset"