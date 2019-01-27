#define	L_REG	ld
#define	S_REG	sd
#define	REG_LEN	8

	.option nopic
	.text
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	_start
	.type	_start, @function
_start:
	la		sp, _stack_top
	
	la		a0, __bss_start
	la		a1, _end
0:
	bge		a0, a1, 1f
	sw		zero, (a0)
	addi	a0, a0, 4
	j		0b
1:
	call	main

	.globl	_exc_handler
	.type	_exc_handler, @function
_exc_handler:
	addi	sp, sp, -REG_LEN*30
	S_REG	 x1, REG_LEN*0(sp)
	S_REG	 x3, REG_LEN*1(sp)
	S_REG	 x4, REG_LEN*2(sp)
	S_REG	 x5, REG_LEN*3(sp)
	S_REG	 x6, REG_LEN*4(sp)
	S_REG	 x7, REG_LEN*5(sp)
	S_REG	 x8, REG_LEN*6(sp)
	S_REG	 x9, REG_LEN*7(sp)
	S_REG	x10, REG_LEN*8(sp)
	S_REG	x11, REG_LEN*9(sp)
	S_REG	x12, REG_LEN*10(sp)
	S_REG	x13, REG_LEN*11(sp)
	S_REG	x14, REG_LEN*12(sp)
	S_REG	x15, REG_LEN*13(sp)
	S_REG	x16, REG_LEN*14(sp)
	S_REG	x17, REG_LEN*15(sp)
	S_REG	x18, REG_LEN*16(sp)
	S_REG	x19, REG_LEN*17(sp)
	S_REG	x20, REG_LEN*18(sp)
	S_REG	x21, REG_LEN*19(sp)
	S_REG	x22, REG_LEN*20(sp)
	S_REG	x23, REG_LEN*21(sp)
	S_REG	x24, REG_LEN*22(sp)
	S_REG	x25, REG_LEN*23(sp)
	S_REG	x26, REG_LEN*24(sp)
	S_REG	x27, REG_LEN*25(sp)
	S_REG	x28, REG_LEN*26(sp)
	S_REG	x29, REG_LEN*27(sp)
	S_REG	x30, REG_LEN*28(sp)
	S_REG	x31, REG_LEN*29(sp)

	call	exc_handler

	L_REG	 x1, REG_LEN*0(sp)
	L_REG	 x3, REG_LEN*1(sp)
	L_REG	 x4, REG_LEN*2(sp)
	L_REG	 x5, REG_LEN*3(sp)
	L_REG	 x6, REG_LEN*4(sp)
	L_REG	 x7, REG_LEN*5(sp)
	L_REG	 x8, REG_LEN*6(sp)
	L_REG	 x9, REG_LEN*7(sp)
	L_REG	x10, REG_LEN*8(sp)
	L_REG	x11, REG_LEN*9(sp)
	L_REG	x12, REG_LEN*10(sp)
	L_REG	x13, REG_LEN*11(sp)
	L_REG	x14, REG_LEN*12(sp)
	L_REG	x15, REG_LEN*13(sp)
	L_REG	x16, REG_LEN*14(sp)
	L_REG	x17, REG_LEN*15(sp)
	L_REG	x18, REG_LEN*16(sp)
	L_REG	x19, REG_LEN*17(sp)
	L_REG	x20, REG_LEN*18(sp)
	L_REG	x21, REG_LEN*19(sp)
	L_REG	x22, REG_LEN*20(sp)
	L_REG	x23, REG_LEN*21(sp)
	L_REG	x24, REG_LEN*22(sp)
	L_REG	x25, REG_LEN*23(sp)
	L_REG	x26, REG_LEN*24(sp)
	L_REG	x27, REG_LEN*25(sp)
	L_REG	x28, REG_LEN*26(sp)
	L_REG	x29, REG_LEN*27(sp)
	L_REG	x30, REG_LEN*28(sp)
	L_REG	x31, REG_LEN*29(sp)
	addi	sp, sp, REG_LEN*30
	mret


	.comm	_stack_bottom, 4096, 16
_stack_top:
