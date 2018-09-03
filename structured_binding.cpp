#include <iostream>
#include <array>
#include <tuple>

// Look ma no template arguments!
std::pair origin{ 0, 0 };
std::array fibonacci{ 1.0, 2.0, 3.0, 5.0, 8.0 };
std::tuple tup{ 1, 6.66, 'x' };


auto main(int argc, char**argv) -> int
{
    const auto [ x, y ] = origin;
    auto [one, two, three, five, eight ] = fibonacci;
    auto& [a, b, c ] = tup;
    std::get<1>(tup) = 9.99;

    std::cout << "x: " << x << " y: " << y << std::endl;
    std::cout << "one: " << one << " two: " << two
              << " three: " << three << " five: " << five 
              << " eight: " << eight << std::endl;
    std::cout << "a: " << a << " b: " << b << " c: " << c
        << std::endl;
    return 0;
}

