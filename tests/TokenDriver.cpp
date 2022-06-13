#include <iostream>
#include <vector>
#include <string>
#include "Token.h"

int main()
{
    std::cout << "Testing an Object of Class Token\n";
    Token t1{"Dunya", 100};
    Token t2{"Anya", 2};
    t2.increment_frequency();
    t1.push_back_line_number(20);
    t1.push_back_line_number(100);
    t1.push_back_line_number(500);

    // std::string s1 = "Long";
    // std::cout << s1.compare("Longer") << std::endl;
    // std::cout << s1.compare("Lon") << std::endl;
    // std::cout << s1.compare("Long") << std::endl;

    std::cout << isShorter(t1, t2) << std::endl;
    std::cout << isLessFrequent(t1, t2) << std::endl;

    std::cout << t1 << std::endl;
    t1.print(std::cout);
    t2.print(std::cout);

    return 0;
}