#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Mem.h"


Mem::Mem()
{
}


Mem::~Mem()
{
}

void Mem::InitMem()
{
	for (int i = 0; i < MEM_SIZE; i++)
	{
		m_memory[i] = i >>8;
	}
}

int Mem::ReadMem(int index)
{
	if (index < 0 || index >= MEM_SIZE)
		return -9999;
	else
		return m_memory[index];
}

std::wstring Mem::PrintMem(int page)
{
	using namespace std;
	wstringstream myBuffer;

	int base = page << 8;

	for (int line = 0; line < 256; line = line + 16)
	{
		myBuffer
			<< hex
			<< setfill(L'0')
			<< setw(2)
			<< page
			<< setw(2)
			<< line
			<< L":  ";

		// print 16 cells as bytes
		for (int cell = 0; cell < 16; cell++)
		{
			if (cell == 8)
				myBuffer << L" ";
			myBuffer << setw(2) << ReadMem(base + cell + line) << L" ";
		}

		myBuffer << L" ";

		// print 16 cells as characters
		for (int cell = 0; cell < 16; cell++)
		{
			if (cell == 8)
				myBuffer << L" ";

			if (isprint(ReadMem(base + cell + line) & 0x7f))
				myBuffer << (char)(ReadMem(base + cell + line) & 0x7f);
			else
				myBuffer << L".";
		}
		myBuffer << L'\r' << L'\n';
	}
	return myBuffer.str();
}


