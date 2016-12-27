#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <numeric>
#include <iomanip>

using namespace std::chrono_literals;

class Stat
{
public:
	static std::string stat(const std::string &strg);
};

std::string seconds_to_hms_string(std::chrono::seconds dur)
{
	auto h = std::chrono::duration_cast<std::chrono::hours>(dur);
	auto m = std::chrono::duration_cast<std::chrono::minutes>(dur -= h);
	auto s = std::chrono::duration_cast<std::chrono::seconds>(dur -= m);
	
	std::stringstream hms_ss;
	std::string hms_string;
	hms_ss << std::setfill('0') << std::setw(2) << std::to_string(h.count()) << '|';
	hms_ss << std::setfill('0') << std::setw(2) << std::to_string(m.count()) << '|';
	hms_ss << std::setfill('0') << std::setw(2) << std::to_string(s.count());
	getline(hms_ss, hms_string);
	return hms_string;
}

std::string Stat::stat(const std::string &strg)
{
	std::stringstream scores_ss;
	scores_ss << strg;
	std::vector<std::chrono::seconds> times_vec;
	while (scores_ss.good() && scores_ss.eof() == false)
	{
		char spacer;
		int h, m, s;
		scores_ss >> h >> spacer >> m >> spacer >> s >> spacer >> std::ws;

		std::chrono::hours hours(h);
		std::chrono::minutes mins(m);
		std::chrono::seconds secs(s);
		std::chrono::seconds duration = hours + mins + secs;
		times_vec.push_back(duration);
	}

	std::sort(times_vec.begin(), times_vec.end());
	auto sum = std::accumulate(times_vec.begin(), times_vec.end(), 0s);
	auto average(sum / times_vec.size());
	auto max = std::max_element(std::begin(times_vec), std::end(times_vec));
	auto min = std::min_element(std::begin(times_vec), std::end(times_vec));
	auto range(*max - *min);
	auto median(times_vec[times_vec.size() / 2]);
	if (times_vec.size() % 2 == false) // if even number of elements must take average of middle -0.5 and middle +0.5
	{
		median += std::chrono::seconds(times_vec[times_vec.size() / 2 - 1]);
		median /= 2;
	}

	return "Range: " + seconds_to_hms_string(range) +
		" Average: " + seconds_to_hms_string(average) +
		" Median: " + seconds_to_hms_string(median);
}

int main()
{
	std::cout << Stat::stat("01|15|59, 1|47|16, 01|17|20, 1|32|34, 2|17|17") << std::endl;
	std::cout << Stat::stat("02|15|59, 2|47|16, 02|17|20, 2|32|34, 2|17|17, 2|22|00, 2|31|41") << std::endl;

	int i;
	std::cin >> i;
}