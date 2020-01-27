# emunes - C++ NES emulator
Hardware architecture implementation of Nintendo Entertainment System in C++. Hardly focused on clock-accurate and abstracted approach of the components.

## Contents
* Design
* Memory mapping
    * CPU Memory Map
    * PPU Memory Map
* iNES File Format
* Build
* Test
* References

---

## Design
This will be updated on-the-go.

## Memory mapping
#### CPU Memory Map
```
--------------------------------------- $10000
 Upper Bank of Cartridge ROM
--------------------------------------- $C000
 Lower Bank of Cartridge ROM
--------------------------------------- $8000
 Cartridge RAM (may be battery-backed)
--------------------------------------- $6000
 Expansion Modules
--------------------------------------- $5000
 Input/Output
--------------------------------------- $2000
 2kB Internal RAM, mirrored 4 times
--------------------------------------- $0000
```
#### PPU Memory Map
```
--------------------------------------- $4000
 Empty
--------------------------------------- $3F20
 Sprite Palette
--------------------------------------- $3F10
 Image Palette
--------------------------------------- $3F00
 Empty
--------------------------------------- $3000
 Attribute Table 3
--------------------------------------- $2FC0
 Name Table 3 (32x30 tiles)
--------------------------------------- $2C00
 Attribute Table 2
--------------------------------------- $2BC0
 Name Table 2 (32x30 tiles)
--------------------------------------- $2800
 Attribute Table 1
--------------------------------------- $27C0
 Name Table 1 (32x30 tiles)
--------------------------------------- $2400
 Attribute Table 0
--------------------------------------- $23C0
 Name Table 0 (32x30 tiles)
--------------------------------------- $2000
 Pattern Table 1 (256x2x8, may be VROM)
--------------------------------------- $1000
 Pattern Table 0 (256x2x8, may be VROM)
--------------------------------------- $0000
```
### iNES File Format
Specifies how to read the iNES files.
```
Byte     Contents
---------------------------------------------------------------------------
0-3      String "NES^Z" used to recognize .NES files.
4        Number of 16kB ROM banks.
5        Number of 8kB VROM banks.
6        bit 0     1 for vertical mirroring, 0 for horizontal mirroring.
         bit 1     1 for battery-backed RAM at $6000-$7FFF.
         bit 2     1 for a 512-byte trainer at $7000-$71FF.
         bit 3     1 for a four-screen VRAM layout. 
         bit 4-7   Four lower bits of ROM Mapper Type.
7        bit 0     1 for VS-System cartridges.
         bit 1-3   Reserved, must be zeroes!
         bit 4-7   Four higher bits of ROM Mapper Type.
8        Number of 8kB RAM banks. For compatibility with the previous
         versions of the .NES format, assume 1x8kB RAM page when this
         byte is zero.
9        bit 0     1 for PAL cartridges, otherwise assume NTSC.
         bit 1-7   Reserved, must be zeroes!
10-15    Reserved, must be zeroes!
16-...   ROM banks, in ascending order. If a trainer is present, its
         512 bytes precede the ROM bank contents.
...-EOF  VROM banks, in ascending order.
---------------------------------------------------------------------------
```

## Build
Before you proceed, make sure to have **GNU Make 4.1** installed, along with required **cpp14** packages. To build, simply run:
```
make clean  # to clean-up previous build steps, if existing 
make        # to build executables
```

## Test
Such empty... for now.

## References
  * [Nintendo Entertainment System Architecture](https://fms.komkon.org/EMUL8/NES.html)
  * [Rockwell r650x](http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf/)
  * [NTSC 2C02 technical reference](http://nesdev.com/2C02%20technical%20reference.TXT)
  * [olcNES](https://github.com/OneLoneCoder/olcNES/)

---

**Author**: [Ramiz Polic](https://github.com/fhivemind)  
**Version**: much alpha
