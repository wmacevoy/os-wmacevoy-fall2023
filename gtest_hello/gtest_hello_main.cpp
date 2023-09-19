#include <iostream>

#include "gtest_hello.h"

int main(int c, const char *argv[])
{
    std::cout << greet("world") << std::endl;

    return 0;
}
