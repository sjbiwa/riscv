	.file	"handler.c"
	.option nopic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.comm	buff,1024,8
	.align	2
	.globl	static_init
	.type	static_init, @function
static_init:
.LFB0:
	.file 1 "handler.c"
	.loc 1 11 0
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
.LBB2:
	.loc 1 12 0
	lla	a5,__init_array_start
	ld	a5,0(a5)
	sd	a5,-24(s0)
	j	.L2
.L3:
	.loc 1 13 0 discriminator 3
	ld	a5,-24(s0)
	ld	a5,0(a5)
	jalr	a5
.LVL0:
	.loc 1 12 0 discriminator 3
	ld	a5,-24(s0)
	addi	a5,a5,8
	sd	a5,-24(s0)
.L2:
	.loc 1 12 0 is_stmt 0 discriminator 1
	lla	a5,__init_array_end
	ld	a5,0(a5)
	ld	a4,-24(s0)
	bltu	a4,a5,.L3
.LBE2:
	.loc 1 14 0 is_stmt 1
	nop
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	addi	sp,sp,32
	.cfi_def_cfa_register 2
	jr	ra
	.cfi_endproc
.LFE0:
	.size	static_init, .-static_init
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xbf
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.byte	0x1
	.4byte	.LASF5
	.byte	0xc
	.4byte	.LASF6
	.4byte	.LASF7
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x2
	.4byte	0x34
	.byte	0x3
	.byte	0
	.byte	0x4
	.4byte	.LASF0
	.byte	0x1
	.byte	0x5
	.4byte	0x3f
	.byte	0x5
	.byte	0x8
	.4byte	0x45
	.byte	0x5
	.byte	0x8
	.4byte	0x2d
	.byte	0x4
	.4byte	.LASF1
	.byte	0x1
	.byte	0x6
	.4byte	0x3f
	.byte	0x6
	.4byte	0x6e
	.4byte	0x67
	.byte	0x7
	.4byte	0x67
	.2byte	0x3ff
	.byte	0
	.byte	0x8
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.byte	0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.byte	0x9
	.4byte	.LASF4
	.byte	0x1
	.byte	0x8
	.4byte	0x56
	.byte	0x9
	.byte	0x3
	.8byte	buff
	.byte	0xa
	.4byte	.LASF8
	.byte	0x1
	.byte	0xa
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.byte	0xb
	.8byte	.LBB2
	.8byte	.LBE2-.LBB2
	.byte	0xc
	.string	"p"
	.byte	0x1
	.byte	0xc
	.4byte	0x3f
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x15
	.byte	0x1
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0x19
	.byte	0x3c
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0x19
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF2:
	.string	"long unsigned int"
.LASF6:
	.string	"handler.c"
.LASF5:
	.string	"GNU C11 7.2.0 -mcmodel=medany -mabi=lp64f -march=rv64imf -mno-small-data-limit= 0 -ggdb"
.LASF0:
	.string	"__init_array_start"
.LASF1:
	.string	"__init_array_end"
.LASF4:
	.string	"buff"
.LASF7:
	.string	"C:\\cygwin64\\home\\biwa\\workspace\\riscv\\sample"
.LASF3:
	.string	"char"
.LASF8:
	.string	"static_init"
	.ident	"GCC: (GNU MCU Eclipse RISC-V Embedded GCC, 64-bits) 7.2.0"
