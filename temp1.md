
以下代码在
```c
#include <config.h>
/*config.h是在include目录下的，这个文件不是源码中本身存在的文件，而是配置过程中自动生成的文件（详见mkconfig脚本）。
这个文件的内容其实是包含了一个头文件：#include <configs/x210_sd.h>.*/
#include <version.h>
#if defined(CONFIG_ENABLE_MMU)
#include <asm/proc/domain.h>
/*asm目录不是uboot中的原生目录，uboot中本来是没有这个目录的。asm目录是配置时创建的一个符号链接，实际指向的是就是
asm-arm（详见mkconfig）*/
#endif
#include <regs.h>
#ifndef CONFIG_ENABLE_MMU
#ifndef CFG_PHY_UBOOT_BASE 
#define CFG_PHY_UBOOT_BASE	CFG_UBOOT_BASE /* uboot在DDR中的物理地址 */
#endif
#endif

/* Jump vector table as in table 3.1 in [1] */
#if defined(CONFIG_EVT1) && !defined(CONFIG_FUSED) /* 启动代码的16字节头部 */
	.word 0x2000
	.word 0x0
	.word 0x0
	.word 0x0
#endif

.globl _start
_start: b	reset    /* 跳转到标号reset处 */
		......
......
/* 一些标号的定义 */
.global _end_vect
_end_vect:
	.balignl 16,0xdeadbeef /* 让当前地址对齐排布，如果当前地址不对齐则自动向后走地址直到对齐，并且向后走的那些内存要用0xdeadbeef来填充 */
......
.globl _bss_start    /* __bss_start、_bss_end: 清bss段会用到 */
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word _end
......
/*
 * the actual reset code
 */
reset:
	msr	cpsr_c, #0xd3		/* I & F disable, Mode: 0x13 - SVC模式 */
	
cpu_init_crit:	
	/* CPU初始化: 设置L2、L1cache和MMU */
	......	
	
	/* Read booting information    读取启动信息到r2，判断出启动介质后将一特殊值存到r3， 再将r3中的值存于一寄存器中 */
	ldr	r0, =PRO_ID_BASE
    ldr	r1, [r0,#OMR_OFFSET]
    bic	r2, r1, #0xffffffc1
	......
	cmp     r2, #0xc		/* SD/MMC BOOT */
	moveq   r3, #BOOT_MMCSD	
	cmp     r2, #0x14		/* NOR BOOT */
	moveq   r3, #BOOT_NOR	
	......
	ldr	r0, =INF_REG_BASE
	str	r3, [r0, #INF_REG3_OFFSET]	
	
	/* 设置栈，为了在内部96KB的iRAM中使用栈；调用lowlevel_init——时钟和DDR的初始化，初始化串口，打印'OK' */
	ldr	sp, =0xd0036000 /* end of sram dedicated to u-boot */
	sub	sp, sp, #12		/* set stack */
	mov	fp, #0
	
	bl	lowlevel_init	/* go setup pll,mux,memory 初始化串口 */
	
    /* 设置栈，为了将来重定位之后能在内存中使用栈；判断当前代码是在iRAM中执行还是在DDR，从而决定是否要进行重定位，如果是重定位完了的则直接跳转到 after_copy ，不执行中间的重定位代码 */
    ldr	sp, _TEXT_PHY_BASE	/* setup temp stack pointer */
	sub	sp, sp, #12
	mov	fp, #0			/* no previous frame, so fp=0 */

	/* when we already run in ram, we don't need to relocate U-Boot.
	 * and actually, memory controller must be configured before U-Boot
	 * is running in ram.
	 */
	ldr	r0, =0xff000fff
	bic	r1, pc, r0		/* r0 <- current base addr of code */
	ldr	r2, _TEXT_BASE		/* r1 <- original base addr in ram */
	bic	r2, r2, r0		/* r0 <- current base addr of code */
	cmp     r1, r2                  /* compare r0, r1                  */
	beq     after_copy		/* r0 == r1 then skip flash copy   */
	
    ldr	r0, =INF_REG_BASE
	ldr	r1, [r0, #INF_REG3_OFFSET]
	cmp	r1, #BOOT_NAND		/* 0x0 => boot device is nand */
	beq	nand_boot
	cmp	r1, #BOOT_ONENAND	/* 0x1 => boot device is onenand */
	beq	onenand_boot
	cmp     r1, #BOOT_MMCSD
	beq     mmcsd_boot
	cmp     r1, #BOOT_NOR
	beq     nor_boot
	cmp     r1, #BOOT_SEC_DEV
	beq     mmcsd_boot

nand_boot:
	mov	r0, #0x1000
	bl	copy_from_nand
	b	after_copy

onenand_boot:
	bl	onenand_bl2_copy
	b	after_copy

mmcsd_boot:
	bl      movi_bl2_copy
	b       after_copy

nor_boot:
	bl      read_hword
	b       after_copy
    
/* after_copy: 重定位完成之后紧接着要做的是--完成
after_copy:


```
