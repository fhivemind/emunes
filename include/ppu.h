#pragma once
#include "core.h"

class PPU
{
public:
	PPU();
	~PPU();
public:
	template <typename T>
	u8 read(u16, bool readOnly = false);
	template <typename T>
	void write(u16, u8);
};

