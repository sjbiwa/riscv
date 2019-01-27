#include "csr.h"

typedef	uint64_t	RegType;

extern void _exc_handler(void);

static const void (*exc_tbl[32])(void) = {
	_exc_handler
};

int main()
{
	uint32_t value = 0x1000;

	_CSRRW(mstatus,value);
	_CSRRS(mstatus,value);
	_CSRRC(mstatus,value);
	_CSRRWI(mstatus,0b00111);
	_CSRRSI(mstatus,0x10);
	_CSRRCI(mstatus,0);

	_CSRR(mstatus);
	_CSRW(mstatus,value);
	_CSRS(mstatus,value);
	_CSRC(mstatus,value);
	_CSRWI(mstatus,0b11111);
	_CSRSI(mstatus,0b00111);
	_CSRCI(mstatus,0x011);

	
	_CSRW(mstatus, 0);
	_CSRW(mip, 0);
	_CSRW(mie, 0);
	_CSRW(mtvec, exc_tbl);

	return _CSRR(mstatus) + _CSRR(mstatus);

	return 0;
}


RegType epc;
RegType cause;

void exc_handler(void)
{
	epc = _CSRR(mepc);
	cause = _CSRR(mcause); 
}

