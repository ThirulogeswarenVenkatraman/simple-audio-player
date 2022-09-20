
cmake_minimum_required(VERSION 3.1)

project(simple-audio-player LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/deps/includes)

if (MSVC)
    # warning level 4(/W4) and all warnings as errors(/WX)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if(WIN32)
    add_executable(${PROJECT_NAME} main.c smp.c animator.c audiomanager.c audioex.c musicbar.c volumebar.c globals.c)

    target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2main.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_mixer.lib 
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_image.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_ttf.lib
    )
endif(WIN32)


