#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <tuple>
#include <random>
#include <algorithm>
#include <numeric>
#include "/opt/homebrew/opt/libomp/include/omp.h"



// C++ Parallel Reduction using threads
template<typename T>
std::pair<T, std::chrono::nanoseconds>
parallel_sum_std(T* a, size_t N, size_t num_threads) {
    std::atomic<T> sum(0);
    std::vector<std::thread> threads;
    auto start_time = std::chrono::steady_clock::now();

    // Start threads to compute partial sums
    for(size_t i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&sum, a, i, N, num_threads]() {
            T partial_sum = 0;
            for(size_t j = i * N / num_threads; j < (i+1) * N / num_threads; ++j) {
                partial_sum += a[j];
            }
            sum.fetch_add(partial_sum, std::memory_order_relaxed);
        }));
    }

    // Wait for all threads to finish
    for(auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::steady_clock::now();
    return std::make_pair(sum.load(), std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time));
}



// Parallel Reduction using OpenMP without the built-in reduction
template<typename T>
std::pair<T, std::chrono::nanoseconds>
parallel_sum_omp_custom(T* a, size_t N, size_t num_threads) {
    T sum = 0;
    auto start_time = std::chrono::steady_clock::now();

#pragma omp parallel num_threads(num_threads)
    {
        T partial_sum = 0;
#pragma omp for nowait
        for(size_t i = 0; i < N; ++i) {
            partial_sum += a[i];
        }
#pragma omp atomic
        sum += partial_sum;
    }

    auto end_time = std::chrono::steady_clock::now();
    return std::make_pair(sum, std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time));
}



// OpenMP built-in reduction
template<typename T>
std::pair<T, std::chrono::nanoseconds>
parallel_sum_omp_builtin(T* a, size_t N, size_t num_threads) {
    T sum = 0;
    auto start_time = std::chrono::steady_clock::now();

#pragma omp parallel for reduction(+:sum) num_threads(num_threads)
    for(size_t i = 0; i < N; ++i) {
        sum += a[i];
    }

    auto end_time = std::chrono::steady_clock::now();
    return std::make_pair(sum, std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time));
}

// Main function
int main() {
    // Strong Scaling: N = 100000 / 200000 / 300000
    // num_threads = 1 ~ 16
    //Weak Scaling: N = 10000 / 20000 / .....
    //num_threads = 1 / 2 / ....

    size_t N = 160000;
    size_t num_threads = 16;
    std::vector<int> data(N);

    // generate random number vector
    std::generate(data.begin(), data.end(), std::rand);

    // time of parallel_sum_std function
    auto [sum_std, time_std] = parallel_sum_std(data.data(), N, num_threads);
    std::cout  << ", Time = " << time_std.count()<< std::endl;

    // time of parallel_sum_omp_custom function
    auto [sum_omp_custom, time_omp_custom] = parallel_sum_omp_custom(data.data(), N, num_threads);
    std::cout  << ", Time = " << time_omp_custom.count()  << std::endl;

    // time of parallel_sum_omp_builtin function
    auto [sum_omp_builtin, time_omp_builtin] = parallel_sum_omp_builtin(data.data(), N, num_threads);
    std::cout  << ", Time = " << time_omp_builtin.count() << std::endl;

    return 0;
}
