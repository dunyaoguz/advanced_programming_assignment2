#include <iostream>
#include <vector>
#include <string>
#ifndef TOKEN_H
#define TOKEN_H

class Token 
{ 
    private: 
        std::string text;                       // string representing the text of the token
        size_t frequency;                       // number of occurences of this token
        std::vector<size_t> number_list;        // list of line numbers associated with this token

    public:
        // constructors
        Token() = delete;
        Token(std::string text, size_t line_num);
        Token(const Token& token) = default;
        Token(Token&& token) = default;

        // assignment operators
        Token& operator=(const Token& rhs) = default;
        Token& operator=(Token&& rhs) = default;

        // destructor
        ~Token() = default;

        // getters
        std::string get_token_text() const; 
        std::vector<size_t> get_number_list() const;
        int get_frequency() const;

        // member functions
        size_t length() const;
        int compare(const Token& aToken) const;
        void increment_frequency();
        void push_back_line_number(size_t line_num);
        void print(std::ostream &output) const;
};

// non member functions
bool operator<(const Token& t1, const Token& t2);
bool isShorter(const Token& first, const Token& second);
bool isLessFrequent(const Token& first, const Token& second);
std::ostream &operator<<(std::ostream &output, const Token &tokenToPrint);
#endif