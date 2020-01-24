#pragma once
#include "core.h"
#include "cartridge.h"

class MMU
{
public:
	MMU(Cartridge *_) : cartridge(_) {}
	~MMU();

public:
	Cartridge *cartridge;

	template <typename T>
	u8 read(u16);

	template <typename T>
	void write(u16, u8);
};
