#include <random>
#include <cstdint>
#include <algorithm>
#include <type_traits>

#include "pcg_random.hpp"

/* TODO: Thread safety? */

class Random {
public:
    template<typename T, typename=typename std::enable_if<std::is_integral<T>::value>::type>
    static T between(const T a, const T b) {
        std::uniform_int_distribution<T> uniform_dist(std::min(a, b), std::max(a, b));
        return uniform_dist(rng);
    }

    template<typename T, typename=typename std::enable_if<std::is_integral<T>::value>::type>
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
