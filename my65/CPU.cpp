#include "stdafx.h"
#include "CPU.h"
#include "Mem.h"


CPU::CPU()
{
}


CPU::~CPU()
{
}

void CPU::Reset()
{
	m_A = 0xf7;
	m_X = 0xaf;
	m_Y = 0xd5;
	m_SP = 0x01ff;
	m_PC = 0xfffe;

}

void CPU::Disassemble(unsigned int start)
{
}

