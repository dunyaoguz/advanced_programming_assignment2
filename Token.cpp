#include "Token.h"

// normal constructor
Token::Token(std::string input, size_t line_num)
{
    text = input;
    frequency = 1;
    number_list.push_back(line_num);
}

// returns a constant pointer to this token's text
std::string Token::get_token_text() const { return text; }

// returns this token's list of line numbers
std::vector<size_t> Token::get_number_list() const { return number_list; } 

// returns this token's frequency
int Token::get_frequency() const { return frequency; }

// returns the length of this token's cstr
size_t Token::length() const { return text.length(); }

// compares this and other token texts
int Token::compare(const Token& aToken) const { return text.compare(aToken.get_token_text()); }

// increments this token's frequency
void Token::increment_frequency() { frequency++; }

// add a specified line number to this token's list of line numbers
// if the specified line number is not in the list
void Token::push_back_line_number(size_t lineNum) 
{ 
    for(size_t i = 0; i<number_list.size(); i++) 
    {
        if(number_list[i] == lineNum) return;
    }
    number_list.push_back(lineNum);
    increment_frequency();
}

void Token::print(std::ostream &output) const
{
    output << *this << " " << "(" << frequency << ")" << std::endl;
}

// < operator overload
bool operator<(const Token& first, const Token& second)
{
    if (first.compare(second) < 0) return true;
    if (first.compare(second) > 0) return false;
    // if exactly the same, return true
    return true;
}

// returns true is the first text is shorter than the second text
bool isShorter(const Token& first, const Token& second)
{
    if (first.length() < second.length()) return true;
    if (first.length() > second.length()) return false;
    // if the two tokens are of the same length we order them alphabetically
    return first < second;
}

// returns true is the first text is less frequent than the second text
bool isLessFrequent(const Token& first, const Token& second)
{
    if (first.get_frequency() < second.get_frequency()) return true;
    if (first.get_frequency() > second.get_frequency()) return false;
    // if the two tokens have the same frequency we order them alphabetically
    return first < second;
}

// << operator overload
// prints this token's text followed by its number list
std::ostream &operator<<(std::ostream &output, const Token &tokenToPrint)
{
    // if used is 0, return empty string because we can't print anything
    if (tokenToPrint.length() == 0)
    {
        return output;
    } 
    std::string string_to_print = tokenToPrint.get_token_text() + ':';
    std::vector<size_t> token_number_list = tokenToPrint.get_number_list();
    for(size_t i = 0; i<token_number_list.size(); i++) 
    {
        string_to_print = string_to_print + " " + std::to_string(token_number_list[i]);
    }
    output << string_to_print;
    return output;
}