#pragma once
#include "core.h"

class Mapper
{
public:
	Mapper() = delete;
	Mapper(u8 _prg, u8 _chr) : prgBanks(_prg),
							   chrBanks(_chr)
	{
	}
	~Mapper() {}

public:
	template <typename T>
	bool read(u16, u32&);
	template <typename T>
	bool write(u16, u32&);

public:
	virtual bool cpuRead(u16, u32&) = 0;
	virtual bool cpuWrite(u16, u32&) = 0;
	virtual bool ppuRead(u16, u32&) = 0;
	virtual bool ppuWrite(u16, u32&) = 0;

protected:
	u8 prgBanks{0};
	u8 chrBanks{0};
};