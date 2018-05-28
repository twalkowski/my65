#pragma once
class CPU
{
public:
	CPU();
	~CPU();

	unsigned int		m_A;
	unsigned int		m_X;
	unsigned int		m_Y;
	unsigned int		m_SP;
	unsigned int		m_PC;
	unsigned int		m_AddrBus;
	unsigned int		m_DataBus;

	void		Reset();

};
