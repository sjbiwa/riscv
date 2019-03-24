#if defined(_LP64)
#define	REG_L		ld
#define	REG_S		sd
#define	REG_SIZE	8
#else
#define	REG_L		lw
#define	REG_S		sw
#define	REG_SIZE	4
#endif
#define	STACK_SIZE	4096

	.global _start
	.type _start, function
_start:
	la		sp, __stack_bottom
	la		s0, trap_entry

	csrw	mtvec, s0
	csrw	mcause, zero
	
	.option push
	.option norelax	
	la		gp, __global_pointer$
	.option pop

// data section copy
	la		s0, __data_start
	la		s1, __data_end
	la		s2, __ldata_start
// data section の LMA==VMAならコピーしない
	beq		s0, s2, 1f
0:
	bgeu	s0, s1, 1f
	lw		a0, (s2)
	sw		a0, (s0)
	addi	s0, s0, 4
	addi	s2, s2, 4
	j		0b
1:
	
// bss clear
	la		s0, __bss_start
	la		s1, __bss_end
0:
	bgeu	s0, s1, 1f
	sw		zero, (s0)
	addi	s0, s0, 4
	j		0b
1:

	call	lprintf_init

// call c++ global constructor
	la		s0, __init_array_start
	la		s1, __init_array_end
0:
	bgeu	s0, s1, 1f
	REG_L	a0, (s0)
	jalr	a0
	addi	s0, s0, REG_SIZE
	j		0b
1:

	call	main
	j		exit

	.global exit
	.type exit, function
exit:

exit_loop:
  j .

#define MSTATUS_MPP 0x00001800
#define NUM_CALLER_SAVE_REGISTERS (1+3+8+4) // save caller integer registers ra, t0-t2, a0-a7, t3-t6

	.global trap_entry
	.align 2
trap_entry:
	addi	sp, sp, -NUM_CALLER_SAVE_REGISTERS*REG_SIZE
	REG_S	ra,  0*REG_SIZE(sp)
	REG_S	t0,  1*REG_SIZE(sp)
	REG_S	t1,  2*REG_SIZE(sp)
	REG_S	t2,  3*REG_SIZE(sp)
	REG_S	a0,  4*REG_SIZE(sp)
	REG_S	a1,  5*REG_SIZE(sp)
	REG_S	a2,  6*REG_SIZE(sp)
	REG_S	a3,  7*REG_SIZE(sp)
	REG_S	a4,  8*REG_SIZE(sp)
	REG_S	a5,  9*REG_SIZE(sp)
	REG_S	a6, 10*REG_SIZE(sp)
	REG_S	a7, 11*REG_SIZE(sp)
	REG_S	t3, 12*REG_SIZE(sp)
	REG_S	t4, 13*REG_SIZE(sp)
	REG_S	t5, 14*REG_SIZE(sp)
	REG_S	t6, 15*REG_SIZE(sp)

	csrr	a0, mcause
	csrr	a1, mepc
	mv		a2, sp
	call	handle_trap
	csrw	mepc, a0

//# Remain in M-mode after mret
	li		t0, MSTATUS_MPP
	csrs	mstatus, t0

	REG_L	ra,  0*REG_SIZE(sp)
	REG_L	t0,  1*REG_SIZE(sp)
	REG_L	t1,  2*REG_SIZE(sp)
	REG_L	t2,  3*REG_SIZE(sp)
	REG_L	a0,  4*REG_SIZE(sp)
	REG_L	a1,  5*REG_SIZE(sp)
	REG_L	a2,  6*REG_SIZE(sp)
	REG_L	a3,  7*REG_SIZE(sp)
	REG_L	a4,  8*REG_SIZE(sp)
	REG_L	a5,  9*REG_SIZE(sp)
	REG_L	a6, 10*REG_SIZE(sp)
	REG_L	a7, 11*REG_SIZE(sp)
	REG_L	t3, 12*REG_SIZE(sp)
	REG_L	t4, 13*REG_SIZE(sp)
	REG_L	t5, 14*REG_SIZE(sp)
	REG_L	t6, 15*REG_SIZE(sp)

	addi	sp, sp, NUM_CALLER_SAVE_REGISTERS*REG_SIZE
	mret

	.weak handle_trap
handle_trap:
	j		.

    .section    .stack,"aw"
	.balign 16
__stack_top:
	.zero	STACK_SIZE
__stack_bottom:
