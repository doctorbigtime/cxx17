#include <string>
#include <functional>
#include <iostream>

void foo(std::string const& s) {
    std::cout << "Goodbye, cruel world: " << s << std::endl;
}

auto main(int argc, char** argv) -> int
{
    auto bar = [](int i, double d) {
        return i + d;
    };

    std::invoke(foo, *argv);
    std::cout << std::invoke(bar, 1, 99.9) << std::endl;

    auto baz = [](double a, double b) {
        return a * b;
    };

    // finally!
    auto args = std::make_tuple(3.14159, 2);
    std::cout << std::apply(baz, args) << std::endl;

    return 0;
}
