#include "randutil.hpp"

namespace nn {
namespace neuron {
	template<std::size_t NUM_INPUTS> class UnipolarNeuron {
	public:
		/**
		 * @brief Initializes a new neuron
		 * 
		 * Initializes the weights and bias of the neuron to a random float
		 */
		UnipolarNeuron();

		/**
		 * @brief Applies the activation function to the inputs and return the result
		 */
		float eval(const float*) const;

		/**
		 * @brief Returns the neuron's input weights
		 */
		float* get_weights() const;

		/**
		 * @brief Returns the neuron's activation bias 
		 */
		float get_bias() const;

		/**
		 * @brief Returns the activation value required for the neuron to be active
		 */
		float get_threshold() const;

	private:
		// a value between 0 and 1 (inclusive) representing the neuron's base activation value
		float bias;
		// the required activation value for the neuron to be fully activated
		float threshold;
		// a collection of multipliers that determines the sensity of the neuron to its inputs
		float* weights;
	};
}
}

template<std::size_t NUM_INPUTS>
nn::neuron::UnipolarNeuron<NUM_INPUTS>::UnipolarNeuron() {
    // initialize the neuron's bias to a random value between 0 and 1
    bias = util::randn::get_random_float(0.0f, 1.0f);
    // initialize each input weight to a value between 0 and 1
    weights = new float[NUM_INPUTS];
	util::randn::init_random_float(weights, NUM_INPUTS, 0.0f, 1.0f);
}

template<std::size_t NUM_INPUTS>
float nn::neuron::UnipolarNeuron<NUM_INPUTS>::eval(const float* inputs) const {
	auto activation_value = 0.0f;
	for(std::size_t i = 0; i < NUM_INPUTS; i++) {
		activation_value += inputs[i] * weights[i];
	}
	return activation_value > threshold ? 1.0f : 0.0f;
}

template<std::size_t NUM_INPUTS>
float* nn::neuron::UnipolarNeuron<NUM_INPUTS>::get_weights() const {
    return weights;
}

template<std::size_t NUM_INPUTS>
float nn::neuron::UnipolarNeuron<NUM_INPUTS>::get_bias() const {
	return bias;
}