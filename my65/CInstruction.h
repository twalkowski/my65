#pragma once

class CInstruction
{
public:
	CInstruction();
	~CInstruction();

	enum AddrMode {
		Implied,
		Accumulator,
		Stack,
		Immediate,			// #$ab
		Relative,			// $ab  ... PC --> PC +/- $ab
		Absolute,			// $abcd
		AbsoluteX,			// $abcd,X
		AbsoluteY,			// $abcd,Y
		AbsoluteInd,		// ($abcd)
		AbsoluteIxInd,		// ($abcd,X)
		ZP,					// $ab
		ZPX,				// $ab,X
		ZPY,				// $ab,Y
		ZPInd,				// ($ab)
		IxInd,				// ($ab,X)
		IndIx				// ($ab),Y
	};

	struct INSTRUCTION {
		int			opcode;						// the instructions's opcode
		WCHAR		mnem[10];					// the instruction's mnemonic to display 
		AddrMode	addrMode;					// the adressing mode used by the intruction
		WCHAR		aFormat[10];				// the format string to display the disassebly
		int			nBytes;						// the number of bytes for this opcode - including the opcode
		int			nCycles;					// the number of cycles to execute the instruction
		bool		addCycle;					// add an extra cycle if crossing a page boundry
		void		(CInstruction::*foo)();		// pointer to the function to perform the instruction
	} instruct[256] = { 0 };					// an array of all 65C02 instructions

	void		InitInst();

private:

	void  fAdc();
	void  fAnd();
	void  fAsl();
	void  fBcc();
	void  fBcs();
	void  fBeq();
	void  fBit();
	void  fBmi();
	void  fBne();
	void  fBpl();
	void  fBra();
	void  fBrk();
	void  fBvc();
	void  fBvs();
	void  fClc();
	void  fCld();
	void  fCli();
	void  fClv();
	void  fCmp();
	void  fCpx();
	void  fCpy();
	void  fDec();
	void  fDex();
	void  fDey();
	void  fEor();
	void  fInc();
	void  fInx();
	void  fIny();
	void  fJmp();
	void  fJsr();
	void  fLda();
	void  fLdx();
	void  fLdy();
	void  fLsr();
	void  fNop();
	void  fOra();
	void  fPha();
	void  fPhp();
	void  fPhx();
	void  fPhy();
	void  fPla();
	void  fPlp();
	void  fPlx();
	void  fPly();
	void  fRol();
	void  fRor();
	void  fRti();
	void  fRts();
	void  fSbc();
	void  fSec();
	void  fSed();
	void  fSei();
	void  fSta();
	void  fStx();
	void  fSty();
	void  fStz();
	void  fTax();
	void  fTay();
	void  fTrb();
	void  fTsb();
	void  fTsx();
	void  fTxa();
	void  fTxs();
	void  fTya();
};

