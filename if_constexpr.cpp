#include <iostream>
#include <type_traits>

#if OLD_AND_BUSTED

template <typename T>
T get_value(T* t) { return *t; }

template <typename T>
T get_value(T t) { return t; }

#else // NEW_HOTNESS
template <typename T>
auto get_value(T t)
{
    if constexpr(std::is_pointer_v<T>)
        return *t;
    else return t;
}

#endif

template <typename T>
void print(T t)
{
    std::cout << get_value(t) << std::endl;
}

auto main(int argc, char** argv) -> int
{
    auto a = 666;
    auto *b = &a;

    print(a); // 666
    print(b); // 666

    return 0;
}
