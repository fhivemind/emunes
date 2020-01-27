#include "mapper.h"

// Top-level IO flow
template<typename T>
bool Mapper::read(u16 addr, u32& mapped_addr)
{
	if constexpr (std::is_same_v<T, CPU>) {
		return cpuRead(addr, mapped_addr);
	}
	else if constexpr (std::is_same_v<T, PPU>) {
		return ppuRead(addr, mapped_addr);
	}
	return false;
}

template<typename T>
bool Mapper::write(u16 addr, u32& mapped_addr)
{
	if constexpr (std::is_same_v<T, CPU>) {
		return cpuWrite(addr, data);
	}
	else if constexpr (std::is_same_v<T, PPU>) {
		return ppuWrite(addr, data);
	}
	return false;
}
