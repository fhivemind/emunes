#pragma once
#include "core.h"
#include "mmu.h"

class PPU
{
public:
	PPU() = delete;
	PPU(MMU *);
	~PPU();

public:
	u8 read(u16, bool _ = false);
	void write(u16, u8);

};

