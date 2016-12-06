#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{

	std::map<std::string, int> phonebook;
	std::ifstream input_file("phonenumbers.txt");
	if (input_file.good())
	{
		while (!input_file.eof())
		{
			std::string name;
			int number;
			input_file >> std::ws >> name >> std::ws >> number >> std::ws;
			phonebook.insert(std::pair<std::string, int>(name, number));
			if (input_file.eof())
			{
				break;
			}
		}

		for (auto item : phonebook)
		{
			std::cout << item.first << " = " << item.second << std::endl;
		}

		input_file.close();
	}
	else
	{
		std::cout << "Could not locate input file" << std::endl;
	}
	int i;
	std::cin >> i;
	return 0;
}