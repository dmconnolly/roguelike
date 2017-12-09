#include <random>
#include <mutex>
#include <cstdint>
#include <algorithm>
#include <type_traits>
#include <optional>

#include "pcg_random.hpp"

class Random {
public:
    template<typename T, typename=typename std::enable_if<std::is_integral<T>::value>::type>
    static T between(const T a, const T b) {
        std::uniform_int_distribution<T> uniform_dist(std::min(a, b), std::max(a, b));
        std::lock_guard<std::mutex> lock(mutex);
        return uniform_dist(rng);
    }

    template<typename T, typename=typename std::enable_if<std::is_integral<T>::value>::type>
    static std::vector<T> between(const T a, const T b, const std::size_t count) {
        std::vector<T> values(count);
        std::uniform_int_distribution<T> uniform_dist(std::min(a, b), std::max(a, b));
        std::lock_guard<std::mutex> lock(mutex);
        for(std::size_t i=count; i--;) {
            values[i] = uniform_dist(rng);
        }
        return values;
    }

    static bool boolean() {
        std::uniform_int_distribution<uint16_t> uniform_dist(0, 1);
        std::lock_guard<std::mutex> lock(mutex);
        return uniform_dist(rng);
    }

    template<typename T, typename=typename std::enable_if<std::is_integral<T>::value>::type>
    static T one_of(T a, T b) {
        std::uniform_int_distribution<uint16_t> uniform_dist(0, 1);
        std::lock_guard<std::mutex> lock(mutex);
        return uniform_dist(rng) ? a : b;
    }

    template<typename T>
    static T& from_vector(std::vector<T> &vec) {
        assert(vec.size() > 0);
        return vec[Random::between(static_cast<std::size_t>(0), vec.size()-1)];
    }

private:
    static pcg32 rng;
    static std::mutex mutex;
};
