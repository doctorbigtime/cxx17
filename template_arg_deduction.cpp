#include <iostream>
#include <vector>
#include <cassert>

template <typename Fun>
struct Thing
{
    Thing(Fun fun) : fun(fun) {}
    Thing& operator()(std::string const& from) {
        data = fun(from);
        return *this;
    }
    Fun fun;
    int data;
};

#if OLD_AND_BUSTED
template <typename Fun>
Thing make_thing(Fun fun) { return Thing(fun); }
#endif

template <typename T>
void print_type(T t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T, typename ... Args>
void print_types(T t, Args ... args)
{
    print_type(t);
    if constexpr(sizeof...(args) != 0)
        print_types(args...);

}

template <typename ...Ts>
auto make_vec(Ts... elems) {
    std::vector v{elems...};
    assert(v.size() == sizeof...(elems));
    return v;
}

auto main(int argc, char** argv) -> int
{
    // simple lambda:
    auto from_string = [](std::string const& src) {
                            return std::stoi(src); 
                        };
#if OLD_AND_BUSTED
    auto thing = make_thing(from_string);
#else // NEW_HOTNESS
    auto thing = Thing(from_string);
#endif
    std::cout << thing("666").data << std::endl;

    // confusing:
    std::vector x{1, 2, 3}; // vector<int>
    std::vector y{x, x};    // vector<vector<int>>
    std::vector z{x};       // ??
    print_types(x, y, z);

    // icky error:
    auto a = make_vec(1, 2, 3); // ok
    auto b = make_vec(1);       // ok
    auto c = make_vec(a, b);    // ok
    auto d = make_vec(c);       // FAIL.

    return 0;
}
