#pragma once

#include <string>

#define MEM_SIZE 256*256

class Mem
{
public:
	Mem();
	~Mem();

	void InitMem();
	int ReadMem(int index);
	std::wstring PrintMem(int page);

	//private:
	int m_memory[MEM_SIZE];
};


