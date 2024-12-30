# # Set the minimum required version of CMake
# cmake_minimum_required(VERSION 3.12)

# # Define the project
# project(PacmanPython)

# # Find Python3 and Pybind11
# find_package(Python3 COMPONENTS Interpreter Development)
# find_package(pybind11 REQUIRED)

# # Define the source files Might need to add all other files.
# set(SOURCES
#     ui/bindings.cpp
#     ui/display.cpp
#     game/game.cpp
# )

# # Create the shared library (.so or .pyd)


# # Include the necessary directories
# target_include_directories(pacman PRIVATE ${Python3_INCLUDE_DIRS} ${pybind11_INCLUDE_DIRS})

# # Link against Python and Pybind11
# target_link_libraries(pacman PRIVATE ${Python3_LIBRARIES} pybind11::module)

# # Set properties for the module (shared library)
# set_target_properties(pacman PROPERTIES
#     PREFIX ""  # Don't prefix with lib
#     SUFFIX ".so"  # Set the output to .so (use .pyd on Windows)
# )

# CMake version requirement
cmake_minimum_required(VERSION 3.12)

# Define the project
project(PacmanGame)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB SOURCES
    *.cpp
    ui/*.cpp
    ui/ghosts/*.cpp
    ui/ghosts/*.png
    game/*.cpp
)

# Include directories
include_directories(
    /opt/homebrew/Cellar/sfml/2.6.2/include
)

# Find pybind11
find_package(pybind11 REQUIRED)

# Add the Python module
pybind11_add_module(pacman ${SOURCES})

# Link SFML libraries using the keyword signature
target_link_libraries(pacman
    PUBLIC
    /opt/homebrew/Cellar/sfml/2.6.2/lib/libsfml-graphics.dylib
    /opt/homebrew/Cellar/sfml/2.6.2/lib/libsfml-window.dylib
    /opt/homebrew/Cellar/sfml/2.6.2/lib/libsfml-system.dylib
)


add_custom_command(
    TARGET pacman POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/animations
    ${CMAKE_CURRENT_BINARY_DIR}/ui/animations
)