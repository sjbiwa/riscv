/*
 * IoPort.cpp
 *
 */

#include "IoPort.h"

uint32_t IoPort::read32(uint64_t addr)
{
	return *reinterpret_cast<volatile uint32_t*>(addr);
}

uint64_t IoPort::read64(uint64_t addr)
{
	return *reinterpret_cast<volatile uint64_t*>(addr);
}

void IoPort::write32(uint64_t addr, uint32_t value)
{
	*reinterpret_cast<volatile uint32_t*>(addr) = value;
}

void IoPort::write64(uint64_t addr, uint64_t value)
{
	*reinterpret_cast<volatile uint64_t*>(addr) = value;
}

uint32_t IoPort::read32(uint64_t addr, uint32_t idx)
{
	return read32(addr + sizeof(uint32_t) * idx);
}

uint64_t IoPort::read64(uint64_t addr, uint32_t idx)
{
	return read64(addr + sizeof(uint64_t) * idx);
}

void IoPort::write32(uint64_t addr, uint32_t idx, uint32_t value)
{
	write32(addr + sizeof(uint32_t) * idx, value);
}

void IoPort::write64(uint64_t addr, uint32_t idx, uint64_t value)
{
	write64(addr + sizeof(uint64_t) * idx, value);
}

