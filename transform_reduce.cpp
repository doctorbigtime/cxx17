#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

auto main(int argc, char** argv) -> int
{
    std::vector<double> v1 {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    std::vector<double> v2 {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};

    auto d = std::transform_reduce(std::execution::seq, v1.begin(), v1.end(), v2.begin()
            , std::plus<>(), std::multiplies<>());

    std::cout << d << std::endl;

    return 0;
}
