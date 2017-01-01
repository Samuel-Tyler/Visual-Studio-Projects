/* #include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <memory>

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

std::string longest(std::string tiles, std::vector<std::unique_ptr<std::string>> & dictionary)
{
	for (auto& const word : dictionary)
	{
		if (scrabble(tiles, *word))
		{
			return *word;
		}
	}
	return "";
}

std::string longest(std::string tiles, std::vector<std::unique_ptr<std::string>> & dictionary)
{
	for (auto& const word : dictionary)
	{
		if (scrabble(tiles, *word))
		{
			return *word;
		}
	}
	return "";
}

void load_dictionary(std::vector<std::unique_ptr<std::string>> & dictionary, std::vector<std::unique_ptr<std::string>> & scrabble_dictionary)
{
	dictionary.reserve(20000000);
	std::ifstream dictionary_file("Enable1.txt");
	while (!dictionary_file.eof())
	{
		std::string word;
		getline(dictionary_file, word);
		dictionary.push_back(std::make_unique<std::string>(word));
		scrabble_dictionary.push_back(std::make_unique<std::string>(word));
	}
	std::sort(dictionary.begin(), dictionary.end(), [](const std::unique_ptr<std::string> &a, const std::unique_ptr<std::string> &b) {return a->length() > b->length(); });

	std::map<std::string, int> scores_map;

	const std::vector<char> scores = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
	for (auto& const word : dictionary)
	{
		auto score = 0;
		for (const auto letter : *word)
		{
			score += scores[static_cast<int>(letter) - 'a'];
		}
		scores_map.insert(std::pair<std::string, int>(*word, score));
	}
	
	std::sort(scrabble_dictionary.begin(), scrabble_dictionary.end(), [&](const std::unique_ptr<std::string> &a, const std::unique_ptr<std::string> &b) {return scores_map[*a] > scores_map[*b]; });
}


int main()
{
	std::vector<std::unique_ptr<std::string>> dictionary, scrabble_dictionary;
	load_dictionary(dictionary, scrabble_dictionary);

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

	std::cout << longest("dcthoyueorza", scrabble_dictionary) << std::endl;
	std::cout << longest("uruqrnytrois", scrabble_dictionary) << std::endl;
	std::cout << longest("rryqeiaegicgeo??", scrabble_dictionary) << std::endl;
	std::cout << longest("udosjanyuiuebr??", scrabble_dictionary) << std::endl;
	std::cout << longest("vaakojeaietg????????", scrabble_dictionary) << std::endl;
	auto i = 0;
	std::cin >> i;
}

*/