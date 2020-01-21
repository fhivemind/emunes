#include "bus.h"
#include <stdexcept>

// ============================================ CTORS

// Initialize with components
Bus::Bus()
{
	cpu.connectBus(this);
}

Bus::~Bus() {}

// ============================================ MEM CONTROL

// Write to memory
template <typename T>
void Bus::write(u16 addr, u8 data)
{
	checkMemRange(addr);
	ram[addr] = data;
}

// Read from memory
template <typename T>
u8 Bus::read(u16 addr, bool readOnly)
{
	checkMemRange(addr);
	return ram[addr];
}

// ============================================ BOUNDS

void Bus::checkMemRange(u16 addr)
{
	if (addr < addr_low && addr > addr_high)
		throw std::out_of_range("Memory address out of range");
}