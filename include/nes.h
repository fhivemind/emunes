#pragma once
#include <array>

#include "core.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "cartridge.h"

class NES
{
public:
	NES();
	~NES();

public:
	// Data
	CPU cpu;
	PPU ppu;
	MMU mmu;
	Cartridge *cartridge;

public:
	// NES Control
	void connectCartridge(Cartridge *);
	void reset();
	void clock();

private:
	// Clock counter
	u32 clockCounter{0};
};