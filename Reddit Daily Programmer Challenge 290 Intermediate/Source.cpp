#include <iostream>
#include <fstream>

#include "computer.h"

using namespace std;


int main()
{
	ifstream commands_file("commands.txt");
	if (commands_file.good())
	{
		Computer computer;
		computer.parse(commands_file);
		computer.run();
	}

	int i;
	cin >> i;
}