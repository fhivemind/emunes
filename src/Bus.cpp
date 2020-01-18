#include <stdexcept>

#include "Bus.h"
#include "core.h"

// ============================================ CTORS
Bus::Bus()
{
	cpu.connectBus(this);
}

Bus::~Bus() {}

// ============================================ MEM CONTROL
void Bus::write(u16 addr, u8 data)
{
	checkMemRange(addr);
	ram[addr] = data;
}

u8 Bus::read(u16 addr, bool readOnly = false)
{
	checkMemRange(addr);
	return ram[addr];
}

// ============================================ MEM BOUNDS
void Bus::checkMemRange(u16 addr) 
{
	if (addr < addr_low && addr > addr_high)
		throw std::out_of_range("Bus address out of range");
}