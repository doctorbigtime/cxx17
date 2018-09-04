#include <iostream>
#include <any>
#include <string>

struct some_elaborate_type
{
    virtual ~some_elaborate_type() {}
};

struct thing : some_elaborate_type
{    
    virtual ~thing() { std::cout << "~thing" << std::endl; }
};

auto main(int argc, char** argv) -> int
{
    std::any a;
    a = std::string{"foobar"};
    std::string v = std::any_cast<std::string>(a);
    std::cout << a.type().name() << ": " << v << std::endl;

    a = thing();
    try
    {
        v = std::any_cast<std::string>(a);
    }
    catch(std::bad_any_cast const& e)
    {
        std::cout << "Not a string: " << e.what() << std::endl;
    }
    a = 999.999;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << std::endl;

    return 0;
}
