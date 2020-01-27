#pragma once
#include "mapper.h"
class Mapper_000 :
	public Mapper
{
public:
	Mapper_000(u8 _prg, u8 _chr) : Mapper(_prg, _chr) {}
	~Mapper_000();

public:
	bool cpuRead(u16, u32&) override;
	bool cpuWrite(u16, u32&) override;
	bool ppuRead(u16, u32&) override;
	bool ppuWrite(u16, u32&) override;

};
