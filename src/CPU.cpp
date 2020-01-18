#include "CPU.h"
#include "Bus.h"
#include "core.h"

// ============================================ CTORS

CPU::CPU()
{
	/* INSTRUCTIONs */
	instrTable[0x00] = INSTRUCTION {"BRK impl", BRK, IMP, 7};
	instrTable[0x01] = INSTRUCTION {"ORA X,ind", ORA, IZX, 6};
	instrTable[0x05] = INSTRUCTION {"ORA zpg", ORA, ZP0, 3};
	instrTable[0x06] = INSTRUCTION {"ASL zpg", ASL, ZP0, 5};
	instrTable[0x08] = INSTRUCTION {"PHP impl", PHP, IMP, 3};
	instrTable[0x09] = INSTRUCTION {"ORA #", ORA, IMM, 2};
	instrTable[0x0A] = INSTRUCTION {"ASL A", ASL, IMP, 2};
	instrTable[0x0D] = INSTRUCTION {"ORA abs", ORA, ABS, 4};
	instrTable[0x0E] = INSTRUCTION {"ASL abs", ASL, ABS, 6};
	instrTable[0x10] = INSTRUCTION {"BPL rel", BPL, REL, 2};
	instrTable[0x11] = INSTRUCTION {"ORA ind,Y", ORA, IZY, 5};
	instrTable[0x15] = INSTRUCTION {"ORA zpg,X", ORA, ZPX, 4};
	instrTable[0x16] = INSTRUCTION {"ASL zpg,X", ASL, ZPX, 6};
	instrTable[0x18] = INSTRUCTION {"CLC impl", CLC, IMP, 2};
	instrTable[0x19] = INSTRUCTION {"ORA abs,Y", ORA, ABY, 4};
	instrTable[0x1D] = INSTRUCTION {"ORA abs,X", ORA, ABX, 4};
	instrTable[0x1E] = INSTRUCTION {"ASL abs,X", ASL, ABX, 7};
	instrTable[0x20] = INSTRUCTION {"JSR abs", JSR, ABS, 6};
	instrTable[0x21] = INSTRUCTION {"AND X,ind", AND, IZX, 6};
	instrTable[0x24] = INSTRUCTION {"BIT zpg", BIT, ZP0, 3};
	instrTable[0x25] = INSTRUCTION {"AND zpg", AND, ZP0, 3};
	instrTable[0x26] = INSTRUCTION {"ROL zpg", ROL, ZP0, 5};
	instrTable[0x28] = INSTRUCTION {"PLP impl", PLP, IMP, 4};
	instrTable[0x29] = INSTRUCTION {"AND #", AND, IMM, 2};
	instrTable[0x2A] = INSTRUCTION {"ROL A", ROL, IMP, 2};
	instrTable[0x2C] = INSTRUCTION {"BIT abs", BIT, ABS, 4};
	instrTable[0x2D] = INSTRUCTION {"AND abs", AND, ABS, 4};
	instrTable[0x2E] = INSTRUCTION {"ROL abs", ROL, ABS, 6};
	instrTable[0x30] = INSTRUCTION {"BMI rel", BMI, REL, 2};
	instrTable[0x31] = INSTRUCTION {"AND ind,Y", AND, IZY, 5};
	instrTable[0x35] = INSTRUCTION {"AND zpg,X", AND, ZPX, 4};
	instrTable[0x36] = INSTRUCTION {"ROL zpg,X", ROL, ZPX, 6};
	instrTable[0x38] = INSTRUCTION {"SEC impl", SEC, IMP, 2};
	instrTable[0x39] = INSTRUCTION {"AND abs,Y", AND, ABY, 4};
	instrTable[0x3D] = INSTRUCTION {"AND abs,X", AND, ABX, 4};
	instrTable[0x3E] = INSTRUCTION {"ROL abs,X", ROL, ABX, 7};
	instrTable[0x40] = INSTRUCTION {"RTI impl", RTI, IMP, 6};
	instrTable[0x41] = INSTRUCTION {"EOR X,ind", EOR, IZX, 6};
	instrTable[0x45] = INSTRUCTION {"EOR zpg", EOR, ZP0, 3};
	instrTable[0x46] = INSTRUCTION {"LSR zpg", LSR, ZP0, 5};
	instrTable[0x48] = INSTRUCTION {"PHA impl", PHA, IMP, 3};
	instrTable[0x49] = INSTRUCTION {"EOR #", EOR, IMM, 2};
	instrTable[0x4A] = INSTRUCTION {"LSR A", LSR, IMP, 2};
	instrTable[0x4C] = INSTRUCTION {"JMP abs", JMP, ABS, 3};
	instrTable[0x4D] = INSTRUCTION {"EOR abs", EOR, ABS, 4};
	instrTable[0x4E] = INSTRUCTION {"LSR abs", LSR, ABS, 6};
	instrTable[0x50] = INSTRUCTION {"BVC rel", BVC, REL, 2};
	instrTable[0x51] = INSTRUCTION {"EOR ind,Y", EOR, IZY, 5};
	instrTable[0x55] = INSTRUCTION {"EOR zpg,X", EOR, ZPX, 4};
	instrTable[0x56] = INSTRUCTION {"LSR zpg,X", LSR, ZPX, 6};
	instrTable[0x58] = INSTRUCTION {"CLI impl", CLI, IMP, 2};
	instrTable[0x59] = INSTRUCTION {"EOR abs,Y", EOR, ABY, 4};
	instrTable[0x5D] = INSTRUCTION {"EOR abs,X", EOR, ABX, 4};
	instrTable[0x5E] = INSTRUCTION {"LSR abs,X", LSR, ABX, 7};
	instrTable[0x60] = INSTRUCTION {"RTS impl", RTS, IMP, 6};
	instrTable[0x61] = INSTRUCTION {"ADC X,ind", ADC, IZX, 6};
	instrTable[0x65] = INSTRUCTION {"ADC zpg", ADC, ZP0, 3};
	instrTable[0x66] = INSTRUCTION {"ROR zpg", ROR, ZP0, 5};
	instrTable[0x68] = INSTRUCTION {"PLA impl", PLA, IMP, 4};
	instrTable[0x69] = INSTRUCTION {"ADC #", ADC, IMM, 2};
	instrTable[0x6A] = INSTRUCTION {"ROR A", ROR, IMP, 2};
	instrTable[0x6C] = INSTRUCTION {"JMP ind", JMP, IND, 5};
	instrTable[0x6D] = INSTRUCTION {"ADC abs", ADC, ABS, 4};
	instrTable[0x6E] = INSTRUCTION {"ROR abs", ROR, ABS, 6};
	instrTable[0x70] = INSTRUCTION {"BVS rel", BVS, REL, 2};
	instrTable[0x71] = INSTRUCTION {"ADC ind,Y", ADC, IZY, 5};
	instrTable[0x75] = INSTRUCTION {"ADC zpg,X", ADC, ZPX, 4};
	instrTable[0x76] = INSTRUCTION {"ROR zpg,X", ROR, ZPX, 6};
	instrTable[0x78] = INSTRUCTION {"SEI impl", SEI, IMP, 2};
	instrTable[0x79] = INSTRUCTION {"ADC abs,Y", ADC, ABY, 4};
	instrTable[0x7D] = INSTRUCTION {"ADC abs,X", ADC, ABX, 4};
	instrTable[0x7E] = INSTRUCTION {"ROR abs,X", ROR, ABX, 7};
	instrTable[0x81] = INSTRUCTION {"STA X,ind", STA, IZX, 6};
	instrTable[0x84] = INSTRUCTION {"STY zpg", STY, ZP0, 3};
	instrTable[0x85] = INSTRUCTION {"STA zpg", STA, ZP0, 3};
	instrTable[0x86] = INSTRUCTION {"STX zpg", STX, ZP0, 3};
	instrTable[0x88] = INSTRUCTION {"DEY impl", DEY, IMP, 2};
	instrTable[0x8A] = INSTRUCTION {"TXA impl", TXA, IMP, 2};
	instrTable[0x8C] = INSTRUCTION {"STY abs", STY, ABS, 4};
	instrTable[0x8D] = INSTRUCTION {"STA abs", STA, ABS, 4};
	instrTable[0x8E] = INSTRUCTION {"STX abs", STX, ABS, 4};
	instrTable[0x90] = INSTRUCTION {"BCC rel", BCC, REL, 2};
	instrTable[0x91] = INSTRUCTION {"STA ind,Y", STA, IZY, 6};
	instrTable[0x94] = INSTRUCTION {"STY zpg,X", STY, ZPX, 4};
	instrTable[0x95] = INSTRUCTION {"STA zpg,X", STA, ZPX, 4};
	instrTable[0x96] = INSTRUCTION {"STX zpg,Y", STX, ZPY, 4};
	instrTable[0x98] = INSTRUCTION {"TYA impl", TYA, IMP, 2};
	instrTable[0x99] = INSTRUCTION {"STA abs,Y", STA, ABY, 5};
	instrTable[0x9A] = INSTRUCTION {"TXS impl", TXS, IMP, 2};
	instrTable[0x9D] = INSTRUCTION {"STA abs,X", STA, ABX, 5};
	instrTable[0xA0] = INSTRUCTION {"LDY #", LDY, IMM, 2};
	instrTable[0xA1] = INSTRUCTION {"LDA X,ind", LDA, IZX, 6};
	instrTable[0xA2] = INSTRUCTION {"LDX #", LDX, IMM, 2};
	instrTable[0xA4] = INSTRUCTION {"LDY zpg", LDY, ZP0, 3};
	instrTable[0xA5] = INSTRUCTION {"LDA zpg", LDA, ZP0, 3};
	instrTable[0xA6] = INSTRUCTION {"LDX zpg", LDX, ZP0, 3};
	instrTable[0xA8] = INSTRUCTION {"TAY impl", TAY, IMP, 2};
	instrTable[0xA9] = INSTRUCTION {"LDA #", LDA, IMM, 2};
	instrTable[0xAA] = INSTRUCTION {"TAX impl", TAX, IMP, 2};
	instrTable[0xAC] = INSTRUCTION {"LDY abs", LDY, ABS, 4};
	instrTable[0xAD] = INSTRUCTION {"LDA abs", LDA, ABS, 4};
	instrTable[0xAE] = INSTRUCTION {"LDX abs", LDX, ABS, 4};
	instrTable[0xB0] = INSTRUCTION {"BCS rel", BCS, REL, 2};
	instrTable[0xB1] = INSTRUCTION {"LDA ind,Y", LDA, IZY, 5};
	instrTable[0xB4] = INSTRUCTION {"LDY zpg,X", LDY, ZPX, 4};
	instrTable[0xB5] = INSTRUCTION {"LDA zpg,X", LDA, ZPX, 4};
	instrTable[0xB6] = INSTRUCTION {"LDX zpg,Y", LDX, ZPY, 4};
	instrTable[0xB8] = INSTRUCTION {"CLV impl", CLV, IMP, 2};
	instrTable[0xB9] = INSTRUCTION {"LDA abs,Y", LDA, ABY, 4};
	instrTable[0xBA] = INSTRUCTION {"TSX impl", TSX, IMP, 2};
	instrTable[0xBC] = INSTRUCTION {"LDY abs,X", LDY, ABX, 4};
	instrTable[0xBD] = INSTRUCTION {"LDA abs,X", LDA, ABX, 4};
	instrTable[0xBE] = INSTRUCTION {"LDX abs,Y", LDX, ABY, 4};
	instrTable[0xC0] = INSTRUCTION {"CPY #", CPY, IMM, 2};
	instrTable[0xC1] = INSTRUCTION {"CMP X,ind", CMP, IZX, 6};
	instrTable[0xC4] = INSTRUCTION {"CPY zpg", CPY, ZP0, 3};
	instrTable[0xC5] = INSTRUCTION {"CMP zpg", CMP, ZP0, 3};
	instrTable[0xC6] = INSTRUCTION {"DEC zpg", DEC, ZP0, 5};
	instrTable[0xC8] = INSTRUCTION {"INY impl", INY, IMP, 2};
	instrTable[0xC9] = INSTRUCTION {"CMP #", CMP, IMM, 2};
	instrTable[0xCA] = INSTRUCTION {"DEX impl", DEX, IMP, 2};
	instrTable[0xCC] = INSTRUCTION {"CPY abs", CPY, ABS, 4};
	instrTable[0xCD] = INSTRUCTION {"CMP abs", CMP, ABS, 4};
	instrTable[0xCE] = INSTRUCTION {"DEC abs", DEC, ABS, 6};
	instrTable[0xD0] = INSTRUCTION {"BNE rel", BNE, REL, 2};
	instrTable[0xD1] = INSTRUCTION {"CMP ind,Y", CMP, IZY, 5};
	instrTable[0xD5] = INSTRUCTION {"CMP zpg,X", CMP, ZPX, 4};
	instrTable[0xD6] = INSTRUCTION {"DEC zpg,X", DEC, ZPX, 6};
	instrTable[0xD8] = INSTRUCTION {"CLD impl", CLD, IMP, 2};
	instrTable[0xD9] = INSTRUCTION {"CMP abs,Y", CMP, ABY, 4};
	instrTable[0xDD] = INSTRUCTION {"CMP abs,X", CMP, ABX, 4};
	instrTable[0xDE] = INSTRUCTION {"DEC abs,X", DEC, ABX, 7};
	instrTable[0xE0] = INSTRUCTION {"CPX #", CPX, IMM, 2};
	instrTable[0xE1] = INSTRUCTION {"SBC X,ind", SBC, IZX, 6};
	instrTable[0xE4] = INSTRUCTION {"CPX zpg", CPX, ZP0, 3};
	instrTable[0xE5] = INSTRUCTION {"SBC zpg", SBC, ZP0, 3};
	instrTable[0xE6] = INSTRUCTION {"INC zpg", INC, ZP0, 5};
	instrTable[0xE8] = INSTRUCTION {"INX impl", INX, IMP, 2};
	instrTable[0xE9] = INSTRUCTION {"SBC #", SBC, IMM, 2};
	instrTable[0xEA] = INSTRUCTION {"NOP impl", NOP, IMP, 2};
	instrTable[0xEC] = INSTRUCTION {"CPX abs", CPX, ABS, 4};
	instrTable[0xED] = INSTRUCTION {"SBC abs", SBC, ABS, 4};
	instrTable[0xEE] = INSTRUCTION {"INC abs", INC, ABS, 6};
	instrTable[0xF0] = INSTRUCTION {"BEQ rel", BEQ, REL, 2};
	instrTable[0xF1] = INSTRUCTION {"SBC ind,Y", SBC, IZY, 5};
	instrTable[0xF5] = INSTRUCTION {"SBC zpg,X", SBC, ZPX, 4};
	instrTable[0xF6] = INSTRUCTION {"INC zpg,X", INC, ZPX, 6};
	instrTable[0xF8] = INSTRUCTION {"SED impl", SED, IMP, 2};
	instrTable[0xF9] = INSTRUCTION {"SBC abs,Y", SBC, ABY, 4};
	instrTable[0xFD] = INSTRUCTION {"SBC abs,X", SBC, ABX, 4};
	instrTable[0xFE] = INSTRUCTION {"INC abs,X", INC, ABX, 7};
}
CPU::~CPU() {}

// ============================================ BUS

// Reads an 8-bit byte from the bus, located at the specified 16-bit address
u8 CPU::read(u16 addr)
{
	return bus->read(addr);
}

// Writes a byte to the bus at the specified address
void CPU::write(u16 addr, u8 val)
{
	bus->write(addr, val);
}

// ============================================ EXTERNAL INPUTS

// Reset CPU state
void CPU::reset()
{
	addr_abs = 0xFFFC;
	pc = (read(addr_abs + 0) << 8) | read(addr_abs + 1);

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
	cycles = 6;
}

// Interrupt
void CPU::irq()
{
	if (getFlag(I) == 0)
	{
		// Push pc lower and upper to stack
		write(0x0100 + stackp, (pc >> 8) & 0x00FF);
		stackp--;
		write(0x0100 + stackp, pc & 0x00FF);
		stackp--;

		// Push status to stack
		setFlag(B, 0);
		setFlag(U, 1);
		setFlag(I, 1);
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
	setFlag(B, 0);
	setFlag(U, 1);
	setFlag(I, 1);
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
		setFlag(U, true);
		pc++;

		// Get instruction data
		cycles = instrTable[opcode].cycles;
		u8 add1 = (this->*instrTable[opcode].addr)();
		u8 add2 = (this->*instrTable[opcode].code)();

		// Compare new cycles state
		cycles += (add1 & add2);

		// Unused back to one
		setFlag(U, true);
	}
	clock_count++;
	cycles--;
}

// Checks if CPU instruction is finished
bool CPU::completed() 
{
	return cycles == 0;
}

// ============================================ FLAGS

// Gets the Status Flag
u8 CPU::getFlag(FLAGS f)
{
	return ((status & f) > 0) ? 1 : 0;
}

// Sets the Status Flag
void CPU::setFlag(FLAGS f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

// ============================================ ADDRESSING MODES

// Fetches data from memory
u8 CPU::fetch() {
	if (instrTable[opcode].addr != &CPU::IMP)
		fetched = read(addr_abs);
	return fetched;
}

u8 CPU::IMP() {
	fetched = a;
	return 0;
}

u8 CPU::IMM() {
	addr_abs = pc++;
	return 0;
}

u8 CPU::ZP0() {
	addr_abs = read(pc);
	pc++;

	addr_abs &= 0x00FF;
	return 0;
}

u8 CPU::ZPX() {
	addr_abs = read(pc) + x;
	pc++;

	addr_abs &= 0x00FF;
	return 0;
}

u8 CPU::ZPY() {
	addr_abs = read(pc) + y;
	pc++;

	addr_abs &= 0x00FF;
	return 0;
}

u8 CPU::REL() {
	addr_rel = read(pc);
	pc++;

	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}

u8 CPU::ABS() {
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	addr_abs = (high << 8) | low;
	return 0;
}

u8 CPU::ABX() {
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	addr_abs = ((high << 8) | low) + x;
	return ((addr_abs & 0xFF00) != (high << 8));
}

u8 CPU::ABY() {
	u16 low = read(pc);
	pc++;
	u16 high = read(pc);
	pc++;

	addr_abs = ((high << 8) | low) + y;
	return ((addr_abs & 0xFF00) != (high << 8));
}

u8 CPU::IND() {
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

u8 CPU::IZX() {
	u16 t = read(pc);
	pc++;

	u16 low = read((u16)(t + (u16)x) & 0x00FF);
	u16 high = read((u16)(t + (u16)x + 1) & 0x00FF);

	addr_abs = (high << 8) | low;
	return 0;
}

u8 CPU::IZY() {
	u16 t = read(pc);
	pc++;

	u16 low = read(t & 0x00FF);
	u16 high = read((t + 1) & 0x00FF);
	
	addr_abs = ((high << 8) | low) + y;
	return (addr_abs & 0xFF00) != (high << 8);
}

// ============================================ INSTRUCTIONS

// Perform addition with carry
u8 CPU::ADC() {
	fetch();
	u16 res = (u16)a + (u16)fetched + (u16)getFlag(FLAGS::C);

	// Set Flags
	setFlag(FLAGS::C, res > 255);
	setFlag(FLAGS::Z, res & 0x00FF == 0);
	setFlag(FLAGS::V, (~((u16)a ^ (u16)fetched) & ((u16)a ^ (u16)res)) & 0x0080);
	setFlag(FLAGS::N, res & 0x0080);

	// Load in accumulator
	a = res & 0x00FF;

	return 1;
}

u8 CPU::AND() {
	fetch();
	a = a & fetched;

	setFlag(FLAGS::Z, a == 0);
	setFlag(FLAGS::N, a & 0x80);
}

u8 CPU::ASL() {
	fetch();
	u16 res = (u16)fetched << 1;

	// Set flags
	setFlag(FLAGS::Z, (res & 0x00FF) == 0);
	setFlag(FLAGS::N, res & 0x80);
	setFlag(FLAGS::C, (res & 0xFF00) > 0);

	// Save to memory or accumulator
	if (instrTable[opcode].addr == &CPU::IMP)
		a = res & 0x00FF;
	else
		write(addr_abs, res & 0x00FF);

	return 0;
}

u8 CPU::BCC() {
	if (getFlag(FLAGS::C) == 0) {
		cycles++;

		addr_abs = pc + addr_rel;
		cycles += (addr_abs & 0xFF00) != (pc & 0xFF00);
		pc = addr_abs;
	}

	return 0;
}


u8 CPU::BCS() {
	if (getFlag(FLAGS::C) == 1) {
		cycles++;

		addr_abs = pc + addr_rel;
		cycles += (addr_abs & 0xFF00) != (pc & 0xFF00);
		pc = addr_abs;
	}
}

u8 CPU::BEQ() {

}

u8 CPU::BIT();

u8 CPU::BMI();
