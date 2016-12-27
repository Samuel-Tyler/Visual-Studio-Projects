#include "computer.h"
#include "command.h"

#include <iostream>
#include <string>

using namespace std;

void Computer::set_reg(char reg, char value)
{
	if (reg == 'a')
		m_reg_a = value;
	if (reg == 'b')
		m_reg_b = value;
}

char Computer::get_reg(char reg)
{
	if (reg == 'a')
		return m_reg_a;
	if (reg == 'b')
		return m_reg_b;
}

void Computer::parse(istream & istream)
{
	while (istream.good())
	{
		string instruction;
		istream >> instruction;

		if (instruction == "out")
		{
			string reg;
			istream >> ws;
			getline(istream, reg, ',');
			istream >> ws;
			getline(istream, reg, '\n');
			cout << "out0 , reg = " << reg << endl;
			m_instruction_memory.push_back(unique_ptr<Command>{ make_unique<out0>(reg[0], *this)});
		}
		else if (instruction == "ld")
		{
			string reg;
			int value;
			istream >> ws;
			getline(istream, reg, ',');
			istream >> ws >> value;
			cout << "ld , reg = " << reg << " value = " << value << endl;
			m_instruction_memory.push_back(unique_ptr<Command>{ make_unique<ld>(reg[0], (char)value, *this)});
		}
		else if (instruction == "rlca")
		{
			cout << "rlca" << endl;
			m_instruction_memory.push_back(unique_ptr<Command>{ make_unique<rlca>(*this)});
		}
		else if (instruction == "rrca")
		{
			cout << "rrca" << endl;
			m_instruction_memory.push_back(unique_ptr<Command>{ make_unique<rrca>(*this)});
		}
		else if (instruction == "djnz")
		{
			string label;
			istream >> ws >> label >> ws;
			cout << "djnz : " << label << endl;
			m_instruction_memory.push_back(unique_ptr<Command>{ make_unique<djnz>(label, *this)});
		}
		else
		{ // if not detected command probably label
			if (instruction.back() == ':')
			{
				instruction.erase(instruction.end() - 1, instruction.end());
				cout << "inserted new label : " << instruction << " = " << m_program_location << endl;
				label_map.insert(make_pair(instruction, m_program_location));
				m_instruction_memory.push_back(unique_ptr<Command>{ make_unique<label>(*this)});
			}
			else
			{
				cout << "Unrecognised command : " << instruction << endl;
				break;
			}
		}
		if (istream.eof())
		{
			break;
		}
		m_program_location++;
	}
}

void Computer::display()
{
	for (int i = 0; i < 8; ++i)
	{
		auto mask = 0b1000'0000 >> i;
		auto output = (m_out0 & mask) ? '*' : '.';
		cout << output;
	}
	cout << endl;
}

void Computer::run()
{
	for (m_program_location = 0; m_program_location < m_instruction_memory.size(); m_program_location++)
	{
		m_instruction_memory[m_program_location]->run();
	}
}

