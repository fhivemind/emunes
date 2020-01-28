#include <type_traits>

#include "mapper.h"
#include "cpu.h"
#include "ppu.h"

// Top-level IO flow
template<typename T>
bool Mapper::read(u16 addr, u32& mapped_addr)
{
	if (std::is_same<T, CPU>::value) {
		return cpuRead(addr, mapped_addr);
	}
	else if (std::is_same<T, PPU>::value) {
		return ppuRead(addr, mapped_addr);
	}
	return false;
}

template<typename T>
bool Mapper::write(u16 addr, u32& mapped_addr)
{
	if (std::is_same<T, CPU>::value) {
		return cpuWrite(addr, mapped_addr);
	}
	else if (std::is_same<T, PPU>::value) {
		return ppuWrite(addr, mapped_addr);
	}
	return false;
}
