#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Window.h"
#include "Rectangl.h"

using namespace std;

pair<bool, Rectangl> find_interception(const vector<Rectangl> & rects)
{
	constexpr auto max_float = numeric_limits<float>::max();
	constexpr auto min_float = numeric_limits<float>::min();
	
	auto intercept = Rectangl{ {-max_float, -max_float}, {max_float, max_float} };
	for (auto rect : rects)
	{
		auto result = find_intercept(intercept, rect);
		intercept = result.second;
		if (result.first == false)
		{
			return make_pair(false, intercept);
		}
	}

	return make_pair(true, intercept);
}


int main(int argc, char** argv)
{
	constexpr char* filename = "rectangles.txt";
	ifstream coords_input(filename);
	vector<Rectangl> input_rectangles;

	if (coords_input.good())
	{

		while (!coords_input.eof())
		{
			auto bottom_left_x = 0.0f;
			auto bottom_left_y = 0.0f;
			auto top_right_x = 0.0f;
			auto top_right_y = 0.0f;
			try 
			{
				string tmp;
				coords_input >> ws >> bottom_left_x;	
				getline(coords_input, tmp, ',');
				coords_input >> ws >> bottom_left_y >> top_right_x;
				getline(coords_input, tmp, ',');
				coords_input >> ws >> top_right_y >> ws;
				auto rect = Rectangl{ {bottom_left_x, bottom_left_y}, {top_right_x, top_right_y} };
				input_rectangles.push_back(rect);
			}
			catch (...)
			{
				cout << "Invalid input format" << filename << endl;
				return -1;
			}
		}

		auto interception = find_interception(input_rectangles);
		Window window{ &argc, argv };

		if (interception.first == true)
		{
			window.add_drawable(interception.second);
			window.set_text(string("Intercept Area = ") + to_string(interception.second.area()));
		}
		else
		{
			window.add_drawable(interception.second);
			window.set_text(string("No interception found! Area = ") + to_string(interception.second.area()));
		}

		for (auto input_rectangle : input_rectangles)
		{
			window.add_drawable(input_rectangle);
		}
		window.begin_loop();
	}
	else
	{
		cout << "Failed to open input file : " << filename << endl;
	}
	return 0;
}
