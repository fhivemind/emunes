#pragma once
#include <string>
#include <fstream>
#include <vector>

#include "core.h"
#include "mapper.h"

class Cartridge
{
public:
	Cartridge(const std::string&);
	~Cartridge();

	enum MIRROR
	{
		HORIZONTAL = 0,
		VERTICAL,
		ONESCREEN_LOW,
		ONESCREEN_HIGH,
	} mirror = MIRROR::HORIZONTAL;

private:
	bool validImage{ false };

	u8 mapperID{ 0 };
	u8 prgBanks{ 0 };
	u8 chrBanks{ 0 };

	std::vector<u8> prgROM;
	std::vector<u8> chrROM;

	Mapper *mapper;

public:
	inline bool imageValid() { return validImage; }

	template <typename T>
	bool read(u16, u8 &);

	template <typename T>
	bool write(u16, u8 &);
};