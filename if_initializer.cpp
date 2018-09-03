#include <iostream>
#include <mutex>
#include <map>
#include <string>

using namespace std::string_literals;

auto main(int argc, char**argv) -> int
{
    std::mutex mtx;
    //std::map<std::string, int> m = {
    std::map m = {
        std::pair{ "foo"s, 1 },
        std::pair{ "bar"s, 2 },
    };

    if(std::unique_lock l(mtx, std::try_to_lock); l.owns_lock())
        std::cout << "We locked the lock." << std::endl;

    if(auto [it, inserted] = m.insert({"foo", 3}); !inserted)
        std::cout << "foo already existed." << std::endl;
    if(auto [it, inserted] = m.insert({"baz", 3}); !inserted) {
        std::cout << "baz already existed." << std::endl;
    } else {
        // still in scope.
        std::cout << "Inserted: " << it->first << " => " << it->second << std::endl;
    }


    // also works with switch

    return 0;
}
