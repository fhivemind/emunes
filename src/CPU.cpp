#include "cpu.h"
#include "mmu.h"

// ============================================ CTORS

CPU::CPU(MMU *_) : mmu(_)
{
	for (int i = 0; i < 256; i++)
		instrTable[i] = {INSTRUCTION{"NON", &CPU::NON, &CPU::IMP, 2}};

	/* INSTRUCTIONs */
	instrTable[0x00] = INSTRUCTION{"BRK impl", &CPU::BRK, &CPU::IMP, 7};
	instrTable[0x01] = INSTRUCTION{"ORA X,ind", &CPU::ORA, &CPU::IZX, 6};
	instrTable[0x05] = INSTRUCTION{"ORA zpg", &CPU::ORA, &CPU::ZP0, 3};
	instrTable[0x06] = INSTRUCTION{"ASL zpg", &CPU::ASL, &CPU::ZP0, 5};
	instrTable[0x08] = INSTRUCTION{"PHP impl", &CPU::PHP, &CPU::IMP, 3};
	instrTable[0x09] = INSTRUCTION{"ORA #", &CPU::ORA, &CPU::IMM, 2};
	instrTable[0x0A] = INSTRUCTION{"ASL A", &CPU::ASL, &CPU::IMP, 2};
	instrTable[0x0D] = INSTRUCTION{"ORA abs", &CPU::ORA, &CPU::ABS, 4};
	instrTable[0x0E] = INSTRUCTION{"ASL abs", &CPU::ASL, &CPU::ABS, 6};
	instrTable[0x10] = INSTRUCTION{"BPL rel", &CPU::BPL, &CPU::REL, 2};
	instrTable[0x11] = INSTRUCTION{"ORA ind,Y", &CPU::ORA, &CPU::IZY, 5};
	instrTable[0x15] = INSTRUCTION{"ORA zpg,X", &CPU::ORA, &CPU::ZPX, 4};
	instrTable[0x16] = INSTRUCTION{"ASL zpg,X", &CPU::ASL, &CPU::ZPX, 6};
	instrTable[0x18] = INSTRUCTION{"CLC impl", &CPU::CLC, &CPU::IMP, 2};
	instrTable[0x19] = INSTRUCTION{"ORA abs,Y", &CPU::ORA, &CPU::ABY, 4};
	instrTable[0x1D] = INSTRUCTION{"ORA abs,X", &CPU::ORA, &CPU::ABX, 4};
	instrTable[0x1E] = INSTRUCTION{"ASL abs,X", &CPU::ASL, &CPU::ABX, 7};
	instrTable[0x20] = INSTRUCTION{"JSR abs", &CPU::JSR, &CPU::ABS, 6};
	instrTable[0x21] = INSTRUCTION{"AND X,ind", &CPU::AND, &CPU::IZX, 6};
	instrTable[0x24] = INSTRUCTION{"BIT zpg", &CPU::BIT, &CPU::ZP0, 3};
	instrTable[0x25] = INSTRUCTION{"AND zpg", &CPU::AND, &CPU::ZP0, 3};
	instrTable[0x26] = INSTRUCTION{"ROL zpg", &CPU::ROL, &CPU::ZP0, 5};
	instrTable[0x28] = INSTRUCTION{"PLP impl", &CPU::PLP, &CPU::IMP, 4};
	instrTable[0x29] = INSTRUCTION{"AND #", &CPU::AND, &CPU::IMM, 2};
	instrTable[0x2A] = INSTRUCTION{"ROL A", &CPU::ROL, &CPU::IMP, 2};
	instrTable[0x2C] = INSTRUCTION{"BIT abs", &CPU::BIT, &CPU::ABS, 4};
	instrTable[0x2D] = INSTRUCTION{"AND abs", &CPU::AND, &CPU::ABS, 4};
	instrTable[0x2E] = INSTRUCTION{"ROL abs", &CPU::ROL, &CPU::ABS, 6};
	instrTable[0x30] = INSTRUCTION{"BMI rel", &CPU::BMI, &CPU::REL, 2};
	instrTable[0x31] = INSTRUCTION{"AND ind,Y", &CPU::AND, &CPU::IZY, 5};
	instrTable[0x35] = INSTRUCTION{"AND zpg,X", &CPU::AND, &CPU::ZPX, 4};
	instrTable[0x36] = INSTRUCTION{"ROL zpg,X", &CPU::ROL, &CPU::ZPX, 6};
	instrTable[0x38] = INSTRUCTION{"SEC impl", &CPU::SEC, &CPU::IMP, 2};
	instrTable[0x39] = INSTRUCTION{"AND abs,Y", &CPU::AND, &CPU::ABY, 4};
	instrTable[0x3D] = INSTRUCTION{"AND abs,X", &CPU::AND, &CPU::ABX, 4};
	instrTable[0x3E] = INSTRUCTION{"ROL abs,X", &CPU::ROL, &CPU::ABX, 7};
	instrTable[0x40] = INSTRUCTION{"RTI impl", &CPU::RTI, &CPU::IMP, 6};
	instrTable[0x41] = INSTRUCTION{"EOR X,ind", &CPU::EOR, &CPU::IZX, 6};
	instrTable[0x45] = INSTRUCTION{"EOR zpg", &CPU::EOR, &CPU::ZP0, 3};
	instrTable[0x46] = INSTRUCTION{"LSR zpg", &CPU::LSR, &CPU::ZP0, 5};
	instrTable[0x48] = INSTRUCTION{"PHA impl", &CPU::PHA, &CPU::IMP, 3};
	instrTable[0x49] = INSTRUCTION{"EOR #", &CPU::EOR, &CPU::IMM, 2};
	instrTable[0x4A] = INSTRUCTION{"LSR A", &CPU::LSR, &CPU::IMP, 2};
	instrTable[0x4C] = INSTRUCTION{"JMP abs", &CPU::JMP, &CPU::ABS, 3};
	instrTable[0x4D] = INSTRUCTION{"EOR abs", &CPU::EOR, &CPU::ABS, 4};
	instrTable[0x4E] = INSTRUCTION{"LSR abs", &CPU::LSR, &CPU::ABS, 6};
	instrTable[0x50] = INSTRUCTION{"BVC rel", &CPU::BVC, &CPU::REL, 2};
	instrTable[0x51] = INSTRUCTION{"EOR ind,Y", &CPU::EOR, &CPU::IZY, 5};
	instrTable[0x55] = INSTRUCTION{"EOR zpg,X", &CPU::EOR, &CPU::ZPX, 4};
	instrTable[0x56] = INSTRUCTION{"LSR zpg,X", &CPU::LSR, &CPU::ZPX, 6};
	instrTable[0x58] = INSTRUCTION{"CLI impl", &CPU::CLI, &CPU::IMP, 2};
	instrTable[0x59] = INSTRUCTION{"EOR abs,Y", &CPU::EOR, &CPU::ABY, 4};
	instrTable[0x5D] = INSTRUCTION{"EOR abs,X", &CPU::EOR, &CPU::ABX, 4};
	instrTable[0x5E] = INSTRUCTION{"LSR abs,X", &CPU::LSR, &CPU::ABX, 7};
	instrTable[0x60] = INSTRUCTION{"RTS impl", &CPU::RTS, &CPU::IMP, 6};
	instrTable[0x61] = INSTRUCTION{"ADC X,ind", &CPU::ADC, &CPU::IZX, 6};
	instrTable[0x65] = INSTRUCTION{"ADC zpg", &CPU::ADC, &CPU::ZP0, 3};
	instrTable[0x66] = INSTRUCTION{"ROR zpg", &CPU::ROR, &CPU::ZP0, 5};
	instrTable[0x68] = INSTRUCTION{"PLA impl", &CPU::PLA, &CPU::IMP, 4};
	instrTable[0x69] = INSTRUCTION{"ADC #", &CPU::ADC, &CPU::IMM, 2};
	instrTable[0x6A] = INSTRUCTION{"ROR A", &CPU::ROR, &CPU::IMP, 2};
	instrTable[0x6C] = INSTRUCTION{"JMP ind", &CPU::JMP, &CPU::IND, 5};
	instrTable[0x6D] = INSTRUCTION{"ADC abs", &CPU::ADC, &CPU::ABS, 4};
	instrTable[0x6E] = INSTRUCTION{"ROR abs", &CPU::ROR, &CPU::ABS, 6};
	instrTable[0x70] = INSTRUCTION{"BVS rel", &CPU::BVS, &CPU::REL, 2};
	instrTable[0x71] = INSTRUCTION{"ADC ind,Y", &CPU::ADC, &CPU::IZY, 5};
	instrTable[0x75] = INSTRUCTION{"ADC zpg,X", &CPU::ADC, &CPU::ZPX, 4};
	instrTable[0x76] = INSTRUCTION{"ROR zpg,X", &CPU::ROR, &CPU::ZPX, 6};
	instrTable[0x78] = INSTRUCTION{"SEI impl", &CPU::SEI, &CPU::IMP, 2};
	instrTable[0x79] = INSTRUCTION{"ADC abs,Y", &CPU::ADC, &CPU::ABY, 4};
	instrTable[0x7D] = INSTRUCTION{"ADC abs,X", &CPU::ADC, &CPU::ABX, 4};
	instrTable[0x7E] = INSTRUCTION{"ROR abs,X", &CPU::ROR, &CPU::ABX, 7};
	instrTable[0x81] = INSTRUCTION{"STA X,ind", &CPU::STA, &CPU::IZX, 6};
	instrTable[0x84] = INSTRUCTION{"STY zpg", &CPU::STY, &CPU::ZP0, 3};
	instrTable[0x85] = INSTRUCTION{"STA zpg", &CPU::STA, &CPU::ZP0, 3};
	instrTable[0x86] = INSTRUCTION{"STX zpg", &CPU::STX, &CPU::ZP0, 3};
	instrTable[0x88] = INSTRUCTION{"DEY impl", &CPU::DEY, &CPU::IMP, 2};
	instrTable[0x8A] = INSTRUCTION{"TXA impl", &CPU::TXA, &CPU::IMP, 2};
	instrTable[0x8C] = INSTRUCTION{"STY abs", &CPU::STY, &CPU::ABS, 4};
	instrTable[0x8D] = INSTRUCTION{"STA abs", &CPU::STA, &CPU::ABS, 4};
	instrTable[0x8E] = INSTRUCTION{"STX abs", &CPU::STX, &CPU::ABS, 4};
	instrTable[0x90] = INSTRUCTION{"BCC rel", &CPU::BCC, &CPU::REL, 2};
	instrTable[0x91] = INSTRUCTION{"STA ind,Y", &CPU::STA, &CPU::IZY, 6};
	instrTable[0x94] = INSTRUCTION{"STY zpg,X", &CPU::STY, &CPU::ZPX, 4};
	instrTable[0x95] = INSTRUCTION{"STA zpg,X", &CPU::STA, &CPU::ZPX, 4};
	instrTable[0x96] = INSTRUCTION{"STX zpg,Y", &CPU::STX, &CPU::ZPY, 4};
	instrTable[0x98] = INSTRUCTION{"TYA impl", &CPU::TYA, &CPU::IMP, 2};
	instrTable[0x99] = INSTRUCTION{"STA abs,Y", &CPU::STA, &CPU::ABY, 5};
	instrTable[0x9A] = INSTRUCTION{"TXS impl", &CPU::TXS, &CPU::IMP, 2};
	instrTable[0x9D] = INSTRUCTION{"STA abs,X", &CPU::STA, &CPU::ABX, 5};
	instrTable[0xA0] = INSTRUCTION{"LDY #", &CPU::LDY, &CPU::IMM, 2};
	instrTable[0xA1] = INSTRUCTION{"LDA X,ind", &CPU::LDA, &CPU::IZX, 6};
	instrTable[0xA2] = INSTRUCTION{"LDX #", &CPU::LDX, &CPU::IMM, 2};
	instrTable[0xA4] = INSTRUCTION{"LDY zpg", &CPU::LDY, &CPU::ZP0, 3};
	instrTable[0xA5] = INSTRUCTION{"LDA zpg", &CPU::LDA, &CPU::ZP0, 3};
	instrTable[0xA6] = INSTRUCTION{"LDX zpg", &CPU::LDX, &CPU::ZP0, 3};
	instrTable[0xA8] = INSTRUCTION{"TAY impl", &CPU::TAY, &CPU::IMP, 2};
	instrTable[0xA9] = INSTRUCTION{"LDA #", &CPU::LDA, &CPU::IMM, 2};
	instrTable[0xAA] = INSTRUCTION{"TAX impl", &CPU::TAX, &CPU::IMP, 2};
	instrTable[0xAC] = INSTRUCTION{"LDY abs", &CPU::LDY, &CPU::ABS, 4};
	instrTable[0xAD] = INSTRUCTION{"LDA abs", &CPU::LDA, &CPU::ABS, 4};
	instrTable[0xAE] = INSTRUCTION{"LDX abs", &CPU::LDX, &CPU::ABS, 4};
	instrTable[0xB0] = INSTRUCTION{"BCS rel", &CPU::BCS, &CPU::REL, 2};
	instrTable[0xB1] = INSTRUCTION{"LDA ind,Y", &CPU::LDA, &CPU::IZY, 5};
	instrTable[0xB4] = INSTRUCTION{"LDY zpg,X", &CPU::LDY, &CPU::ZPX, 4};
	instrTable[0xB5] = INSTRUCTION{"LDA zpg,X", &CPU::LDA, &CPU::ZPX, 4};
	instrTable[0xB6] = INSTRUCTION{"LDX zpg,Y", &CPU::LDX, &CPU::ZPY, 4};
	instrTable[0xB8] = INSTRUCTION{"CLV impl", &CPU::CLV, &CPU::IMP, 2};
	instrTable[0xB9] = INSTRUCTION{"LDA abs,Y", &CPU::LDA, &CPU::ABY, 4};
	instrTable[0xBA] = INSTRUCTION{"TSX impl", &CPU::TSX, &CPU::IMP, 2};
	instrTable[0xBC] = INSTRUCTION{"LDY abs,X", &CPU::LDY, &CPU::ABX, 4};
	instrTable[0xBD] = INSTRUCTION{"LDA abs,X", &CPU::LDA, &CPU::ABX, 4};
	instrTable[0xBE] = INSTRUCTION{"LDX abs,Y", &CPU::LDX, &CPU::ABY, 4};
	instrTable[0xC0] = INSTRUCTION{"CPY #", &CPU::CPY, &CPU::IMM, 2};
	instrTable[0xC1] = INSTRUCTION{"CMP X,ind", &CPU::CMP, &CPU::IZX, 6};
	instrTable[0xC4] = INSTRUCTION{"CPY zpg", &CPU::CPY, &CPU::ZP0, 3};
	instrTable[0xC5] = INSTRUCTION{"CMP zpg", &CPU::CMP, &CPU::ZP0, 3};
	instrTable[0xC6] = INSTRUCTION{"DEC zpg", &CPU::DEC, &CPU::ZP0, 5};
	instrTable[0xC8] = INSTRUCTION{"INY impl", &CPU::INY, &CPU::IMP, 2};
	instrTable[0xC9] = INSTRUCTION{"CMP #", &CPU::CMP, &CPU::IMM, 2};
	instrTable[0xCA] = INSTRUCTION{"DEX impl", &CPU::DEX, &CPU::IMP, 2};
	instrTable[0xCC] = INSTRUCTION{"CPY abs", &CPU::CPY, &CPU::ABS, 4};
	instrTable[0xCD] = INSTRUCTION{"CMP abs", &CPU::CMP, &CPU::ABS, 4};
	instrTable[0xCE] = INSTRUCTION{"DEC abs", &CPU::DEC, &CPU::ABS, 6};
	instrTable[0xD0] = INSTRUCTION{"BNE rel", &CPU::BNE, &CPU::REL, 2};
	instrTable[0xD1] = INSTRUCTION{"CMP ind,Y", &CPU::CMP, &CPU::IZY, 5};
	instrTable[0xD5] = INSTRUCTION{"CMP zpg,X", &CPU::CMP, &CPU::ZPX, 4};
	instrTable[0xD6] = INSTRUCTION{"DEC zpg,X", &CPU::DEC, &CPU::ZPX, 6};
	instrTable[0xD8] = INSTRUCTION{"CLD impl", &CPU::CLD, &CPU::IMP, 2};
	instrTable[0xD9] = INSTRUCTION{"CMP abs,Y", &CPU::CMP, &CPU::ABY, 4};
	instrTable[0xDD] = INSTRUCTION{"CMP abs,X", &CPU::CMP, &CPU::ABX, 4};
	instrTable[0xDE] = INSTRUCTION{"DEC abs,X", &CPU::DEC, &CPU::ABX, 7};
	instrTable[0xE0] = INSTRUCTION{"CPX #", &CPU::CPX, &CPU::IMM, 2};
	instrTable[0xE1] = INSTRUCTION{"SBC X,ind", &CPU::SBC, &CPU::IZX, 6};
	instrTable[0xE4] = INSTRUCTION{"CPX zpg", &CPU::CPX, &CPU::ZP0, 3};
	instrTable[0xE5] = INSTRUCTION{"SBC zpg", &CPU::SBC, &CPU::ZP0, 3};
	instrTable[0xE6] = INSTRUCTION{"INC zpg", &CPU::INC, &CPU::ZP0, 5};
	instrTable[0xE8] = INSTRUCTION{"INX impl", &CPU::INX, &CPU::IMP, 2};
	instrTable[0xE9] = INSTRUCTION{"SBC #", &CPU::SBC, &CPU::IMM, 2};
	instrTable[0xEA] = INSTRUCTION{"NOP impl", &CPU::NOP, &CPU::IMP, 2};
	instrTable[0xEC] = INSTRUCTION{"CPX abs", &CPU::CPX, &CPU::ABS, 4};
	instrTable[0xED] = INSTRUCTION{"SBC abs", &CPU::SBC, &CPU::ABS, 4};
	instrTable[0xEE] = INSTRUCTION{"INC abs", &CPU::INC, &CPU::ABS, 6};
	instrTable[0xF0] = INSTRUCTION{"BEQ rel", &CPU::BEQ, &CPU::REL, 2};
	instrTable[0xF1] = INSTRUCTION{"SBC ind,Y", &CPU::SBC, &CPU::IZY, 5};
	instrTable[0xF5] = INSTRUCTION{"SBC zpg,X", &CPU::SBC, &CPU::ZPX, 4};
	instrTable[0xF6] = INSTRUCTION{"INC zpg,X", &CPU::INC, &CPU::ZPX, 6};
	instrTable[0xF8] = INSTRUCTION{"SED impl", &CPU::SED, &CPU::IMP, 2};
	instrTable[0xF9] = INSTRUCTION{"SBC abs,Y", &CPU::SBC, &CPU::ABY, 4};
	instrTable[0xFD] = INSTRUCTION{"SBC abs,X", &CPU::SBC, &CPU::ABX, 4};
	instrTable[0xFE] = INSTRUCTION{"INC abs,X", &CPU::INC, &CPU::ABX, 7};
}
CPU::~CPU() {}

// ============================================ MMU

// Reads an 8-bit byte from the memory, located at the specified 16-bit address
u8 CPU::read(u16 addr)
{
	return mmu->read<CPU>(addr);
}

// Writes a byte to the memory at the specified address
void CPU::write(u16 addr, u8 val)
{
	mmu->write<CPU>(addr, val);
}

// ============================================ EXTERNAL INPUTS

// Reset CPU state
void CPU::reset()
{
	addr_abs = 0xFFFC;
	pc = ((u16)read(addr_abs + 1) << 8) | (u16)read(addr_abs + 0);

	// Reset internal registers
	a = 0;
	x = 0;
	y = 0;
	stackp = 0xFD;
	status = 0x00 | U;

	// Clear
	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	// Perform clearence
	cycles = 8;
}

// Interrupt
void CPU::irq()
{
	if (I() == 0)
	{
		// Push pc lower and upper to stack
		write(0x0100 + stackp, (pc >> 8) & 0x00FF);
		stackp--;
		write(0x0100 + stackp, pc & 0x00FF);
		stackp--;

		// Push status to stack
		B(false);
		U(true);
		I(true);
		write(0x0100 + stackp, status);
		stackp--;

		// Read new pc
		addr_abs = 0xFFFE;
		u16 low = read(addr_abs + 0);
		u16 high = read(addr_abs + 1);
		pc = (high << 8) | low;

		// Perform operation
		cycles = 7;
	}
}

// A Non-Maskable Interrupt
void CPU::nmi()
{
	// Push pc lower and upper to stack
	write(0x0100 + stackp, (pc >> 8) & 0x00FF);
	stackp--;
	write(0x0100 + stackp, pc & 0x00FF);
	stackp--;

	// Push status to stack
	B(false);
	U(true);
	I(true);
	write(0x0100 + stackp, status);
	stackp--;

	// Read new pc
	addr_abs = 0xFFFA;
	u16 low = read(addr_abs + 0);
	u16 high = read(addr_abs + 1);
	pc = (high << 8) | low;

	cycles = 8;
}

// Perform one clock cycles worth of emulation
void CPU::clock()
{
	if (cycles == 0)
	{
		// Read instruction
		opcode = read(pc);
		U(true);
		pc++;

		// Get instruction data
		cycles = instrTable[opcode].cycles;
		u8 add1 = (this->*instrTable[opcode].addr)();
		u8 add2 = (this->*instrTable[opcode].code)();

		// Compare new cycles state
		cycles += (add1 & add2);

		// Unused back to one
		U(true);
	}
	clock_count++;
	cycles--;
}

// Checks if CPU instruction is finished
inline bool CPU::completed()
{
	return cycles == 0;
}

// ============================================ FLAGS

// Gets the Status Flag
inline u8 CPU::getFlag(FLAGS f)
{
	return ((status & f) > 0) ? 1 : 0;
}

// Sets the Status Flag
inline void CPU::setFlag(FLAGS f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

// ============================================ ADDRESSING MODES

// Fetches data from memory
inline u8 CPU::fetch()
{
	if (instrTable[opcode].addr != &CPU::IMP)
		fetched = read(addr_abs);
	return fetched;
}

u8 CPU::IMP()
{
	fetched = a;
	return 0;
}

u8 CPU::IMM()
{
	addr_abs = pc++;
	return 0;
}

u8 CPU::ZP0()
{
	addr_abs = read(pc);
	pc++;

	addr_abs &= 0x00FF;
	return 0;
}

u8 CPU::ZPX()
{
	addr_abs = read(pc) + x;
	pc++;

	addr_abs &= 0x00FF;
	return 0;
}

u8 CPU::ZPY()
{
	addr_abs = read(pc) + y;
	pc++;

	addr_abs &= 0x00FF;
	return 0;
}

u8 CPU::REL()
{
	addr_rel = read(pc);
	pc++;

	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}

u8 CPU::ABS()
{
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	addr_abs = (high << 8) | low;
	return 0;
}

u8 CPU::ABX()
{
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	addr_abs = ((high << 8) | low) + x;
	return ((addr_abs & 0xFF00) != (high << 8));
}

u8 CPU::ABY()
{
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	addr_abs = ((high << 8) | low) + y;
	return ((addr_abs & 0xFF00) != (high << 8));
}

u8 CPU::IND()
{
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	u16 ptr = (high << 8) | low;
	if (ptr == 0x00FF)
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	return 0;
}

u8 CPU::IZX()
{
	u16 t = read(pc);
	pc++;

	u16 low = read((u16)(t + (u16)x) & 0x00FF);
	u16 high = read((u16)(t + (u16)x + 1) & 0x00FF);

	addr_abs = (high << 8) | low;
	return 0;
}

u8 CPU::IZY()
{
	u16 t = read(pc);
	pc++;

	u16 low = read(t & 0x00FF);
	u16 high = read((t + 1) & 0x00FF);

	addr_abs = ((high << 8) | low) + y;
	return (addr_abs & 0xFF00) != (high << 8);
}

// ============================================ INSTRUCTIONS

// Perform addition with carry
u8 CPU::ADC()
{
	fetch();
	u16 res = (u16)a + (u16)fetched + (u16)C();

	// Set Flags
	C(res > 255);
	Z((res & 0x00FF) == 0);
	V((~((u16)a ^ (u16)fetched) & ((u16)a ^ (u16)res)) & 0x0080);
	N(res & 0x0080);

	// Load in accumulator
	a = res & 0x00FF;

	return 1;
}

u8 CPU::AND()
{
	fetch();
	a = a & fetched;

	Z(a == 0);
	N(a & 0x80);

	return 1;
}

u8 CPU::ASL()
{
	fetch();
	u16 res = (u16)fetched << 1;

	// Set flags
	Z((res & 0x00FF) == 0);
	N(res & 0x80);
	C((res & 0xFF00) > 0);

	// Save to memory or accumulator
	if (instrTable[opcode].addr == &CPU::IMP)
		a = res & 0x00FF;
	else
		write(addr_abs, res & 0x00FF);

	return 0;
}

// Helper function for pc = address
void CPU::op_branch()
{
	cycles++;

	addr_abs = pc + addr_rel;
	cycles += (addr_abs & 0xFF00) != (pc & 0xFF00);
	pc = addr_abs;
}

u8 CPU::BCC()
{
	if (C() == 0)
		op_branch();
	return 0;
}

u8 CPU::BCS()
{
	if (C() == 1)
		op_branch();
	return 0;
}

u8 CPU::BEQ()
{
	if (Z() == 1)
		op_branch();
	return 0;
}

u8 CPU::BIT()
{
	fetch();
	u8 res = a & fetched;

	Z((res & 0x00FF) == 0);
	N(fetched & (1 << 7));
	V(fetched & (1 << 6));
	return 0;
}

u8 CPU::BMI()
{
	if (N() == 1)
		op_branch();
	return 0;
}

u8 CPU::BNE()
{
	if (Z() == 0)
		op_branch();
	return 0;
}

u8 CPU::BPL()
{
	if (N() == 0)
		op_branch();
	return 0;
}

u8 CPU::BRK()
{
	pc++;

	I(true);

	write(0x0100 + stackp, (pc >> 8) & 0x00FF);
	stackp--;
	write(0x0100 + stackp, pc & 0x00FF);
	stackp--;

	B(true);
	write(0x0100 + stackp, status);
	stackp--;
	B(false);

	pc = (u16)read(0xFFFE) | ((u16)read(0xFFFF) << 8);
	return 0;
}

u8 CPU::BVC()
{
	if (V() == 0)
		op_branch();
	return 0;
}

u8 CPU::BVS()
{
	if (V() == 1)
		op_branch();
	return 0;
}

u8 CPU::CLC()
{
	C(false);
	return 0;
}

u8 CPU::CLD()
{
	D(false);
	return 0;
}

u8 CPU::CLI()
{
	I(false);
	return 0;
}

u8 CPU::CLV()
{
	V(false);
	return 0;
}

u8 CPU::CMP()
{
	fetch();
	u16 res = (u16)a - (u16)fetched;

	C(a >= fetched);
	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	return 1;
}

u8 CPU::CPX()
{
	fetch();
	u16 res = (u16)x - (u16)fetched;

	C(x >= fetched);
	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	return 0;
}

u8 CPU::CPY()
{
	fetch();
	u16 res = (u16)y - (u16)fetched;

	C(y >= fetched);
	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	return 0;
}

u8 CPU::DEC()
{
	fetch();
	u16 res = fetched - 1;
	write(addr_abs, res & 0x00FF);

	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	return 0;
}

u8 CPU::DEX()
{
	--x;

	Z(x == 0);
	N(x & 0x80);

	return 0;
}

u8 CPU::DEY()
{
	--y;

	Z(y == 0);
	N(y & 0x80);

	return 0;
}

u8 CPU::EOR()
{
	fetch();
	a ^= fetched;

	Z(a == 0);
	N(a & 0x80);

	return 1;
}

u8 CPU::INC()
{
	fetch();
	u16 res = fetched + 1;
	write(addr_abs, res & 0x00FF);

	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	return 0;
}

u8 CPU::INX()
{
	++x;

	Z(x == 0);
	N(x & 0x80);

	return 0;
}

u8 CPU::INY()
{
	++y;

	Z(y == 0);
	N(y & 0x80);

	return 0;
}

u8 CPU::JMP()
{
	pc = addr_abs;
	return 0;
}

u8 CPU::JSR()
{
	pc--;

	write(0x0100 + stackp, (pc >> 8) & 0x00FF);
	stackp--;
	write(0x0100 + stackp, pc & 0x00FF);
	stackp--;

	pc = addr_abs;
	return 0;
}

u8 CPU::LDA()
{
	fetch();
	a = fetched;

	Z(a == 0);
	N(a & 0x80);

	return 1;
}

u8 CPU::LDX()
{
	fetch();
	x = fetched;

	Z(x == 0);
	N(x & 0x80);

	return 1;
}

u8 CPU::LDY()
{
	fetch();
	y = fetched;

	Z(y == 0);
	N(y & 0x80);

	return 1;
}

u8 CPU::LSR()
{
	fetch();
	u16 res = fetched >> 1;

	C(fetched & 0x0001);
	Z((res & 0x00FF) == 0);
	C(res & 0x0080);

	if (instrTable[opcode].addr == &CPU::IMP)
		a = res & 0x00FF;
	else
		write(addr_abs, res & 0x00FF);

	return 0;
}

u8 CPU::NOP()
{
	switch (opcode)
	{
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}

u8 CPU::ORA()
{
	fetch();
	a = a | fetched;

	Z(a == 0);
	N(a & 0x80);

	return 1;
}

u8 CPU::PHA()
{
	write(0x0100 + stackp, a);
	stackp--;

	return 0;
}

u8 CPU::PHP()
{
	write(0x0100 + stackp, status | FLAGS::B | FLAGS::U);
	stackp--;

	B(false);
	U(false);

	return 0;
}

u8 CPU::PLA()
{
	stackp++;
	a = read(0x0100 + stackp);

	Z(a == 0);
	N(a & 0x80);

	return 0;
}

u8 CPU::PLP()
{
	stackp++;
	status = read(0x0100 + stackp);

	U(true);

	return 0;
}

// TODO: Implement following op functions
u8 CPU::ROL()
{
	fetch();
	u16 res = (u16)(fetched << 1) | C();

	C(res & 0xFF00);
	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	if (instrTable[opcode].addr == &CPU::IMP)
		a = res & 0x00FF;
	else
		write(addr_abs, res & 0x00FF);

	return 0;
}

u8 CPU::ROR()
{
	fetch();
	u16 res = (u16)(C() << 7) | (fetched << 1);

	C(fetched & 0x01);
	Z((res & 0x00FF) == 0);
	N(res & 0x0080);

	if (instrTable[opcode].addr == &CPU::IMP)
		a = res & 0x00FF;
	else
		write(addr_abs, res & 0x00FF);

	return 0;
}

u8 CPU::RTI()
{
	stackp++;
	status = read(0x0100 + stackp);
	status &= ~FLAGS::B;
	status &= ~FLAGS::U;

	// Set high, low pc states
	stackp++;
	pc = (u16)read(0x0100 + stackp);
	stackp++;
	pc |= (u16)read(0x0100 + stackp) << 8;

	return 0;
}

u8 CPU::RTS()
{
	// Set high, low pc states
	stackp++;
	pc = (u16)read(0x0100 + stackp);
	stackp++;
	pc |= (u16)read(0x0100 + stackp) << 8;
	pc++;

	return 0;
}

u8 CPU::SBC()
{
	fetch();

	// Perform complement addition
	u16 value = ((u16)fetched) ^ 0x00FF;
	u16 res = (u16)a + (u16)value + (u16)C();

	// Set Flags
	C(res & 0xFF00);
	Z((res & 0x00FF) == 0);
	V((res ^ (u16)a) & (res ^ value) & 0x0080);
	N(res & 0x0080);

	// Load in accumulator
	a = res & 0x00FF;

	return 1;
}

u8 CPU::SEC()
{
	C(true);
	return 0;
}

u8 CPU::SED()
{
	D(true);
	return 0;
}

u8 CPU::SEI()
{
	I(true);
	return 0;
}

u8 CPU::STA()
{
	write(addr_abs, a);
	return 0;
}

u8 CPU::STX()
{
	write(addr_abs, x);
	return 0;
}

u8 CPU::STY()
{
	write(addr_abs, y);
	return 0;
}

u8 CPU::TAX()
{
	x = a;

	Z(x == 0);
	N(x & 0x80);

	return 0;
}

u8 CPU::TAY()
{
	y = a;

	Z(y == 0);
	N(y & 0x80);

	return 0;
}

u8 CPU::TSX()
{
	x = stackp;

	Z(x == 0);
	N(x & 0x80);

	return 0;
}

u8 CPU::TXA()
{
	a = x;

	Z(a == 0);
	N(a & 0x80);

	return 0;
}

u8 CPU::TXS()
{
	stackp = x;
	return 0;
}

u8 CPU::TYA()
{
	a = y;

	Z(a == 0);
	N(a & 0x80);

	return 0;
}

u8 CPU::NON()
{
	return 0;
}