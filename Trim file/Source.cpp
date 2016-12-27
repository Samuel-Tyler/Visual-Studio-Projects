#include <fstream>
#include <regex>
#include <sstream>
using namespace std;

int main()
{
	ifstream in("subreddits.txt");
	ofstream out("out.txt");


	while (!in.eof())
	{
		string line;
		getline(in, line);
		if (regex_match(line, regex("(/r/)(.*)")))
		{
			stringstream tmp;
			tmp << line;
			getline(tmp, line, ':');
			out << line << std::endl;
		}
	}
}