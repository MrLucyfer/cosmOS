
# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso
GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -c -o
ASPARAMS = --32
LDPARAMS = -melf_i386

ASSEMBLER = /usr/local/Cellar/x86_64-elf-binutils/2.36.1/bin/x86_64-elf-as 
CC = /usr/local/Cellar/x86_64-elf-gcc/10.3.0/bin/x86_64-elf-gcc
LD = /usr/local/Cellar/x86_64-elf-binutils/2.36.1/bin/x86_64-elf-ld

objects = src/kernel.o src/loader.o src/GDT.o src/Interrupts.o src/Port.o src/interruptstubs.o


%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(GCCPARAMS) $@ $<
%.o: %.s
	mkdir -p $(@D)
	$(ASSEMBLER) $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	$(LD)	$(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

.PHONY: clean
clean:
	rm src/*.o
