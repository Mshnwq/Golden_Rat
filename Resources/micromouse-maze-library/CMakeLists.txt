## author: Ryotaro Onuki <kerikun11+github@gmail.com>
## date: 2022.04.16
cmake_minimum_required(VERSION 3.13)
project("MicroMouse Maze Library" CXX)

## global build options
set(CMAKE_CXX_STANDARD 14) # enable option -std=c++14
set(CMAKE_CXX_EXTENSIONS OFF) # without compiler extensions like gnu++14

## make a static library
set(MICROMOUSE_MAZE_LIBRARY "maze") # target name
file(GLOB SRC_FILES src/*.cpp)
add_library(${MICROMOUSE_MAZE_LIBRARY} STATIC ${SRC_FILES})
target_include_directories(${MICROMOUSE_MAZE_LIBRARY}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
## c.f. https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#Warning-Options
target_compile_options(${MICROMOUSE_MAZE_LIBRARY} PUBLIC
  -fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/= # make __FILE__ macro relative path
  -fdiagnostics-color=always # colorized output for gcc
  -mno-ms-bitfields # for use of '__attribute__((__packed__))' on MSYS environment
  -Wall # This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.
  -Wextra # This enables some extra warning flags that are not enabled by -Wall.
  -Wundef # Warn if an undefined identifier is evaluated in an #if directive. Such identifiers are replaced with zero.
  -Wcast-align # Warn whenever a pointer is cast such that the required alignment of the target is increased.
  -Wdouble-promotion # Give a warning when a value of type float is implicitly promoted to double.
  -Wfloat-equal # Warn if floating-point values are used in equality comparisons.
  -Wfatal-errors # This option causes the compiler to abort compilation on the first error occurred rather than trying to keep going and printing further error messages.
)

## unit test
add_subdirectory(test)
## examples
add_subdirectory(examples)
## python module
add_subdirectory(pybind11)
## documentation
add_subdirectory(docs)
