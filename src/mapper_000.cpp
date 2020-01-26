#include "mapper_000.h"
#include "cpu.h"
#include "ppu.h"

// Top-level IO flow
template<typename T>
bool Mapper_000::read(u16 addr, u32& data)
{
	if constexpr (std::is_same_v<T, CPU>) {
		return cpuRead(addr, data);
	}
	else if constexpr (std::is_same_v<T, PPU>) {
		return ppuRead(addr, data);
	}
	return false;
}

template<typename T>
bool Mapper_000::write(u16 addr, u32 data)
{
	if constexpr (std::is_same_v<T, CPU>) {
		return cpuWrite(addr, data);
	}
	else if constexpr (std::is_same_v<T, PPU>) {
		return ppuWrite(addr, data);
	}
	return false;
}

// Default IO flow
bool Mapper_000::cpuRead(u16, u32&)
{
	return false;
}

bool Mapper_000::cpuWrite(u16, u32)
{
	return false;
}

bool Mapper_000::ppuRead(u16, u32&)
{
	return false;
}

bool Mapper_000::ppuWrite(u16, u32)
{
	return false;
}
