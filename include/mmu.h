#pragma once
#include "core.h"
#include "cartridge.h"

class MMU
{
public:
	MMU() {}
	~MMU();

public:
	u8 ROM[256] = {0};
	Cartridge *cartridge;

	template <typename T>
	u8 read(u16);
	template <typename T>
	void write(u16, u8);

	void connectCartridge(Cartridge*);
};
