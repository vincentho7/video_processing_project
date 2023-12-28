cmake_minimum_required(VERSION 2.8)
project(tvid)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find the SDL2 and SDL2_image packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include the SDL2 and SDL2_image directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

# Include your project directories
include_directories(src src/app)

# Add your source files
add_executable(tvid
    src/main.cpp
    src/app/App.cpp
    src/Image.cpp
    src/app/SDLManager.cpp)

# Link against the SDL2 and SDL2_image libraries
target_link_libraries(tvid ${SDL2_LIBRARIES}  ${SDL2_IMAGE_LIBRARIES})
