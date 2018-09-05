#include <cstddef>
#include <iostream>
#include <iomanip>

auto main(int argc, char** argv) -> int
{
    std::byte a{0xf};
    std::byte b{0xff};
    auto i = std::to_integer<int>(b);
    //std::byte c = a | 0xca; FAIL
    //std::byte c = a + 1; FAIL
    std::byte c = a & b;
    auto j = std::to_integer<int>(c);
    std::cout << "0x" << std::hex << j << std::endl;
    return 0;
}
