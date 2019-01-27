/*
 * PortDefs.h
 *
 */

#ifndef RISCV_PORTDEFS_H_
#define RISCV_PORTDEFS_H_

/* CLINT */
static const uint64_t MTIMECMP = 0x02004000;
static const uint64_t MTIME = 0x0200BFF8;

/* PLIC */
static const uint64_t PLIC_PRIORITY = 0x0C000000;
static const uint64_t PLIC_PENDING = 0x0C001000;
static const uint64_t PLIC_ENABLE = 0x0C002000;
static const uint64_t PLIC_THRESHOLD = 0x0c200000;
static const uint64_t PLIC_CLAIM = 0x0c200004;
static const uint64_t PLIC_COMPLETE = 0x0c200004;
	
#endif /* RISCV_PORTDEFS_H_ */
