# git status may display remote/branch names. That disturbs sed later on
REVISION := $(shell git status -bs -u no|tr / -)
ifeq ("$(REVISION)", "")
    REVISION := $(shell svnversion -n)
endif

# if you want to run standard tests you need WANT_IGNORECASE flag set
AOPTS=--defsym WANT_IGNORECASE=1
# if you want debug info add -g
AOPTS+=-g

CROSS=arm-linux-gnueabihf-
QEMU=qemu-system-arm
BOARD=$(shell uname -m)
ifeq ("$(BOARD)", "armv7l")
   CROSS=
   QEMU=
endif
LANG=C


%.o: %.asm buildinfo
	$(CROSS)as $(AOPTS) --warn -al=amforth.list -I ../../arm -I ../../arm/devices/linux -I ../../shared -o $@ $<

all: amforth

amforth: amforth.o
	$(CROSS)ld -T memmap -z max-page-size=4096 $< -o $@ 

clean:
	rm -f amforth *.elf *.bin *.o *.log *.lst *.hex *.list words/build-info.s

buildinfo: words/build-info.tmpl
	cat words/build-info.tmpl | sed "s/%d/ `date`/" | sed "s/%r/${REVISION}/" > words/build-info.s

# To run amforth in emulated container you can use a container runtime that supports --platform linux/arm/v7
# For MacOS check out https://orbstack.dev/ (Free for personal use)
# See Dockerfile for the details of what goes into the container image, tweak to heart's desire.
image: amforth
	docker build --tag amforth:latest .

# Starts the amforth container with a terminal session.
# Once terminal to the container opens you can start amforth, the binary is on the PATH.
# The whole host amforth directory is mounted in the container at /amforth.
# Apparently cannot run gdb inside the container, because ptrace sys call is not supported in emulation.
drun: image
	docker run --interactive --tty --rm \
		--volume $(shell pwd)/../..:/amforth \
		amforth:latest

# Run standard tests and output the results, requires WANT_IGNORECASE enabled above
# because the standard tests are in all caps and all amforth words are in lowercase.
# Currently segfaults, presumably because variables don't work yet which are central
# to the implementation of the testing framework (see the tester source)
test: image
	docker run --rm --volume $(shell pwd)/../..:/amforth amforth:latest /bin/sh -c \
		'cd amforth/common/lib/forth2012/tester; cat tester-amforth.frt core.fr | amforth'

# Starts amforth under QEMU
# WARNING(mk): This seems incomplete and does not work at least on MacOSX
# setup some terminal settings. Otherwise all input will be echo'ed
run: amforth
	qemu-img resize ./amforth 128k
	stty -icanon -echo
	$(QEMU) -machine raspi0 -display none -serial mon:stdio ./amforth || true
	stty sane
