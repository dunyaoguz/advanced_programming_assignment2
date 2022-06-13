#include <ostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h"

// constructor
Dictionary::Dictionary(const string& filename) : filename(filename)
{
    // create an input file stream
    std::ifstream fin(filename); 
    if (!fin)
    {
        std::cout << "could not open input file: " << filename << std::endl;
        exit(1);
    }
    int linenum = 0;
    string line;
    getline(fin, line); // very important first attempt to read

    // this first attemot will get the i/o flags initialized
    while (fin)
    {
        // std::cout << line << std::endl;
        ++linenum; // count the line
        std::istringstream sin(line); // turn the line into an input string stream
        string tokenStr;
        while (sin >> tokenStr) // extract token strings
        {
            // std::cout << tokenStr << std::endl;
            processToken(tokenStr, linenum);
        }
        getline(fin, line); // attempt to read the next line, if any
    }
    fin.close();
}

void Dictionary::processToken(const string& token, int linenum)
{
    size_t index = bucketIndex(token);
    this->tokenListBuckets[index].addSorted(token, linenum);
    // char* cstr = (char *) &token;
    // Token newToken = Token(cstr,linenum);
    // this->tokenListBuckets[index].addSorted(newToken);
}

void Dictionary::print(std::ostream& output) const
{
    char c = 'A'; 
    for (const TokenList &t : this->tokenListBuckets)
    { 
        std::cout << "<<<< " << c << " >>>>" << std::endl;
        std::cout << std::endl;
		c++;
        t.print(output);
        std::cout << std::endl;
    }
}

size_t Dictionary::bucketIndex(const string& token) const
{
    size_t index = 26; // bucket index for tokens not beginning with a letter
    if (isalpha(token[0]))
    {
        if(isupper(token[0])) index = token[0] - 'A';
        else index = token[0] - 'a';
    }
    return index;
}