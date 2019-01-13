/*
 * IoPort.h
 *
 */

#ifndef RISCV_IOPORT_H_
#define RISCV_IOPORT_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

class IoPort {
public:
	static uint32_t read32(uint64_t addr);
	static uint64_t read64(uint64_t addr);
	static void write32(uint64_t addr, uint32_t value);
	static void write64(uint64_t addr, uint64_t value);

	static uint32_t read32(uint64_t addr, uint32_t idx);
	static uint64_t read64(uint64_t addr, uint32_t idx);
	static void write32(uint64_t addr, uint32_t idx, uint32_t value);
	static void write64(uint64_t addr, uint32_t idx, uint64_t value);

private:
	IoPort() {}
};

#endif /* RISCV_IOPORT_H_ */
