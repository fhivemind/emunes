#pragma once
#include <array>

#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"
#include "core.h"

class Bus
{
public:
	Bus();
	~Bus();

public:
	// Data
	CPU cpu;
	PPU ppu;
	Cartridge* cartridge;
	u8  ram[2048] = { 0 };

public:
	// NES Control
	void connectCartridge(Cartridge*);
	void reset();
	void clock();

	// IO controllers
	template <typename T>
	void write(u16, u8);
	template <typename T>
	u8   read(u16, bool _ = false);

private:
	// Clock counter
	u32 clockCounter{ 0 };

	// Memory bounds
	u16 addr_low{ 0x0000 };
	u16 addr_high{ 0xFFFF };

	// Verify memory range
	inline void checkMemRange(u16);
};