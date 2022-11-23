#include <string>

#include "neuron.hpp"
#include "opusutil.hpp"
    
int main() {
	srand(time(NULL));

    std::string file_path = "/Users/kadeem/Spaces/Projects/NeuralNetworkFromScratch/data/mswc_microset/en/clips/bed/common_voice_en_17253379.opus";
	std::unique_ptr<float[]> sample_data = opus::get_samples(file_path.c_str());

	auto neuron = nn::neuron::UnipolarNeuron<10>();
    auto activation = neuron.eval(sample_data.get());
}