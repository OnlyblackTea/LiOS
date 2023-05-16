# RISC-V SBI规范（选录）

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [RISC-V SBI规范（选录）](#risc-v-sbi规范选录)
  - [第一章、导论](#第一章-导论)
  - [第二章、术语和缩写](#第二章-术语和缩写)
  - [第三章、二进制编码](#第三章-二进制编码)
  - [第四章、基本扩展（EID #0x10）](#第四章-基本扩展eid-0x10)
    - [4.1 函数：获取SBI规范版本（FID #0）](#41-函数获取sbi规范版本fid-0)
    - [4.2 函数：获取SBI实现ID（FID #1）](#42-函数获取sbi实现idfid-1)
    - [4.3 函数：获取SBI实现版本（FID #2）](#43-函数获取sbi实现版本fid-2)
    - [4.4 函数：探测SBI扩展（FID #3）](#44-函数探测sbi扩展fid-3)
    - [4.5 函数：获取机器供应商ID（FID #4）](#45-函数获取机器供应商idfid-4)
    - [4.6 函数：获取机器架构ID（FID #5）](#46-函数获取机器架构idfid-5)
    - [4.7 函数：获取机器实现ID（FID #6）](#47-函数获取机器实现idfid-6)
    - [4.8 函数列表](#48-函数列表)
  - [第五章、遗留扩展（EID #0x00 - #0x0F）](#第五章-遗留扩展eid-0x00---0x0f)
    - [5.1 扩展：Set Timer（EID #0x00）](#51-扩展set-timereid-0x00)
    - [5.2 扩展：Console Putchar（EID #0x01）](#52-扩展console-putchareid-0x01)
    - [5.3 扩展：Console Getchar（EID #0x02）](#53-扩展console-getchareid-0x02)
    - [5.4 扩展：Clear IPI（EID #0x03）](#54-扩展clear-ipieid-0x03)
    - [5.5 扩展：Send IPI（EID #0x04）](#55-扩展send-ipieid-0x04)

<!-- /code_chunk_output -->



## 第一章、导论

本规范描述RISC-V Supervisor模式二进制接口，又称SBI。以为平台定义抽象的方式，SBI允许S-mode或VS-mode软件在所有RISC-V平台上可迁移。SBI的设计遵循RISC-V的一般理念，即拥有一个小核心以及一组可选的模块化扩展。

SBI规范不指定任何用于发现硬件的方法。S-Mode软件必须依赖于其他工业标准硬件探索方法（例如硬件树或ACPI）。

## 第二章、术语和缩写

| Term | Meaning |
|---|---|
| SBI | Supervisor Binary Interface |
| SEE | Supervisor Execution Environment |
| EID | Extension ID |
| FID | Function ID |
| HSM | Hart State Management |
| PMU | Performance Monitoring Unit |
| IPI | Inter Processor Interrupt |
| ASID | Address Space Identifier |
| VMID | Virtual Machine Identifier |

## 第三章、二进制编码

所有SBI函数共享一个简单的二进制编码，这有助于混合SBI扩展。SBI规范遵循以下调用习俗：

* ECALL指令被用作Supervisor和SEE之间的控制转移指令。
* a7寄存器编码SBI EID
* a6寄存器对于a7寄存器中给定的EID编码SBI FID，用于在SBI v0.2或之后的任何SBI扩展
* 除了a0和a1以外的任何寄存器必须在被调用者的SBI调用中保留。
* SBI函数必须在a0和a1寄存器中返回错误码和数值，类似在C语言中的如下结构体：

```
struct sbiret{
  long error;
  long value;
};
```

出于兼容性的考虑，SBI EID和SBI FID被编码为带符号的32位整数。在寄存器中传递时，这些遵循上述调用约定规则的标准。
下表提供了标准SBI错误码：

| Error Type | Value |
|---|---|
| SBI_SUCCESS | 0 |
| SBI_ERR_FAILED | -1 |
| SBI_ERR_NOT_SUPPORTED | -2 |
| SBI_ERR_INVALID_PARAM | -3 |
| SBI_ERR_DENIED | -4 |
| SBI_ERR_INVALID_ADDRESS | -5 |
| SBI_ERR_ALREADY_AVAILABLE | -6 |
| SBI_ERR_ALREADY_STARTED | -7 |
| SBI_ERR_ALREADY_STOPPED | -8 |

对于带有不支持EID参数或FID参数的ECALL调用必须返回错误码`SBI_ERR_NOT_SUPPORTED`

每个SBI函数应该倾向于使用`unsigned long`作为数据类型。它保持简洁的规格，并且可以轻松地适应所有的RISC-V ISA类型。如果数据被定义为32位宽，更高权限软件必须确保它只使用32位数据。

## 第四章、基本扩展（EID #0x10）

### 4.1 函数：获取SBI规范版本（FID #0）
```
struct sbiret sbi_get_spec_version(void);
```

### 4.2 函数：获取SBI实现ID（FID #1）
```
struct sbiret sbi_get_impl_id(void);
```

### 4.3 函数：获取SBI实现版本（FID #2）
```
struct sbiret sbi_get_impl_version(void);
```

### 4.4 函数：探测SBI扩展（FID #3）
```
struct sbiret sbi_probe_extension(long extension_id);
```

### 4.5 函数：获取机器供应商ID（FID #4）
```
struct sbiret sbi_get_mvendorid(void)
```

### 4.6 函数：获取机器架构ID（FID #5）
```
struct sbiret sbi_get_marchid(void);
```

### 4.7 函数：获取机器实现ID（FID #6）
```
struct sbiret sbi-get_mimpid(void);
```

### 4.8 函数列表

| Function Name | SBI Version | FID | EID |
|---|---|---|---|
| sbi_get_sbi_spec_version | 0.2 | 0 | 0x10 |
| sbi_get_sbi_impl_id | 0.2 | 1 | 0x10 |
| sbi_get_sbi_impl_version | 0.2 | 2 | 0x10 |
| sbi_probe_extension | 0.2 | 3 | 0x10 |
| sbi_get_mvendorid | 0.2 | 4 | 0x10 |
| sbi_get_marchid | 0.2 | 5 | 0x10 |
| sbi_get_mimpid | 0.2 | 6 | 0x10 |

## 第五章、遗留扩展（EID #0x00 - #0x0F）

SBI遗留扩展遵循一个与SBI v0.2（或更高）版本规范轻微不同的调用约定：

* a6寄存器中的SBI FID字段被忽略，因为它们被编码为多个SBI扩展ID
* a1寄存器不获得任何返回值
* 除a0寄存器之外的所有寄存器都必须在被调用者的SBI调用中保留
* a0寄存器中返回的值是特定于SBI遗留扩展的

### 5.1 扩展：Set Timer（EID #0x00）
```
long sbi_set_timer(uint64_t stime_value)
```
在stime_value时间后为下一个事件编程时钟，该函数还清除挂起的定时器中断位。

如果Supervisor希望在不安排下一个定时器事件的情况下清除定时器中断，它可以请求无限远的未来定时器中断（即`(uint64_t)-1`），或者它可以通过清除sie.STIE CSR位来屏蔽定时器中断

此SBI调用返回0表示成功或特定于实现的负错误代码。

### 5.2 扩展：Console Putchar（EID #0x01）
```
long sbi_console_putchar(int ch)
```
将ch中存在的数据写入调试控制台。

与sbi_console_getchar()不同，如果仍有任何未决字符要传输或接收终端尚未准备好接收字节，则此SBI调用将阻塞。但是，如果控制台根本不存在，那么该字符将被丢弃。

此SBI调用返回0表示成功或特定于实现的负错误代码。

### 5.3 扩展：Console Getchar（EID #0x02）
```
long sbi_console_getchar(void)
```
从调试控制台中读取一个字节

此SBI调用在成功时返回这个字节，失败时返回-1

### 5.4 扩展：Clear IPI（EID #0x03）
```
long sbi_clear_ipi(void)
```
清除挂起的IPI（如果有）。IPI仅在调用此SBI调用的hart中清除。sbi_clear_ipi()已被弃用因为S-Mode代码可以直接清除`sip.SSIP`CSR位。

此SBI调用返回0如果没有IPI被挂起，或者返回一个特定于实现的正值如果有一个IPI已被挂起。

### 5.5 扩展：Send IPI（EID #0x04）
```
long sbi_send_ipi(const unsigned long *hart_mask)
```
向hart_mask中定义的所有harts发送处理器间中断。处理器间中断在接收端表现为Supervisor软件中断。

hart_mask是指向harts位向量的虚拟地址。位向量表示为`unsigned long`序列，其长度等于系统中的harts数量除以`unsigned long`位数，向上舍入到下一个整数。

此SBI调用返回0表示成功，或者返回特定于实现的负错误代码。

### 5.6 扩展：Remote FENCE.I（EID #0x05）
### 5.7 扩展：Remote SFENCE.VMA （EID #0x06）
### 5.8 扩展：Remote SFENCE.VMA with ASID （EID #0x07）
### 5.9 扩展：System Shutdown（EID #0x08）
```
void sbi_shutdown(void)
```
从Supervisor的角度来看，将所有hart置于关闭状态。

无论是成功还是失败，此SBI调用都不会返回。

### 5.10 函数列表

| Function Name | SBI Version | FID | EID | Replacement EID |
|---|---|---|---|---|
| sbi_set_timer | 0.1 | 0 | 0x00 | 0x54494D45 |
| sbi_console_putchar | 0.1 | 0 | 0x01 | N/A |
| sbi_console_getchar | 0.1 | 0 | 0x02 | N/A |
| sbi_clear_ipi | 0.1 | 0 | 0x03 | N/A |
| sbi_send_ipi | 0.1 | 0 | 0x04 | 0x735049 |
| sbi_remote_fence_i | 0.1 | 0 | 0x05 | 0x52464E43 |
| sbi_remote_sfence_vma | 0.1 | 0 | 0x06 | 0x52464E43 |
| sbi_remote_sfence_vma_asid | 0.1 | 0 | 0x07 | 0x52464E43 |
| sbi_shutdown | 0.1 | 0 | 0x08 | 0x53525354 |
| **RESERVED** |   |   | 0x09-0x0F |   |