/*
 * PLICMgr.h
 * 
 */

#ifndef RISCV_PLICMGR_H_
#define RISCV_PLICMGR_H_

class PLICMgr {
public:
	typedef	void (*PLICHandler)();
	
	static void registerHandler(uint32_t intno, PLICHandler handler);
	
	
	static void handlerStub(CSRREGTYPE mcause, CSRREGTYPE mepc, CSRREGTYPE sp);
	
private:
	static PLICHandler m_handler_tbl[64];
	
	PLICMgr();
};

#endif /* RISCV_PLICMGR_H_ */
