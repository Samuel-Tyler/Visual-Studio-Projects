#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

bool find_and_remove_tile(std::string & tiles, const char search_char)
{
	auto found_position = tiles.find(search_char);
	if (found_position == std::string::npos)
	{
		return false;
	}
	else
	{
		tiles.erase(found_position, 1);
		return true;
	}
}

bool scrabble(std::string tiles, const std::string possible_word)
{
	for (auto search_character : possible_word)
	{
		if (find_and_remove_tile(tiles, search_character))
		{
			continue;
		}
		else if (find_and_remove_tile(tiles, '?'))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

std::string longest(const std::string & tiles, const std::vector<std::string> & dictionary)
{
	for (const auto word : dictionary)
	{
		if (scrabble(tiles, word))
		{
			return word;
		}
	}
	return "";
}

int calculate_score(std::string tiles, std::string word)
{
	auto score = 0;
	const std::vector<char> scores = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
	std::string common_tiles(20, ' ');

	std::sort(tiles.begin(), tiles.end());
	std::sort(word.begin(), word.end());
	
	std::set_intersection(word.begin(), word.end(), tiles.begin(), tiles.end(), common_tiles.begin());

	for (const auto letter : common_tiles)
	{
		auto letter_num = static_cast<int>(letter);
		if (letter_num >= 'a' && letter_num <= 'z')
		{
			score += scores[letter_num - 'a'];
		}
	}

	return score;
}

std::string highest(const std::string & tiles, const std::vector<std::string> & dictionary)
{
	std::string current_highest = "";
	int high_score = 0;
	for (const auto word : dictionary)
	{
		if (scrabble(tiles, word))
		{
			auto score = calculate_score(tiles, word);
			if (score > high_score)
			{
				high_score = score;
				current_highest = word;
			}
		}
	}
	return current_highest;
}

void load_dictionary(std::vector<std::string> & dictionary)
{
	dictionary.reserve(600000);
	std::ifstream dictionary_file("Enable1.txt");
	while (!dictionary_file.eof())
	{
		std::string word;
		getline(dictionary_file, word);
		dictionary.push_back(word);
	}
	std::sort(dictionary.begin(), dictionary.end(), [](std::string &a, std::string & b) {return a.length() > b.length(); });
}


int main()
{
	std::vector<std::string> dictionary;
	load_dictionary(dictionary);

	std::cout << scrabble("ladilmy", "daily") << std::endl;
	std::cout << scrabble("eerriin", "eerie") << std::endl;
	std::cout << scrabble("orrpgma", "program") << std::endl;
	std::cout << scrabble("orppgma", "program") << std::endl;

	std::cout << scrabble("pizza??", "pizzazz") << std::endl;
	std::cout << scrabble("piizza?", "pizzazz") << std::endl;
	std::cout << scrabble("a??????", "program") << std::endl;
	std::cout << scrabble("b??????", "program") << std::endl;

	std::cout << longest("dcthoyueorza", dictionary) << std::endl;
	std::cout << longest("uruqrnytrois", dictionary) << std::endl;
	std::cout << longest("rryqeiaegicgeo??", dictionary) << std::endl;
	std::cout << longest("udosjanyuiuebr??", dictionary) << std::endl;
	std::cout << longest("vaakojeaietg????????", dictionary) << std::endl;

	std::cout << highest("dcthoyueorza", dictionary) << std::endl;
	std::cout << highest("uruqrnytrois", dictionary) << std::endl;
	std::cout << highest("rryqeiaegicgeo??", dictionary) << std::endl;
	std::cout << highest("udosjanyuiuebr??", dictionary) << std::endl;
	std::cout << highest("vaakojeaietg????????", dictionary) << std::endl;
	auto i = 0;
	std::cin >> i;
}

