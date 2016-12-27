#include <iostream>
#include <cmath>

bool is_kaprekar(const int n, const int base = 10)
{
	const int square = std::pow(n, 2);
	auto first = n, second = 0;
	for (auto i = 1; ; ++i)
	{
		first = square / std::pow(base, i);
		if (first == 0)
		{
			break;
		}
		second = square % (int)std::pow(base, i);
		if ((first + second) == n && second != 0)
		{
		//	std::cout << "square = " << square << " first = " << first << " second = " << second << std::endl;
			return true;
		}
	}
	return false;
}

int main()
{
	int start, end;
	std::cout << "Enter smallest and largest values to test" << std::endl;
	std::cin >> start >> end;
	std::cout << "Numbers : " << std::endl;
	for (int i = start; i <= end; ++i)
	{
		if (is_kaprekar(i))
		{
			std::cout << i << ", ";
		}
	}
	int i;
	std::cin >> i;
}