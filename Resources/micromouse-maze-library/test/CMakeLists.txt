# author: Ryotaro Onuki <kerikun11+github@gmail.com>
# date: 2021.01.03

# find GoogleTest
find_package(GTest)
if(NOT GTEST_FOUND)
  message(WARNING "GoogleTest not found in your environment! skipping...")
  RETURN()
endif()

# find Threads for GoogleTest
find_package(Threads REQUIRED)

# make a target to test
set(TARGET_NAME "test")
file(GLOB SRC_FILES
  ${PROJECT_SOURCE_DIR}/src/*.cpp # rebuild with coverage options
  *.cpp
)
add_executable(${TARGET_NAME} ${SRC_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_options(${TARGET_NAME} PRIVATE -g -O0 -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline)
target_link_libraries(${TARGET_NAME} PRIVATE GTest::GTest Threads::Threads)
target_link_options(${TARGET_NAME} PRIVATE -coverage)
# make a custom target to run
add_custom_target(${TARGET_NAME}_run
  COMMAND ${TARGET_NAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  USES_TERMINAL
)

# make a custom target to run lcov (statement coverage)
set(CUSTOM_TARGET_NAME "lcov")
set(INFO_FILENAME "${CMAKE_PROJECT_NAME}.info")
add_custom_target(${CUSTOM_TARGET_NAME}
  COMMAND lcov --quiet --output ${INFO_FILENAME} --zerocounters --directory ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${TARGET_NAME}
  COMMAND lcov --quiet --output ${INFO_FILENAME} --capture --directory ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND lcov --quiet --output ${INFO_FILENAME} --extract ${INFO_FILENAME} ${PROJECT_SOURCE_DIR}/{include,src}/'*'
  COMMAND lcov --summary ${INFO_FILENAME}
  COMMAND genhtml --quiet ${INFO_FILENAME} --output ${CMAKE_CURRENT_BINARY_DIR}/html
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  USES_TERMINAL
)
add_custom_target(${CUSTOM_TARGET_NAME}_init
  COMMAND lcov --quiet --output ${INFO_FILENAME} --zerocounters --directory ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND lcov --quiet --output ${INFO_FILENAME} --capture --directory ${CMAKE_CURRENT_BINARY_DIR} --initial
  COMMAND lcov --summary ${INFO_FILENAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  USES_TERMINAL
)
add_custom_target(${CUSTOM_TARGET_NAME}_capture
  COMMAND lcov --quiet --output ${INFO_FILENAME} --capture --directory ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND lcov --quiet --output ${INFO_FILENAME} --extract ${INFO_FILENAME} ${PROJECT_SOURCE_DIR}/{include,src}/'*'
  COMMAND lcov --summary ${INFO_FILENAME}
  COMMAND genhtml --quiet ${INFO_FILENAME} --output ${CMAKE_CURRENT_BINARY_DIR}/html
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  USES_TERMINAL
)
