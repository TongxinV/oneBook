
#include <config.h>
#include <version.h>
#if defined(CONFIG_ENABLE_MMU)
#include <asm/proc/domain.h>
#endif
#include <regs.h>

#ifndef CONFIG_ENABLE_MMU
#ifndef CFG_PHY_UBOOT_BASE
#define CFG_PHY_UBOOT_BASE	CFG_UBOOT_BASE
#endif
#endif

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */

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
	ldr	pc, _fiq

_undefined_instruction:
	.word undefined_instruction
_software_interrupt:
	.word software_interrupt
_prefetch_abort:
	.word prefetch_abort
_data_abort:
	.word data_abort
_not_used:
	.word not_used
_irq:
	.word irq
_fiq:
	.word fiq
_pad:
	.word 0x12345678 /* now 16*4=64 */
.global _end_vect
_end_vect:

	.balignl 16,0xdeadbeef
/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************
 */

_TEXT_BASE:
	.word	TEXT_BASE

/*
 * Below variable is very important because we use MMU in U-Boot.
 * Without it, we cannot run code correctly before MMU is ON.
 * by scsuh.
 */
_TEXT_PHY_BASE:
	.word	CFG_PHY_UBOOT_BASE

.globl _armboot_start
_armboot_start:
	.word _start

/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word _end

#if defined(CONFIG_USE_IRQ)
/* IRQ stack memory (calculated at run-time) */
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word	0x0badc0de

/* IRQ stack memory (calculated at run-time) */
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word 0x0badc0de
#endif

/*
 * the actual reset code
 */

reset:
	/*
	 * set the cpu to SVC32 mode and IRQ & FIQ disable
	 */
	@;mrs	r0,cpsr
	@;bic	r0,r0,#0x1f
	@;orr	r0,r0,#0xd3
	@;msr	cpsr,r0
	msr	cpsr_c, #0xd3		@ I & F disable, Mode: 0x13 - SVC


/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
