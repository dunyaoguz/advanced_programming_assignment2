#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include <set>
#include <forward_list>
#include "Token.h"
#include "Dictionary.h"


int main()
{
    // std::string filename = "input_files/test_input_file.txt";
    std::string filename = "input_files/input_file.txt";
    Dictionary dictionary(filename);

    std::set<char> char_set = {'1', 'D', 's', 'w'};
    // dictionary.print_input_lines(char_set);
    // dictionary.print_input_tokens(char_set);
    // dictionary.print_sorted_on_token_text(char_set);
    // dictionary.print_sorted_on_token_frequency(char_set);
    dictionary.print_sorted_on_token_length();

    return 0; // 0 means success!
}
