#include <iostream>

void binary(int number);

int main() {
	int number;
	std::cout << "Please enter a positive integer: ";
	std::cin >> number;
	if (number < 0)
		std::cout << "That is not a positive integer.\n";
	else {
		std::cout << number << " converted to binary is: ";
		binary(number);
		std::cout << std::endl;
	}
	std::cin >> number;
	return 0;
}

void binary(int number) {
	int remainder;

	if (number <= 1) {
		std::cout << number;
		return;
	}

	remainder = number % 2;
	binary(number /= 2);
	std::cout << remainder;
}