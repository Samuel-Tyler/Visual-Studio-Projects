#include <iostream>
#include <string>

using namespace std;

bool morph_word(string input_a, const string & input_b)
{
	cout << input_a << endl;
	if (input_a.length() == input_b.length())
	{
		for (size_t i = 0; i < input_a.length(); ++i)
		{
			if (input_a[i] != input_b[i])
			{
				input_a[i] = input_b[i];
				cout << input_a << endl;
			}
		}
	}
	else
	{
		cout << "Error : word lengths do not match" << endl;
		return false;
	}
	return true;
}


int main()
{
	string input_a, input_b;
	getline(cin, input_a);
	getline(cin, input_b);
	morph_word(input_a, input_b);

	int i;
	cin >> i;
}