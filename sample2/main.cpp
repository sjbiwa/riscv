#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "csr.h"

#define	XS_MASK				(0x01ull << 13)
#define	MIE_MASK			(0x01ull << 3)
#define	MTIP_MASK			(0x01ull << 7)

#define	MTIME_REG			((volatile uint64_t*)0x0200BFF8)
#define	MTIMECMP_REG		((volatile uint64_t*)0x02004000)

extern void lprintf_init(void);
extern int tsprintf(char* buff,const char* fmt, ...);
extern int lprintf(const char* fmt, ...);

class MyClass {
public:
	MyClass() : a(100) { lprintf("0\n\r"); b = a + 100; }
	void exec() { a = a * 10; }

	int a;
	int b;
};

class MyClass1 {
public:
	MyClass1() : a(100) { lprintf("1\n\r"); b = a + 100; }
	void exec() { a = a * 10; }

	int a;
	int b;
};

class MyClass2 {
public:
	MyClass2() : a(100) { lprintf("2\n\r"); b = a + 100; }
	void exec() { a = a * 10; }

	int a;
	int b;
};

class MyClass3 {
public:
	MyClass3() : a(100) { lprintf("3\n\r"); b = a + 100; }
	void exec() { a = a * 10; }

	int a;
	int b;
};

MyClass aaa;
MyClass1 bbb;
MyClass2 ccc;
MyClass3 ddd;


char msg[16000] = {1,2,3,4,5};

char buff[] = {0x30, 0x31, 0x32, 0x33};

static uint32_t s_intr_count = 0;

volatile uint64_t s_total_count = 0;

static double fvalue = 0.0f;

static void irq_enable()
{
	_CSRS(mstatus, MIE_MASK);
}

static void irq_disable()
{
	_CSRC(mstatus, MIE_MASK);
}

int main()
{
	lprintf("%02X %02X %02X %02X\n\r", buff[0], buff[1], buff[2], buff[3]);
	lprintf("%02X %02X %02X %02X\n\r", aaa.a, bbb.a, ccc.a, ddd.a);
	
	_CSRW(mstatus, 0);
	_CSRW(medeleg, 0);
	_CSRW(mideleg, 0);
	_CSRW(mie, 0);
	
	_CSRW(mscratch, 0);
	_CSRW(mepc, 0);
	_CSRW(mtval, 0);
	_CSRW(mcause, 0);
	_CSRW(mip, 0);

	*MTIMECMP_REG = 0;
	_CSRW(mstatus, XS_MASK);
	_CSRW(fcsr, 0);
	_CSRW(mie, MTIP_MASK);
	irq_enable();
	
	for (;;) {
		s_total_count++;
		fvalue += 13.24f + (s_total_count % 6345) * 3;
		irq_disable();
		uint64_t value = uint64_t(fvalue);
		lprintf("F:%04X%04X\n\r", uint32_t(value >> 32), uint32_t(value));
		irq_enable();
	}
	return 0;
}


extern "C" {
CSRREGTYPE handle_trap(CSRREGTYPE mcause, CSRREGTYPE mepc, CSRREGTYPE sp)
{
	s_intr_count++;
	*MTIMECMP_REG = s_intr_count * 0x40000ull;
	
	uint64_t value;
	if ( false ) {
		value = mepc;
		lprintf("MEPC:%08X%08X\n\r", uint32_t(value >> 32), uint32_t(value));
		value = mcause;
		lprintf("MCAUSE:%08X%08X\n\r", uint32_t(value >> 32), uint32_t(value));
	}
	value = *MTIME_REG;
	lprintf("TIMER:%08X%08X\n\r", uint32_t(value >> 32), uint32_t(value));
	value = s_total_count;
	lprintf("TOTAL:%08X%08X\n\r", uint32_t(value >> 32), uint32_t(value));
	value = uint64_t(fvalue);
	lprintf("FVALUE:%08X%08X\n\r", uint32_t(value >> 32), uint32_t(value));
	
	return mepc;
}
}
