#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include <set>
#include <forward_list>
#include <regex>
#include "Token.h"

class Dictionary
{
    private:
        std::string filename;                                   // input file name
        const std::string separators;                           // separator characters
        std::vector<std::string> input_lines;                   // the lines in the input file
        std::array<std::list<Token>, 27> token_list_buckets;    // array of 26 alpha buckets + 1 none-alpha bucket
        
        // member functions
        size_t bucket_index(const std::string& tokenText) const;
        std::vector<std::string> extract_tokens_from_line(const std::string& line) const;
        void push_back_into_bucket(const std::string& tokenText, size_t line_number);
        void extract_and_push(const std::string& line, size_t line_number);

        // custom helper functions
        void print_bucket(std::string c, std::list<Token> bucket) const;
        void print_bucket_fl(std::string c, std::forward_list<Token> bucket) const;
        void print_operation(std::string operation) const;
    
    public:
        // constructors
        Dictionary(const std::string& filename, const std::string& separators = " \t\n");
        Dictionary() = delete;                                                                  
        Dictionary(const Dictionary& ) = default;
        Dictionary(Dictionary&&) = default;
        
        // assignment operators
        Dictionary& operator=(const Dictionary&);
        Dictionary& operator=( Dictionary&&);
        
        // destructor
        ~Dictionary() = default;

        // member functions
        void print_input_lines(std::set<char>& char_set) const;
        void print_input_lines() const;
        void print_input_tokens(std::set<char>& char_set) const;
        void print_input_tokens() const;
        void print_sorted_on_token_text(std::set<char>& char_set) const;
        void print_sorted_on_token_text() const;
        void print_sorted_on_token_frequency(std::set<char>& char_set) const;
        void print_sorted_on_token_frequency() const;
        void print_sorted_on_token_length(std::set<char>& char_set) const;
        void print_sorted_on_token_length() const;

        // An example of a static member function, which could otherwise be a free function
        // replaces \t and \n with \\t and \\n in separators and returns the resulting string
        static std::string restore_fake_tab_newline_chars(const std::string& str)
        {
            std::string fake_tab{ "\\t" }; // two characters, \ and t
            std::string real_tab{ "\t" };  // one character, \t

            std::string temp{ str };
            // restore tabs
            std::string::size_type pos = temp.find(fake_tab);
            while (pos != std::string::npos)
            {
                temp.replace(pos, 2, real_tab);
                pos = temp.find(fake_tab);
            }

            std::string fake_newline{ "\\n" }; // two characters, \ and n
            std::string real_newline{ "\n" };  // one character, \n

            // restore newlines
            pos = temp.find(fake_newline);
            while (pos != std::string::npos)
            {
                temp.replace(pos, 2, real_newline);
                pos = temp.find(fake_newline);
            }

            return temp;
        }
};
#endif