#define	L_REG	ld
#define	S_REG	sd
#define	REG_LEN	8

	.option nopic
	.text
	.align	1

	.globl	_func_sample
	.type	_func_sample, @function
_func_sample:
// 命令フォーマットは４種類
// R type:(register type?) レジスタのみを使用 3オペランド  add x1, x2, x3など
// I type:(immidiate type?) 12bit即値と2個のレジスタ       add x1, x2, #100 / lw x1, 100(x2) など
// S type: (save type?) Iと同様に12bit即値と2個のレジスタ ただし定義位置が違う  sw x1, 100(x2)など compare-and-branch命令も含まれる
// U type: (upper type?) 20bit即値と1個のレジスタ (LUIとかAUIPCとか？ 直接は使わないかも。li/la疑似命令とか)

	la		a0, _data_buff			// 疑似命令
	li		a1, 0x43216543			// 疑似命令
	call	_func					// 疑似命令
	
	// 条件分岐命令は ビットアサインが特殊(オフセット値のビットが命令上は不連続)
	beq		a3, a4, 1f				// S-type 2-reg + imm
1:
	bne		s0, s1, 1f				// S-type 2-reg + imm
1:
	blt		t0, t1, 1f				// S-type 2-reg + imm
1:
	bge		s10, s11, 1f			// S-type 2-reg + imm
1:
	bltu	s0, s10, 1f				// S-type 2-reg + imm
1:
	bgeu	t0, t6, 1f				// S-type
1:
	ble		t0, t6, 1f				// S-type
1:
	ble		t0, t6, 1f				// S-type
1:
	lb		a6, 256(x1)				// I-type
	lh		a5, -100(x1)			// I-type
	lw		a4, 1000(x3)			// I-type
	ld		a3, 2000(x4)			// I-type

	lbu		a0, 100(x3)				// I-type
	lhu		a0, 100(x3)				// I-type
	
	sb		s0, -100(a0)			// S-type  imm (7:5それぞれを連続に確保 BRUNCH命令と違う */
	sh		s0, -200(a1)			// S-type
	sw		a0, 128(x0)				// S-type
	sd		a0, -1000(x2)			// S-type

	// I-type形式
	// 算術演算
	addi	a0, a1, -200			// I-type
	slti	t0, t1, 1				// I-type Set LessThan , IF t1 < imm (signed ext)
	sltiu	t0, t1, 10				// I-type Set LessThan, IF t1 < imm (unsigned)
	// 論理演算
	xori	a0, a1, 0x100			// I-type
	ori		t0, a2, 0x20			// I-type
	andi	a2, a4, 0xfe			// I-type
	// シフト命令
	slli	a0, a1, 10				// I-type Shift Left Logical / immidiaate
	srli	a0, a1, 20				// I-type Shift Right Logical / immidiate
	srai	a0, a1, 30				// I-type Shift Right Arithmetic /immidiate

	// R-type形式
	add		a0, a1, a3				// R-type
	sub		a0, a1, a3				// R-type
	slt		a0, a1, a3				// R-type Set less than
	sltu	a0, s0, s1				// R-type Set Less than unsigned
	
	xor		t0, t1, t2				// R-type
	or		t0, t1, t2				// R-tpye
	and		t0, t1, t2				// R-type
	
	sll		a0, a1, a2				// R-type Shift Left Logical
	srl		t0, t1, t2				// R-type Shift Right Logical
	sra		t0, t1, t2				// R-type Shift Right Arithmetic

	// 特殊
	fence
	fence.i	#10
	ecall
	ebreak
	
	csrrw	t0, mstatus, t1
	csrrs	t0, mstatus, t1
	csrrc	t0, mstatus, t1
	csrrwi	t0, mstatus, 10
	csrrsi	t0, mstatus, 10
	csrrci	t0, mstatus, 10


	// RV64I
	lwu		t0, 10(t1)				// I-type Zero-extended 32bit Load
	addiw	t0, t1, 1000			// I-type Add Sign-extended imm and t1(sign-extended 32bit->64bit), result 32bit sign-extended
	slliw	t0, t1, 10				// I-type 32bit shift Left Logical and sign extended
	srliw	t0, t1, 20				// I-type Shift Right Right Logical and sign-extended
	sraiw	t0, t1, 10				// I-type Shift Right Arithmetic and sign-extended
	addw	t0, t1, t2				// I-type Add Sign-extended imm and t1(sign-extended 32bit->64bit), result 32bit sign-extended
	sllw	t0, t1, t2				// I-type 32bit shift Left Logical and sign extended
	srlw	t0, t1, t2				// I-type Shift Right Right Logical and sign-extended
	sraw	t0, t1, t2				// I-type Shift Right Arithmetic and sign-extended
	
	// atomic
	lr.w	a1, (a2)
	sc.w	a0, a1, (a2)
	lr.d	a1, (a2)
	sc.d	a0, a1, (a2)
	
	
	// 疑似命令でよく使いそうなもの
	j		_func					// jump
	call	_func					// call subroutin
	ret								// return from subroutin
	li		x0, 0x121212			// load immidiate
	la		x0, _func				// load address
	
_func:
	ret

_data_buff:
