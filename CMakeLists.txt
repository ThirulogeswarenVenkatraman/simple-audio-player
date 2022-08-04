
cmake_minimum_required(VERSION 3.1)

project(simple-media-player LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories($ENV{SDL_INCLUDE})

add_executable(smp main.c smp.c animator.c audiomanager.c globals.c)

target_link_libraries(smp 
$ENV{SDL_LIBS}/SDL2main.lib 
$ENV{SDL_LIBS}/SDL2.lib 
$ENV{SDL_LIBS}/SDL2_mixer.lib 
$ENV{SDL_LIBS}/SDL2_image.lib 
)


