/*
 * PLICMgr.cpp
 *
 */

#include "PLICMgr.h"


extern "C" {
CSRREGTYPE handle_trap(CSRREGTYPE mcause, CSRREGTYPE mepc, CSRREGTYPE sp)
{
	PLICMgr::handlerStub(mcause, mepc, sp);
	return mepc;
}
}

void PLICMgr::handlerStub(CSRREGTYPE code, CSRREGTYPE mepc, CSRREGTYPE sp)
{
	bool is_intr = ((mcause >> (sizeof(CSRREGTYPE) * 8 - 1)) & 1) ? true : false;
	if ( is_intr ) {
		CSRREGTYPE code = mcause & 0xffffu;
		if ( (code < ARRAYNUM(m_handler_tbl)) &&  (m_handler_tbl[code] != nullptr) ) {
			m_handler_tbl[code]();
		}
	}
}
