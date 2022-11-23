#include <cstdlib>

namespace util{
namespace randn {
    /**
     * @brief Returns a random float in the specified closed range 
     * 
     * @param lower_bound The lowest desired value for the random float
     * @param upper_bound The highest desired value for the random float
     * @return float 
     */
    float get_random_float(const float lower_bound, const float upper_bound);

    /**
     * @brief Initializes each value in an array to a random number in the specified closed range 
     * 
     * @param values 
     * @param num_values 
     * @param lower_bound 
     * @param upper_bound 
     */
    void init_random_float(float* values, const std::size_t num_values, 
                           const float lower_bound, const float upper_bound);
}
}