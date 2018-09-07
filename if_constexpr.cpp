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

#if OLD_AND_BUSTED

template <unsigned N>
struct fibonacci
{
    static const unsigned v = fibonacci<n-1>::v + fibonacci<n-2>::v;
};

template <>
struct fibonacci<0>
{
    static const unsigned v = 1;
};

#else

template <unsigned n>
constexpr unsigned fibonacci() {
    if constexpr(n < 2) return 1;
    else return fibonacci<n - 1>() + fibonacci<n - 2>();
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

    static_assert(fibonacci<12>() == 144);

    return 0;
}
