# BOOTLOADER

采用RISCV架构定义的SBI标准来引导内核启动。该标准有多个不同的实现，本项目选择RustSBI。RustSBI为QEMU环境提供了platform-specified版本。

## RustSBI

### 自动操作

本项目已经包含了可引导启动的RustSBI固件(rustsbi-qemu-debug/rustsbi-qemu)。为了引导内核启动，你首先需要安装riscv架构的工具链(riscv64-elf-binutils等)以及riscv64架构的qemu。然后使用`make build`命令编译内核于build目录下。最后使用`make run`命令启动虚拟机。

注：你需要修改Makefile中的一些变量以适配你的编译环境，例如\$ARCH变量是工具链命名前缀，\$CFLAGS和\$LDFLAGS是编译参数，\$BOOTLOADER是rustsbi的目录，\$QEMU是你电脑中的qemu程序名或程序目录，\$QEMUOPTS是启动qemu虚拟机时的参数。

### 手动操作

[仓库地址](https://github.com/rustsbi/rustsbi-qemu)
从该地址的Releases中下载rustsbi-qemu-debug.zip，解压后得到rustsbi-qemu(elf文件)和rustsbi-qemu.bin(纯二进制文件)。你可以在Makefile中找到BOOTLOADER变量，它代表virt机的bios固件，将这个变量修改为rustsbi-qemu(elf文件)的路径，即可通过make run命令启动内核。

## [参照阅读] (Deprecated) OpenSBI

RISCV架构提供了三种引导方式
* fw_payload
* fw_jump
* fw_dynamic

本项目使用fw_jump，以u-boot为二级引导，

根据uboot项目文档和opensbi项目文档中提供的方法，编译U-boot和OpenSBI然后启动QEMU。但是需要插入含有Kernel的Device，在U-boot中引导该Device中的Kernel启动。本项目不包含此方面的具体文档，在此仅作为提示，欢迎有志同学自行尝试。