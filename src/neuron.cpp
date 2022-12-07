#include <string>
#include <iostream> 
#include <filesystem>
#include <vector>
#include <algorithm>

#include "neuron.hpp"
#include "opusutil.hpp"

namespace fs = std::filesystem;

typedef std::unique_ptr<float[]> series_t;
typedef std::unique_ptr<series_t[]> dataframe_t;
/**
 * @brief Loads the PCM sample data of the specified number of training instances from the specified directory
 * 
 * @param data_directory 
 * @param num_instances 
 * 
 * @throws std::filesystem::filesystem_error if an OS error prevents reading from a training file or the directory
 * @return float** 
 */
template<typename... paths>
dataframe_t get_training_samples(const std::size_t num_instances, const paths... dir_paths) {
	dataframe_t samples{std::make_unique<series_t[]>(num_instances)};

	std::vector paths{dir_paths};
	if (std::all_of(
			paths.cbegin(), 
			paths.cend(), 
			[] (fs::path dir_path) {return fs::exists(dir_path) && fs::is_directory(dir_path);})) {
		// iterate over the first `num_instances` training clips in the directory and store their PCM data in the array
		std::vector<fs::directory_iterator> dir_iters;
		dir_iters.capacity(sizeof...(dir_paths));
		for (auto i = 0; i < sizeof...(dir_paths); i++) {
			dir_iters[i] = paths[i].begin();
		}
		for (auto i = 0; i < num_instances; i++) {
			for (auto iter_i = 0; iter_i < paths.length(); iter_i++) {
				samples[(i * paths.length()) + iter_i] = opus::get_samples(entry.path().c_str());
			}
		}
	}
	return samples;
}

bool is_one(unsigned char index) {
	return index >= 300;
}

typedef std::pair<const float**, std::size_t> dataview_t;
typedef std::pair<dataview_t, dataview_t> splitview_t;
typedef 
/// @brief Returns 5 cross validation splits of the dataset 
/// @param dataset 
/// @param dataset_size 
/// @return 
std::vector<splitview_t> get_cross_validation_splits(const dataframe_t datasetB, const std::size_t dataset_size) {
	const auto validation_set_size = static_cast<std::size_t>(dataset_size * 0.20f);
	const auto training_set_size = dataset_size - validation_set_size;
	
	std::vector<splitview_t> cross_validation_splits;
	for (auto i = 0; i < 5; i++) {
		auto validation_set = new float*[validation_set_size];
		const auto validation_set_start_ix = validation_set_size * i;
		for (std::size_t validation_instance_ix = 0; validation_instance_ix < validation_set_size; validation_instance_ix++) {
			// alternate taking the validation instance from dataset A and dataset B every iteration
			validation_set[validation_instance_ix] = dataset[(validation_set_start_ix + validation_instance_ix) % dataset_size].get();
		}
		dataview_t validation_data{static_cast<const float**>(validation_set), validation_set_size};

		auto training_set = new float*[training_set_size];
		const auto training_set_start_ix = validation_set_start_ix + validation_set_size;
		for (std::size_t training_instance_ix = 0; training_instance_ix < training_set_size; training_instance_ix++) {
			// alternate taking the training instance from dataset A and dataset B every iteration
			training_set[training_instance_ix] = dataset[(training_set_start_ix + training_instance_ix) % dataset_size].get();
		}
		dataview_t training_data{static_cast<const float**>(training_set), training_set_size};
		splitview_t cross_validation_split{training_data, validation_data};
		cross_validation_splits.push_back(cross_validation_split);
	}
	return cross_validation_splits;
}

// Note, we are trying to let the neuron learn to predict ones 
int main() {
	srand(time(NULL));

	const std::size_t NUM_SAMPLES = 300;
	const std::size_t NUM_EPOCHS = 10; const fs::path training_data_dir{"/Users/kadeem/Spaces/Projects/neural-net/data/mswc_microset/en/clips/"};
	auto clip_sample_data = get_training_samples(NUM_SAMPLES, training_data_dir/"zero", training_data_dir/"one");

	auto cross_validation_splits = get_cross_validation_splits(clip_sample_data, NUM_SAMPLES);
	for(auto validation_split: cross_validation_splits) {
		auto training_set = validation_split.getLeft();
		auto validaiton_set = validation_split.getRight();

		auto neuron = nn::neuron::UnipolarNeuron<10>();
		for (auto epoch = 0; epoch < NUM_EPOCHS; epoch++) {
			for (dataview_t batch: batch(training_set, 50)) {
				neuron.learn(batch);
			}
		}

		print_evaluation(neuron, validation_set);
	}
}