#pragma once
#include "core.h"
#include "cartridge.h"

class MMU
{
private:
	// CPU related
	u8 ROM[256] = { 0 };

	// PPU related
	u8 PatternTable[2][2048];
	u8 NameTable[2][1024];
	u8 PaletteTable[32];

	// Cartridge related
	Cartridge* cartridge;

public:
	MMU() {}
	~MMU();

public:
	template <typename T>
	u8 read(u16);
	template <typename T>
	void write(u16, u8);
	inline void connectCartridge(Cartridge*);

};