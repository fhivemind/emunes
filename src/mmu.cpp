#include <type_traits>

#include "mmu.h"
#include "cpu.h"
#include "ppu.h"

MMU::MMU()
{
}

MMU::~MMU()
{
}

template<>
u8 MMU::read<CPU>(u16 addr)
{
	u8 data{ 0 };
	if (cartridge->read<CPU>(addr, data)) {}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		data = ROM[addr & 0x07FF];
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		// PPU to CPU Read
	}
	return data;
}

template<>
u8 MMU::read<PPU>(u16 addr)
{
	u8 data{ 0 };
	addr &= 0x3FFF;
	cartridge->read<PPU>(addr, data);
	return data;
}

template<>
void MMU::write<CPU>(u16 addr, u8 data)
{
	if (cartridge->write<CPU>(addr, data)) {}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		ROM[addr & 0x07FF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		// PPU to CPU Write
	}
}

template<>
void MMU::write<PPU>(u16 addr, u8 data)
{
	addr &= 0x3FFF;
	cartridge->write<PPU>(addr, data);
}

inline void MMU::connectCartridge(Cartridge* _cartridge)
{
	cartridge = _cartridge;
}
