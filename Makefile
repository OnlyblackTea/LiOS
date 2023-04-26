.PHONY: clean
SRC_DIRS = $(shell find src -type d | grep "/" | sed 's/src\///g')
include configs.mk

all: 
	@mkdir -p $(PREFIX)
	make -C src
	$(LD) $(LDFLAGS) -T src/bootloader/kernel.ld -o $(PREFIX)/kernel $(foreach dirs, $(shell find build -type d | grep "/"), $(wildcard $(dirs)/*.o))
	$(OBJDUMP) -S $(PREFIX)/kernel > $(PREFIX)/kernel.asm
	$(OBJDUMP) -t $(PREFIX)/kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(PREFIX)/kernel.sym
	@echo 'Build kernel done'

clean:
	rm -rf $(PREFIX)

run: build/kernel
	$(QEMU) $(QEMUOPTS)

debug: build/kernel
	$(QEMU) $(QEMUDBGFLAGS) $(QEMUOPTS)
