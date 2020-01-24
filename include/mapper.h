#pragma once
#include "core.h"

class Mapper
{
public:
	Mapper(u8 _prg, u8 _chr) : prgBanks(_prg),
							   chrBanks(_chr)
	{
	}
	~Mapper();

public:
	virtual bool read(u16, u32 &) = 0;
	virtual bool write(u16, u32 &) = 0;

protected:
	u8 prgBanks{0};
	u8 chrBanks{0};
};