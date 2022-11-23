include(FetchContent)
FetchContent_Declare(
    Ogg
    GIT_REPOSITORY https://github.com/xiph/ogg.git
)
FetchContent_Declare(
    Opus
    GIT_REPOSITORY https://github.com/xiph/opus.git
)
FetchContent_Declare(
    OpusFile
    GIT_REPOSITORY https://github.com/xiph/opusfile.git
)
FetchContent_MakeAvailable(
    Ogg Opus OpusFile
)

add_library(opusutil opusutil.hpp opusutil.cpp)
target_link_libraries(opusutil PUBLIC OpusFile::opusfile)