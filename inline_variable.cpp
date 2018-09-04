#include "inline_variable.hpp"
#include <iostream>

auto main(int argc, char** argv) -> int
{
    std::cout << extern_thing << std::endl;
    return 0;
}
