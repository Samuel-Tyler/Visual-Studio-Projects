    #include <vector>
    #include <iostream>
    #include <memory>
    #include <string>

    using namespace std;

    struct char_or_array
    {
	    unique_ptr<vector<char_or_array>> pointer;
	    char content;

	    char_or_array(char input) : pointer{ nullptr }, content{ input } {}
	    char_or_array(const vector<char_or_array> & node_vector) : pointer{ make_unique<vector<char_or_array>>(node_vector) }, content{ 0 } {}
	    char_or_array::char_or_array(const char_or_array &in) : content{in.content}, pointer{ nullptr }
	    {
		    if (in.pointer != nullptr)
		    {
			    pointer = make_unique<vector<char_or_array>>(*in.pointer);
		    }
	    }
    };

    vector<char_or_array> parse_string(const string & input_string)
    {
	    vector<char_or_array> output;
	    for (decltype(input_string.size()) i = 0; i < input_string.size(); i++)
	    {
		    if (input_string[i] == '(')
		    {
			    // find parenthesis sub string
			    string sub_string{""};
			    auto open_paren_count = 0;
			    auto close_paren_count = 0;
			    do 
			    {
				    if (i > input_string.size())
				    {
					    throw exception("Error, invalid input : no matching ')' found.");
				    }
				    if (input_string[i] == '(')
				    {
					    open_paren_count++;
                        if (open_paren_count > 1)
                        {
                            sub_string.push_back(input_string[i]);
                        }
				    }
				    else if (input_string[i] == ')')
				    {
					    close_paren_count++;
                        if (open_paren_count != close_paren_count)
                        {
                            sub_string.push_back(input_string[i]);
                        }
				    }
                    else //any other char
                    {
                        sub_string.push_back(input_string[i]);
                    }
				    i++;
			    } while (open_paren_count != close_paren_count);
                i--;
			    auto embedded_array = parse_string(sub_string);
			    output.push_back(char_or_array(embedded_array));
		    }
		    else
		    {
			    output.push_back(char_or_array{ input_string[i] });
		    }
	    }
	    output.push_back(char_or_array{ '\0' });
	    return output;
    }

    void print(const vector<char_or_array> & input_vector)
    {
	    for (const auto& cell : input_vector)
	    {
		    if (cell.pointer.get() == nullptr)
		    {
			    std::cout << cell.content;
		    }
		    else
		    {
			    std::cout << '[';
			    print(*(cell.pointer));
			    std::cout << ']';
		    }
	    }
    }

    int main()
    {
	    string input_string;
        while (1)
        {
            try
            {
                cin >> input_string;
                auto result = parse_string(input_string);
                print(result);
                std::cout << std::endl;
            }
            catch (exception  e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (...)
            {
                cout << "Error parsing input" << endl;
                return -1;
            }
        }
    }