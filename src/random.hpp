#include <random>
#include <cstdint>
#include <algorithm>

#include "pcg_random.hpp"

class Random {
public:
    template<typename T>
    static T between(const T a, const T b) {
        std::uniform_int_distribution<T> uniform_dist(std::min(a, b), std::max(a, b));
        return uniform_dist(rng);
    }

    template<typename T>
    static std::vector<T> between(const T a, const T b, const std::size_t count) {
        std::vector<T> values(count);
        std::uniform_int_distribution<T> uniform_dist(std::min(a, b), std::max(a, b));
        for(std::size_t i=count; i--;) {
            values[i] = uniform_dist(rng);
        }
        return values;
    }

private:
    static pcg32 rng;
};
