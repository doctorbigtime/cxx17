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
    // binary right fold: ( <pack expr> <op> ... <op> <init> )
    // expands to:
    // ( arg1 + ( arg2 + ( arg3 + <init> ) ) )
    // binary left fold: ( <init> <op> ... <op> <pack expr> )
    // expands to:
    // ( ( ( <init> + arg1 ) + arg2 ) + arg3 )
}

// Also:
template <typename ... Bools>
bool all(Bools... bools)
{
    return ( ... && bools);
    // unary right fold: ( ... <op> <pack expr> )
    // expands to:
    // ( ( arg1 && arg2 ) && arg3 )
    // unary left fold: ( <pack expr> <op> ... )
    // expands to:
    // ( arg1 && ( arg2 && arg3 ) )
}

// Cool:
template <typename F, typename...Args>
void for_each_arg(F fun, Args... args)
{
    // unary right fold over comma operator.
    (fun(args), ...);
    // expands to:
    // ( ( ( fun(arg1) ), fun(arg2) ), fun(arg3) ))
}
#endif


auto main(int argc, char** argv) -> int
{
    assert(sum(1, 2, 3, 4, 5) == 15);
    assert(false == all(true, true, false));
    assert(true == all(true, true));
    assert(true == all()); // for &&, init defaults to "true"

    for_each_arg([](auto arg) { std::cout << arg << std::endl; }, 1, 666.6, 'z');
    return 0;
}
