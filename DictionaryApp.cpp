#include "Dictionary.h"

std::string print_menu_options()
{
    std::cout << std::endl;
    std::cout << "Choose one of the options listed below and, optionally, " << std::endl;
    std::cout << "enter the initial character of the tokens to print: " << std::endl;
    std::cout << "\t1- Print input lines " << std::endl;
    std::cout << "\t2- Print original unsorted tokens " << std::endl;
    std::cout << "\t3- Print tokens sorted by text " << std::endl;
    std::cout << "\t4- Print tokens sorted by frequency " << std::endl;
    std::cout << "\t5- Print tokens sorted by length " << std::endl;
    std::cout << "\t0- Exit " << std::endl;

    std::cout << "Enter your input: ";
    std::string user_input;
    std::cin >> user_input;
    std::cout << std::endl;
    return user_input;
}

int main()
{
    std::cout << "Enter the name of input text file: " ;
    std::string filename;
    std::cin >> filename;

    std::cout << "Enter the seperator characters: " ;
    std::string separators;
    std::cin >> separators;

    Dictionary dunyasDictionary(filename, separators);

    while(true)
    {
        std::string accepted_first_chars = "012345";
        std::string user_input = print_menu_options();
        std::string menu_option = user_input.substr(0, 1);
        std::string optional_chars = user_input.substr(1, user_input.length()-1);

        std::set<char> char_set;
        if(!optional_chars.empty())
        {
            for(const char &c : optional_chars)
            {
                char_set.insert(c);
            }
        }

        while(accepted_first_chars.find(menu_option) == std::string::npos)
        {
            std::cout << "Invalid menu option. Try again: ";
            std::cin >> user_input;
            menu_option = user_input.substr(0, 1);
        }

        if(menu_option.compare("0") == 0) 
        {
            std::cout << "Exiting program... Bye." << std::endl;
            exit(1);
        }
        else if(menu_option.compare("1") == 0)
        {
            dunyasDictionary.print_input_lines(char_set);
        }
        else if(menu_option.compare("2") == 0)
        {
            dunyasDictionary.print_input_tokens(char_set);
        }
        else if(menu_option.compare("3") == 0)
        {
            dunyasDictionary.print_sorted_on_token_text(char_set);
        }
        else if(menu_option.compare("4") == 0)
        {
            dunyasDictionary.print_sorted_on_token_frequency(char_set);
        }
        else if(menu_option.compare("5") == 0)
        {
            dunyasDictionary.print_sorted_on_token_length(char_set);
        }
    }
    return 0;
}

