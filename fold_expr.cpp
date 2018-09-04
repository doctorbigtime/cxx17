#include <cassert>
#include <iostream>

#if OLD_AND_BUSTED

auto sum()
{
    return 0;
}

template <typename N>
auto sum(N n)
{
    return n;
}

template <typename N0, typename ... Ns>
auto sum(N0 n0, Ns... ns)
{
    return n0 + sum(ns...);
}

#else

template <typename ... Ns>
auto sum(Ns... ns)
{
    // brackets required.
    return (ns + ... + 0);
}

// Also:
template <typename ... Bools>
bool all(Bools... bools)
{
    return ( ... && bools);
}

template <typename F, typename...Args>
void for_each_arg(F fun, Args&&... args)
{
    // unary right fold over comma operator.
    (fun(std::forward<Args>(args)), ...);
}
#endif


auto main(int argc, char** argv) -> int
{
    assert(sum(1, 2, 3, 4, 5) == 15);
    assert(false == all(true, true, false));
    assert(true == all(true, true));
    assert(true == all());

    for_each_arg([](auto arg) { std::cout << arg << std::endl; }, 1, 666.6, 'z');
    return 0;
}
