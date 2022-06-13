#include "Dictionary.h"

// normal constructor
Dictionary::Dictionary(const std::string& filename, const std::string& separators) : filename(filename), separators(separators)
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
        getline(fin, line);                      // attempt to read the next line, if any
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
    for(int i = 0; i<line.length(); i++) 
    {
        char current_char = line.at(i);
        if(separators.find(current_char) == std::string::npos) 
        {
            word = word + current_char;
        }
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
    for(int i = 0; i<words_in_line.size(); i++) 
    {
        push_back_into_bucket(words_in_line[i], line_number);
    }
}