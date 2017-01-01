#pragma once
class Computer;
#include <string>

struct Command {
	Command(Computer& computer) : m_computer(computer) {}
	virtual ~Command() {};
	virtual void run() = 0;
	Computer & m_computer;
};

struct out0 : public Command {
	out0(char reg, Computer & computer) : Command(computer), m_reg(reg) {}
	void run();
	char m_reg;
};

struct ld : public Command {
	ld(char reg, char value, Computer & computer) : Command(computer), m_reg(reg), m_value(value) {}
	void run();
	char m_reg;
	char m_value;
};

struct rlca : public Command {
	rlca(Computer & computer) : Command(computer) {}
	void run();
	char m_reg;
};

struct rrca : public Command {
	rrca(Computer & computer) : Command(computer) {}
	void run();
	char m_reg;
};

struct djnz : public Command {
	djnz(std::string label, Computer & computer) : m_label(label), Command(computer) {}
	void run();
	std::string m_label;
};

struct label : public Command {
	label(Computer & computer) : Command(computer) {}
	void run();
};