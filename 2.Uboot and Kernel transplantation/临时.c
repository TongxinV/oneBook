


#include <config.h> 	//config.h是在include目录下的，这个文件不是源码中本身存在的文件，而
                        //是配置过程中自动生成的文件。（详见mkconfig脚本）。这个文件的内容其
                        //实是包含了一个头文件：#include <configs/x210_sd.h>.
#include <version.h>
#if defined(CONFIG_ENABLE_MMU)
#include <asm/proc/domain.h>
                        //asm目录不是uboot中的原生目录，uboot中本来是没有这个目录的。asm目录
                        //是配置时创建的一个符号链接，实际指向的是就是asm-arm（详见mkconfig）
#endif
#include <regs.h>
#ifndef CONFIG_ENABLE_MMU
#ifndef CFG_PHY_UBOOT_BASE
#define CFG_PHY_UBOOT_BASE	CFG_UBOOT_BASE
						//uboot在DDR中的物理地址
#endif
#endif

/* Jump vector table as in table 3.1 in [1] */

#if defined(CONFIG_EVT1) && !defined(CONFIG_FUSED)
	.word 0x2000
	.word 0x0
	.word 0x0
	.word 0x0
#endif

.globl _start
_start: b	reset
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
......
/*
 * the actual reset code
 */
 



