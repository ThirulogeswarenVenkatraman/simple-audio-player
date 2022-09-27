
cmake_minimum_required(VERSION 3.1)

project(simple-audio-player LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/deps/includes)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(WIN32 AND MSVC)
    add_executable(${PROJECT_NAME} WIN32_EXECUTABLE main.c smp.c animator.c audiomanager.c audioex.c musicbar.c volumebar.c globals.c)

    target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2main.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_mixer.lib 
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_image.lib
    ${CMAKE_SOURCE_DIR}/deps/libs/SDL2_ttf.lib
    )
endif(WIN32 AND MSVC)

if(APPLE)
    add_executable(${PROJECT_NAME} main.c smp.c animator.c audiomanager.c audioex.c musicbar.c volumebar.c globals.c)
    
    target_link_directories(${PROJECT_NAME} PUBLIC /usr/local/lib)
    target_link_libraries(${PROJECT_NAME} -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
endif(APPLE)

