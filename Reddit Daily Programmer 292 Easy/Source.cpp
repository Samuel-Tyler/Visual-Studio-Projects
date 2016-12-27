#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

auto increasing_range_parse(const std::string & range)
{
	std::stringstream range_ss;
	range_ss << range;
	auto nums_in = std::vector<int>{};

	while (!range_ss.eof())
	{
		auto segment = std::string();
		auto exp = std::regex("[0-9]+(:|..|-)[0-9]+");
		auto match = std::smatch{};

		std::getline(range_ss, segment, ',');

		if (std::regex_match(segment, match, exp))
		{
			std::string & rang = static_cast<std::string>(match[0]);
			int first = std::stoi(rang);
			std::string s_second = "";
			while (rang.back() >= '0' && rang.back() <= '9')
			{
				s_second.insert(s_second.begin(), rang.back());
				rang.pop_back();
			}
			int second = std::stoi(s_second);
			
			if (first < second)
			{
				for (auto i = first; i <= second; ++i)
				{
					nums_in.push_back(i);
				}
			}
			else
			{
				for (auto i = first; i >= second; --i)
				{
					nums_in.push_back(i);
				}
			}
		}
		else
		{
			nums_in.push_back(stoi(segment));
		}
	}

	std::cout << "Input = " << range << std::endl;

	int highest = 0;
	for (auto num : nums_in)
	{
		int num_base = std::pow(10, std::ceil(log10(num)));
		if (highest % num_base > num)
		{
			highest += num_base;
		}

		auto remainder = highest % num_base;
		highest -= remainder;
		highest += num;

		std::cout << highest << std::endl;
	}
}

int main()
{
	increasing_range_parse("1,3,7,2,4,1");
	increasing_range_parse("1-3,1-2");
	increasing_range_parse("1:5:2");
	increasing_range_parse("104-2");
	increasing_range_parse("104..02");
	increasing_range_parse("545,64:11");

	int i;
	std::cin >> i;
}