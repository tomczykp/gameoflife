cmake_minimum_required(VERSION 3.21)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(GameOfLife main.cpp
        src/Plain.cpp include/Plain.h
        src/Organism.cpp include/Organism.h
        src/LTexture.cpp include/LTexture.h
        src/Tile.cpp include/Tile.h
        include/global.h src/global.cpp
        src/View.cpp include/View.h)
target_link_libraries(GameOfLife ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
