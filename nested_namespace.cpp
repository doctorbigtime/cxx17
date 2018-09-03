#include <iostream>

#ifdef OLD_AND_BUSTED

namespace thing {
namespace detail {
namespace more_detail {

struct mine {};

} // namespace more_detail
} // namespace detail
} // namespace thing

#else

namespace thing::detail::more_detail {
    struct mine {}; 
} // namespace thing::detail::more_detail

#endif

auto main(int argc, char**argv) -> int
{
    using thing::detail::more_detail::mine;
    std::cout << __cplusplus << std::endl;
    return 0;
}
