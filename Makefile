
# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso
GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -c -o
ASPARAMS = --32
LDPARAMS = -melf_i386

ASSEMBLER = as
CC = gcc

objects = src/kernel.o src/loader.o


%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(GCCPARAMS) $@ $<
%.o: %.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

.PHONY: clean
clean:
	rm src/*.o
