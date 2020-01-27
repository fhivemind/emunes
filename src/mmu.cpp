#include "mmu.h"

MMU::MMU()
{
}

MMU::~MMU()
{
}

template<typename T>
inline u8 MMU::read(u16 addr)
{
	u8 data{ 0 };
	if constexpr (std::is_same_v<T, CPU>) {
		if (cartridge->read<CPU>(addr, data)) {}
		else if (addr >= 0x0000 && addr <= 0x1FFF)
		{
			data = ROM[addr & 0x07FF];
		}
		else if (addr >= 0x2000 && addr <= 0x3FFF)
		{
			// PPU to CPU Read
		}
	}
	else if constexpr (std::is_same_v<T, PPU>) {
		addr &= 0x3FFF;
		cartridge->read<PPU>(addr, data);
	}
	return data;
}

template<typename T>
inline void MMU::write(u16 addr, u8 data)
{
	if constexpr (std::is_same_v<T, CPU>) {
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
	else if constexpr (std::is_same_v<T, PPU>) {
		addr &= 0x3FFF;
		cartridge->write<PPU>(addr, data);
	}
}

inline void MMU::connectCartridge(Cartridge* _cartridge)
{
	cartridge = _cartridge;
}
