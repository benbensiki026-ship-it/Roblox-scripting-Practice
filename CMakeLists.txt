cmake_minimum_required(VERSION 3.10)
project(LuauRobloxPractice VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/luau_practice.cpp
    src/app.cpp
)

# Create executable
add_executable(luau_practice ${SOURCES})

# Installation rules
install(TARGETS luau_practice DESTINATION bin)

# Create examples directory in build
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/challenges)
