#include <chrono>
#include <iostream>
#include <numeric>
#include <array>
#include <vector>
#include <random>
#include <limits>

constexpr auto REPEATS = 100'000;

class Timer
{
public:
	void start() 
	{
		begin_time_ = std::chrono::high_resolution_clock::now();
	};
	void end()
	{
		end_time_ = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time_ - begin_time_);
		std::cout << "Function duration = " << duration.count() << "s." << std::endl;
	};
private:
	std::chrono::high_resolution_clock::time_point begin_time_;
	std::chrono::high_resolution_clock::time_point end_time_;
};


template <size_t SIZE>
void cpp_array_add(std::array<int, SIZE> & intarray)
{
	auto sum = 0ll;
	Timer t;

	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i = 0; i < SIZE; ++i)
		{
			sum += intarray[i];
		}
	}
	t.end();
	std::cout << "Sum of " << SIZE << " elements using C++ style array equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;

	if (SIZE % 5)
	{
		throw "Elements must be a multiple of 5 for this test!";
	}

	sum = 0;
	auto sum0 = 0ll;
	auto sum1 = 0ll;
	auto sum2 = 0ll;
	auto sum3 = 0ll;
	auto sum4 = 0ll;

	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i = 0; i < SIZE; i+=5)
		{
			sum0 += intarray[i + 0];
			sum1 += intarray[i + 1];
			sum2 += intarray[i + 2];
			sum3 += intarray[i + 3];
			sum4 += intarray[i + 4];
		}
		sum = sum0 + sum1 + sum2 + sum3 + sum4;
	}
	t.end();
	std::cout << "Sum of " << SIZE << " elements using C++ style array, parallel instructions equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;

	sum = 0ll;
	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i : intarray)
		{
			sum += i;
		}
	}
	t.end();
	std::cout << "Sum of " << SIZE << " elements using C++ style array and ranged based for loop equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;

	sum = 0ll;
	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		sum += std::accumulate(intarray.begin(), intarray.end(), 0);
	}
	t.end();

	std::cout << "Sum of " << SIZE << " elements using C++ style array and std::accumulate equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;
}

void c_array_add(int * intarray, int elements)
{
	auto sum = 0ll;
	Timer t;

	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i = 0; i < elements; ++i)
		{
			sum += intarray[i];
		}
	}
	t.end();
	std::cout << "Sum of " << elements << " elements using C style array equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;

	sum = 0ll;

	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i = elements - 1; i >= 0; --i)
		{
			sum += intarray[i];
		}
	}
	t.end();
	std::cout << "Sum of " << elements << " elements using C style array reversed equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;
}

void cpp_vector_add(std::vector<int> & intvector)
{
	auto sum = 0ll;
	Timer t;

	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i = 0u; i < intvector.size(); ++i)
		{
			sum += intvector[i];
		}
	}
	t.end();
	std::cout << "Sum of " << intvector.size() << " elements using C++ vector array equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;

	sum = 0ll;
	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		for (auto i : intvector)
		{
			sum += i;
		}
	}
	t.end();
	std::cout << "Sum of " << intvector.size() << " elements using C++ vector and ranged based for loop equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;

	sum = 0ll;
	t.start();
	for (auto j = 0; j < REPEATS; ++j)
	{
		sum += std::accumulate(intvector.begin(), intvector.end(), 0);
	}
	t.end();

	std::cout << "Sum of " << intvector.size() << " elements using C++ vector and std::accumulate equals : " << sum << std::endl;
	std::cout << '\n' << std::endl;
}

int main()
{
	constexpr auto elements = 10'000;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(-50, 1000);

	int int_array[elements];
	for (auto i = 0; i < elements; i++)
	{
		int_array[i] = distribution(generator);
	}
	c_array_add(int_array, elements);

	{
		std::array<int, elements> cpp_int_array;
		for (auto i = 0; i < elements; i++)
		{
			cpp_int_array[i] = int_array[i];
		}
		cpp_array_add(cpp_int_array);
	}

	{
		std::vector<int> int_vector;
		int_vector.resize(elements);
		for (auto i = 0; i < elements; i++)
		{
			int_vector[i] = int_array[i];
		}
		cpp_vector_add(int_vector);
	}

	int i;
	std::cin >> i;
}