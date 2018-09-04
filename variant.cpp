#include <variant>
#include <iostream>

#include <iostream>

auto main(int argc, char** argv) -> int
{
    using variant = std::variant<int, double, std::string>;

    auto print_visitor = [](auto const& v) {
        std::cout << v << std::endl;
    };

    variant v = 123;   // contains int
    int i = std::get<int>(v);
    std::visit(print_visitor, v);
    v = 999.99e-9;
    try
    {
        std::string d = std::get<std::string>(v);
    }
    catch(std::bad_variant_access const& e)
    {
        std::cout << "Not a string: " << e.what() << std::endl;
    }
    v = "foobar";
    std::visit([](auto const& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr(std::is_same_v<T, int>)
                std::cout << "int: " << v << std::endl;
            else if constexpr(std::is_same_v<T, double>)
                std::cout << "double: " << v << std::endl;
            else if constexpr(std::is_same_v<T, std::string>)
                std::cout << "std::string: " << v << std::endl;
    }, v);

    struct static_visitor
    {
        void operator()(int i) { std::cout << "sv: int: " << i << std::endl; }
        void operator()(double i) { std::cout << "sv: double: " << i << std::endl; }
        void operator()(std::string i) { std::cout << "sv: std::string: " << i << std::endl; }
    };
    v = 12345;
    std::visit(static_visitor(), v);

    return 0;
}
