
cmake_minimum_required(VERSION 3.20.0)

project(simple-audio-player LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(WIN32 AND MSVC)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(sdl2-image CONFIG REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)
    
    add_executable(${PROJECT_NAME} main.c smp.c animator.c audiomanager.c audioex.c musicbar.c volumebar.c globals.c)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static> 
    )
endif(WIN32 AND MSVC)

if(APPLE)
    add_executable(${PROJECT_NAME} main.c smp.c animator.c audiomanager.c audioex.c musicbar.c volumebar.c globals.c)
    
    target_link_directories(${PROJECT_NAME} PUBLIC /usr/local/lib)
    target_link_libraries(${PROJECT_NAME} -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
endif(APPLE)
