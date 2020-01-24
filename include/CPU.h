#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <map>
#include <vector>

#include "core.h"

// Include forward MMU
class MMU;

class CPU
{
public:
	CPU(MMU *);
	~CPU();

public:
	// ============================================ Control

	// Status register
	enum FLAGS
	{
		C = (1 << 0),
		Z = (1 << 1),
		I = (1 << 2),
		D = (1 << 3),
		B = (1 << 4),
		U = (1 << 5),
		V = (1 << 6),
		N = (1 << 7),
	};

	// Registers
	inline u8 A() { return a; }
	inline u8 X() { return x; }
	inline u8 Y() { return y; }
	inline u16 PC() { return pc; }
	inline u8 SP() { return stackp; }
	inline u8 S() { return status; }

	// Event functions
	void nmi();		  // Non-Maskable Interrupt Request
	void irq();		  // Interrupt Request
	void reset();	 // Reset Interrupt
	void clock();	 // Perform a clock cycle
	inline bool completed(); // Instruction state

private:
	// ============================================ Data
	// CPU Registers
	u8 a{0x00};		 // Accumulator Register
	u8 x{0x00};		 // X Register
	u8 y{0x00};		 // Y Register
	u8 stackp{0x00}; // Stack Pointer
	u8 status{0x00}; // Status Register
	u16 pc{0x0000};  // Program Counter

	// Internal states
	u8 fetched{0x00};
	u16 addr_abs{0x0000};
	u16 addr_rel{0x00};
	u8 opcode{0x00};
	u8 cycles{0};
	u32 clock_count{0};

	// ============================================ Control
	// MMU link
	MMU *mmu = nullptr;
	u8 read(u16);
	void write(u16, u8);

	// Status register control
	inline u8 getFlag(FLAGS);
	inline void setFlag(FLAGS, bool);

	// Flag helpers
	inline bool N() { return getFlag(FLAGS::N); }
	inline bool V() { return getFlag(FLAGS::V); }
	inline bool U() { return getFlag(FLAGS::U); }
	inline bool B() { return getFlag(FLAGS::B); }
	inline bool D() { return getFlag(FLAGS::D); }
	inline bool I() { return getFlag(FLAGS::I); }
	inline bool Z() { return getFlag(FLAGS::Z); }
	inline bool C() { return getFlag(FLAGS::C); }

	inline void N(bool _v) { setFlag(FLAGS::N, _v); }
	inline void V(bool _v) { setFlag(FLAGS::V, _v); }
	inline void U(bool _v) { setFlag(FLAGS::U, _v); }
	inline void B(bool _v) { setFlag(FLAGS::B, _v); }
	inline void D(bool _v) { setFlag(FLAGS::D, _v); }
	inline void I(bool _v) { setFlag(FLAGS::I, _v); }
	inline void Z(bool _v) { setFlag(FLAGS::Z, _v); }
	inline void C(bool _v) { setFlag(FLAGS::C, _v); }

	// Data read
	inline u8 fetch();

	// Opcode calculation helpers
	typedef u8 (CPU::*CodeExec)(void);
	typedef u8 (CPU::*AddrExec)(void);
	struct INSTRUCTION
	{
		std::string name;
		CodeExec code = nullptr;
		AddrExec addr = nullptr;
		u8 cycles = 0;
	};

	// Default instruction table
	INSTRUCTION instrTable[256];

	// Addressing modes
	u8 IMP();
	u8 IMM();
	u8 ZP0();
	u8 ZPX();
	u8 ZPY();
	u8 REL();
	u8 ABS();
	u8 ABX();
	u8 ABY();
	u8 IND();
	u8 IZX();
	u8 IZY();

	// Opcode helpers
	void op_branch();

	// Opcodes
	u8 ADC();
	u8 AND();
	u8 ASL();
	u8 BCC();
	u8 BCS();
	u8 BEQ();
	u8 BIT();
	u8 BMI();
	u8 BNE();
	u8 BPL();
	u8 BRK();
	u8 BVC();
	u8 BVS();
	u8 CLC();
	u8 CLD();
	u8 CLI();
	u8 CLV();
	u8 CMP();
	u8 CPX();
	u8 CPY();
	u8 DEC();
	u8 DEX();
	u8 DEY();
	u8 EOR();
	u8 INC();
	u8 INX();
	u8 INY();
	u8 JMP();
	u8 JSR();
	u8 LDA();
	u8 LDX();
	u8 LDY();
	u8 LSR();
	u8 NOP();
	u8 ORA();
	u8 PHA();
	u8 PHP();
	u8 PLA();
	u8 PLP();
	u8 ROL();
	u8 ROR();
	u8 RTI();
	u8 RTS();
	u8 SBC();
	u8 SEC();
	u8 SED();
	u8 SEI();
	u8 STA();
	u8 STX();
	u8 STY();
	u8 TAX();
	u8 TAY();
	u8 TSX();
	u8 TXA();
	u8 TXS();
	u8 TYA();
	u8 NON();

	// Not implemented
public:
	std::map<u16, std::string> test(u16, u16);
};