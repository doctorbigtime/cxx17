constexpr int factorial(int n) {
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

auto main(int argc, char**argv) -> int
{
    static_assert(120 == factorial(5));
    return 0;
}

