cmake_minimum_required(VERSION 3.26)
project(Mergen)

set(CMAKE_CXX_STANDARD 20)
find_package(Threads)
include_directories(/usr/local/include/)

add_executable(Mergen
        main.cpp
        global.hpp

        aud/microphone.cpp
        aud/microphone.hpp
        aud/sound_card.cpp
        aud/sound_card.hpp
        aud/speaker.cpp
        aud/speaker.hpp

        vis/bitmap.hpp
        vis/camera.cpp
        vis/camera.hpp
        vis/memory.cpp
        vis/memory.hpp
        vis/segment.hpp
        vis/segmentation.cpp
        vis/segmentation.hpp
        vis/visual_stm.cpp
        vis/visual_stm.hpp
)

target_link_libraries(Mergen ${CMAKE_THREAD_LIBS_INIT})
