#include <type_traits>

#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"
#include "mapper_000.h"

Cartridge::Cartridge(const std::string& fileName)
{
	// iNES Format Header
	struct sHeader
	{
		char name[4];
		u8 prg_rom_chunks;
		u8 chr_rom_chunks;
		u8 mapper1;
		u8 mapper2;
		u8 prg_ram_size;
		u8 tv_system1;
		u8 tv_system2;
		char unused[5];
	} header;

	// Initial
	validImage = false;

	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::binary);

	if (ifs.is_open())
	{
		// Read file
		ifs.read((char*)&header, sizeof(sHeader));

		// Skip first 512 places
		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		// Load data
		mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror	 = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;
		prgBanks = header.prg_rom_chunks;
		chrBanks = header.chr_rom_chunks;

		prgROM.resize(prgBanks * 16 * 1024);
		chrROM.resize(chrBanks * 8 * 1024);

		// Load ROM
		ifs.read((char*)prgROM.data(), prgROM.size());
		ifs.read((char*)chrROM.data(), chrROM.size());

		// Load appropriate mapper
		switch (mapperID)
		{
			case 0: mapper = std::make_shared<Mapper_000>(prgBanks, chrBanks); break;
		}

		validImage = true;
		ifs.close();
	}
}

Cartridge::~Cartridge()
{
}

template<>
bool Cartridge::read<CPU>(u16 addr, u8& data)
{
	u32 mapped_addr{ 0 };
	if (mapper->cpuRead(addr, mapped_addr)) {
		data = prgROM.at(mapped_addr);
		return true;
	}
	return false;
}

template<>
bool Cartridge::read<PPU>(u16 addr, u8& data)
{
	u32 mapped_addr{ 0 };
	if (mapper->ppuRead(addr, mapped_addr)) {
		data = chrROM.at(mapped_addr);
		return true;
	}
	return false;
}

template<>
bool Cartridge::write<CPU>(u16 addr, u8 data)
{
	u32 mapped_addr{ 0 };
	if (mapper->cpuWrite(addr, mapped_addr)) {
		prgROM[mapped_addr] = data;
		return true;
	}
	return false;
}

template<>
bool Cartridge::write<PPU>(u16 addr, u8 data)
{
	u32 mapped_addr{ 0 };
	if (mapper->ppuWrite(addr, mapped_addr)) {
		chrROM[mapped_addr] = data;
		return true;
	}
	return false;
}