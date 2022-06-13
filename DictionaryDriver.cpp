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
    std::string filename = "test/test.txt";
    Dictionary dictionary(filename);

    for(std::list<Token> i : dictionary.token_list_buckets) 
    {
        auto it = i.begin();

        for(Token t: i) 
        {
            std::cout << *it << std::endl;
            it++;
        }
    }

    // std::list<int> listOfInts;
    // for (int i = 0; i < 10; i++)
    //     listOfInts.push_back(i);

    // std::list<int>::iterator it = listOfInts.begin();
    // for (int i: listOfInts) 
    // {
    //     std::cout << *it << std::endl;
    //     it++;
    // }

    return 0; // 0 means success!
}
