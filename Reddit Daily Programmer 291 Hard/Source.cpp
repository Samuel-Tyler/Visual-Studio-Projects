#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <utility>
#include <set>
#include <chrono>
#include <algorithm>
#include <memory>

class Wire_grid {
public:
	Wire_grid() : m_width(0), m_height(0), m_grid() {};
	Wire_grid(int width, int height) : m_width(width), m_height(height), m_grid(width, std::vector<char>(height, '.')) {};
	
	bool set_cell(int x, int y, char wire);
	bool set_cell(std::pair<int, int> xy, char wire) { return set_cell(xy.first, xy.second, wire); }
	void overriding_set_cell(int x, int y, char wire);
	void overriding_set_cell(std::pair<int, int> xy, char wire) { overriding_set_cell(xy.first, xy.second, wire); }
	void remove_other_wires(char wire);

	std::pair<bool, char> get_cell(int x, int y) const { if (x < m_width && x >= 0 && y < m_height && y >= 0) return std::make_pair(true, m_grid[x][y]); else return std::make_pair(false, '\0'); }
	std::pair<bool, char> get_cell(std::pair<int, int> xy) const { return get_cell(xy.first, xy.second); } 

	void set_grid_size(int width, int height);
	void print() const;
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }

private:
	int m_width;
	int m_height;
	std::vector<std::vector<char>> m_grid;
};

class Starting_wire_grid : public Wire_grid{
public:
	std::pair<int, int> get_wire_start(char c) const { return m_wire_start_cells.find(c)->second; }
	std::pair<int, int> get_wire_end(char c) const { return m_wire_end_cells.find(c)->second; }
	Starting_wire_grid& operator<< (std::istream & istream);

	std::set<char> m_wires;
private:
	std::map<char, std::pair<int, int>> m_wire_start_cells;
	std::map<char, std::pair<int, int>> m_wire_end_cells;
};

using coordinate = std::pair<std::pair<int, int>, char>;
using coordinate_set = std::set<std::pair<std::pair<int, int>, char>>;

coordinate_set grid_to_coords(const Wire_grid& grid)
{
	coordinate_set coords;

	auto height = grid.get_height();
	auto width = grid.get_width();

	for (auto y = 0; y < height; ++y)
	{
		for (auto x = 0; x < width; ++x)
		{
			auto cell = grid.get_cell(x, y);

			if (cell.first && cell.second != '.')
			{
				coords.insert(std::make_pair(std::make_pair(x, y), cell.second));
			}
		}
	}
	return coords;
}

void Wire_grid::remove_other_wires(char wire)
{
	for (auto y = 0; y < m_height; ++y)
	{
		for (auto x = 0; x < m_width; ++x)
		{
			if (m_grid[x][y] != wire)
			{
				m_grid[x][y] = '.';
			}
		}
	}
}

Wire_grid coords_to_grid(coordinate_set coords, int width, int height)
{
	Wire_grid grid(width, height);
	for (auto coordinate : coords)
	{
		grid.set_cell(coordinate.first, coordinate.second);
	}
	return grid;
}

void route_find_recursive(const char wire, const std::pair<int, int>current_position, const std::pair<int, int>end_position, std::unique_ptr<Wire_grid>&& route, std::vector<coordinate_set> & route_permutations)
{
	const auto up = std::make_pair(current_position.first, current_position.second + 1);
	const auto down = std::make_pair(current_position.first, current_position.second - 1);
	const auto left = std::make_pair(current_position.first - 1, current_position.second);
	const auto right = std::make_pair(current_position.first + 1, current_position.second);

	// if new cell has more than one neighbor we can ignore as it will be redundant
	{
		const std::vector<std::pair<int, int>> directions = { up, down, left, right };
		int i = 0;
		for (auto direction : directions)
		{
			if (direction == end_position)
			{
				auto grid = Wire_grid(*route);
				grid.remove_other_wires(wire);
				auto coordinates = grid_to_coords(grid);
				route_permutations.push_back(coordinates);
				return;
			}
			const auto result = route->get_cell(direction);
			if (result.first && result.second == wire && direction != end_position)
			{
				i++;
			}
			if (i > 1)
			{
				return;
			}
		}
	}
	
	try 
	{
		std::unique_ptr<Wire_grid> up_route = std::make_unique<Wire_grid>(*route);
		std::unique_ptr<Wire_grid> down_route = std::make_unique<Wire_grid>(*route);
		std::unique_ptr<Wire_grid> left_route = std::make_unique<Wire_grid>(*route);
		std::unique_ptr<Wire_grid> right_route = std::make_unique<Wire_grid>(*route);
		route.reset();

		if (up_route->set_cell(up, wire))
		{
			route_find_recursive(wire, up, end_position, std::move(up_route), route_permutations);
		}
		if (down_route->set_cell(down, wire))
		{
			route_find_recursive(wire, down, end_position, std::move(down_route), route_permutations);
		}
		if (left_route->set_cell(left, wire))
		{
			route_find_recursive(wire, left, end_position, std::move(left_route), route_permutations);
		}
		if (right_route->set_cell(right, wire))
		{
			route_find_recursive(wire, right, end_position, std::move(right_route), route_permutations);
		}
	}
	catch (...)
	{
		std::cout << "Error failed to allocate grid!" << std::endl;
		while (1);
	}
}

bool Wire_grid::set_cell(int x, int y, char wire)
{
	if (x < m_width && x >= 0 && y < m_height && y >= 0)
	{
		if (m_grid[x][y] == '.')
		{
			m_grid[x][y] = wire;
			return true;
		}
	}
	return false;
}

void Wire_grid::overriding_set_cell(int x, int y, char wire)
{
	if (x < m_width && x >= 0 && y < m_height && y >= 0)
	{
		m_grid[x][y] = wire;
	}
}

void Wire_grid::set_grid_size(int width, int height) {
	m_width = width;
	m_height = height;
	std::vector<std::vector<char>> new_grid(m_width, std::vector<char>(m_height, '.'));
	m_grid = new_grid;
}

void Wire_grid::print() const
{
	for (auto y = 0; y < m_height; ++y)
	{
		for (auto x = 0; x < m_width; ++x)
		{
			std::cout << get_cell(x, y).second;
		}
	std::cout << std::endl;
	}
}

Starting_wire_grid& Starting_wire_grid::operator<< (std::istream & istream)
{
	try 
	{
		int width;
		int height;
		istream >> width;
		istream >> height;
		set_grid_size(width, height);
		
		for (char c = 'A';; ++c)
		{
			int start_x, start_y, end_x, end_y;
			istream >> start_x >> start_y >> end_x >> end_y;

			m_wire_start_cells.insert(std::make_pair(c, std::make_pair(start_x, start_y)));
			m_wire_end_cells.insert(std::make_pair(c, std::make_pair(end_x, end_y)));
			m_wires.insert(c);

			set_cell(start_x, start_y, c);
			set_cell(end_x, end_y, c);

			if (istream.eof())
			{
				break;
			}
		}

	}
	catch (...)
	{
		std::cout << "Error parsing grid input : Invalid format" << std::endl;
	}
	return *this;
}

std::vector<coordinate_set> find_compatable_routes(const std::vector<coordinate_set> & lhs_routes, const std::vector<coordinate_set> & rhs_routes)
{
	std::cout << "Finding compatable routes between route vectors of size " << lhs_routes.size() << " and " << rhs_routes.size() << std::endl;
	std::vector<coordinate_set> combined_routes;
	for (auto lhs_coords : lhs_routes)
	{
		for (auto rhs_coords : rhs_routes)
		{
			auto matching = std::find_first_of(lhs_coords.begin(), lhs_coords.end(), rhs_coords.begin(), rhs_coords.end(),
				[](const coordinate & lhs, const coordinate &rhs) {return lhs.first == rhs.first; });

			if (matching == lhs_coords.end()) // no clashing co ordinates
			{
				auto combined_coords = lhs_coords;
				combined_coords.insert(rhs_coords.begin(), rhs_coords.end());
				combined_routes.push_back(combined_coords);

			}
		}
	}
	std::cout << "Found " << combined_routes.size() << " compatable routes." << std::endl;
	return combined_routes;
}

void remove_redundant_routes(std::vector<coordinate_set> & routes)
{
	std::sort(routes.begin(), routes.end(), [](const coordinate_set &lhs, const coordinate_set &rhs) -> bool { return (lhs.size() < rhs.size()); });
	std::cout << "Removing redundant routes. Starting number of routes = " << routes.size() << std::endl;

	// Check if route coordinates contain any subset, if so remove route

	routes.erase(std::remove_if(routes.begin(), routes.end(), [&](const coordinate_set & route) -> bool
	{
		
		for (auto comparison_route : routes)
		{
			if (route.size() > comparison_route.size() && comparison_route.size() != 0)
			{
				if (std::includes(route.begin(), route.end(), comparison_route.begin(), comparison_route.end()))
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		return false;
	}), routes.end());
	std::cout << "Removing redundant routes. Final number of routes = " << routes.size() << std::endl;
}

void find_permutations(const Starting_wire_grid & starting_grid)
{
	std::vector<std::vector<coordinate_set>> permutations_by_wire;
	std::vector<coordinate_set> final_routes;

	for (auto wire : starting_grid.m_wires)
	{
		std::vector<coordinate_set> permutations;

		auto begin = std::chrono::system_clock::now();

		auto route_tmp = std::make_unique<Wire_grid>(starting_grid);
		
		route_find_recursive(wire, starting_grid.get_wire_start(wire), starting_grid.get_wire_end(wire), std::move(route_tmp), permutations);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = end - begin;

		std::cout << "Finding " << permutations.size() << " routes for wire " << wire << " had a duration of " << elapsed_time.count() << "s" << std::endl;

		permutations_by_wire.push_back(permutations);
	}

	for (auto & permutations : permutations_by_wire)
	{
		remove_redundant_routes(permutations);
	}
	
	for (auto i = 0; i < permutations_by_wire.size() -1; i++)
	{
		auto combined = find_compatable_routes(permutations_by_wire[i], permutations_by_wire[i + 1]);
		permutations_by_wire[i + 1] = combined;
		final_routes = permutations_by_wire[i + 1];	
	}

	for (auto coords : final_routes)
	{
		auto grid = coords_to_grid(coords, starting_grid.get_width(), starting_grid.get_height());
		grid.print();
	}
}

int main()
{
	//load starting wire grid object
	std::ifstream input("starting_locations.txt");
	if (input.good())
	{
		Starting_wire_grid grid;
		grid << input;
		grid.print();

		find_permutations(grid);
		
	}
	else
	{
		std::cout << "Error : Failed to load input file" << std::endl;
	}
	//calculte all possible routes for each wire
	//overlay routes and remove intecepts
	int i;
	std::cin >> i;
}