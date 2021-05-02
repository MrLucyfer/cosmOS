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
