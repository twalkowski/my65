#include "stdafx.h"
#include "CInstruction.h"
//#include "CPU.h"


CInstruction::CInstruction()
{
}


CInstruction::~CInstruction()
{
}


void CInstruction::InitInst()
{
	INSTRUCTION		*pinst;
	pinst = &CInstruction::instruct[0];

	// 0x00 -- BREAK
	pinst->opcode = 0x00;
	StringCchPrintf(pinst->mnem, _countof(pinst->mnem), _T("%s"), L"brk");
	pinst->addrMode = Implied;
	StringCchPrintf(pinst->aFormat, _countof(pinst->aFormat), _T("%s"), L"");
	pinst->nBytes = 1;
	pinst->nCycles = 7;
	pinst->addCycle = false;
	pinst->foo = &CInstruction::fBrk;

	// 0x01 --  ORA (zp,X)
	pinst++;
	pinst->opcode = 0x01;
	StringCchPrintf(pinst->mnem, _countof(pinst->mnem), _T("%s"), L"ora");
	pinst->addrMode = IxInd;
	StringCchPrintf(pinst->aFormat, _countof(pinst->aFormat), _T("%s"), L"($%02x,X)");
	pinst->nBytes = 2;
	pinst->nCycles = 5;
	pinst->addCycle = false;
	pinst->foo = &CInstruction::fOra;
}

#pragma region Instruction Functions
//
//   Define the functions to implement each instrction
//

void CInstruction::fAdc()
{
}

void CInstruction::fAnd()
{
}

void CInstruction::fAsl()
{
}

void CInstruction::fBcc()
{
}

void CInstruction::fBcs()
{
}

void CInstruction::fBeq()
{
}

void CInstruction::fBit()
{
}

void CInstruction::fBmi()
{
}

void CInstruction::fBne()
{
}

void CInstruction::fBpl()
{
}

void CInstruction::fBra()
{
}

void CInstruction::fBrk()
{
}

void CInstruction::fBvc()
{
}

void CInstruction::fBvs()
{
}

void CInstruction::fClc()
{
}

void CInstruction::fCld()
{
}

void CInstruction::fCli()
{
}

void CInstruction::fClv()
{
}

void CInstruction::fCmp()
{
}

void CInstruction::fCpx()
{
}

void CInstruction::fCpy()
{
}

void CInstruction::fDec()
{
}

void CInstruction::fDex()
{
}

void CInstruction::fDey()
{
}

void CInstruction::fEor()
{
}

void CInstruction::fInc()
{
}

void CInstruction::fInx()
{
}

void CInstruction::fIny()
{
}

void CInstruction::fJmp()
{
}

void CInstruction::fJsr()
{
}

void CInstruction::fLda()
{
}

void CInstruction::fLdx()
{
}

void CInstruction::fLdy()
{
}

void CInstruction::fLsr()
{
}

void CInstruction::fNop()
{
}

void CInstruction::fOra()
{
}

void CInstruction::fPha()
{
}

void CInstruction::fPhp()
{
}

void CInstruction::fPhx()
{
}

void CInstruction::fPhy()
{
}

void CInstruction::fPla()
{
}

void CInstruction::fPlp()
{
}

void CInstruction::fPlx()
{
}

void CInstruction::fPly()
{
}

void CInstruction::fRol()
{
}

void CInstruction::fRor()
{
}

void CInstruction::fRti()
{
}

void CInstruction::fRts()
{
}

void CInstruction::fSbc()
{
}

void CInstruction::fSec()
{
}

void CInstruction::fSed()
{
}

void CInstruction::fSei()
{
}

void CInstruction::fSta()
{
}

void CInstruction::fStx()
{
}

void CInstruction::fSty()
{
}

void CInstruction::fStz()
{
}

void CInstruction::fTax()
{
}

void CInstruction::fTay()
{
}

void CInstruction::fTrb()
{
}

void CInstruction::fTsb()
{
}

void CInstruction::fTsx()
{
}

void CInstruction::fTxa()
{
}

void CInstruction::fTxs()
{
}

void CInstruction::fTya()
{
}

#pragma endregion 



