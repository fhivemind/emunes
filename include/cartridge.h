#pragma once
#include "core.h"
#include "mapper.h"

class Cartridge
{
public:
	Cartridge(Mapper *_) : mapper(_) {}
	~Cartridge();

private:
	u8 prgROM[16 * 1024] = {0};
	u8 chrROM[8 * 1024] = {0};

	Mapper *mapper;

public:
	template <typename T>
	bool read(u16, u8 &);

	template <typename T>
	bool write(u16, u8 &);
};