#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <functional>
#include <exception>
#include <algorithm>
#include <map>

using namespace std;


template <typename... Args>
void print(Args&&... args) {
    (std::cout << ... << args) << std::endl;
}


template <typename T, typename Func>
void for_range(T start, T end, Func action) {
    for (T i = start; i < end; ++i) {
        action(i);
    }
}

template <typename Func>
void benchmark(const std::string& name, Func action) {
    auto start = std::chrono::high_resolution_clock::now();
    action();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "[Timer] " << name << " took: " << elapsed.count() << " ms" << std::endl;
}

template <typename Setup, typename Teardown, typename Action>
void with_resource(Setup setup, Teardown teardown, Action action) {
    setup();
    try {
        action();
    } catch (...) {
        teardown(); 
        throw;
    }
    teardown();
}

template <typename In, typename Out>
auto memoize(Out (*func)(In)) {
    return [func](In input) {
        static std::map<In, Out> cache;
        if (cache.find(input) == cache.end()) {
            cache[input] = func(input);
        }
        return cache[input];
    };
}

template <typename Func>
void secure_run(Func action) {
    try {
        action();
    } catch (const std::exception& e) {
        std::cerr << "Automated Error Capture: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }
}

template <typename T, typename TransformFunc>
auto map_vec(const std::vector<T>& input, TransformFunc func) {
    using ReturnType = decltype(func(std::declval<T>()));
    std::vector<ReturnType> output;
    output.reserve(input.size());

    for (const auto& item : input) {
        output.push_back(func(item));
    }
    return output;
}

enum class Comparison { Equal, NotEqual, Greater, Less };
bool evaluate(int a, int b, Comparison op) {
    switch (op) {
        case Comparison::Equal:    return a == b;
        case Comparison::NotEqual: return a != b;
        case Comparison::Greater:  return a > b;
        case Comparison::Less:     return a < b;
        default:                   return false;
    }
}
