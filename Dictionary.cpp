#include "Dictionary.h"

// normal constructor
Dictionary::Dictionary(const std::string& filename, const std::string& separators) : filename{filename}, separators{separators}
{
    // create an input file stream 
    std::ifstream fin(filename); 
    if (!fin)
    {
        std::cout << "could not open input file: " << filename << std::endl;
        exit(1);
    }
    size_t line_number = 0;
    std::string line;
    getline(fin, line);
    while (fin)
    {
        // std::cout << line << std::endl;
        ++line_number;
        input_lines.push_back(line);
        extract_and_push(line, line_number);
        getline(fin, line);
    }
    fin.close();
}

// returns the index of the bucket corresponding to tokenText[0]
size_t Dictionary::bucket_index(const std::string& tokenText) const { 
    size_t index = 26; // bucket index for tokens not beginning with a letter
    if (isalpha(tokenText[0]))
    {
        if(isupper(tokenText[0])) index = tokenText[0] - 'A';
        else index = tokenText[0] - 'a';
    }
    return index;
}

// extracts and returns the tokens separated by separators in the specified line
std::vector<std::string> Dictionary::extract_tokens_from_line(const std::string& line) const
{
    std::vector<std::string> words;
    std::string word = "";

    std::string actual_separators = restore_fake_tab_newline_chars(separators);

    for(int i = 0; i<line.length(); i++) 
    {
        char current_char = line.at(i);
        if(actual_separators.find(current_char) == std::string::npos) { word += current_char; }
        else {
            words.push_back(word);
            word = "";
        }
    }
    // add the last word
    words.push_back(word);
    return words;
}

// creates a token with the specified tokenText and line_number and then pushes (inserts)
// the token at the end of the bucket list corresponding to tokenText[0].
void Dictionary::push_back_into_bucket(const std::string& tokenText, size_t line_number)
{
    size_t index = bucket_index(tokenText);
    Token newToken = Token(tokenText, line_number);
    // check if the token already exists
    std::list<Token>::iterator it = token_list_buckets[index].begin();
    for(int i = 0; i<token_list_buckets[index].size(); i++)
    {
        if(newToken.compare(*it) == 0)
        {
            it->push_back_line_number(line_number);
            return;
        }
        it++;
    }
    token_list_buckets[index].push_back(newToken);
}

// using extract_tokens_from_line and push_back_into_bucket, inserts the tokens
// extracted from the specified line and line_number into appropriate buckets
void Dictionary::extract_and_push(const std::string& line, size_t line_number)
{
    std::vector<std::string> words_in_line = extract_tokens_from_line(line);
    for(int i = 0; i<words_in_line.size(); i++) { push_back_into_bucket(words_in_line[i], line_number); }
}

// prints the input lines beginning with the characters stored in char_set
// if char_set is empty, then it prints all input lines
void Dictionary::print_input_lines(std::set<char>& char_set) const
{
    print_operation("INPUT LINES");
    if(char_set.empty())
    {
        for(int i=0; i < input_lines.size(); i++) { std::cout << input_lines[i] << std::endl; }
        return;
    }

    for(int i=0; i < input_lines.size(); i++) 
    {
        for(const char &c : char_set) 
        {
            if(input_lines[i].find(c) == 0) { std::cout << input_lines[i] << std::endl; }
        }
    }
}

void Dictionary::print_input_lines() const
{
    std::set<char> s;  
    print_input_lines(s);
}

void Dictionary::print_bucket(std::string c, std::list<Token> bucket) const
{
    if(!isalpha(c[0])) { c = "<>"; }
    std::cout << "<---- " << c << " ---->" << std::endl;
    std::cout << std::endl;

    for(const Token &t : bucket) { t.print(std::cout); }
    std::cout << std::endl;
}

void Dictionary::print_bucket_fl(std::string c, std::forward_list<Token> bucket) const
{
    if(!isalpha(c[0])) { c = "<>"; }
    std::cout << "<---- " << c << " ---->" << std::endl;
    std::cout << std::endl;

    for(const Token &t : bucket) { t.print(std::cout); }
    std::cout << std::endl;
}

void Dictionary::print_operation(std::string operation) const
{
    std::cout << std::endl;
    std::cout << operation << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;
}

// For each character ch in char-set:
// if ch is a letter, it prints original unsorted bucket corresponding to ch;
// if ch is not a letter, it prints the original unsorted foreign bucket.
void Dictionary::print_input_tokens(std::set<char>& char_set) const
{
    print_operation("INPUT TOKENS");
    if(char_set.empty())
    {
        char c = 'a'; 
        for(int i=0; i < token_list_buckets.size(); i++) 
        {
            std::string s(1, c);
            print_bucket(s, token_list_buckets[i]);
            c++;
        }
        return;
    }

    for(const char &c : char_set) 
    {
        std::string s(1, c);
        size_t index = bucket_index(s);
        if(!token_list_buckets[index].empty()) { print_bucket(s, token_list_buckets[index]); }
    }
}

void Dictionary::print_input_tokens() const
{
    std::set<char> s;  
    print_input_tokens(s);
}

void Dictionary::print_sorted_on_token_text(std::set<char>& char_set) const
{
    print_operation("INPUT TOKENS SORTED ON TEXT");
    if(char_set.empty())
    {
        char c = 'a'; 
        for(int i=0; i < token_list_buckets.size(); i++) 
        {
            std::forward_list<Token> forward_list { std::begin(token_list_buckets[i]), 
                                                    std::end(token_list_buckets[i]) };
            forward_list.sort();
            std::string s(1, c);
            print_bucket_fl(s, forward_list);
            c++;
        }
        return;   
    }

    for(const char &c : char_set) 
    {
        std::string s(1, c);
        size_t index = bucket_index(s);
        if(!token_list_buckets[index].empty())
        {
            std::forward_list<Token> forward_list { std::begin(token_list_buckets[index]), 
                                                    std::end(token_list_buckets[index]) };
            forward_list.sort();
            print_bucket_fl(s, forward_list);
        }
    } 
}

void Dictionary::print_sorted_on_token_text() const
{
    std::set<char> s;  
    print_sorted_on_token_text(s);
}

void Dictionary::print_sorted_on_token_frequency(std::set<char>& char_set) const
{
    print_operation("INPUT TOKENS SORTED ON FREQUENCY");
    if(char_set.empty())
    {
        char c = 'a'; 
        for(int i=0; i < token_list_buckets.size(); i++) 
        {
            std::forward_list<Token> forward_list { std::begin(token_list_buckets[i]), 
                                                    std::end(token_list_buckets[i]) };
            forward_list.sort(isLessFrequent);
            std::string s(1, c);
            print_bucket_fl(s, forward_list);
            c++;
        }
        return;   
    }

    for(const char &c : char_set) 
    {
        std::string s(1, c);
        size_t index = bucket_index(s);
        if(!token_list_buckets[index].empty())
        {
            std::forward_list<Token> forward_list { std::begin(token_list_buckets[index]), 
                                                    std::end(token_list_buckets[index]) };
            forward_list.sort(isLessFrequent);
            print_bucket_fl(s, forward_list);
        }
    } 
}

void Dictionary::print_sorted_on_token_frequency() const
{
    std::set<char> s;  
    print_sorted_on_token_frequency(s);
}

void Dictionary::print_sorted_on_token_length(std::set<char>& char_set) const
{
    print_operation("INPUT TOKENS SORTED ON TOKEN LENGTH");
    if(char_set.empty())
    {
        char c = 'a'; 
        for(int i=0; i < token_list_buckets.size(); i++) 
        {
            std::forward_list<Token> forward_list { std::begin(token_list_buckets[i]), 
                                                    std::end(token_list_buckets[i]) };
            forward_list.sort(isShorter);
            std::string s(1, c);
            print_bucket_fl(s, forward_list);
            c++;
        }
        return;   
    }

    for(const char &c : char_set) 
    {
        std::string s(1, c);
        size_t index = bucket_index(s);
        if(!token_list_buckets[index].empty())
        {
            std::forward_list<Token> forward_list { std::begin(token_list_buckets[index]), 
                                                    std::end(token_list_buckets[index]) };
            forward_list.sort(isShorter);
            print_bucket_fl(s, forward_list);
        }
    } 
}

void Dictionary::print_sorted_on_token_length() const
{
    std::set<char> s;  
    print_sorted_on_token_length(s);
}