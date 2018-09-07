#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#include <random>
#include <chrono>
#include <thread>

using namespace std::chrono;


template <typename F, typename... Args>
void for_each_arg(F fun, Args&& ... args)
{
    (fun(std::forward<Args>(args)), ...);
}

template <int N, typename ... Vs>
void randomize(Vs& ... vs)
{
    std::mt19937 engine(666);
    std::normal_distribution<> rand;

    for(int i = 0; i < N; ++i) {
        for_each_arg([&](auto& v) { v.emplace_back(rand(engine)); }, vs...);
    }
}

constexpr int N = 1000;
std::vector<double> results;

void naive(std::vector<double> const& m1, std::vector<double> const& m2)
{
    for(auto row = 0; row < N; ++row) {
        for(auto col = 0; col < N; ++col) {
            double& dot = results[row*N + col];
            dot = .0;
            for(auto i = 0; i < N; ++i) {
                dot += m1[row*N + i] * m2[i*N + row];
            }
        }
    }
}

void hand_rolled_threads(std::vector<double> const& m1, std::vector<double> const& m2)
{
    int nthreads = std::thread::hardware_concurrency();

    int rows  = N / nthreads;
    int extra = N % nthreads;
    int start = 0;
    int end   = rows;

    std::vector<std::thread> workers;

    for(int t = 1; t <= nthreads; ++t) {
        if(nthreads == t) end += extra;
        auto loopbody = [&](int start, int end) {
            for(int i = start; i < end; ++i) {
                for(int k = 0; k < N; ++k) {
                    for(int j = 0; j < N; ++j) {
                        results[i*N + j] += (m1[i*N + k] * m2[k*N + i]);
                    }
                }
            }
        };
        workers.push_back(std::thread{loopbody, start, end});
        start = end;
        end   = start + rows;
    }
    for(auto& t : workers)
        t.join();
}


template <typename Fun>
void run_and_time(std::string const& name, Fun fun, std::vector<double> const& m1, std::vector<double> const& m2)
{
    std::cout << "Running \"" << name << "\"" << std::endl;
    auto start = high_resolution_clock::now();
    fun(m1, m2);
    auto end = high_resolution_clock::now();
    std::cout << name << " took " << duration_cast<milliseconds>(end-start).count() << "ms" << std::endl;
}

auto main(int argc, char** argv) -> int
{
    std::vector<double> m1, m2;
    m1.reserve(N*N);
    m2.reserve(N*N);
    results.reserve(N*N);

    randomize<N*N>(m1, m2);

#define X(x) std::pair(#x, x)
    std::vector funs {
        X(naive),
        X(hand_rolled_threads),
    };
#undef X

    for(auto const& f : funs) 
        run_and_time(f.first, f.second, m1, m2);

    return 0;
}
