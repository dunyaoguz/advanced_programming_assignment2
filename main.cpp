#include <iostream>
#include "Dictionary.h"

int main()
{
    const char *filename = "input_file_A1.txt";

    Dictionary dunyasDictionary{filename};

    dunyasDictionary.print(std::cout);
    std::cout << std::endl;
    return 0;
}

