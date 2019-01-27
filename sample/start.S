	.option nopic
	.text
	.align	2
	.globl	_start
	.type	_start, @function
_start:
	lla		sp, _sp_end

	lla		a0, __bss_start
	lla		a1, _end

	bgeu	a0, a1, 2f
1:
	sw		zero, (a0)
	addi	a0, a0, 4
	bltu	a0, a1, 1b
2:
	/* sttaic initializer */
	call	static_init
	
	call	main
	j		.
	
	.bss
	.comm _sp_top, 1024
	.comm _sp_end, 4
	
