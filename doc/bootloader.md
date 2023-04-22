# BOOTLOADER

采用RISCV架构定义的SBI标准来引导内核启动。该标准有多个不同的实现，本项目选择OPENSBI。同时，针对各开发板，提供了一些platform-specified版本样例。本项目采用qemu启动，因此编译virt开发板版本。

RISCV架构提供了三种引导方式
* fw_payload
* fw_jump
* fw_dynamic

本项目使用fw_payload，以内核为payload，直接引导进入kernel启动。有兴趣的同学也可以尝试使用其他方法引导内核启动。

根据(教程Tutorial-I部分)[https://riscv.org/wp-content/uploads/2019/12/Summit_bootflow.pdf]，编译OpenSBI然后启动QEMU：

`make PLATFORM=qemu/virt FW_PAYLOAD_PATH=$(PATH_TO_IMAGE)`

```
./qemu-system-riscv64 -M virt -m 256M -nographic \
-kernel opensbi/build/platform/qemu/virt/firmware/fw_payload.elf \
-drive file=lios_rootfs.img,format=raw,id=hd0 \
## 以下部分存疑
-device virtio-blk-device,drive=hd0 \
-append "root=/dev/sda/ rw console=ttyS0"
```
