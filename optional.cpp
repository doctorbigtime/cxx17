#include <optional>
#include <map>
#include <string>

std::optional<std::string> getName(std::string const& arg)
{
    static std::map<std::string, std::string> m = {
        { "foo", "bar" },
        { "baz", "qux" },
    };
    if(auto itr = m.find(arg); itr == m.end())
        return {};
    else return itr->second;
}

#include <iostream>

auto main(int argc, char** argv) -> int
{
    if(auto n = getName("foo"); n)
        std::cout << "foo => " << *n << std::endl;
    else std::cout << "foo not found." << std::endl;
    auto n = getName("qux");
    if(!n.has_value())
        std::cout << "qux not found." << std::endl;
    std::cout << "qux => " << n.value_or("[unknown]") << std::endl;
    return 0;
}

