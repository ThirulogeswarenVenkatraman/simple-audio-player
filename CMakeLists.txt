
cmake_minimum_required(VERSION 3.1)

project(simple-media-player LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


include_directories(${CMAKE_SOURCE_DIR}/deps/includes)

add_executable(smp main.c smp.c animator.c audiomanager.c globals.c)

if(WIN32)
    message("linking for WINDOWS")
    target_link_libraries(smp 
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2main.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_mixer.lib 
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_image.lib
    )
endif(WIN32)


if(UNIX)
    message("linking for UNIX")
    target_link_libraries(smp 
    /usr/lib/libSDL2main.a
    /usr/lib/libSDL2.so
    /usr/lib/libSDL2_image.so
    /usr/lib/libSDL2_mixer.so
    )
endif(UNIX)

