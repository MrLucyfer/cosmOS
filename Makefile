<<<<<<< HEAD
KERNEL_HDD = disk.hdd

.PHONY: clean all run

all: $(KERNEL_HDD)


src/kernel.elf:
	$(MAKE) -C src

$(KERNEL_HDD): limine src/kernel.elf
	rm -f $(KERNEL_HDD)
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNEL_HDD)
	parted -s $(KERNEL_HDD) mklabel gpt
	parted -s $(KERNEL_HDD) mkpart primary 2048s 100%
	echfs-utils -g -p0 $(KERNEL_HDD) quick-format 512
	echfs-utils -g -p0 $(KERNEL_HDD) import src/kernel.elf kernel.elf
	echfs-utils -g -p0 $(KERNEL_HDD) import limine.cfg limine.cfg
	echfs-utils -g -p0 $(KERNEL_HDD) import limine/limine.sys limine.sys
	./limine/limine-install $(KERNEL_HDD)

clean:
	rm -f $(KERNEL_HDD)
	$(MAKE) -C src clean
=======

# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso
GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-threadsafe-statics -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -c -o
ASPARAMS = --32
LDPARAMS = -melf_i386

#ASSEMBLER = /usr/local/Cellar/x86_64-elf-binutils/2.36.1/bin/x86_64-elf-as
#CC = /usr/local/Cellar/x86_64-elf-gcc/10.3.0/bin/x86_64-elf-gcc
#LD = /usr/local/Cellar/x86_64-elf-binutils/2.36.1/bin/x86_64-elf-ld

ASSEMBLER = as
CC = gcc
LD = ld

objects = src/Kernel/kernel.o src/Kernel/loader.o src/Kernel/GDT.o src/Kernel/Interrupts.o src/Kernel/Port.o \
		  src/Kernel/interruptstubs.o src/Kernel/Terminal.o


%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(GCCPARAMS) $@ $<
%.o: %.s
	mkdir -p $(@D)
	$(ASSEMBLER) $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	$(LD) $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

#kernel.iso: mykernel.bin
#	mkdir iso
#	mkdir iso/boot
#	mkdir iso/boot/grub
#	cp mykernel.bin iso/boot/mykernel.bin
#	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
#	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
#	echo ''                                  >> iso/boot/grub/grub.cfg
#	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
#	echo '  multiboot /boot/mykernel.bin'    >> iso/boot/grub/grub.cfg
#	echo '  boot'                            >> iso/boot/grub/grub.cfg
#	echo '}'                                 >> iso/boot/grub/grub.cfg
#	grub-mkrescue --output=mykernel.iso iso
#	rm -rf iso

.PHONY: clean
clean:
	rm src/Kernel/*.o src/AK/*.o
	rm mykernel.bin
>>>>>>> ca37ee63dd2f19f5059c9db9cb15a504b16ea327
