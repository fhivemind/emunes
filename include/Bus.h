#pragma once
#include <array>

#include "CPU.h"
#include "core.h"

class Bus
{
public:
	Bus();
	~Bus();

public:
	// Data
	CPU cpu;
	u8 ram[64 * 1024] = { 0 };

	// Memory controllers
	void write(u16, u8);
	u8 read(u16, bool readOnly = false);

private:
	// Memory bounds
	u16 addr_low{ 0x0000 };
	u16 addr_high{ 0xFFFF };

	// Verify memory range
	inline void checkMemRange(u16);
};