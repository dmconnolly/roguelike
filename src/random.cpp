#include "random.hpp"

pcg32 Random::rng = pcg32(pcg_extras::seed_seq_from<std::random_device>());
std::mutex Random::mutex;
