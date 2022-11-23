#include <memory>
#include <array>

#include "opusutil.hpp"
#include "opusfile.h"

/**
 * @brief Read 1 seconds worth of PCM data from the specified opus file at an expected sample rate of 48KHz
 */
std::unique_ptr<float[]> get_samples(OggOpusFile* file) {
	static const int expected_sample_rate = 48000;
	// ensure that the current opus file is sampled at the expected rate
	const OpusHead* head = op_head(file, -1);
	assert((*head).input_sample_rate == expected_sample_rate);

	int total_samples_to_read = 1 * expected_sample_rate;
	std::unique_ptr<float[]> samples = std::make_unique<float[]>(total_samples_to_read);
	std::size_t samples_read = 0; 
	std::size_t total_samples_read = 0;
	// read samples from the opus file until the desired number of samples is read or unti
	// there are no more samples to be read
	do {
		// read a variable number of samples from the opus file into the output array starting at
		// the next available index, ensuring that it does overflow
		samples_read = op_read_float(file, 
									 samples.get() + total_samples_read, 
									 total_samples_to_read - total_samples_read, 
									 NULL); 
		total_samples_read += samples_read;
	} while(samples_read > 0 && total_samples_read < total_samples_to_read);

	// ensure that the desired number of samples has been read  
	assert(total_samples_read == total_samples_to_read);
	return samples;
}

/**
 * @brief Read 1 seconds worth of PCM data from the specified opus file at an expected sample rate of 48KHz
 * 
 * @param file_path 
 * @return std::unique_ptr<float[]> 
 */
std::unique_ptr<float[]> opus::get_samples(const char* file_path) {
	int* error = new int;
	OggOpusFile* file = op_open_file(file_path, error);
	// read the PCM data if the file has been opened successfully
	std::unique_ptr<float[]> samples = NULL;
	if (error == 0) {
		samples = opus::get_samples(file);	
		// TODO: investigate if there are any error states where the file may still be open 
		op_free(file);
	}
	// TODO: handle failure to open opus file i.e `error` < 0
	return samples;
}