#if OLD_AND_BUSTED

template <typename T, T v>
struct integral_constant
{
    static constexpr T value = v;
};

using one_c = integral_constant<int, 1>;
using true_c = integral_constant<bool, true>;

#else // NEW_HOTNESS

template <auto v>
struct integral_constant
{
    static constexpr auto value = v;
};

using one_c = integral_constant<1>;
using true_c = integral_constant<true>;

#endif

static_assert(one_c::value == 1, "");
static_assert(true_c::value == true, "");

auto main(int argc, char** argv) -> int
{
    return 0;
}
