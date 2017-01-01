#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <map>

#include "command.h"

class Computer
{
public:
	Computer() : m_reg_a(0), m_reg_b(0), m_out0(0), m_program_location(0), label_map() {}
	void display();
	void parse(std::istream & istream);
	void run();


	void set_reg(char reg, char value);
	char get_reg(char reg);
	void set_out0(char value) { m_out0 = value; display(); }
	char get_out0() { return m_out0; }
	void jump(std::string label) { m_program_location = label_map[label]; }

private:
	char m_reg_a;
	char m_reg_b = 0;
	char m_out0 = 0;

	std::map<std::string, int> label_map;
	std::vector<std::unique_ptr<Command>> m_instruction_memory;
	int m_program_location;
};