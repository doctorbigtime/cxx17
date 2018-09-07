#include <iostream>

#if OLD_AND_BUSTED

template <unsigned N>
struct Arg
{
    template <class T, class ...Ts>
    constexpr auto operator()(T t, Ts... ts) const {
        return Arg<N-1>{}(ts...);
    }
};

template <>
struct Arg<0>
{
    template <class T, class ... Ts>
    constexpr auto operator()(T t, Ts...) const {
        return t;
    }
};


#else 

template <unsigned N>
struct Arg
{
    template <typename T, typename ... Ts>
    constexpr auto operator()(T t, Ts... ts) const {
        if constexpr(N > sizeof...(ts)) {
            return;
        } else if constexpr(N > 0) {
            return Arg<N-1>{}(ts...);
        } else {
            return t;
        }
    }
};

#endif

template <unsigned N>
constexpr auto arg = Arg<N>{};

auto main(int argc, char** argv) -> int
{
    static_assert(arg<2>(0, 1, 2, 3, 4, 5) == 2);
    return 0;
}
