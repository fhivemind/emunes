#include "mapper_000.h"
#include "cpu.h"
#include "ppu.h"

// Default IO flow
bool Mapper_000::cpuRead(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		mapped_addr = addr & (prgBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::cpuWrite(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		mapped_addr = addr & (prgBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::ppuRead(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		mapped_addr = addr;
		return true;
	}
	return false;
}

bool Mapper_000::ppuWrite(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		mapped_addr = addr;
		return true;
	}
	return false;
}
