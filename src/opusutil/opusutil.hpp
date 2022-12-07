#include <memory>

#include "opusfile.h"

namespace opus {
    const int SAMPLE_RATE = 48000;

    /**
     * @brief Read 1 seconds worth of PCM data from the specified opus file at an expected sample rate of 48KHz
     */
    std::unique_ptr<float[]> get_samples(OggOpusFile* file);

    /**
     * @brief Read 1 seconds worth of PCM data from the specified opus file at an expected sample rate of 48KHz
     * 
     * @param file_path 
     * @return std::unique_ptr<float[]> 
     */
    std::unique_ptr<float[]> get_samples(const char* file_path);
}