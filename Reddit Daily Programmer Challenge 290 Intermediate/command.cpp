#include "command.h"
#include "computer.h"

void out0::run()
{
	m_computer.set_out0(m_computer.get_reg(m_reg));
}

void ld::run()
{
	m_computer.set_reg(m_reg, m_value);
}

void rlca::run()
{
	auto current_value = m_computer.get_reg('a');
	auto extra_bit = (current_value & 0b1000'0000) ? 0b0000'0001 : 0b0000'0000;
	current_value <<= 1;
	current_value |= extra_bit;
	m_computer.set_reg('a', current_value);
}

void rrca::run()
{
	auto current_value = m_computer.get_reg('a');
	auto extra_bit = (current_value & 0b0000'0001) ? 0b1000'0000 : 0b0000'0000;
	current_value >>= 1;
	current_value &= 0b0111'1111;
	current_value |= extra_bit;
	m_computer.set_reg('a', current_value);
}

void label::run()
{
}

void djnz::run()
{
	char new_value = m_computer.get_reg('b') - 1;
	m_computer.set_reg('b', new_value);
	if (new_value != 0)
	{
		m_computer.jump(m_label);
	}
}