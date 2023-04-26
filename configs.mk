ARCH = riscv64-elf-
GDB = $(ARCH)gdb
CC = $(ARCH)gcc
AS = $(ARCH)gcc
LD = $(ARCH)ld
OBJCOPY = $(ARCH)objcopy
OBJDUMP = $(ARCH)objdump

PREFIX = build

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -nostdlib
CFLAGS += $(foreach dir, $(SRC_DIRS), -I../../headers/$(dir))
# 这句话的意思是，如果-fno-stack-protector(无堆栈保护??)选项存在，就添加它。过程蛮复杂的。
# -fstack-protector-all 启用 堆栈保护, 为所有函数 插入保护代码
# -E 仅作预处理，不进行编译、汇编和链接
# -x c 指明使用的语言为 c语言
# 前一个 /dev/null 用来指定 目标文件
# >/dev/null 2>&1 将标准输出与错误输出重定向到 /dev/null(哑型设备  无用信息收集器 (不会打印信息，哑巴))
# /dev/null是一个 垃圾桶 一样的东西
# ‘&&’之前的半句表示，试着对一个垃圾 跑一下这个命令，所有的 输出 都作为垃圾，为了快一点，开了-E。
# 如果不能运行，那么&&前面的条件不成立，后面的就被忽视。======================s
# 如果可以运行，那么&&后面的句子得到执行，于是 CFLAGS += -fno-stack-protector
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
CFLAGS += -D LOG_LEVEL_DEBUG
# 关闭PIE
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
CFLAGS += -fno-pie -no-pie
endif
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
CFLAGS += -fno-pie -nopie
endif

LDFLAGS = -z ax-page-size=4096

BOARD ?= qemu
SBI   ?= rustsbi
BOOTLOADER := ./rustsbi-qemu-debug/rustsbi-qemu

QEMU = qemu-system-riscv64
QEMUDBGFLAGS  = -S -gdb tcp::2002
QEMUOPTS = \
	-m 256M \
	-nographic \
	-machine virt \
	-bios $(BOOTLOADER) \
	-kernel build/kernel 
