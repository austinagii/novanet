#include <cstdlib>

#include "randutil.hpp"

float util::randn::get_random_float(const float lower_bound, const float upper_bound) {
    return lower_bound + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

void util::randn::init_random_float(float* values, const std::size_t num_values, 
                                     const float lower_bound, const float upper_bound) {
    for(std::size_t i = 0; i < num_values; i++) {
        values[i] = randn::get_random_float(lower_bound, upper_bound);
    }
}