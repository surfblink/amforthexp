
REVISION := $(shell git status -bs -u no|tr / -)
CROSS=arm-none-eabi-
LANG=C

BOSSAC=/Users/martin/Library/Arduino15/packages/arduino/tools/bossac/1.9.1-arduino5/bossac
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
	$(CROSS)as --warn --fatal-warnings -alms=unor4.list -I../../arm -I ../../arm/devices/cortex-m4 -I ../../shared -o $@ $<

all: unor4.hex unor4.lst

unor4.elf: unor4.o ../../arm/amforth.s buildinfo
	$(CROSS)ld -T memmap $< -o $@

clean:
	rm -f *.elf *.bin *.o *.log *.lst *.hex *.list words/build-info.s

upload: unor4.bin
	$(BOSSAC) -d --port=$(PORT) -U -e -w unor4.bin -a

buildinfo: words/build-info.tmpl
	cat words/build-info.tmpl | sed "s/%d/ `date`/" | sed "s/%r/${REVISION}/" > words/build-info.s

